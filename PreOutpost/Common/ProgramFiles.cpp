// Program File List and Descriptor


#include "pch.h"
#include "ProgramFiles.h"
#include "filename.h"
#include "filesrch.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "RegExpr.h"


ProgramFiles::ProgramFiles() {findDirs(_T("C:"), _T("Program*"), programDirs);}


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

  while (fileSrch.getName(s)) dirs.nextData() = s;   //[dirs.end()]
  }


int ProgramFiles::findOutpostFiles(TCchar* path) {

  if (outpFiles.end() <= 0) findFiles(path, _T("*Outpost*"), outpFiles);

  return outpFiles.end();
  }


void ProgramFiles::findFiles(TCchar* initialPath, TCchar* srchPat, Descriptors& files) {
FileSrch fileSrch;
String   s;

  fileSrch.findFiles(initialPath, srchPat);

  while(fileSrch.getName(s)) files.nextData() = s;     //[files.end()]
  }



ProgramDsc& ProgramDsc::operator= (String& fullPath)
                         {path = getPath(fullPath);   name = removePath(fullPath);   return *this;}


