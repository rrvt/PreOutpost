// Outpost Addresses


#include "stdafx.h"
#include "Addresses.h"
#include "EditAddrDlg.h"
#include "filesrch.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "OPaddress.h"


Addresses addresses;                            // The Address list and methods


static TCchar* Section   = _T("ADDRESS DEFINITION");
static TCchar* AddrVer   = _T("Version");
static TCchar* AddrName  = _T("ADDRname");
static TCchar* ORGname   = _T("ORGname");
static TCchar* AddrData  = _T("ADDRdata");
static TCchar* RECtype   = _T("RECtype");
static TCchar* PHONEcell = _T("PHONEcell");
static TCchar* PHONEhome = _T("PHONEhome");
static TCchar* PHONEbus  = _T("PHONEbus");
static TCchar* NAMEagy1  = _T("NAMEagy1");
static TCchar* NAMEagy2  = _T("NAMEagy2");
static TCchar* PHONEagy1 = _T("PHONEagy1");
static TCchar* PHONEagy2 = _T("PHONEagy2");
static TCchar* AddrNote  = _T("ADDRnote");
static TCchar* MOREnote  = _T("MOREnote");



void Addresses::load() {
String   adrPath = theApp.addrPath;                          //path + _T("addr.d\\");
FileSrch src;
bool     rslt  = src.findFiles(adrPath, _T("*.addr"));
String   fn;
Addr     addr;

  list.clr();

  while (src.getName(fn)) {
    IniFile ini;  ini.setPath(fn);
    addr.clear();
    ini.readString(Section, AddrName,  addr.virt);
    ini.readString(Section, ORGname,   addr.orgLoc);
    ini.readString(Section, AddrData,  addr.actual);
    ini.readString(Section, PHONEcell, addr.cellPh);
    ini.readString(Section, PHONEhome, addr.homePh);
    ini.readString(Section, PHONEbus,  addr.busPh);
    ini.readString(Section, NAMEagy1,  addr.agency1Name);
    ini.readString(Section, PHONEagy1, addr.agency1Ph);
    ini.readString(Section, NAMEagy2,  addr.agency2Name);
    ini.readString(Section, PHONEagy2, addr.agency2Ph);
    ini.readString(Section, AddrNote,  addr.notes);
    ini.readString(Section, MOREnote,  addr.moreNotes);

    if (!addr.virt.isEmpty()) {addr.getKey();  insert(addr);}
    }
  }



void Addresses::load(Addr& addr) {
Addr* p = find(addr.getKey());

  if (p) {
    if (p->virt       != addr.virt)        {p->virt        = addr.virt;        p->dirty = true;};
    if (p->orgLoc     != addr.orgLoc)      {p->orgLoc      = addr.orgLoc;      p->dirty = true;};
    if (p->actual     != addr.actual)      {p->actual      = addr.actual;      p->dirty = true;};
    if (p->cellPh     != addr.cellPh)      {p->cellPh      = addr.cellPh;      p->dirty = true;};
    if (p->homePh     != addr.homePh)      {p->homePh      = addr.homePh;      p->dirty = true;};
    if (p->busPh      != addr.busPh)       {p->busPh       = addr.busPh;       p->dirty = true;};
    if (p->agency1Name!= addr.agency1Name) {p->agency1Name = addr.agency1Name; p->dirty = true;};
    if (p->agency1Ph  != addr.agency1Ph)   {p->agency1Ph   = addr.agency1Ph;   p->dirty = true;};
    if (p->agency2Name!= addr.agency2Name) {p->agency2Name = addr.agency2Name; p->dirty = true;};
    if (p->agency2Ph  != addr.agency2Ph)   {p->agency2Ph   = addr.agency2Ph;   p->dirty = true;};
    if (p->notes      != addr.notes)       {p->notes       = addr.notes;       p->dirty = true;};
    if (p->moreNotes  != addr.moreNotes)   {p->moreNotes   = addr.moreNotes;   p->dirty = true;};
    return;
    }

  addr.dirty = true; list[list.end()] = addr;
  }


bool Addresses::anyChanges() {
Addr*  addr;

  for (addr = startLoop(); addr; addr = nextAddr()) if (addr->dirty || addr->deleted) return true;

  return false;
  }


void Addresses::saveAll() {
Addr*  addr;

  for (addr = startLoop(); addr; addr = nextAddr()) addr->update();
  }



Addr* Addresses::find(String& key) {

  for (int i = 0; i < list.end(); i++) if (list[i].key == key) return &list[i];

  return 0;
  }


int Addresses::noFound(String& key) {
int i;
int no;

  for (i = 0, no = 0; i < list.end(); i++) if (list[i].key == key) no++;

  return no;
  }



void Addresses::insert(Addr& addr) {
int   i;
Addr* p;

  for (i = 0; i < list.end(); i++) {
    p = &list[i];
    if (p->key == addr.key) {
      if (p->actual != addr.actual) {p->store(addr.actual, true); return;}
      }
    }

  list[i] = addr;
  }




bool Addresses::delAddr(String& s) {
int    pos    = s.find('\t');   if (pos < 0) return false;
String key    = s.substr(0, pos);
String actual = s.substr(pos+1);
int    i;

  for (i = 0; i < list.end(); i++) if (list[i].key == key) {list[i].deleted = true; return true;}

  return false;
  }





