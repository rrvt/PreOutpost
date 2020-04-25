// Identity Info Class
// rrvt Copywrite, all rights reserved


#pragma once
#include "Resource.h"
#include "IdentityDialog.h"


class IdentityInfo {
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

  IdentityInfo() : isTacticalID(false), profilesDesired(0), severity(0), handling(0), subjStyle(0),
                                 practiceDay(0), subjWSecurity(false), includeAddrBook(false) {}
 ~IdentityInfo() {}

  void loadDialogBox(IdentityDialog& dlg);
  void unloadDialogBox(IdentityDialog& dlg);
  };
