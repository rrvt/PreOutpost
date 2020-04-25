// Identity Info Class
// rrvt Copywrite, all rights reserved


#include "stdafx.h"
#include "IdentityInfo.h"



void IdentityInfo::loadDialogBox(IdentityDialog& dlg) {
  dlg.subjWSecurity    = subjWSecurity;
  dlg.includeAddrBook  = includeAddrBook;
  dlg.isTacticalID     = isTacticalID;
  dlg.tacticalCallSign = tacticalCallSign;
  dlg.tacticalText     = tacticalText;
  dlg.tacticalIDPrefix = tacticalIDPrefix;
  dlg.tacSignature     = tacSignature;
  dlg.userCallSign     = userCallSign;
  dlg.userName         = userName;
  dlg.userIDPrefix     = userIDPrefix;
  dlg.userSignature    = userSignature;
  dlg.organization     = organization;
  dlg.city             = city;
  dlg.county           = county;
  dlg.state            = state;
  dlg.tacticalLocation = tacticalLocation;
  dlg.textVariable2    = textVariable2;
  dlg.textVariable3    = textVariable3;
  dlg.taskID           = taskID;
  dlg.taskName         = taskName;
  dlg.profilesDesired  = profilesDesired;
  dlg.severity         = severity;
  dlg.handling         = handling;
  dlg.subjStyle        = subjStyle;
  dlg.practiceDay      = practiceDay;
  dlg.subject          = subject;
  }


void IdentityInfo::unloadDialogBox(IdentityDialog& dlg) {
  subjWSecurity     = dlg.subjWSecurity;
  includeAddrBook   = dlg.includeAddrBook;
  todaysDate        = dlg.todaysDate;
  isTacticalID      = dlg.isTacticalID;
  tacticalCallSign  = dlg.tacticalCallSign;
  tacticalText      = dlg.tacticalText;
  tacticalIDPrefix  = dlg.tacticalIDPrefix;
  tacSignature      = dlg.tacSignature;
  userCallSign      = dlg.userCallSign;
  userName          = dlg.userName;
  userIDPrefix      = dlg.userIDPrefix;
  userSignature     = dlg.userSignature;
  organization      = dlg.organization;
  city              = dlg.city;
  county            = dlg.county;
  state             = dlg.state;
  tacticalLocation  = dlg.tacticalLocation;
  textVariable2     = dlg.textVariable2;
  textVariable3     = dlg.textVariable3;
  taskID            = dlg.taskID;
  taskName          = dlg.taskName;
  profilesDesired   = dlg.profilesDesired;
  severity          = dlg.severity;
  handling          = dlg.handling;
  subjStyle         = dlg.subjStyle;
  practiceDay       = dlg.practiceDay;
  subject           = dlg.subject;
  }

