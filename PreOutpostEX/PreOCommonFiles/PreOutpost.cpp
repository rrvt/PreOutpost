
// PreOutpost.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#ifndef Win2K
#include "afxwinappex.h"
#endif
#include "PreOutpost.h"
#include "MainFrm.h"
#include "BBSsuffix.h"
#include "CopyFile.h"
#include "DeleteMasterProfile.h"
#include "DialogBar.h"
#include "filesrch.h"
#include "filename.h"
#include "IdentityDialog.h"
#include "DeleteMasterProfile.h"
#include "LoadScratchPad.h"
#include "MasterProfile.h"
#include "ManageMasterProfiles.h"
#include "MessageBox.h"
#include "OutpostChoiceDlg.h"
#include "Resources.h"
#include <TlHelp32.h>


static TCchar* PathSection = _T("Path");
static TCchar* ProfileKey  = _T("Profile");
static TCchar* OutpostKey  = _T("Outpost");


PreOutpost theApp;                          // The one and only PreOutpost object
IniFile    iniFile;                         // Implements Read/Write to Private Profile File


static bool pathFileExists(TCchar* s);


// PreOutpost

BEGIN_MESSAGE_MAP(PreOutpost, CWinApp)
END_MESSAGE_MAP()


// PreOutpost construction

PreOutpost::PreOutpost() : subjWSecurity(false), includeAddrBook(false), makeMaster(false),
                                              usrData(_T("usr")), tacData(_T("tac")), nMetaProfiles(0) {
ResourceData res;
String       appID;

  if (res.getAppID(appID)) SetAppID(appID);
  }


// PreOutpost initialization
// This program uses it's own INI file, see IniFile.h for details.

BOOL PreOutpost::InitInstance() {

#ifdef Win2K
  makeMaster = !strcmp(m_lpCmdLine, _T("/MakeMaster")) || !strcmp(m_lpCmdLine, _T("-MakeMaster"));
#else
  makeMaster = !StrCmp(m_lpCmdLine, _T("/MakeMaster")) || !StrCmp(m_lpCmdLine, _T("-MakeMaster"));
#endif

  myPath = helpFile = getPath(m_pszHelpFilePath);  helpFile += _T("PreOutpost.chm");

  roamingPath = iniFile.getAppDataPath(helpFile);

  CWinApp::InitInstance();

  // To create the main window, this code creates a new frame window
  // object and then sets it as the application's main window object

  MainFrame* pFrame = new MainFrame;   if (!pFrame) return FALSE;

  m_pMainWnd = pFrame;

  // create and load the frame with its resources

  pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

  GetStartupInfo(&startUpInfo);

  // The one and only window has been initialized, but implement the program with dialog boxes
  // and then quit...

  outputPaths.getProfilePath();
  getMetaProfiles();

  usrData.initialize(outputPaths.profilePath);
  tacData.initialize(outputPaths.profilePath);

  bbsInfo.load();

  if (makeMaster) createNewMaster();

#ifdef NewDialog
  else            testNewDialog();
#else
  else            updateIDMakeProfile();
#endif

  return false;

  // Apparently opening multiple dialog boxes requires at least the semblance of a windows program.
  // However, we don't actually need to show the window...

  pFrame->SetWindowPos(&CWnd::wndTopMost, 200, 200, 600, 600, SWP_NOMOVE);

  pFrame->ShowWindow(SW_SHOW); pFrame->UpdateWindow();

  return TRUE;
  }



void PreOutpost::testNewDialog() {
IdentityDialog idDialog;

  if (idDialog.DoModal() !=  IDOK) return;

  bbsInfo.save();
  }



// Read .ini file for all meta profiles, checking that they are still available and correcting .ini file
// in the process

void PreOutpost::getMetaProfiles() {
int    n;
String metaProfile;
int    i;
bool   missing = false;

  nMetaProfiles = 0;
  n = iniFile.readInt(_T("MetaProfiles"), _T("nMetaProfiles"), 0);

  if (!n) {
    if (iniFile.readString(PathSection, _T("MetaProfile"), metaProfilePath[nMetaProfiles])) {
      missing = true; nMetaProfiles++;
      iniFile.writeString(PathSection, _T("MetaProfile"), String(_T("")));
      }
    }

  for (i = 0; i < n; i++) {

    getMetaName(i, metaProfile);

    if (!iniFile.readString(_T("MetaProfiles"), metaProfile, metaProfilePath[nMetaProfiles]))
      {missing = true; continue;}

    if (metaProfilePath[nMetaProfiles].empty()) {missing = true; continue;}

    if (!pathFileExists(metaProfilePath[i].str())) {missing = true; continue;}

    nMetaProfiles++;
    }

  if (missing) setMetaProfiles(n);
  }


