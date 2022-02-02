// Identity Info Class
// rrvt Copywrite, all rights reserved


#pragma once
#include "Resource.h"
#include "IdentityDlg.h"
#include "UsrData.h"


class IdentityInfo {

IniFile metaProfile;

public:

bool    subjWSecurity;
bool    includeAddrBook;
String  todaysDate;

String userCallSign;
String userName;
String userIDPrefix;
String userSignature;
bool   isTacticalID;
String tacticalCallSign;
String tacticalText;
String tacticalIDPrefix;
String tacSignature;
String organization;
String city;
String county;
String state;
String tacticalLocation;
String textVariable2;
String textVariable3;
String taskID;
String taskName;
int    profilesDesired;
int    severity;
int    handling;
String subject;
int    subjStyle;
int    practiceDay;

UsrData usrData;
UsrData tacData;

  IdentityInfo() : isTacticalID(false), profilesDesired(0), severity(0), handling(0), subjStyle(0),
                    practiceDay(0), subjWSecurity(false), includeAddrBook(false),
                    usrData(_T("usr")), tacData(_T("tac")) {}
 ~IdentityInfo() {}

  bool operator() (TCchar* profileName, String& metaPath, int allProfiles);

  void process(TCchar* profileName, String& metaPath);
  void createNewProfiles(String& metaPath);
  void createSubjLine(String& stg);

  void loadDialogBox(  IdentityDlg& dlg);
  void unloadDialogBox(IdentityDlg& dlg);

  void clearOldProfiles(String& metaPath);    // Remove old created profiles from Outposts data dir

private:

  void readMetaFile();
  void writeMetaFile();

  void readSubject(TCchar* profileName);
  void writeSubject(TCchar* profileName);

  void readOptions();
  void writeOptions();

  void setTitle(String& metaPath, int allProfiles, String& title);
  };


extern IdentityInfo idInfo;

