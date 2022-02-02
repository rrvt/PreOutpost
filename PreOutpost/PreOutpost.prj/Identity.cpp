// Identity Info Class
// rrvt Copywrite, all rights reserved


#include "stdafx.h"
#include "Identity.h"
#include "BBSinfo.h"
#include "CopyFile.h"
#include "filename.h"
#include "filesrch.h"
#include "IdentityDlg.h"
#include "IniFile.h"
#include "PreOutpost.h"
#include "ProgramFiles.h"
#include "Resources.h"


IdentityInfo idInfo;


// Display the ID and Report Info dialog box and get the input from the user.

bool IdentityInfo::operator() (TCchar* profileName, String& metaPath, int allProfiles) {
IdentityDlg dlg;

  setTitle(metaPath, allProfiles, dlg.title);

  readOptions();

  metaProfile.setPath(metaPath);   readMetaFile();

  profilesDesired = 0;

  readSubject(profileName);

  usrData.load(userCallSign);

  userName = usrData.name;   userIDPrefix = usrData.userID;    userSignature = usrData.signature;

  tacData.load(tacticalCallSign);

  tacticalText = tacData.name;   tacticalIDPrefix = tacData.userID;   tacSignature = tacData.signature;

  loadDialogBox(dlg);

  if (dlg.DoModal() == IDCANCEL) return false;

  unloadDialogBox(dlg);

  usrData.callSign = userCallSign; usrData.name      = userName;
  usrData.userID   = userIDPrefix; usrData.signature = userSignature;

  tacData.callSign = tacticalCallSign; tacData.name      = tacticalText;
  tacData.userID   = tacticalIDPrefix; tacData.signature = tacSignature;

  return true;
  }


// Use the input ID and Report input to update the master profile.  Then update the Master File with
// the BBS name for each profile to be copied to the Outpost profile directory.

void IdentityInfo::process(TCchar* profileName, String& metaPath) {

  writeOptions();

  metaProfile.setPath(metaPath);   writeMetaFile();

  writeSubject(profileName);

  clearOldProfiles(metaPath);

  createNewProfiles(metaPath);

  usrData.store(userCallSign);

  tacData.store(tacticalCallSign);
  }


static TCchar* OptSection         = _T("Options");
static TCchar* SubjWSecurityKey   = _T("SubjWSecurity");
static TCchar* IncludeAddrBookKey = _T("IncludeAddrBook");


void IdentityInfo::readOptions() {
  subjWSecurity   = iniFile.readInt(OptSection, SubjWSecurityKey,   0) != 0;
  includeAddrBook = iniFile.readInt(OptSection, IncludeAddrBookKey, 0) != 0;
  }


void IdentityInfo::writeOptions() {

  iniFile.writeInt(OptSection, SubjWSecurityKey,   subjWSecurity);
  iniFile.writeInt(OptSection, IncludeAddrBookKey, includeAddrBook);
  }



TCchar* SubjectSfx     = _T(".Subject");
TCchar* SeverityKey    = _T("Severity");
TCchar* HandlingKey    = _T("Handling");
TCchar* StyleKey       = _T("Style");
TCchar* PracticeDayKey = _T("PracticeDay");
TCchar* SubjectKey     = _T("Subject");


void IdentityInfo::readSubject(TCchar* profileName) {
String section = profileName; section += SubjectSfx;

  severity    = iniFile.readInt(section, SeverityKey,    2);
  handling    = iniFile.readInt(section, HandlingKey,    2);
  subjStyle   = iniFile.readInt(section, StyleKey,       0);
  practiceDay = iniFile.readInt(section, PracticeDayKey, 0);
  iniFile.readString(           section, SubjectKey,     subject);
  }


void IdentityInfo::writeSubject(TCchar* profileName) {
String section = profileName; section += SubjectSfx;

  iniFile.writeInt(   section, SeverityKey,    severity);
  iniFile.writeInt(   section, HandlingKey,    handling);
  iniFile.writeInt(   section, StyleKey,       subjStyle);
  iniFile.writeInt(   section, PracticeDayKey, practiceDay);
  iniFile.writeString(section, SubjectKey,     subject);
  }


