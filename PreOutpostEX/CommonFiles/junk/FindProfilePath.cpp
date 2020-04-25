// Search for Profile Path on the C drive
// First look for "Program*" directories
// Then look for "*Packet*" directory
// Then look for *Outpost* files


#include "stdafx.h"
#include "FindProfilePath.h"
#include "IniFile.h"
#include "filesrch.h"
#include "Expandable.h"


static bool findOutpostPaths(String& confFile, String& exeFile);



bool findProfilePaths(String& profilePath, String& outpostPath) {
String   confFile;
IniFile  iniFile;
FileSrch fileSrch;

  if (!findOutpostPaths(confFile, outpostPath)) return false;

  iniFile.setPath(confFile);

  if (iniFile.readString(_T("DataDirectory"), _T("DataDir"), profilePath)) return true;
  if (iniFile.readString(_T("Data Directory Declaration/I"), _T("DataDir"), profilePath)) return true;
  return false;
  }



bool findOutpostPaths(String& confFile, String& exeFile) {
FileSrch              fileSrch;
int                   nDir;
Expandable<String, 2> directories;
int                   nMyPath;
String                myPath[10];
int                   nMyFiles;
Expandable<String, 4> myFiles;
int                   i;
RegExpr               re;

  fileSrch.findSubDirs(_T("C:"), _T("Program*"));

  for (nDir = 0; fileSrch.getName(directories[nDir]); nDir++) continue;

  for (i = 0, nMyPath = 0; i < nDir; i++) {
    fileSrch.findSubDirs(directories[i], _T("*Packet*"));

    for ( ; fileSrch.getName(myPath[nMyPath]); nMyPath++) continue;
    }

  for (i = 0, nMyFiles = 0; i < nMyPath; i++) {
    fileSrch.findFiles(myPath[i], _T("*Outpost*"));

    for ( ; fileSrch.getName(myFiles[nMyFiles]); nMyFiles++) continue;
    }

  if (!re.setWildCardPattern(_T("*.conf"))) return false;

  for (i = 0; i < nMyFiles; i++) if (re.match(myFiles[i])) {confFile = myFiles[i]; break;}

  if (!re.setWildCardPattern(_T("*.exe"))) return false;

  for (i = 0; i < nMyFiles; i++) if (re.match(myFiles[i])) {exeFile = myFiles[i]; break;}

  if (confFile.empty() || exeFile.empty()) return false;

  return true;
  }