// Display a dialog box to create or delete a Master Profile.

void PreOutpost::createNewMaster() {
int                  i;
int                  j;
int                  rslt;
String               mProfileName;
String               selectedProfile;
ManageMasterProfiles manageProfiles;

  for (i = 0; i < nMetaProfiles; i++) {
    mProfileName = removePath(metaProfilePath[i]);

    manageProfiles.addListBoxItem(mProfileName);
    }

  rslt = manageProfiles.DoModal();
  if (rslt == CreateMaster) {OnSelectMasterProfile(); return;}
  if (rslt != DeleteMaster || nMetaProfiles <= 0) return;

  // Delete MetaProfile Selected

  selectedProfile = manageProfiles.getListBoxSelection();

  mProfileName = roamingPath; mProfileName += selectedProfile;

  DeleteMasterProfile delMasterProfile;

  delMasterProfile.MasterProfileName = selectedProfile.str();

  if (delMasterProfile.DoModal() == IDCANCEL) return;

  if (pathFileExists(mProfileName.str())) removeFile(mProfileName.str());

  clearOldProfiles(getMainName(mProfileName));

  for (i = 0; i < nMetaProfiles; i++) {
    if (mProfileName == metaProfilePath[i]) break;
    }

  if (i < nMetaProfiles) {
    metaProfilePath[i].clear();

    for (j = i+1; j < nMetaProfiles; j++, i++) {
      metaProfilePath[i] = metaProfilePath[j];
      }
    nMetaProfiles--;
    }

  setMetaProfiles(nMetaProfiles+1);

  return;
  }


bool pathFileExists(TCchar* s) {
#ifdef Win2K
  FILE* lu;
  int   e = fopen_s(&lu, s, _T("r"));  if (!e) fclose(lu);

    return !e;

#else

  return PathFileExists(s) == TRUE;

#endif
  }


// Find all the Outpost profiles that have not been created by this program.  Put them in a Dialog list
// box.  Choose one for the new Master Profile, make a copy in this programs directory and insert the name
// in the INI file for this program.  The insertion is done so that the list remains sorted.

void PreOutpost::OnSelectMasterProfile() {
FileSrch  fileSrch;
String    profile;
String    profileName;
RegExpr   re;
DialogBar dialogBar;
String    selection;
String    selected;
String    newMetaProfile;
String    metaProfileName;
String    metaLabel;

  fileSrch.findFiles(outputPaths.profilePath, _T("*.profile"));

  re.setWildCardPattern(_T("~*~W*~"));

  while (fileSrch.getName(profile)) {

    profileName = getMainName(profile.str());    if (re.match(profileName)) continue;

    dialogBar.addListBoxItem(removePath(profile));
    }

  if (dialogBar.DoModal() != IDOK) return;

  selected = dialogBar.getListBoxSelection();
  selection += outputPaths.profilePath;
  selection += selected;
  newMetaProfile = roamingPath + selected;

  if (!change_extension(newMetaProfile, _T("MProfile"))) return;

  copyFile(selection, newMetaProfile);

  if (insertNewProfile(newMetaProfile)) setMetaProfiles(nMetaProfiles);
  }


// Collect ID and Report information from the user in the dialog box and create new Outpost Profiles
// from the information.  If there is no Master Profile, create one.  If there is only one Master Profile
// then collect the identity info and start Outpost.  If there are two or more, then select one or all
// Master Profiles.  One additional choice is included with the ID and Report Information, whether
// profiles for all six BBSes or just W1XSC should be created.

