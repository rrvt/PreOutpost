// Log File Operations


#include "pch.h"
#include "LogFile.h"
#include "Addresses.h"
#include "filesrch.h"
#include "Outpost.h"
#include "RegExpr.h"


static RegExpr re[] = {_T("^~$"),                     // Nil
                       _T("Outpost/Opsessn"),         // Modem
                       _T("^\\[JNOS-"),               // JNOS
                       _T("^SP"),                     // Transmit Message single address
                       _T("^SC"),                     // Transmit Message multiple address
                       _T("^SP "),                    // Raw Send Address
                       _T("^SC"),                     // Raw Send List
                       _T("^/EX"),                    // Exit Transmit
                                                      //
                       _T("^#T: form"),               // Form Follows
                       _T("^!SCCoPIFO!"),             // New Forms

                       _T("^R "),                     // Receive Message
                       _T("^To:"),                    // To
                       _T("^7a\\.:"),                 // To Virtual Addr  all but 213
                       _T("^7b\\.:"),                 // To Virtual Location  all but 213
                       _T("^7\\.:"),                  // To Virtual Addr for 213
                       _T("^9a\\.:"),                 // To virtual Location for 213

                       _T("^From:"),                  // From
                       _T("^8a\\.:"),                 // From Virtual Address all but 213
                       _T("^8b\\.:"),                 // From Virtual Location all but 213
                       _T("^8\\.:"),                  // From in ICS 213
                       _T("^9b\\.:"),                 // Loc in ICS 213

                       _T("^Subject:"),               // Subject followed by a blank line the body
                       _T("^(#[0-9]*) >$"),           // End Receive Msg

                       _T("^MsgNo:"),
                       _T("^!/ADDON!"),               // End Form
                       _T("^B$")                      // Bye
                       };



LogFile::LogFile() : curTime(0) { }


bool LogFile::open() {
CTime  tm = CTime::GetCurrentTime();;
bool   rslt;
String name;

  if (tm == curTime) return fileIO.reOpen();

  if (!find(name)) return false;

  if (rslt = fileIO.open(name, FileIO::Read)) {curTime = tm; return rslt;}

  return false;
  }


bool LogFile::find(String& name) {
CTime    tm;
FileSrch fs;
CString  today;
String   target;
String   path(outpost.getProfile() + _T("logs\\"));

  tm = CTime::GetCurrentTime();

  if (tm == curTime) return true;

  today = tm.Format(_T("%y%m%d"));

  target  = _T("transaction") + tm.Format(_T("%y%m%d")) + _T(".log");

  return fs.findFiles(path, target) && fs.getName(name);
  }


void LogFile::process() {
int i;

  if (!fileIO.isOpen()) return;

  state = ModemSt;

  while (fileIO.read(line)) {

    for (i = 0; i < noElements(re); i++) if (re[i].match(line)) break;

    code = i < noElements(re) ? (Code) i : Nil;

    switch (state) {
      case ModemSt    : if (code == Jnos) state = JNOSSt; break;
      case JNOSSt     : doJNOS();     break;
      case ReceiveSt  : doReceive();  break;
      case TransmitSt : doTransmit(); break;
      case RawSt      : doRawMsg();   break;
      case Not213St   : doNot213();   break;
      case ICS213St   : doICS213();   break;
      }
    }
  }


void LogFile::clear()
    {to.clear(); from.clear(); subject.clear(); virtAddr.clear(); virtLoc.clear(); rcvCnt = -9999;}


void LogFile::doJNOS() {
  switch (code) {
    case SP  :
    case SC  : state = TransmitSt; break;
    case Rcv : state = ReceiveSt; clear(); break;
    case Bye : state = ModemSt; break;
    default  : break;
    }
  }


static RegExpr reICS213(_T("ics213.html"));


void LogFile::doReceive() {
String formType;

  switch (code) {
    case From   : from = get(); break; ;
    case To     : to = get(); break;
    case Subject: subject = get(); rcvCnt = 0; break;
    case Nil    : if (rcvCnt++ >= 1) state = RawSt; break;
    case PIFO   : rcvCnt = -9999; break;
    case Form   : formType = get(); state = reICS213.match(formType) ? ICS213St : Not213St; break;
    case EndRcv : state = JNOSSt; break;
    case Bye    : state = ModemSt; break;
    default: break;
    }
  }


void LogFile::doTransmit() {
  switch (code) {
    case EndForm: state = JNOSSt;  break;
    case EX     : state = JNOSSt; break;
    case Bye    : state = ModemSt; break;
    default     : break;
    }
  }


void LogFile::doRawMsg() {
  switch (code) {
    case EndRcv : state = JNOSSt;  break;
    case Bye    : state = ModemSt; break;
    default     : break;
    }
  }


void LogFile::doNot213() {
  switch (code) {
    case FVaddr : virtAddr = getBrktd(); break;
    case FVloc  : virtLoc  = getBrktd(); install(); break;
    case EndForm: state = JNOSSt;  break;
    case Bye    : state = ModemSt; break;
    default     : break;
    }
  }


void LogFile::doICS213() {
  switch (code) {
    case FVaddr3: virtAddr = getBrktd(); break;
    case FVloc3 : virtLoc  = getBrktd(); install(); break;
    case EndForm: state = JNOSSt;  break;
    case Bye    : state = ModemSt; break;
    default     : break;
    }
  }


void LogFile::install() {
Tchar  ch = _T('A') - 1;
String s = virtAddr;
Addr   addr;

  virtAddr.upperCase();

  for (s = virtAddr; addresses.find(s); s = virtAddr + ch) if (++ch > _T('Z')) return;

  sanitize(s);

  addr.virt         = s;
  addr.organization = virtLoc;
  addr.actual       = from;
  addr.notes        = subject;
  addresses.add(addr);
  }


void LogFile::sanitize(String& name) {
int n = name.length();
int i;

  for (i = 0; i < n; i++) {
    Tchar& ch = name[i];
    if (_T('A') <= ch && ch <= _T('Z')) continue;
    if (_T('0') <= ch && ch <= _T('9')) continue;
    if (ch == _T('.') || ch == _T('_')) continue;
    ch = ch == _T('-') ? _T('_') : _T('.');
    }
  }


String LogFile::getBrktd() {
int beg = line.find('[') + 1;
int end = line.find(']') - beg;

  return beg >= 0 && end >= 0 ? line.substr(beg, end) : String(_T(""));
  }


String LogFile::get()
       {int pos = line.find(_T(' '));  return pos >= 0 ? line.substr(pos).trim() : String(_T(""));}