void IdentityInfo::setTitle(String& metaPath, int allProfiles, String& title) {
String       metaName = getMainName(metaPath);
ResourceData res;
String       t;
String       pn;
String       cn;
String       ds;
String       ver;

  title = _T("FCC and Tactical Identity for ");

  title += allProfiles ? _T("All Master Files") : metaName.str();

  if (res.getCompanyName(cn)) title += _T(" / ") + cn;

  if (res.getProductName(pn)) {
    if (!title.empty())       title += _T(" / ") + pn;
    else                      title = pn;
    }

  if (res.getVersion(ver))     title += _T(" / ") + ver;
  }


// Create New Profiles as required

void IdentityInfo::createNewProfiles(String& metaPath) {
int      i;
BBSIter  iter(bbsInfo);
BBSdata* bbs;
String   s;

  for (i = 0; !iter() && i < 2; i++) {bbsInfo.getSuffixes();}

  for (bbs = iter(); bbs; bbs = iter++) {

    if (bbs->suffix.isEmpty()) continue;

    s  = _T("~"); s += getMainName(metaPath); s += _T("~"); s += bbs->suffix; s += _T("~.profile");

    s = outputPaths.profilePath + s;

    metaProfile.writeString(_T("GENERAL VARIABLES"), _T("BbsCName"), bbs->cName);
    metaProfile.writeString(_T("GENERAL VARIABLES"), _T("BbsFName"), bbs->fName);

    copyFile(metaPath, s);

    if (profilesDesired) break;
    }
  }


// Delete all Outpost Profiles that contain metaName.

void IdentityInfo::clearOldProfiles(String& metaPath) {
String   wildCardPat;
FileSrch fileSrch;
RegExpr  re;
String   name;

  wildCardPat = _T("*\\~"); wildCardPat += getMainName(metaPath); wildCardPat += _T("~*~.profile");

  re.setWildCardPattern(wildCardPat);

  if (fileSrch.findFiles(outputPaths.profilePath, _T("*.profile")))
    while (fileSrch.getName(name))
      if (re.match(name)) removeFile(name);
  }





