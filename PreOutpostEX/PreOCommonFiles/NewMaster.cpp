// Create New Masters


#include "stdafx.h"
#include "NewMaster.h"
#include "CopyFile.h"
#include "DelMasterDlg.h"
#include "filename.h"
#include "filesrch.h"
#include "MasterMgmtDlg.h"
#include "MasterProf.h"
#include "NewMasterDlg.h"
#include "PreOutpost.h"
#include "ProgramFiles.h"


static TCchar* MasterExt = _T("MProfile");


// Display a dialog box to create or delete a Master Profile.

void NewMaster::operator() () {
MasterMgmtDlg dlg;
MPIter        iter(masterProf);
Master*       m;
String        selected;

  for (m = iter(); m; m = iter++) dlg.addListBoxItem(m->name);

  switch (dlg.DoModal()) {
    case CreateMaster: selectNew(); return;
    case DeleteMaster: selected = dlg.getListBoxSelection(); deleteMaster(selected); return;
    }
  }


// Find all the Outpost profiles that have not been created by this program.  Put them in a Dialog list
// box.  Choose one for the new Master Profile, make a copy in this programs directory and insert the name
// in the INI file for this program.  The insertion is done so that the list remains sorted.

void NewMaster::selectNew() {
NewMasterDlg dlg;
FileSrch     fileSrch;
String       profile;
String       profileName;
RegExpr      re;
String       selection;
String       selected;
String       newMetaProfile;
String       metaProfileName;
String       metaLabel;

  fileSrch.findFiles(outputPaths.profilePath, _T("*.profile"));

  re.setWildCardPattern(_T("~*~W*~"));

  while (fileSrch.getName(profile)) {

    profileName = getMainName(profile.str());    if (re.match(profileName)) continue;

    dlg.addListBoxItem(removePath(profile));
    }

  if (dlg.DoModal() != IDOK) return;

  selected = dlg.getListBoxSelection();
  selection += outputPaths.profilePath;
  selection += selected;
  newMetaProfile = theApp.roamingPath + selected;

  if (!change_extension(newMetaProfile, MasterExt)) return;

  copyFile(selection, newMetaProfile);

  if (masterProf.insertNewProfile(newMetaProfile)) masterProf.setMetaProfiles();
  }


// Delete MetaProfile Selected

void NewMaster::deleteMaster(String& selected) {
DelMasterDlg dlg;
String       path;

  dlg.MasterProfileName = selected;

  if (dlg.DoModal() == IDCANCEL) return;

  path = theApp.roamingPath + selected;    change_extension(path, MasterExt);

  if (PathFileExists(path)) removeFile(path);

  idInfo.clearOldProfiles(getMainName(selected));

  masterProf.readIniFile();
  }
