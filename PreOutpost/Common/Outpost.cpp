// Outpost Data


#include "pch.h"
#include "Outpost.h"
#include "IniFileEx.h"
#include "MessageBox.h"
#include "OutpostChoiceDlg.h"
#include "ProgramFiles.h"
#include "Resource.h"
#include "WaitMsgDlg.h"


Outpost outpost;


static TCchar* PathSection = _T("Path");
static TCchar* ProfileKey  = _T("Profile");
static TCchar* OutpostKey  = _T("Outpost");


void Outpost::initialize(TCchar* outpost, TCchar* profile) {
String path;

  if (iniFile.readString(PathSection, OutpostKey, path)) {
    if (!outpost || !*outpost || path == outpost) exePath = path;
    else setOutpost(outpost);
    }
  else setOutpost(outpost);

  if (iniFile.readString(PathSection, ProfileKey, path)) {
    if (!profile || !*profile || path == profile) dataPath = path;
    else setProfile(profile);
    }
  else setProfile(profile);

  if (exePath.isEmpty() || dataPath.isEmpty()) choose();
  }


void Outpost::setOutpost(TCchar* path)
        {if (path && *path) {exePath = path;   iniFile.write(PathSection, OutpostKey, exePath);}}


void Outpost::setProfile(TCchar* path)
        {if (path && *path) {dataPath = path;   iniFile.write(PathSection, ProfileKey, dataPath);}}



// We've already opened the INI file for PreOutpost.  See if we've found the paths to the Outpost
// Executable and Profiles stored them in the INI file.  If not, then find the paths and store
// them.  The paths are stored in the PreOutpost object.

bool Outpost::getProfilePath() {

  if (iniFile.readString(PathSection, ProfileKey, dataPath)  &&
      iniFile.readString(PathSection, OutpostKey, exePath)) return true;

  return choose();
  }


bool Outpost::choose() {
WaitMsgDlg       waitDlg;
OutpostChoiceDlg dlg;

  waitDlg.DoModal();

  if (programFiles.nFolders() == 0) {
    String s;
    s = _T("Unable to locate any directories with names that include \"");
    s += PacketPat;   s += _T("\" or \"");   s += OutpostPat;   s += _T("\"");

    messageBox(s);   return false;
    }

  if (dlg.DoModal() != IDOK)
                            {messageBox(_T("Did not complete search for Outpost.")); return false;}

  return saveOutpostPath(dlg.exeFilePath, dlg.confFilePath);
  }


bool Outpost::saveOutpostPath(String& path, String& profile) {

  if (path.isEmpty() || profile.isEmpty()) return false;

  exePath = path;   dataPath = profile;

  iniFile.writeString(PathSection, ProfileKey, dataPath);
  iniFile.writeString(PathSection, OutpostKey, exePath);   return true;
  }