void PreOutpost::updateIDMakeProfile() {
int    i;
String mProfileName;
String selectedProfile;

  if (nMetaProfiles == 0) {createNewMaster(); return;}

  if (nMetaProfiles == 1) {

    metaProfPath = metaProfilePath[0];

    if (!getIdentityInfo(metaProfPath, false)) return;

    processMetaFile(metaProfPath);

    createSubjLine(subjectLine);
    }

  else {
    MasterProfile mProfDlg;

    mProfDlg.allMasterProfiles = 0;

    for (i = 0; i < nMetaProfiles; i++) {
      mProfileName = getMainName(metaProfilePath[i].str());
      mProfDlg.addListBoxItem(mProfileName);
      }

    if (mProfDlg.DoModal() != IDOK) {
      String err;   getError(GetLastError(), err);
      return;
      }

    mProfileName = mProfDlg.getListBoxSelection();

    if (!processMetaProfileIdentity(mProfileName, mProfDlg.allMasterProfiles)) return;
    }


  if (idInfo.includeAddrBook) startOPaddress();

  startOutpost();

  if (idInfo.includeAddrBook) killOPaddress();
  }


// Process identity for selected meta profile file, then either copy one Meta Profile or all Meta
// Profiles

bool PreOutpost::processMetaProfileIdentity(String& mProfileName, int allMasterProfiles) {
//String       metaProfPath = myPath;
int          i;

  metaProfPath = roamingPath + mProfileName; metaProfPath += _T(".MProfile");

  SubjectSection = mProfileName + _T(".Subject");

  if (!getIdentityInfo(metaProfPath, allMasterProfiles)) return false;

  if (allMasterProfiles) {
    for (i = 0; i < nMetaProfiles; i++)
                              {metaProfPath = metaProfilePath[i]; processMetaFile(metaProfPath);}
    }

  else processMetaFile(metaProfPath);

  createSubjLine(subjectLine);   return true;
  }


// Display the ID and Report Info dialog box and get the input from the user.

bool PreOutpost::getIdentityInfo(String& metaPath, int allMasterProfiles) {
IniFile        metaProfile;
IdentityDialog idDialog;

  setTitle(metaPath, allMasterProfiles, idDialog.title);

  idInfo.subjWSecurity = iniFile.readInt(  _T("Options"), _T("SubjWSecurity"),   0) != 0;
  idInfo.includeAddrBook = iniFile.readInt(_T("Options"), _T("IncludeAddrBook"), 0) != 0;
  metaProfile.setPath(metaPath);

  idInfo.isTacticalID  = metaProfile.readInt(_T("IDENTIFICATION"), _T("TCnPEnabled"), 0) != 0;
  metaProfile.readString(_T("IDENTIFICATION"), _T("TacCall"),  idInfo.tacticalCallSign);
  metaProfile.readString(_T("IDENTIFICATION"), _T("TacName"),  idInfo.tacticalText);
  metaProfile.readString(_T("IDENTIFICATION"), _T("TacID"),    idInfo.tacticalIDPrefix);

  metaProfile.readString(_T("IDENTIFICATION"), _T("UsrCall"),  idInfo.userCallSign);
  metaProfile.readString(_T("IDENTIFICATION"), _T("UsrName"),  idInfo.userName);
  metaProfile.readString(_T("IDENTIFICATION"), _T("UsrID"),    idInfo.userIDPrefix);

  metaProfile.readString(_T("REPORT TAGS"),    _T("Org"),      idInfo.organization);
  metaProfile.readString(_T("REPORT TAGS"),    _T("City"),     idInfo.city);
  metaProfile.readString(_T("REPORT TAGS"),    _T("County"),   idInfo.county);
  metaProfile.readString(_T("REPORT TAGS"),    _T("State"),    idInfo.state);
  metaProfile.readString(_T("REPORT TAGS"),    _T("TacLoc"),   idInfo.tacticalLocation);
  metaProfile.readString(_T("REPORT TAGS"),    _T("Text2"),    idInfo.textVariable2);
  metaProfile.readString(_T("REPORT TAGS"),    _T("Text3"),    idInfo.textVariable3);
  metaProfile.readString(_T("REPORT TAGS"),    _T("TaskID"),   idInfo.taskID);
  metaProfile.readString(_T("REPORT TAGS"),    _T("TaskName"), idInfo.taskName);

  idInfo.profilesDesired = 0;

  idInfo.severity    = iniFile.readInt(   SubjectSection, _T("Severity"),    2);
  idInfo.handling    = iniFile.readInt(   SubjectSection, _T("Handling"),    2);
  idInfo.subjStyle   = iniFile.readInt(   SubjectSection, _T("Style"),       0);
  idInfo.practiceDay = iniFile.readInt(   SubjectSection, _T("practiceDay"), 0);
  iniFile.readString(                     SubjectSection, _T("Subject"),     idInfo.subject);

  usrData.load(idInfo.userCallSign);
  idInfo.userName      = usrData.name; idInfo.userIDPrefix = usrData.userID;
  idInfo.userSignature = usrData.signature;

  tacData.load(idInfo.tacticalCallSign);
  idInfo.tacticalText = tacData.name; idInfo.tacticalIDPrefix = tacData.userID;
  idInfo.tacSignature = tacData.signature;

  idInfo.loadDialogBox(idDialog);

  if (idDialog.DoModal() == IDCANCEL) return false;

  idInfo.unloadDialogBox(idDialog);

  usrData.callSign = idInfo.userCallSign; usrData.name      = idInfo.userName;
  usrData.userID   = idInfo.userIDPrefix; usrData.signature = idInfo.userSignature;

  tacData.callSign = idInfo.tacticalCallSign; tacData.name      = idInfo.tacticalText;
  tacData.userID   = idInfo.tacticalIDPrefix; tacData.signature = idInfo.tacSignature;

  return true;
  }







