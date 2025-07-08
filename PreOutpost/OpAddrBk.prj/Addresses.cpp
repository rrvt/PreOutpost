// Outpost Addresses


#include "pch.h"
#include "Addresses.h"
#include "AddressDlg.h"
#include "CfgFile.h"
#include "FileIO.h"
#include "filename.h"
#include "filesrch.h"
#include "GetPathDlg.h"
#include "IniFileEx.h"
#include "StatusBar.h"


TCchar* AddrExt = _T(".addr");

Addresses addresses;


void  Addresses::newAddr(TCchar* addrPath) {
Addr addr;

  addr.version = curVersion;

  if (!addr.edit(_T("New Address"), true) || addr.virt.isEmpty() || addr.deleted) return;

  addr.path = addrPath + addr.virt + AddrExt;   add(addr);
  }


void Addresses::edit(TCchar* key) {
Addr*  p      = find(key);        if (!p) return;
String oldKey = p->virt;
Addr   addr;
String path;
String ext;

  addr = *p;   addr.edit(_T("Edit Address"));    addr.version = curVersion;   addresses.add(addr);

  if (addr.deleted) return;

  p = addresses.find(oldKey);

  if (p->virt != addr.virt)
      {p->deleted = true;    path = getPath(addr.path);    addr.path = path + addr.virt + AddrExt;}
  }


