// PreOutpost.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "PreOutpost.h"
#include "BBSinfo.h"
#include "ClipLine.h"
#include "filesrch.h"
#include "filename.h"
#include "IdentityDlg.h"
#include "DelMasterDlg.h"
#include "MasterProf.h"
#include "MasterMgmtDlg.h"
#include "NewMaster.h"
#include "Outpost.h"
#include "Resources.h"


static TCchar* PathSection = _T("Path");
static TCchar* ProfileKey  = _T("Profile");
static TCchar* OutpostKey  = _T("Outpost");


PreOutpost theApp;                          // The one and only PreOutpost object
IniFile    iniFile;                         // Implements Read/Write to Private Profile File


// PreOutpost

BEGIN_MESSAGE_MAP(PreOutpost, CWinAppEx)
END_MESSAGE_MAP()


// PreOutpost initialization
// This program uses it's own INI file, see IniFile.h for details.
// Collect ID and Report information from the user in the dialog box and create new Outpost Profiles
// from the information.  If there is no Master Profile, create one.  If there is only one Master Profile
// then collect the identity info and start Outpost.  If there are two or more, then select one or all
// Master Profiles.  One additional choice is included with the ID and Report Information, whether
// profiles for all six BBSes or just W1XSC should be created.

BOOL PreOutpost::InitInstance() {
bool   makeMaster;                                // When true make a Master Profile
String s;
  CWinApp::InitInstance();

  makeMaster = !StrCmp(m_lpCmdLine, _T("/MakeMaster")) || !StrCmp(m_lpCmdLine, _T("-MakeMaster"));

  myPath = helpFile = getPath(m_pszHelpFilePath);  helpFile += _T("PreOutpost.chm");

  roamingPath = iniFile.getAppDataPath(helpFile);

  m_pMainWnd = 0;

  outpost.getProfilePath();
  masterProf.readIniFile();

  idInfo.usrData.initialize();
  idInfo.tacData.initialize();

  bbsInfo.load();

  if (makeMaster || !masterProf.nMasters()) {NewMaster newMaster;  newMaster();}

  if (!masterProf.process(masterProf.select())) return 0;

  idInfo.createSubjLine(subjectLine);

  if (idInfo.includeAddrBook) startOPaddress();

  loadClipBoard(subjectLine);

  startOutpost();

  idInfo.clearOldProfiles(_T("*"));

  if (idInfo.includeAddrBook) opAddrExe.stop();

  return 0;
  }


bool PreOutpost::startOPaddress() {
String cmd   = myPath + _T("OpAddr.exe");

String opDir = outpost.getPath();
String prDir = outpost.getProfile();

  return opAddrExe.start(3, cmd.str(), opDir.str(), prDir.str());
  }


void PreOutpost::startOutpost()
           {Executable outpostExe;   if (outpostExe.start(1, outpost.getPath().str())) outpostExe.wait();}


// Just exit.

int PreOutpost::ExitInstance() {return CWinApp::ExitInstance();}