// Various Formats for raw message subject lines:
//
// <message-number>_O/R_Check-In <TacticalCallSign>, <TacticalName>
// <message-number>_O/R_Check-In <FCCCallSign>, <FullName>
// <message-number>_O/R_Check-in <date> - <FCCCallSign> - <first-name> - <city-or-agency>
// <message-number>_<Severity>/<HandlingOrder>_<Subject>
// Or if Option SubjWSecurity is false
// <message-number>_<HandlingOrder>_<Subject>

void PreOutpost::createSubjLine(String& stg) {
String           subj     = idInfo.subject;
bool             weekly   = false;
bool             handling = true;
bool             stdSubj  = false;
bool             bareSubj = false;
//CString          stg;

  switch (idInfo.subjStyle) {
    case 0  : handling = false;        // Form (fall thru to set weekly)
    case 1  : weekly   = true; break;  // New Message
    case 2  : stdSubj  = true; break;
    default : bareSubj = true; break;
    }

  if (handling) {
    stg += _T("_");
    if (idInfo.subjWSecurity) {
      switch (idInfo.severity) {
        case 0  : stg += _T("E/"); break;
        case 1  : stg += _T("U/"); break;
        default : stg += _T("O/"); break;
        }
      }
    switch (idInfo.handling) {
      case 0  : stg += _T("I"); break;
      case 1  : stg += _T("P"); break;
      default : stg += _T("R"); break;
      }
    stg += _T("_");
    }

  subj.trim();   stg += subj;

  if (!bareSubj) {

    stg += _T(" ");

    if (idInfo.isTacticalID)
         {stg += idInfo.tacticalCallSign;   stg += _T(", ");   stg += idInfo.tacticalText;}
    else {stg += idInfo.userCallSign;       stg += _T(", ");   stg += idInfo.userName;}

    if (weekly) {stg += _T(", "); stg += idInfo.city; stg += _T(", ");}

    if (weekly) {
      COleDateTime     ctm         = COleDateTime::GetCurrentTime();
      double           dayOfWeek   = (double) ctm.GetDayOfWeek();
      double           practiceDay = idInfo.practiceDay + 2.0;
      double           delta       = practiceDay - dayOfWeek;    if (delta < 0) delta += 7.0;

      if (delta != 0.0) {COleDateTimeSpan span( delta); ctm += span;}

      stg += ctm.Format(_T("%x"));
      }
    }
  }


void PreOutpost::setTitle(String& metaPath, int allMasterProfiles, String& title) {
//CWnd*        wnd = AfxGetMainWnd();   if (!wnd) return;
String       metaName = getMainName(metaPath);
ResourceData res;
String       t;
String       pn;
String       cn;
String       ds;
String       ver;

  title = _T("FCC and Tactical Identity for ");

  title += allMasterProfiles ? _T("All Master Files") : metaName.str();

  if (res.getCompanyName(cn)) title += _T(" / ") + cn;

  if (res.getProductName(pn)) {
    if (!title.empty())       title += _T(" / ") + pn;
    else                      title = pn;
    }

  if (res.getVersion(ver))     title += _T(" / ") + ver;
  }


