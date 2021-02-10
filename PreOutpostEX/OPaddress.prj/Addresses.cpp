// Outpost Addresses


#include "stdafx.h"
#include "Addresses.h"
#include "EditAddrDlg.h"
#include "filename.h"
#include "filesrch.h"
#include "IniFile.h"
#include "OPaddress.h"


TCchar* AddrExt = _T(".addr");

Addresses addresses;



void Addresses::load() {
String   adrPath = theApp.addrPath;                          //path + _T("addr.d\\");
FileSrch src;
String   path;

  addrs.clear();   src.findFiles(adrPath, _T("*.addr"));

  while (src.getName(path)) {
    Addr addr;   addr.read(path);

    if (!addr.virt.isEmpty()) {addr.fixVirt(); insert(addr);}
    }
  }


void Addresses::insert(Addr& addr) {
AddrIter iter(*this);
Addr*    p;

  for (p = iter(); p; p = iter++) {

    if (p->virt == addr.virt) {
      if (p->actual != addr.actual) {p->store(addr.actual, true); return;}
      }
    }

  addrs += addr;
  }



void Addresses::load(Addr& addr) {
Addr* p = find(addr.virt);   if (addr.virt.isEmpty()) return;

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

  addr.dirty = true; addrs += addr;
  }


bool Addresses::anyChanges() {
AddrIter iter(*this);
Addr*    addr;

  for (addr = iter(); addr; addr = iter++) if (addr->dirty || addr->deleted) return true;

  return false;
  }


void Addresses::saveAll() {
AddrIter iter(*this);
Addr*    addr;
//int      i;

  for (addr = iter(); addr; addr = iter++) {addr->update(); if (addr->deleted) iter.remove();}
  }


void Addr::update() {
String   fileName = virt + AddrExt;
String   newPath  = theApp.addrPath + fileName;
String   oldPath  = path;
FileSrch srch;

  if (srch.findFiles(theApp.addrPath, fileName) && srch.getName(newPath)) {

    if (deleted) {removeFile(newPath); return;}

    if (!dirty)  return;
    }

  if (oldPath != newPath) {removeFile(oldPath);  path = newPath;}

  if (!deleted) write();   dirty = false;
  }



Addr* Addresses::find(String& name) {
AddrIter iter(*this);
Addr*    p;

  for (p = iter(); p; p = iter++) if (p->virt == name) return p;

  return 0;
  }


void Addr::clear() {
  path.clear();        version.clear();   virt.clear();        orgLoc.clear();     actual.clear();
  cellPh.clear();      homePh.clear();    busPh.clear();
  agency1Name.clear(); agency1Ph.clear(); agency2Name.clear(); agency2Ph.clear();
  notes.clear();       moreNotes.clear(); dirty = deleted = false;
  }


void Addr::fixVirt() {
String mainName = getMainName(path);    mainName.upperCase();

  if (mainName != virt) {virt = mainName; dirty = true;}
  }


bool Addr::edit(TCchar* title, bool newAddr) {
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

  if (ed.DoModal() != IDOK) return false;

  virt         = ed.name;
  if (newAddr) path = theApp.addrPath + virt + AddrExt;
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
  return true;
  }




void Addr::store(String& act, bool modified) {actual = act; dirty = modified; deleted = false;}



void Addr::copy(Addr& a) {
    path        = a.path;
    version     = a.version;
    virt        = a.virt;
    orgLoc      = a.orgLoc;
    actual      = a.actual;
    cellPh      = a.cellPh;
    homePh      = a.homePh;
    busPh       = a.busPh;
    agency1Name = a.agency1Name;
    agency1Ph   = a.agency1Ph;
    agency2Name = a.agency2Name;
    agency2Ph   = a.agency2Ph;
    notes       = a.notes;
    moreNotes   = a.moreNotes;
    dirty       = a.dirty;
    deleted     = a.deleted;
    }




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


void Addr::read(TCchar*  path) {
IniFile ini;

  ini.setPath(path);   this->path = path;

  ini.readString(Section, AddrVer,   version);
  ini.readString(Section, AddrName,  virt);
  ini.readString(Section, ORGname,   orgLoc);
  ini.readString(Section, AddrData,  actual);
  ini.readString(Section, PHONEcell, cellPh);
  ini.readString(Section, PHONEhome, homePh);
  ini.readString(Section, PHONEbus,  busPh);
  ini.readString(Section, NAMEagy1,  agency1Name);
  ini.readString(Section, PHONEagy1, agency1Ph);
  ini.readString(Section, NAMEagy2,  agency2Name);
  ini.readString(Section, PHONEagy2, agency2Ph);
  ini.readString(Section, AddrNote,  notes);
  ini.readString(Section, MOREnote,  moreNotes);
  }


void Addr::write() {
IniFile  addrFile;

  addrFile.setPath(path);

  addrFile.writeString(Section, AddrVer,   version);
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


#if 0
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
#endif

