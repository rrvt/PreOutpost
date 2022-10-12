// PreOutpost.h : An application composed of two dialog boxes to support Outpost, an Amateur Radio Packet
//                application.
// rrvt 6/6/16  Copyright all rights reserved


#pragma once
#include "CApp.h"
#include "Executable.h"
#include "iniFile.h"
#include "Identity.h"
#include "MasterProf.h"


class PreOutpost : public CApp {
bool       subjWSecurity;
bool       includeAddrBook;

public:

String     myPath;                                // Path to this program when running
String     helpFile;                              // path and filename for help file
String     roamingPath;                           // Path to roaming directory
String     subjectLine;
Executable opAddrExe;

  PreOutpost() : CApp(this), subjWSecurity(false), includeAddrBook(false) { }

public:

  virtual BOOL InitInstance();                  // Everything is done in this function
  virtual int  ExitInstance();


public:

  DECLARE_MESSAGE_MAP()

private:

  void startOutpost();
  bool startOPaddress();
  };


extern PreOutpost theApp;

