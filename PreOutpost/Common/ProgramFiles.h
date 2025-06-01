// Program File List and Descriptor


#pragma once
#include "Appfile.h"
#include "Expandable.h"
#include "IterT.h"
#include "OutpostFolders.h"



class ProgramFiles;
typedef IterT<ProgramFiles, String> PrgIter;              // ProgramDsc


class ProgramFiles {

AppFile               directories;            // All Program directories
OutpostFolders        outputFldrs;            // Output Folders Only
Expandable<String, 2> data;                   // outpFiles;

public:

                  ProgramFiles() : directories(_T("C:\\Program*")) { }

                 ~ProgramFiles() { }

  void            loadOutputFldrs(TCchar* srchPat);
  OutpostFolders& getFolders() {return outputFldrs;}
  String          getProfilePath(TCchar* path);
  String          findFile(TCchar* path, TCchar* extPat);

  int             nFolders() {return outputFldrs.nData();}
  int             nData()    {return data.end();}       // Returns number of data items in array,
                                                        // not necessarily private
private:

  void            findOutputFldrs(TCchar* initialPath, TCchar* srchPat);
  int             loadOutputFiles(TCchar* path);
  void            findOutputFiles(TCchar* initialPath, TCchar* srchPat);

  // returns either a pointer to datum at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}
  void    removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename PrgIter;
  };


extern ProgramFiles programFiles;


/////------------------------

//  String          findExeFile(TCchar* path);
//  String          findConfFile(TCchar* path);
#if 0
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
#endif
//typedef Expandable<ProgramDsc, 2> Descriptors;

