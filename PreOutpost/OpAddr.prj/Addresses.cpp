// Outpost Addresses


#include "pch.h"
#include "Addresses.h"
#include "AddressDlg.h"
#include "DeleteDlg.h"
#include "filename.h"
#include "filesrch.h"
#include "IniFile.h"

//#include "MessageBox.h"

TCchar* AddrExt = _T(".addr");

Addresses addresses;


void  Addresses::newAddr(TCchar* addrPath) {
Addr addr;

  addr.version = curVersion;

  if (!addr.edit(_T("New Address"), true) || addr.virt.isEmpty()) return;

  addr.path = addrPath + addr.virt + AddrExt;   load(addr);
  }


void Addresses::edit(TCchar* key) {
Addr*  p = find(key);        if (!p) return;
String oldKey = p->virt;
Addr   addr;
String path;
String ext;

  addr = *p;     addr.edit(_T("Edit Address"));    addr.version = curVersion;   addresses.load(addr);

  p = addresses.find(oldKey);

  if (p->virt != addr.virt)
            {p->deleted = true;    path = getPath(addr.path);    addr.path = path + addr.virt + AddrExt;}
  }


bool Addresses::delAddr(TCchar* key) {
Addr*     addr = find(key);     if (!addr) return false;
DeleteDlg dlg;

  dlg.delAddr = addr->virt + _T("   ") + addr->actual;

  if (dlg.DoModal() != IDOK) return false;

  addr->deleted = true; return true;
  }


void Addresses::load(TCchar* adrPath) {
FileSrch src;
String   path;

  addrs.clear();   src.findFiles(adrPath, _T("*.addr"));

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


void Addresses::saveAll(TCchar* addrPath) {
AddrIter iter(*this);
Addr*    addr;

  for (addr = iter(); addr; addr = iter++) {addr->update(addrPath); if (addr->deleted) iter.remove();}
  }


void Addr::update(TCchar* addrPath) {
String   fileName = virt + AddrExt;
String   newPath  = addrPath + fileName;      //theApp.addrPath
String   oldPath  = path;
FileSrch srch;

  if (srch.findFiles(addrPath, fileName) && srch.getName(newPath)) {

    if (deleted) {removeFile(newPath); return;}

    if (!dirty)  return;
    }

  if (oldPath != newPath) {removeFile(oldPath);  path = newPath;}

  if (!deleted) write();   dirty = false;
  }



Addr* Addresses::find(TCchar* name) {
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


bool Addr::edit(TCchar* title, bool isNewAddr) {
AddressDlg ed;

  ed.title         = title;
  ed.path          = _T("Ugly");
  ed.isNewAddr     = isNewAddr;

  ed.version       = version;
  ed.name          = virt;
  ed.orgLoc        = orgLoc;
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
    mainName    = a.mainName;

    version     = a.version;
    virt        = a.virt;
    orgLoc      = a.orgLoc;
    actual      = a.actual;
    notes       = a.notes;
    homePh      = a.homePh;
    cellPh      = a.cellPh;
    busPh       = a.busPh;
    agency1Name = a.agency1Name;
    agency1Ph   = a.agency1Ph;
    agency2Name = a.agency2Name;
    agency2Ph   = a.agency2Ph;
    moreNotes   = a.moreNotes;

    dirty       = a.dirty;
    deleted     = a.deleted;
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
IniFile ini;

  ini.setPath(path);   this->path = path;   mainName = getMainName(path);

  ini.readString(Section, AddrVer,   version);
  ini.readString(Section, AddrName,  virt);
  ini.readString(Section, ORGname,   orgLoc);
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

  addrFile.deleteSection(_T("End"));   addrFile.deleteSection(_T("End"));   addrFile.writeEnd();
  dirty = false;
  }