void Addresses::load(TCchar* adrPath) {
FileSrch src;
String   path;

  clear();   src.findFiles(adrPath, _T("*.addr"));

  while (src.getName(path)) {
    Addr addr;   addr.read(path);

    if (!addr.virt.isEmpty()) {addr.fixVirt(); insert(addr);}
    if (addr.mainName.isEmpty() && !addr.version.isEmpty() && curVersion.isEmpty())
                                                                         curVersion = addr.version;
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

  data = addr;
  }



void Addresses::add(Addr& addr) {
Addr* p = find(addr.virt);   if (addr.virt.isEmpty()) return;

  if (!p) {addr.dirty = true; data = addr;   return;}

  if (p->virt         != addr.virt)        {p->virt        = addr.virt;          p->dirty = true;}
  if (p->organization != addr.organization)
                                          {p->organization = addr.organization;  p->dirty = true;}
  if (p->actual       != addr.actual)      {p->actual      = addr.actual;        p->dirty = true;}
  if (p->cellPh       != addr.cellPh)      {p->cellPh      = addr.cellPh;        p->dirty = true;}
  if (p->homePh       != addr.homePh)      {p->homePh      = addr.homePh;        p->dirty = true;}
  if (p->busPh        != addr.busPh)       {p->busPh       = addr.busPh;         p->dirty = true;}
  if (p->agency1Name  != addr.agency1Name) {p->agency1Name = addr.agency1Name;   p->dirty = true;}
  if (p->agency1Ph    != addr.agency1Ph)   {p->agency1Ph   = addr.agency1Ph;     p->dirty = true;}
  if (p->agency2Name  != addr.agency2Name) {p->agency2Name = addr.agency2Name;   p->dirty = true;}
  if (p->agency2Ph    != addr.agency2Ph)   {p->agency2Ph   = addr.agency2Ph;     p->dirty = true;}
  if (p->notes        != addr.notes)       {p->notes       = addr.notes;         p->dirty = true;}
  if (p->moreNotes    != addr.moreNotes)   {p->moreNotes   = addr.moreNotes;     p->dirty = true;}
  if (addr.deleted)                        {p->deleted     = addr.deleted;       p->dirty = true;}
  }


bool Addresses::anyChanges() {
AddrIter iter(*this);
Addr*    addr;

  for (addr = iter(); addr; addr = iter++) if (addr->dirty || addr->deleted) return true;

  return false;
  }


void Addresses::saveAll(TCchar* addrPath, StatusBar& statusBar) {
AddrIter iter(*this);
Addr*    addr;

  if (!anyChanges()) {statusBar.setText(_T("No changes"));  return;}

  statusBar.setText(_T("Updating Files"));

  for (addr = iter(); addr; addr = iter++)
                                        {addr->update(addrPath); if (addr->deleted) iter.remove();}
  statusBar.setText(_T("Updating Files Completed"));
  }


void Addr::update(TCchar* addrPath) {
String   fileName = virt     + AddrExt;
String   newPath  = addrPath + fileName;
String   oldPath  = path;
FileSrch srch;

  if (srch.findFiles(addrPath, fileName) && srch.getName(newPath)) {

    if (deleted) {removeFile(newPath); return;}

    if (!dirty)  return;
    }

  if (oldPath != newPath) {removeFile(oldPath);  path = newPath;}

  if (!deleted) write();   dirty = false;
  }


#if 0
Addr* Addresses::find(TCchar* name) {
AddrIter iter(*this);
Addr*    p;

  for (p = iter(); p; p = iter++) if (p->virt == name) return p;

  return 0;
  }
#endif

void Addr::clear() {
  path.clear();        version.clear();   virt.clear();        organization.clear();
  actual.clear();      cellPh.clear();    homePh.clear();      busPh.clear();
  agency1Name.clear(); agency1Ph.clear(); agency2Name.clear(); agency2Ph.clear();
  notes.clear();       moreNotes.clear(); dirty = deleted = false;
  }


void Addr::fixVirt() {
String mainName = getMainName(path);    mainName.upperCase();

  if (mainName != virt) {virt = mainName; dirty = true;}
  }


bool Addr::edit(TCchar* title, bool isNewAddr) {
AddressDlg ed;

  ed.title         = title;
  ed.path          = path;
  ed.isNewAddr     = isNewAddr;
  ed.isDeleted     = deleted;

  ed.version       = version;
  ed.name          = virt;
  ed.organization  = organization;
  ed.actual        = actual;
  ed.homePhone     = homePh;
  ed.cellPhone     = cellPh;
  ed.businessPhone = busPh;
  ed.agency1Name   = agency1Name;
  ed.agency1Phone  = agency1Ph;
  ed.agency2Name   = agency2Name;
  ed.agency2Phone  = agency2Ph;
  ed.notes         = notes;
  ed.moreNotes     = moreNotes;

  if (ed.DoModal() != IDOK) return false;

  virt         = ed.name;
  organization = ed.organization;
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

  deleted      = ed.isDeleted;
  return true;
  }


void Addr::store(String& act, bool modified) {actual = act; dirty = modified; deleted = false;}


void Addr::copy(Addr& a) {
    path         = a.path;
    mainName     = a.mainName;

    version      = a.version;
    virt         = a.virt;
    organization = a.organization;
    actual       = a.actual;
    notes        = a.notes;
    homePh       = a.homePh;
    cellPh       = a.cellPh;
    busPh        = a.busPh;
    agency1Name  = a.agency1Name;
    agency1Ph    = a.agency1Ph;
    agency2Name  = a.agency2Name;
    agency2Ph    = a.agency2Ph;
    moreNotes    = a.moreNotes;

    dirty        = a.dirty;
    deleted      = a.deleted;
    }


static TCchar* Section   = _T("ADDRESS DEFINITION");
static TCchar* AddrVer   = _T("Version");
static TCchar* AddrName  = _T("ADDRname");
static TCchar* ORGname   = _T("ORGname");
static TCchar* AddrData  = _T("ADDRdata");
static TCchar* AddrNote  = _T("ADDRnote");
static TCchar* RECtype   = _T("RECtype");           // Not in ver 3.3.80/2085:173822
static TCchar* PHONEhome = _T("PHONEhome");
static TCchar* PHONEcell = _T("PHONEcell");
static TCchar* PHONEbus  = _T("PHONEbus");
static TCchar* NAMEagy1  = _T("NAMEagy1");
static TCchar* NAMEagy2  = _T("NAMEagy2");
static TCchar* PHONEagy1 = _T("PHONEagy1");
static TCchar* PHONEagy2 = _T("PHONEagy2");
static TCchar* MOREnote  = _T("MOREnote");


void Addr::read(TCchar* path) {
CfgFile ini;

  ini.setPath(path);   this->path = path;   mainName = getMainName(path);

  ini.readString(Section, AddrVer,   version);
  ini.readString(Section, AddrName,  virt);
  ini.readString(Section, ORGname,   organization);
  ini.readString(Section, AddrData,  actual);
  ini.readString(Section, AddrNote,  notes);
  ini.readString(Section, PHONEhome, homePh);
  ini.readString(Section, PHONEcell, cellPh);
  ini.readString(Section, PHONEbus,  busPh);
  ini.readString(Section, NAMEagy1,  agency1Name);
  ini.readString(Section, PHONEagy1, agency1Ph);
  ini.readString(Section, NAMEagy2,  agency2Name);
  ini.readString(Section, PHONEagy2, agency2Ph);
  ini.readString(Section, MOREnote,  moreNotes);
  }


void Addr::write() {
CfgFile  addrFile;

  addrFile.setPath(path);

  addrFile.writeString(Section, AddrVer,   version);
  addrFile.writeString(Section, AddrName,  virt);
  addrFile.writeString(Section, ORGname,   organization);
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

  addrFile.deleteSection(_T("End"));   addrFile.deleteSection(_T("End"));   addrFile.writeEnd();
  dirty = false;
  }


void Addresses::saveData(StatusBar& statusBar) {
PathDlgDsc dsc(_T("Current Addresses"), _T("Addresses"), _T("txt"), _T("*.txt"));
String     path;
FileIO     file;
AddrIter   iter(*this);
Addr*      addr;
int        virtLng;

  statusBar.setText(_T("Save Displayed Addresses"));

  if (!getSaveAsPathDlg(dsc, path) || !file.open(path, FileIO::Write | FileIO::Create))
                                                          {statusBar.setText(_T("Ready")); return;}
  for (virtLng = 0, addr = iter(); addr; addr = iter++)
                               {int lng = addr->virt.length();   if (lng > virtLng) virtLng = lng;}

  for (addr = iter(); addr; addr = iter++) addr->output(file, virtLng + 3);

  statusBar.setText(_T("Save Displayed Addresses Completed"));
  }


void Addr::output(FileIO& file, int brk) {
int tab = brk - virt.length();

  file.write(virt);     for (int i = 0; i < tab; i++) file.write(_T(' '));
  file.write(actual);   file.crlf();
  }



