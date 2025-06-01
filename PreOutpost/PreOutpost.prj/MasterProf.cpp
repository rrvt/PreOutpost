// Master Profile Manipulation


#include "pch.h"
#include "MasterProf.h"
#include "copyFile.h"
#include "DelMasterDlg.h"
#include "filename.h"
#include "filesrch.h"
#include "Identity.h"
#include "IniFile.h"
#include "MasterMgmtDlg.h"
#include "PreOutpost.h"
#include "SelectMasterDlg.h"
#include "MessageBox.h"


static TCchar* Section = _T("MetaProfiles");


MasterProf masterProf;


// Read .ini file for all meta profiles, checking that they are still available and correcting
// .ini file in the process

void MasterProf::readIniFile() {
int    n;
String path;
int    i;
bool   missing = false;

  masters.clear();

  n = iniFile.readInt(Section, _T("nMetaProfiles"), 0);

  for (i = 0; i < n; i++) {

    if (!iniFile.readString(Section, getKey(i), path))
      {missing = true; continue;}

    if (path.empty() || !PathFileExists(path)) {missing = true; continue;}

    Master& m = masters.nextData();

    m.path = path;  m.name = getMainName(path);
    }

  if (missing) setMetaProfiles();
  }


// Write Meta Profiles back into ini file after deleting

void MasterProf::setMetaProfiles() {
int n = masters.end();
int i;
String metaProfile;

  iniFile.deleteSection(Section);

  iniFile.writeInt(Section, _T("nMetaProfiles"), n);

  for (i = 0; i < n; i++) {iniFile.writeString(_T("MetaProfiles"), getKey(i), masters[i].path);}
  }


// Produce a Property Name to be used in an ini file.  Good for putting the Master Files in sort
// order for MetaProfile00 to MetaProfile99.  Should be enough for this program...

String MasterProf::getKey(int i) {
String name = _T("MetaProfile");

  if (i < 10) name += _T("0");   name += toString(i);   return name;
  }





Master* MasterProf::select() {
MPIter          iter(*this);
Master*         m;
SelectMasterDlg dlg;

  dlg.allProfiles = 0;

  if (masters.end() == 1) {allProfiles = false; return &masters[0];}

  for (m = iter(); m; m = iter++) {dlg.addListBoxItem(m->name);}

  if (dlg.DoModal() == IDOK) {
    name = dlg.getListBoxSelection();   allProfiles = dlg.allProfiles;

    for (m = iter(); m; m = iter++) if (m->name == name) return m;
    }

  return 0;
  }


// Process identity for selected meta profile file, then either copy one Meta Profile or all Meta
// Profiles

bool MasterProf::process(Master* m) {
MPIter  iter(*this);

  if (!m) return false;

  if (!idInfo(m->name, m->path, allProfiles)) return false;

  if (allProfiles) {
    for (m = iter(); m; m = iter++) {idInfo.process(m->name, m->path);}
    }

  else idInfo.process(m->name, m->path);

  return true;
  }


// Insertion sort new profile into metaProfilePath

bool MasterProf::insertNewProfile(String& newProfile) {
String  name = getMainName(newProfile);
MPIter  iter(*this);
Master* m;
String  stg;

  for (m = iter(); m; m = iter++) if (name == m->name) return false;

  m = &masters.nextData();   m->path = newProfile;  m->name = name;

  qsort(&masters[0], &masters[masters.end()-1]);   return true;
  }

