// PreOutpost.h : An application composed of two dialog boxes to support Outpost, an Amateur Radio Packet
//                application.
// rrvt 6/6/16  Copyright all rights reserved


#pragma once
#include "resource.h"       // main symbols
#include "iniFile.h"
#include "IdentityInfo.h"
#include "Expandable.h"
#include "UsrData.h"


// PreOutpost:
// See PreOutpost.cpp for the implementation of this class
//

class PreOutpost : public CWinApp {
bool                   subjWSecurity;
bool                   includeAddrBook;
public:

bool                   makeMaster;              // When true make a Master Profile
String                 myPath;                  // Path to this program when running
String                 helpFile;                // path and filename for help file
String                 roamingPath;             // Path to roaming directory
//IniFile                preIniFile;              // Implements Read/Write to Private Profile File
IniFile                metaProfile;
int                    nMetaProfiles;           // Number of Meta Profiles being maintained
Expandable <String, 2> metaProfilePath;         // Full path to Meta Profiles (master profile?)
String                 metaProfPath;            // Current Meta Profile Path
String                 SubjectSection;          // combination of MetaProfile Name and ".Subject"
UsrData                usrData;
UsrData                tacData;
String                 subjectLine;

STARTUPINFO            startUpInfo;
PROCESS_INFORMATION    OPaddrPrcInfo;

IdentityInfo           idInfo;

  PreOutpost();

// Overrides

public:

  virtual BOOL InitInstance();                  // Everything is done in this function
  virtual int  ExitInstance();

// Implementation

  void createNewMaster();                       // Create a new Master File or Delete one
  void OnSelectMasterProfile();                 // Select a Profile to make into a Master Profile

  void testNewDialog();
  void updateIDMakeProfile();                   // Get user ID and Report info and create Outpost Profiles
  void getMetaProfiles();                       // Read .ini file for all meta profiles, checking that
                                                // they are still available.
  void setMetaProfiles(int n);                  // Write Meta Profiles back into ini file after updating
  void getMetaName(int i, String& name);
  bool insertNewProfile(String& newProfile);    // Insertion sort new profile into metaProfilePath
  bool processMetaProfileIdentity(String& mProfileName, int allMasterProfiles);
  bool getIdentityInfo(String& metaPath, int allMasterProfiles);
  void processMetaFile(String& metaPath);
  void startOutpost();
  bool startOPaddress();
  void killOPaddress();

  void createNewProfiles(String& metaPath);   // Create New Profiles as required
  void clearOldProfiles(String& metaPath);      // Remove old created profiles from Outposts data dir

public:

  DECLARE_MESSAGE_MAP()

private:

  void setTitle(String& metaPath, int allMasterProfiles, String& title);
  void createSubjLine(String& stg);
  };


extern PreOutpost theApp;