// Use the input ID and Report input to update the master profile.  Then update the Master File with
// the BBS name for each profile to be copied to the Outpost profile directory.

void PreOutpost::processMetaFile(String& metaPath) {

  iniFile.writeInt(         _T("Options"),        _T("SubjWSecurity"), idInfo.subjWSecurity);
  iniFile.writeInt(         _T("Options"),        _T("IncludeAddrBook"), idInfo.includeAddrBook);

  metaProfile.setPath(metaPath);

  metaProfile.writeString(  _T("IDENTIFICATION"), _T("UsrCall"),     idInfo.userCallSign);
  metaProfile.writeString(  _T("IDENTIFICATION"), _T("UsrName"),     idInfo.userName);
  metaProfile.writeString(  _T("IDENTIFICATION"), _T("UsrID"),       idInfo.userIDPrefix);
  metaProfile.writeInt(     _T("IDENTIFICATION"), _T("TCnPEnabled"), idInfo.isTacticalID);

  metaProfile.writeString(  _T("IDENTIFICATION"), _T("TacCall"),     idInfo.tacticalCallSign);
  metaProfile.writeString(  _T("IDENTIFICATION"), _T("TacName"),     idInfo.tacticalText);
  metaProfile.writeString(  _T("IDENTIFICATION"), _T("TacID"),       idInfo.tacticalIDPrefix);
  if (idInfo.isTacticalID) {
    metaProfile.writeString(_T("IDENTIFICATION"), _T("ActMyCall"),   idInfo.tacticalCallSign);
    metaProfile.writeString(_T("IDENTIFICATION"), _T("ActMyName"),   idInfo.tacticalText);
    metaProfile.writeString(_T("IDENTIFICATION"), _T("ActMyID"),     idInfo.tacticalIDPrefix);
    }
  else {
    metaProfile.writeString(_T("IDENTIFICATION"), _T("ActMyCall"),   idInfo.userCallSign);
    metaProfile.writeString(_T("IDENTIFICATION"), _T("ActMyName"),   idInfo.userName);
    metaProfile.writeString(_T("IDENTIFICATION"), _T("ActMyID"),     idInfo.userIDPrefix);
    }
  metaProfile.writeString(  _T("REPORT TAGS"),    _T("Org"),         idInfo.organization);
  metaProfile.writeString(  _T("REPORT TAGS"),    _T("City"),        idInfo.city);
  metaProfile.writeString(  _T("REPORT TAGS"),    _T("County"),      idInfo.county);
  metaProfile.writeString(  _T("REPORT TAGS"),    _T("State"),       idInfo.state);
  metaProfile.writeString(  _T("REPORT TAGS"),    _T("TacLoc"),      idInfo.tacticalLocation);
  metaProfile.writeString(  _T("REPORT TAGS"),    _T("Text2"),       idInfo.textVariable2);
  metaProfile.writeString(  _T("REPORT TAGS"),    _T("Text3"),       idInfo.textVariable3);
  metaProfile.writeString(  _T("REPORT TAGS"),    _T("TaskID"),      idInfo.taskID);
  metaProfile.writeString(  _T("REPORT TAGS"),    _T("TaskName"),    idInfo.taskName);

  iniFile.writeInt(   SubjectSection,             _T("Severity"),    idInfo.severity);
  iniFile.writeInt(   SubjectSection,             _T("Handling"),    idInfo.handling);
  iniFile.writeInt(   SubjectSection,             _T("Style"),       idInfo.subjStyle);
  iniFile.writeInt(   SubjectSection,             _T("practiceDay"), idInfo.practiceDay);
  iniFile.writeString(SubjectSection,             _T("Subject"),     idInfo.subject);

  clearOldProfiles(metaPath);

  createNewProfiles(metaPath);

  usrData.store(idInfo.userCallSign);
  tacData.store(idInfo.tacticalCallSign);
  }


// Create New Profiles as required

void PreOutpost::createNewProfiles(String& metaPath) {
int      i;
BBSdata* bbs;
String   s;

  for (i = 0; !bbsInfo.isAvailable() && i < 2; i++) {BBSSuffix bbs;  bbs.getSuffixes();}

  for (i = 0; bbs = bbsInfo.get(i); i++) {

    s  = _T("~"); s += getMainName(metaPath); s += _T("~"); s += bbs->suffix; s += _T("~.profile");

    s = outputPaths.profilePath + s;

    metaProfile.writeString(_T("GENERAL VARIABLES"), _T("BbsCName"), bbs->cName);
    metaProfile.writeString(_T("GENERAL VARIABLES"), _T("BbsFName"), bbs->fName);

    copyFile(metaPath, s);

    if (idInfo.profilesDesired) break;
    }
  }


