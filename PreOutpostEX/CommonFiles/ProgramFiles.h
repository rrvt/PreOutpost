// Program File List and Descriptor


#pragma once
#include "Expandable.h"



class ProgramDsc {
public:
String path;
String name;

  ProgramDsc() { }
  ProgramDsc(ProgramDsc& d) {path = d.path; name = d.name;}
  ProgramDsc& operator= (ProgramDsc& d) {path = d.path; name = d.name; return *this;}

 ~ProgramDsc() { }

  ProgramDsc& operator= (String& fullPath);
  String      fullPath() {String s = path + name; return s;}
  };



class ProgramFiles {
typedef Expandable<ProgramDsc, 2> Descriptors;

Descriptors programDirs;

public:

Descriptors outpDirs;
Descriptors outpFiles;

  ProgramFiles();
 ~ProgramFiles() { }

  void    findOutpostDirs(TCchar* srchPat);

  String  getProfilePath(TCchar* path);
  String  findExeFile(TCchar* path);

private:

  String  findConfFile(TCchar* path);
  void    findDirs( TCchar* initialPath, TCchar* srchPat, Descriptors& dirs);
  int     findOutpostFiles(TCchar* path);
  void    findFiles(TCchar* initialPath, TCchar* srchPat, Descriptors& files);
  };


struct OutputPaths {
String outpostPath;                           // Full path to Outpost executable including file name
String profilePath;                           // Path to directory where Outpost stores its profiles


  OutputPaths() { }
 ~OutputPaths() { }

  void getProfilePath( );      // Little function to find profilePath and outpostPath
  void choose();

  void saveOutpostPath(String& profile, String& exe);
  };


extern OutputPaths outputPaths;
