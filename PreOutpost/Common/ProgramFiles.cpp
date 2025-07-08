// Program File List and Descriptor


#include "pch.h"
#include "ProgramFiles.h"
#include "CfgFile.h"
#include "filename.h"
#include "filesrch.h"
#include "RegExpr.h"




void ProgramFiles::loadOutputFldrs(TCchar* srchPat) {
AppIter iter(directories);
String* dsc;

  for (dsc = iter(); dsc; dsc = iter++) findOutputFldrs(*dsc, srchPat);
  }


void ProgramFiles::findOutputFldrs(TCchar* initialPath, TCchar* srchPat) {
FileSrch fileSrch;
String   s;

  fileSrch.findSubDirs(initialPath, srchPat);

  while (fileSrch.getName(s)) outputFldrs.add(s);
  }


String ProgramFiles::getProfilePath(TCchar* path) {
String  confFilePath = findFile(path, _T("*.conf"));
CfgFile confFile;
String  s;

  confFile.setPath(confFilePath);

  if (confFile.readString(_T("DataDirectory"), _T("DataDir"), s) ||
      confFile.readString(_T("Data Directory Declaration/I"), _T("DataDir"), s)) s += _T('\\');

  return s;
  }



String ProgramFiles::findFile(TCchar* path, TCchar* extPat) {
PrgIter iter(*this);
String* pth;
RegExpr re;
String  s;

  loadOutputFiles(path);   if (!re.setWildCardPattern(extPat)) return s;

  for (pth = iter(); pth; pth = iter++) if (re.match(*pth)) return *pth;

  return s;
  }


int ProgramFiles::loadOutputFiles(TCchar* path) {

  if (data.end() <= 0) findOutputFiles(path, _T("*Outpost*"));

  return data.end();
  }


void ProgramFiles::findOutputFiles(TCchar* initialPath, TCchar* srchPat) {
FileSrch fileSrch;
String   s;

  fileSrch.findFiles(initialPath, srchPat);

  while(fileSrch.getName(s)) data.nextData() = s;
  }


#if 0
ProgramDsc& ProgramDsc::operator= (String& fullPath)
                         {path = getPath(fullPath);   name = removePath(fullPath);   return *this;}
#endif




///---------------------

#if 1
#else
RegExpr re;
int     n;
int     i;

  n = loadOutputFiles(path);

  if (!re.setWildCardPattern(_T("*.conf"))) return 0;

  for (i = 0; i < n; i++) if (re.match(outpFiles[i].name)) return outpFiles[i].fullPath();

  return 0;
#endif

#if 1
#else
RegExpr re;
int     n;
int     i;

  n = loadOutputFiles(path);

  if (!re.setWildCardPattern(_T("*.exe"))) return 0;

  for (i = 0; i < n; i++) if (re.match(outpFiles[i].name)) return outpFiles[i].fullPath();

  return 0;
#endif
#if 1
#else
int         n;
int         i;

  for (i = 0, n = programDirs.end(); i < n; i++) findDirs(programDirs[i].path, srchPat, outpDirs);
#endif
#if 0
String ProgramFiles::findConfFile(TCchar* path) {
#if 1

  return findFile(path, _T("*.conf"));

#else
PrgIter     iter(*this);
ProgramDsc* dsc;
RegExpr     re;
String      s;


  loadOutputFiles(path);   if (!re.setWildCardPattern(_T("*.conf"))) return s;

  for (dsc = iter(); dsc; dsc = iter++) if (re.match(dsc->name)) return dsc->fullPath();

  return s;
#endif
  }


String ProgramFiles::findExeFile(TCchar* path) {
#if 1

  return findFile(path, _T("*.exe"));
#else
PrgIter     iter(*this);
ProgramDsc* dsc;
RegExpr     re;
String      s;

  loadOutputFiles(path);

  if (!re.setWildCardPattern(_T("*.exe"))) return s;

  for (dsc = iter(); dsc; dsc = iter++) if (re.match(dsc->name)) return dsc->fullPath();

  return s;
  #endif
  }
#endif
//#include "MessageBox.h"

