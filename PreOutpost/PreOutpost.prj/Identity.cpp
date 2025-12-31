// Identity Info Class
// rrvt Copywrite, all rights reserved


#include "pch.h"
#include "Identity.h"
#include "BBSinfo.h"
#include "CopyFile.h"
#include "filename.h"
#include "filesrch.h"
#include "IdentityDlg.h"
#include "IniFileEx.h"
#include "PreOutpost.h"
#include "Outpost.h"
#include "ResourceData.h"


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

  userName      = usrData.name;        userIDPrefix = usrData.userID;
  userSignature = usrData.signature;   postSssnTxt  = usrData.postSssnTxt;

  tacData.load(tacCallSign);

  tacText     = tacData.name;
  tacIDprefix = tacData.userID;
  tacSignature     = tacData.signature;

  loadDialogBox(dlg);

  if (dlg.DoModal() == IDCANCEL) return false;

  unloadDialogBox(dlg);

  usrData.callSign    = userCallSign; usrData.name      = userName;
  usrData.userID      = userIDPrefix; usrData.signature = userSignature;
  usrData.postSssnTxt = postSssnTxt;

  tacData.callSign = tacCallSign; tacData.name      = tacText;
  tacData.userID   = tacIDprefix; tacData.signature = tacSignature;

  return true;
  }


// Use the input ID and Report input to update the master profile.  Then update the Master File
// with the BBS name for each profile to be copied to the Outpost profile directory.

void IdentityInfo::process(TCchar* profileName, String& metaPath) {

  writeOptions();

  metaProfile.setPath(metaPath);   writeMetaFile();

  writeSubject(profileName);

  clearOldProfiles(metaPath);

  createNewProfiles(metaPath);

  usrData.store(userCallSign);

  tacData.store(tacCallSign);
  }


static TCchar* OptSection         = _T("Options");
static TCchar* IncludeAddrBookKey = _T("IncludeAddrBook");


void IdentityInfo::readOptions() {
//  subjWSecurity   = iniFile.readInt(OptSection, SubjWSecurityKey,   0) != 0;
  includeAddrBook = iniFile.readInt(OptSection, IncludeAddrBookKey, 1) != 0;
  }


void IdentityInfo::writeOptions() {

  iniFile.writeInt(OptSection, IncludeAddrBookKey, includeAddrBook);
  }



TCchar* SubjectSfx     = _T(".Subject");
TCchar* HandlingKey    = _T("Handling");
//TCchar* StyleKey       = _T("Style");
TCchar* SubjectKey     = _T("Subject");


void IdentityInfo::readSubject(TCchar* profileName) {
String section = profileName; section += SubjectSfx;

  handling    = iniFile.readInt(section, HandlingKey,    2);
//  subjStyle   = iniFile.readInt(section, StyleKey,       0);
  iniFile.readString(           section, SubjectKey,     subject);
  }


void IdentityInfo::writeSubject(TCchar* profileName) {
String section = profileName; section += SubjectSfx;

  iniFile.writeInt(   section, HandlingKey,    handling);
//  iniFile.writeInt(   section, StyleKey,       subjStyle);
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

    s = outpost.getProfile() + s;

    metaProfile.writeString(_T("GENERAL VARIABLES"), _T("BbsCName"), bbs->cName);
    metaProfile.writeString(_T("GENERAL VARIABLES"), _T("BbsFName"), bbs->fName);

    copyFile(metaPath, s);

    if (profilesDesired) break;
    }
  }


// Delete all Outpost Profiles that contain metaName.

void IdentityInfo::clearOldProfiles(TCchar* metaPath) {
String   wildCardPat;
FileSrch fileSrch;
RegExpr  re;
String   name;

  wildCardPat = _T("*\\~"); wildCardPat += getMainName(metaPath); wildCardPat += _T("~*~.profile");

  re.setWildCardPattern(wildCardPat);

  if (fileSrch.findFiles(outpost.getProfile(), _T("*.profile")))
    while (fileSrch.getName(name))
      if (re.match(name)) removeFile(name);
  }





void IdentityInfo::loadDialogBox(IdentityDlg& dlg) {
  dlg.includeAddrBook  = includeAddrBook;
  dlg.isTacticalID     = isTacticalID;
  dlg.tacCallSign      = tacCallSign;
  dlg.tacText          = tacText;
  dlg.tacIDprefix      = tacIDprefix;
  dlg.tacSignature     = tacSignature;
  dlg.userCallSign     = userCallSign;
  dlg.userName         = userName;
  dlg.userIDPrefix     = userIDPrefix;
  dlg.userSignature    = userSignature;
  dlg.postSssnTxt      = postSssnTxt;
  dlg.organization     = organization;
  dlg.city             = city;
  dlg.county           = county;
  dlg.state            = state;
  dlg.tacLocation = tacLocation;
  dlg.textVariable2    = textVariable2;
  dlg.textVariable3    = textVariable3;
  dlg.reportID           = reportID;
  dlg.reportName         = reportName;
  dlg.profilesDesired  = profilesDesired;
  dlg.handling         = handling;
  dlg.subject          = subject;
  }


