// Log File Operations


#include "stdafx.h"
#include "LogFile.h"
#include "filesrch.h"
#include "match.h"
#include "OPaddress.h"
#include "ProgramFiles.h"


LogFile::LogFile() : curTime(0), path(outputPaths.profilePath + _T("logs\\")) {}


bool LogFile::open() {
CTime tm = CTime::GetCurrentTime();;
bool  rslt;

  if (tm == curTime) return fileIO.reOpen();

  if (!find()) return false;

  if (rslt = fileIO.open(name, FileIO::Read)) {curTime = tm; return rslt;}

  return false;
  }




bool LogFile::find() {
CTime    tm;
FileSrch fs;
CString  today;

  tm = CTime::GetCurrentTime();

  if (tm == curTime) return true;

  today = tm.Format(_T("%y%m%d"));

  target  = _T("transaction") + tm.Format(_T("%y%m%d")) + _T(".log");

  return fs.findFiles(path, target) && fs.getName(name);
  }






void LogFile::process() {

  if (!fileIO.isOpen()) return;

  state = Modem;

  while (fileIO.read(line)) {

    code = getCode();

    switch (state) {
      case Modem: processModem(); break;
      case JNOS : processJNOS(); break;
      }
    }
  }


void LogFile::processModem() {
  if (code == Jnos) state = JNOS;
  }


void LogFile::processJNOS() {
String s;
int    lng;
int    pos;

  switch (code) {
    case Modm   : state = Modem; break;
    case SC     : addr.clear(); getData(addr.actual, 3);

                  fileIO.read(s);

                  pos = s.find(',');   if (pos >= 0) s[pos] = ';';

                  lng = s.length();    if (lng > 1) addr.actual +=  _T("; ") + s.substr(0, lng-1);

                  isForm = false; direction = SndDir; break;

    case SP      : addr.clear(); getData(addr.actual, 3); isForm = false; direction = SndDir; break;

//    case MsgNo  : getData(addr.msgNo);                                break;

    case Virt   : if (direction == SndDir) getData(addr.virt);        break;

    case VLoc   : if (direction == SndDir) getData(addr.orgLoc);        break;

    case Rcv    : addr.clear(); isForm = false; direction = RcvDir;   break;

    case From   : if (direction == RcvDir) getData(addr.actual, 6);   break;

    case FromV  : if (direction == RcvDir) getData(addr.virt);        break;

    case FLocV  : if (direction == RcvDir) getData(addr.orgLoc);        break;

    case Form   : isForm = true; break;

    case EndForm: if (isForm) {addresses.load(addr); isForm = false; addr.clear();}   break;

    case Bye    : state = Modem; break;
    }
  }


bool LogFile::getData(String& s) {
int beg = line.find('[') + 1;          if (beg < 0) return false;
int end = line.find(']') - beg;

  s = line.substr(beg, end);   return true;
  }


bool LogFile::getData(String& s, int pos) {
int lng = line.length();

  if (lng < pos) return false;

  s = line.substr(pos, lng - pos - 1);   return true;
  }



// Commands and other patterns

static RegExpr reJnos(   _T("^\\[JNOS-"));
static RegExpr reSC(     _T("^SC "));
static RegExpr reSP(     _T("^SP "));
static RegExpr reVirt(   _T("^7a\\.:"));                // To:
static RegExpr reVLoc(   _T("^7b.: "));                 // Loc:
static RegExpr reRcv(    _T("^R "));
static RegExpr reFrom(   _T("^From: "));
static RegExpr reFromV(  _T("^8a.: "));                 // From:
static RegExpr reFLocV(  _T("^8b.: "));                 // Loc:
static RegExpr reModem(  _T("Outpost/Opsessn"));
static RegExpr reMsgNo(  _T("^MsgNo: "));
static RegExpr reForm(   _T("^#T: form"));
static RegExpr reEndForm(_T("^!/ADDON!"));



LogFile::Code LogFile::getCode() {

  if (reSC.match(line))      return SC;
  if (reSP.match(line))      return SP;
  if (reRcv.match(line))     return Rcv;
  if (reFrom.match(line))    return From;
  if (reFromV.match(line))   return FromV;
  if (reFLocV.match(line))   return FLocV;
  if (reVirt.match(line))    return Virt;
  if (reVLoc.match(line))    return VLoc;
  if (reModem.match(line))   return Modm;
  if (reMsgNo.match(line))   return MsgNo;
  if (reForm.match(line))    return Form;
  if (reEndForm.match(line)) return EndForm;
  if (reJnos.match(line))    return Jnos;
  if (line == _T("B\n"))         return Bye;
  return Nil;
  }