// Delete all Outpost Profiles that contain metaName.

void PreOutpost::clearOldProfiles(String& metaPath) {
String    wildCardPat;
FileSrch  fileSrch;
RegExpr   re;
String    name;

  wildCardPat = _T("*\\~"); wildCardPat += getMainName(metaPath); wildCardPat += _T("~*~.profile");

  re.setWildCardPattern(wildCardPat);

  if (fileSrch.findFiles(outputPaths.profilePath, _T("*.profile")))
    while (fileSrch.getName(name))
      if (re.match(name)) removeFile(name);
  }


// Start Outpost -- when outpost returns clear out profiles

void PreOutpost::startOutpost() {
String              outpostDir = getPath(outputPaths.outpostPath);
PROCESS_INFORMATION processInfo;

  loadScratchPad(subjectLine);

  if (CreateProcess(outputPaths.outpostPath, 0, 0, 0, false, NORMAL_PRIORITY_CLASS, 0,
                                                              outpostDir, &startUpInfo, &processInfo))
    WaitForSingleObject(processInfo.hProcess, INFINITE);

  clearOldProfiles(String(_T("*")));
  }


bool PreOutpost::startOPaddress() {
String cmdName    = myPath;
String outpostDir = getPath(outputPaths.outpostPath);

#ifdef WinXP
  cmdName += _T("OPaddressXP.exe");
#else
  cmdName += _T("OPaddress.exe");
#endif

  return (bool) CreateProcess(cmdName, 0, 0, 0, false, NORMAL_PRIORITY_CLASS, 0,
                                                              outpostDir, &startUpInfo, &OPaddrPrcInfo);
  }



static HWND opAddrHwnd;
static BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM opAddrProcID);


void PreOutpost::killOPaddress() {

  opAddrHwnd = 0;

  if (EnumWindows(EnumWindowsProcMy, OPaddrPrcInfo.dwProcessId)) return;

  if (opAddrHwnd) SendMessage(opAddrHwnd, WM_CLOSE, 0, 0);
  }


// Called for each top-level window on the screen

BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM opAddrProcID) {
DWORD processID;

  GetWindowThreadProcessId(hwnd, &processID);

  if (processID == opAddrProcID) {opAddrHwnd = hwnd; return false;}

  return true;
  }



// Insertion sort new profile into metaProfilePath

bool PreOutpost::insertNewProfile(String& newProfile) {
int    j;
int    i;
String stg;

  for (j = 0; j < nMetaProfiles; j++) {
    if (newProfile == metaProfilePath[j]) return false;
    }

  for (j = nMetaProfiles, i = j - 1; i >= 0; j--, i--) {

    if (newProfile > metaProfilePath[i]) break;

    stg = metaProfilePath[i]; metaProfilePath[j] = stg;
    }

  metaProfilePath[j] = newProfile; nMetaProfiles++; return true;
  }


// Write Meta Profiles back into ini file after deleting

void PreOutpost::setMetaProfiles(int n) {
int i;
String metaProfile;

  iniFile.writeInt(_T("MetaProfiles"), _T("nMetaProfiles"), nMetaProfiles);

  for (i = 0; i < nMetaProfiles; i++) {

    getMetaName(i, metaProfile);

    iniFile.writeString(_T("MetaProfiles"), metaProfile, metaProfilePath[i]);
    }
  for ( ; i < n; i++) {
    getMetaName(i, metaProfile); iniFile.writeString(_T("MetaProfiles"), metaProfile, String(_T("")));
    }
  }


// Produce a Property Name to be used in an ini file.  Good for putting the Master Files in sort order
// for MetaProfile00 to MetaProfile99.  Should be enough for this program...

void PreOutpost::getMetaName(int i, String& name) {
  name = _T("MetaProfile");   if (i < 10) name += _T("0");   name += toString(i);
  }



// Just exit.

int PreOutpost::ExitInstance() {return CWinApp::ExitInstance();}