void IdentityInfo::unloadDialogBox(IdentityDlg& dlg) {
  includeAddrBook   = dlg.includeAddrBook;
  isTacticalID      = dlg.isTacticalID;
  tacCallSign  = dlg.tacCallSign;
  tacText      = dlg.tacText;
  tacIDprefix  = dlg.tacIDprefix;
  tacSignature      = dlg.tacSignature;
  userCallSign      = dlg.userCallSign;
  userName          = dlg.userName;
  userIDPrefix      = dlg.userIDPrefix;
  userSignature     = dlg.userSignature;
  postSssnTxt       = dlg.postSssnTxt;
  organization      = dlg.organization;
  city              = dlg.city;
  county            = dlg.county;
  state             = dlg.state;
  tacLocation  = dlg.tacLocation;
  textVariable2     = dlg.textVariable2;
  textVariable3     = dlg.textVariable3;
  reportID            = dlg.reportID;
  reportName          = dlg.reportName;
  profilesDesired   = dlg.profilesDesired;
  handling          = dlg.handling;
  subject           = dlg.subject;
  }


static TCchar* IDSection       = _T("IDENTIFICATION");
static TCchar* RptSection      = _T("REPORT TAGS");

static TCchar* TacCallKey      = _T("TacCall");
static TCchar* TacNameKey      = _T("TacName");
static TCchar* TacIDKey        = _T("TacID");
static TCchar* UsrCallKey      = _T("UsrCall");
static TCchar* UsrNameKey      = _T("UsrName");
static TCchar* UsrIDKey        = _T("UsrID");
static TCchar* OrgKey          = _T("Org");
static TCchar* CityKey         = _T("City");
static TCchar* CountyKey       = _T("County");
static TCchar* StateKey        = _T("State");
static TCchar* TacLocKey       = _T("TacLoc");
static TCchar* Text2Key        = _T("Text2");
static TCchar* Text3Key        = _T("Text3");
static TCchar* TaskIDKey       = _T("TaskID");
static TCchar* TaskNameKey     = _T("TaskName");
static TCchar* ActMyCallKey    = _T("ActMyCall");
static TCchar* ActMyNameKey    = _T("ActMyName");
static TCchar* ActMyIDKey      = _T("ActMyID");
static TCchar* TacCallEnbldKey = _T("TCnPEnabled");



void IdentityInfo::readMetaFile() {

  isTacticalID  = metaProfile.readInt(IDSection, TacCallEnbldKey, 0) != 0;
  metaProfile.readString(IDSection,  TacCallKey,  tacCallSign);
  metaProfile.readString(IDSection,  TacNameKey,  tacText);
  metaProfile.readString(IDSection,  TacIDKey,    tacIDprefix);

  metaProfile.readString(IDSection,  UsrCallKey,  userCallSign);
  metaProfile.readString(IDSection,  UsrNameKey,  userName);
  metaProfile.readString(IDSection,  UsrIDKey,    userIDPrefix);

  metaProfile.readString(RptSection, OrgKey,      organization);
  metaProfile.readString(RptSection, CityKey,     city);
  metaProfile.readString(RptSection, CountyKey,   county);
  metaProfile.readString(RptSection, StateKey,    state);
  metaProfile.readString(RptSection, TacLocKey,   tacLocation);
  metaProfile.readString(RptSection, Text2Key,    textVariable2);
  metaProfile.readString(RptSection, Text3Key,    textVariable3);
  metaProfile.readString(RptSection, TaskIDKey,   reportID);
  metaProfile.readString(RptSection, TaskNameKey, reportName);
  }


