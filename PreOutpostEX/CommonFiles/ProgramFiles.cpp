// Program File List and Descriptor


#include "stdafx.h"
#include "ProgramFiles.h"
#include "filename.h"
#include "filesrch.h"
#include "IniFile.h"
#include "match.h"
#include "MessageBox.h"
#include "OutpostChoiceDlg.h"


OutputPaths outputPaths;


static TCchar* PathSection = _T("Path");
static TCchar* ProfileKey  = _T("Profile");
static TCchar* OutpostKey  = _T("Outpost");



// We've already opened the INI file for PreOutpost.  See if we've found the paths to the Outpost
// Executable and Profiles stored them in the INI file.  If not, then find the paths and store them.
// The paths are stored in the PreOutpost object.

void OutputPaths::getProfilePath() {

  if (iniFile.readString(PathSection, ProfileKey, profilePath)  &&
      iniFile.readString(PathSection, OutpostKey, outpostPath)) return;

  choose();
  }


void OutputPaths::choose() {
OutpostChoiceDlg opChoice;

  if (opChoice.DoModal() != IDOK) {messageBox(_T("Did not complete search for Outpost."));}
  }


void OutputPaths::saveOutpostPath(String& profile, String& exe) {

  profilePath = profile;  outpostPath = exe;

  iniFile.writeString(PathSection, ProfileKey, profilePath);
  iniFile.writeString(PathSection, OutpostKey, outpostPath);
  }



ProgramFiles::ProgramFiles() {
  findDirs(_T("C:"), _T("Program*"), programDirs);
  }


void ProgramFiles::findOutpostDirs(TCchar* srchPat) {
int         n;
int         i;

  for (i = 0, n = programDirs.end(); i < n; i++) findDirs(programDirs[i].path, srchPat, outpDirs);
  }


String ProgramFiles::getProfilePath(TCchar* path) {
String  confFilePath = findConfFile(path);
IniFile confFile;
String  s;

  confFile.setPath(confFilePath);

  if (confFile.readString(_T("DataDirectory"), _T("DataDir"), s) ||
      confFile.readString(_T("Data Directory Declaration/I"), _T("DataDir"), s)) s += _T('\\');

  return s;
  }


String ProgramFiles::findConfFile(TCchar* path) {
RegExpr re;
int     n;
int     i;

  n = findOutpostFiles(path);

  if (!re.setWildCardPattern(_T("*.conf"))) return 0;

  for (i = 0; i < n; i++) if (re.match(outpFiles[i].name)) return outpFiles[i].fullPath();

  return 0;
  }


String ProgramFiles::findExeFile(TCchar* path) {
RegExpr re;
int     n;
int     i;

  n = findOutpostFiles(path);

  if (!re.setWildCardPattern(_T("*.exe"))) return 0;

  for (i = 0; i < n; i++) if (re.match(outpFiles[i].name)) return outpFiles[i].fullPath();

  return 0;
  }



void ProgramFiles::findDirs(TCchar* initialPath, TCchar* srchPat, Descriptors& dirs) {
FileSrch fileSrch;
String   s;

  fileSrch.findSubDirs(initialPath, srchPat);

  while (fileSrch.getName(s)) dirs[dirs.end()] = s;
  }




int ProgramFiles::findOutpostFiles(TCchar* path) {

  if (outpFiles.end() <= 0) findFiles(path, _T("*Outpost*"), outpFiles);

  return outpFiles.end();
  }



void ProgramFiles::findFiles(TCchar* initialPath, TCchar* srchPat, Descriptors& files) {
FileSrch fileSrch;
String   s;

  fileSrch.findFiles(initialPath, srchPat);

  while(fileSrch.getName(s)) files[files.end()] = s;
  }



ProgramDsc& ProgramDsc::operator= (String& fullPath)
                              {path = getPath(fullPath);   name = removePath(fullPath);   return *this;}