void Addr::clear() {
  key.clear(); virt.clear(); orgLoc.clear(); actual.clear();
  cellPh.clear(); homePh.clear(); busPh.clear();
  agency1Name.clear(); agency1Ph.clear(); agency2Name.clear(); agency2Ph.clear();
  notes.clear();  moreNotes.clear();
  dirty = deleted = false;                              // msgNo.clear();
  }



void Addr::edit(TCchar* title, bool newAddr) {
EditAddrDlg ed;

  ed.title         = title;
  ed.path          = theApp.addrPath;
  ed.newAddr       = newAddr;

  ed.name          = virt;
  ed.orgLoc        = orgLoc;
  ed.actual        = actual;
  ed.cellPhone     = cellPh;
  ed.homePhone     = homePh;
  ed.businessPhone = busPh;
  ed.agency1Name   = agency1Name;
  ed.agency1Phone  = agency1Ph;
  ed.agency2Name   = agency2Name;
  ed.agency2Phone  = agency2Ph;
  ed.notes         = notes;
  ed.moreNotes     = moreNotes;

  if (ed.DoModal() == IDOK) {
    virt         = ed.name;
    orgLoc       = ed.orgLoc;
    actual       = ed.actual;
    cellPh       = ed.cellPhone;
    homePh       = ed.homePhone;
    busPh        = ed.businessPhone;
    agency1Name  = ed.agency1Name;
    agency1Ph    = ed.agency1Phone;
    agency2Name  = ed.agency2Name;
    agency2Ph    = ed.agency2Phone;
    notes        = ed.notes;
    moreNotes    = ed.moreNotes;
    key          = getKey();
    }
  }


static int offset = _T('a') - _T('A');

void makeKey(TCchar* name, TCchar* orgLoc, String& key) {
String nm   = name;
String orgL = orgLoc;
int   n;
int   i;
Tchar tch;

  key = orgL.isEmpty() ? name : nm + _T(".") + orgL;   n = key.length();

  for (i = 0; i < n; i++) {
    tch = key[i];

    if (_T('A') <= tch && tch <= _T('Z')) continue;
    if (_T('a') <= tch && tch <= _T('z')) {key[i] = tch - offset; continue;}
    if (_T('0') <= tch && tch <= _T('9')) continue;
    if (tch == _T('_') || tch == _T('.')) continue;

    key[i] = tch == _T(' ') ? _T('_') : _T('.');
    }
  }


void Addr::store(String& act, bool modified) {actual = act; dirty = modified; deleted = false;}


void Addr::update() {
String   upper    = key;
String   fileName;
FileSrch src;
String   fn;

  fileName = key + _T(".addr");

  if (src.findFiles(theApp.addrPath, fileName) && src.getName(fn)) {

    if (deleted) {del(fn); return;}
    if (!dirty)  return;
    }

  if (!deleted) write(fileName);
  }


void Addr::del(String& filePath) {
String msg;

  try {CFile::Remove(filePath);}

  catch (CFileException* pEx)
      {msg.format(_T("File %s cannot be removed\n"), filePath.str()); messageBox(msg);   pEx->Delete();}
  }


void Addr::write(String& fileName) {
IniFile  addrFile;

  addrFile.setPath(theApp.addrPath + fileName);

  addrFile.writeString(Section, AddrVer,   String(_T("3.3.80/2085:173822")));
  addrFile.writeString(Section, AddrName,  virt);
  addrFile.writeString(Section, ORGname,   orgLoc);
  addrFile.writeString(Section, AddrData,  actual);
  addrFile.writeString(Section, AddrNote,  notes);
  addrFile.writeString(Section, PHONEhome, homePh);
  addrFile.writeString(Section, PHONEcell, cellPh);
  addrFile.writeString(Section, PHONEbus,  busPh);
  addrFile.writeString(Section, NAMEagy1,  agency1Name);
  addrFile.writeString(Section, NAMEagy2,  agency2Name);
  addrFile.writeString(Section, PHONEagy1, agency1Ph);
  addrFile.writeString(Section, PHONEagy2, agency2Ph);
  addrFile.writeString(Section, MOREnote,  moreNotes);
  addrFile.writeEnd();

  dirty = false;
  }



void Addr::copy(Addr& src, Addr& dst) {
    dst.key         = src.key;
    dst.virt        = src.virt;
    dst.orgLoc      = src.orgLoc;
    dst.actual      = src.actual;
    dst.cellPh      = src.cellPh;
    dst.homePh      = src.homePh;
    dst.busPh       = src.busPh;
    dst.agency1Name = src.agency1Name;
    dst.agency1Ph   = src.agency1Ph;
    dst.agency2Name = src.agency2Name;
    dst.agency2Ph   = src.agency2Ph;
    dst.notes       = src.notes;
    dst.moreNotes   = src.moreNotes;

    dst.dirty = src.dirty; dst.deleted = src.deleted;             // dst.msgNo = src.msgNo;
    }



#if 0
[ADDRESS DEFINITION]
Version=3.3.65/19222:000142
ADDRname=TESTMSG
ORGname=My Org
ADDRdata=k6rwy@w3xsc
ADDRnote=This is a test
PHONEhome=408 923-4403
PHONEcell=408 799-6463
PHONEbus=
NAMEagy1=
NAMEagy2=
PHONEagy1=
PHONEagy2=
MOREnote=More Notes
[END]
#endif