void IdentityInfo::writeMetaFile() {

  metaProfile.writeString(  IDSection,  UsrCallKey,      userCallSign);
  metaProfile.writeString(  IDSection,  UsrNameKey,      userName);
  metaProfile.writeString(  IDSection,  UsrIDKey,        userIDPrefix);
  metaProfile.writeInt(     IDSection,  TacCallEnbldKey, isTacticalID);

  metaProfile.writeString(  IDSection,  TacCallKey,      tacCallSign);
  metaProfile.writeString(  IDSection,  TacNameKey,      tacText);
  metaProfile.writeString(  IDSection,  TacIDKey,        tacIDprefix);
  if (isTacticalID) {
    metaProfile.writeString(IDSection,  ActMyCallKey,    tacCallSign);
    metaProfile.writeString(IDSection,  ActMyNameKey,    tacText);
    metaProfile.writeString(IDSection,  ActMyIDKey,      tacIDprefix);
    }
  else {
    metaProfile.writeString(IDSection,  ActMyCallKey,    userCallSign);
    metaProfile.writeString(IDSection,  ActMyNameKey,    userName);
    metaProfile.writeString(IDSection,  ActMyIDKey,      userIDPrefix);
    }
  metaProfile.writeString(  RptSection, OrgKey,          organization);
  metaProfile.writeString(  RptSection, CityKey,         city);
  metaProfile.writeString(  RptSection, CountyKey,       county);
  metaProfile.writeString(  RptSection, StateKey,        state);
  metaProfile.writeString(  RptSection, TacLocKey,       tacLocation);
  metaProfile.writeString(  RptSection, Text2Key,        textVariable2);
  metaProfile.writeString(  RptSection, Text3Key,        textVariable3);
  metaProfile.writeString(  RptSection, TaskIDKey,       reportID);
  metaProfile.writeString(  RptSection, TaskNameKey,     reportName);
  }


// Various Formats for raw message subject lines:
//
// <message-number>_R_Check-In <TacticalCallSign>, <TacticalName>
// <message-number>_R_Check-In <FCCCallSign>, <FullName>
// <message-number>_R_Check-in <date> - <FCCCallSign> - <first-name> - <city-or-agency>
// <message-number>_<HandlingOrder>_<Subject>

void IdentityInfo::createSubjLine(String& stg) {
String           subj     = subject;
bool             hndlg    = true;

  if (hndlg) {
    stg += _T("_");
    switch (handling) {
      case 0  : stg += _T("I"); break;
      case 1  : stg += _T("P"); break;
      default : stg += _T("R"); break;
      }
    stg += _T("_");
    }

  subj.trim();   stg += subj;

#if 0
bool             weekly   = false;
bool             stdSubj  = true;
  switch (subjStyle) {
    case 0  : hndlg    = false;        // Form (fall thru to set weekly)
    case 1  : weekly   = true; break;  // New Message
    case 2  : stdSubj  = true; break;
    default : bareSubj = true; break;
    }

  if (!bareSubj) {

    stg += _T(" ");

    if (isTacticalID)
         {stg += tacCallSign;   stg += _T(", ");   stg += tacText;}
    else {stg += userCallSign;  stg += _T(", ");   stg += userName;}

    if (weekly) {stg += _T(", "); stg += city; stg += _T(", ");}

    if (weekly) {
      COleDateTime     ctm         = COleDateTime::GetCurrentTime();
      double           dayOfWeek   = (double) ctm.GetDayOfWeek();
      double           practice    = 2.0;
      double           delta       = practice - dayOfWeek;    if (delta < 0) delta += 7.0;

      if (delta != 0.0) {COleDateTimeSpan span( delta); ctm += span;}

      stg += ctm.Format(_T("%m/%d/%Y"));
      }
    }
#endif
  }




/////////////--------
//  dlg.severity         = severity;
//  dlg.practiceDay      = practiceDay;
//  dlg.subjWSecurity    = subjWSecurity;
//static TCchar* SubjWSecurityKey   = _T("SubjWSecurity");
// Or if Option SubjWSecurity is false
//TCchar* SeverityKey    = _T("Severity");
//TCchar* PracticeDayKey = _T("PracticeDay");
//  iniFile.writeInt(   section, SeverityKey,    severity);
//  iniFile.writeInt(   section, PracticeDayKey, practiceDay);
//  severity    = iniFile.readInt(section, SeverityKey,    2);
//  practiceDay = iniFile.readInt(section, PracticeDayKey, 0);
//  iniFile.writeInt(OptSection, SubjWSecurityKey,   subjWSecurity);
#if 0
    if (subjWSecurity) {
      switch (severity) {
        case 0  : stg += _T("E/"); break;
        case 1  : stg += _T("U/"); break;
        default : stg += _T("O/"); break;
        }
      }
#endif
//CString          stg;
//  subjWSecurity     = dlg.subjWSecurity;
//  todaysDate        = dlg.todaysDate;
//  dlg.subjStyle        = subjStyle;
  //  severity          = dlg.severity;
//  subjStyle         = dlg.subjStyle;
//  practiceDay       = dlg.practiceDay;