void IdentityInfo::loadDialogBox(IdentityDlg& dlg) {
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


void IdentityInfo::unloadDialogBox(IdentityDlg& dlg) {
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


static TCchar* IDSection      = _T("IDENTIFICATION");
static TCchar* RptSection     = _T("REPORT TAGS");

static TCchar* TacCallKey     = _T("TacCall");
static TCchar* TacNameKey     = _T("TacName");
static TCchar* TacIDKey       = _T("TacID");
static TCchar* UsrCallKey     = _T("UsrCall");
static TCchar* UsrNameKey     = _T("UsrName");
static TCchar* UsrIDKey       = _T("UsrID");
static TCchar* OrgKey         = _T("Org");
static TCchar* CityKey        = _T("City");
static TCchar* CountyKey      = _T("County");
static TCchar* StateKey       = _T("State");
static TCchar* TacLocKey      = _T("TacLoc");
static TCchar* Text2Key       = _T("Text2");
static TCchar* Text3Key       = _T("Text3");
static TCchar* TaskIDKey      = _T("TaskID");
static TCchar* TaskNameKey    = _T("TaskName");
static TCchar* ActMyCallKey   = _T("ActMyCall");
static TCchar* ActMyNameKey   = _T("ActMyName");
static TCchar* ActMyIDKey     = _T("ActMyID");
static TCchar* TCnPEnabledKey = _T("TCnPEnabled");



void IdentityInfo::readMetaFile() {

  isTacticalID  = metaProfile.readInt(IDSection, _T("TCnPEnabled"), 0) != 0;
  metaProfile.readString(IDSection,  TacCallKey,  tacticalCallSign);
  metaProfile.readString(IDSection,  TacNameKey,  tacticalText);
  metaProfile.readString(IDSection,  TacIDKey,    tacticalIDPrefix);

  metaProfile.readString(IDSection,  UsrCallKey,  userCallSign);
  metaProfile.readString(IDSection,  UsrNameKey,  userName);
  metaProfile.readString(IDSection,  UsrIDKey,    userIDPrefix);

  metaProfile.readString(RptSection, OrgKey,      organization);
  metaProfile.readString(RptSection, CityKey,     city);
  metaProfile.readString(RptSection, CountyKey,   county);
  metaProfile.readString(RptSection, StateKey,    state);
  metaProfile.readString(RptSection, TacLocKey,   tacticalLocation);
  metaProfile.readString(RptSection, Text2Key,    textVariable2);
  metaProfile.readString(RptSection, Text3Key,    textVariable3);
  metaProfile.readString(RptSection, TaskIDKey,   taskID);
  metaProfile.readString(RptSection, TaskNameKey, taskName);
  }


void IdentityInfo::writeMetaFile() {

  metaProfile.writeString(  IDSection,  UsrCallKey,     userCallSign);
  metaProfile.writeString(  IDSection,  UsrNameKey,     userName);
  metaProfile.writeString(  IDSection,  UsrIDKey,       userIDPrefix);
  metaProfile.writeInt(     IDSection,  TCnPEnabledKey, isTacticalID);

  metaProfile.writeString(  IDSection,  TacCallKey,     tacticalCallSign);
  metaProfile.writeString(  IDSection,  TacNameKey,     tacticalText);
  metaProfile.writeString(  IDSection,  TacIDKey,       tacticalIDPrefix);
  if (isTacticalID) {
    metaProfile.writeString(IDSection,  ActMyCallKey,   tacticalCallSign);
    metaProfile.writeString(IDSection,  ActMyNameKey,   tacticalText);
    metaProfile.writeString(IDSection,  ActMyIDKey,     tacticalIDPrefix);
    }
  else {
    metaProfile.writeString(IDSection,  ActMyCallKey,   userCallSign);
    metaProfile.writeString(IDSection,  ActMyNameKey,   userName);
    metaProfile.writeString(IDSection,  ActMyIDKey,     userIDPrefix);
    }
  metaProfile.writeString(  RptSection, OrgKey,         organization);
  metaProfile.writeString(  RptSection, CityKey,        city);
  metaProfile.writeString(  RptSection, CountyKey,      county);
  metaProfile.writeString(  RptSection, StateKey,       state);
  metaProfile.writeString(  RptSection, TacLocKey,      tacticalLocation);
  metaProfile.writeString(  RptSection, Text2Key,       textVariable2);
  metaProfile.writeString(  RptSection, Text3Key,       textVariable3);
  metaProfile.writeString(  RptSection, TaskIDKey,      taskID);
  metaProfile.writeString(  RptSection, TaskNameKey,    taskName);
  }





// Various Formats for raw message subject lines:
//
// <message-number>_O/R_Check-In <TacticalCallSign>, <TacticalName>
// <message-number>_O/R_Check-In <FCCCallSign>, <FullName>
// <message-number>_O/R_Check-in <date> - <FCCCallSign> - <first-name> - <city-or-agency>
// <message-number>_<Severity>/<HandlingOrder>_<Subject>
// Or if Option SubjWSecurity is false
// <message-number>_<HandlingOrder>_<Subject>

void IdentityInfo::createSubjLine(String& stg) {
String           subj     = subject;
bool             weekly   = false;
bool             hndlg    = true;
bool             stdSubj  = false;
bool             bareSubj = false;
//CString          stg;

  switch (subjStyle) {
    case 0  : hndlg    = false;        // Form (fall thru to set weekly)
    case 1  : weekly   = true; break;  // New Message
    case 2  : stdSubj  = true; break;
    default : bareSubj = true; break;
    }

  if (hndlg) {
    stg += _T("_");
    if (subjWSecurity) {
      switch (severity) {
        case 0  : stg += _T("E/"); break;
        case 1  : stg += _T("U/"); break;
        default : stg += _T("O/"); break;
        }
      }
    switch (handling) {
      case 0  : stg += _T("I"); break;
      case 1  : stg += _T("P"); break;
      default : stg += _T("R"); break;
      }
    stg += _T("_");
    }

  subj.trim();   stg += subj;

  if (!bareSubj) {

    stg += _T(" ");

    if (isTacticalID)
         {stg += tacticalCallSign;   stg += _T(", ");   stg += tacticalText;}
    else {stg += userCallSign;       stg += _T(", ");   stg += userName;}

    if (weekly) {stg += _T(", "); stg += city; stg += _T(", ");}

    if (weekly) {
      COleDateTime     ctm         = COleDateTime::GetCurrentTime();
      double           dayOfWeek   = (double) ctm.GetDayOfWeek();
      double           practice    = practiceDay + 2.0;
      double           delta       = practice - dayOfWeek;    if (delta < 0) delta += 7.0;

      if (delta != 0.0) {COleDateTimeSpan span( delta); ctm += span;}

      stg += ctm.Format(_T("%x"));
      }
    }
  }

