// PreOutpost.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "PreOutpost.h"
#include "BBSinfo.h"
#include "ClipBoard.h"
#include "filesrch.h"
#include "filename.h"
#include "FindDirThrd.h"
#include "FileName.h"
#include "GetPathDlg.h"
#include "Help.h"
#include "IdentityDlg.h"
#include "iniFileEx.h"
#include "DelMasterDlg.h"
#include "MasterProf.h"
#include "MasterMgmtDlg.h"
#include "NewMaster.h"
#include "Outpost.h"
#include "ProgramFiles.h"
#include "ResourceData.h"
#include "ThreadBase.h"
#include "Utilities.h"


static TCchar* PathSection   = _T("Path");
static TCchar* DataPathKey   = _T("Data");
static TCchar* DBDataPathKey = _T("DBdata");
static TCchar* ProfileKey    = _T("Profile");
static TCchar* OutpostKey    = _T("Outpost");


PreOutpost   theApp;                         // The one and only PreOutpost object
IniFileEx    iniFile(theApp);                // Implements Read/Write to Private Profile File
BBSinfo      bbsInfo;
ProgramFiles programFiles;                   // The one and only program Files object
MasterProf   masterProf;


// PreOutpost

BEGIN_MESSAGE_MAP(PreOutpost, CWinAppEx)
END_MESSAGE_MAP()


// PreOutpost initialization
// This program uses it's own INI file, see IniFileEx.h for details.
// Collect ID and Report information from the user in the dialog box and create new Outpost
// Profiles from the information.  If there is no Master Profile, create one.  If there is only
// one Master Profile then collect the identity info and start Outpost.  If there are two or more,
// then select one or all Master Profiles.  One additional choice is included with the ID and
// Report Information, whether profiles for all six BBSes or just W1XSC should be created.

BOOL PreOutpost::InitInstance() {
bool      makeMaster;                 // When true make a Master Profile
String    s;
ClipBoard clipBoard;
String    path;

  CWinAppEx::InitInstance();

  makeMaster = !StrCmp(m_lpCmdLine, _T("/MakeMaster")) || !StrCmp(m_lpCmdLine, _T("-MakeMaster"));

  helpFile = m_pszHelpFilePath;    help.init(helpFile);
  myPath   = getPath(m_pszHelpFilePath);
  iniFile.getAppDataPath(m_pszHelpFilePath);
  dataPath = getDataPath();

  m_pMainWnd = 0;

  if (!outpost.getProfilePath()) return 1;

  masterProf.readIniFile();

  idInfo.usrData.initialize();
  idInfo.tacData.initialize();

  bbsInfo.load();

  if (makeMaster || !masterProf.nMasters()) {NewMaster newMaster;  newMaster();}

  if (!masterProf.process(masterProf.select())) return 0;

  idInfo.createSubjLine(subjectLine);

  if (idInfo.includeAddrBook) startOPaddress();

  clipBoard.load(subjectLine);

  startOutpost();

  idInfo.clearOldProfiles(_T("*"));

  if (idInfo.includeAddrBook) opAddrExe.stop();

  return 0;
  }


bool PreOutpost::startOPaddress() {
String cmd   = myPath + _T("OpAddrBk.exe");

String opDir = outpost.getPath();
String prDir = outpost.getProfile();

  return opAddrExe.start(3, cmd.str(), opDir.str(), prDir.str());
  }


void PreOutpost::startOutpost()
    {Executable outpostExe;   if (outpostExe.start(1, outpost.getPath().str())) outpostExe.wait();}


// Just exit.

int PreOutpost::ExitInstance() {return CDialogApp::ExitInstance();}


String PreOutpost::getDataPath() {
String path;

#ifdef _DEBUG
  if (!iniFile.read(PathSection, DBDataPathKey, path)) {

    if (getDirPathDlg(_T("Debug Store Path"), path) && !path.isEmpty())
                                                   iniFile.write(PathSection, DBDataPathKey, path);

    else {
      path = iniFile.getAppDataPath(m_pszHelpFilePath);

      iniFile.write(PathSection, DataPathKey, path);
      }
    }
#else

  if (!iniFile.read(PathSection, DataPathKey, path) || path.isEmpty()) {
    path = iniFile.getAppDataPath(m_pszHelpFilePath);

    iniFile.write(PathSection, DataPathKey, path);
    }
#endif

  return path;
  }


///------------------------

#if 0
#if 1
#else
String    configPath;                // Path to several files in Roaming (useful for debugging

  myPath = getPath(m_pszHelpFilePath);

  helpFile = myPath + _T("PreOutpost.chm");

#ifdef _DEBUG
  configPath = myPath + _T("PreOutpostDbg.exe");
#else
  configPath = helpFile;
#endif

  dataPath = iniFile.getAppDataPath(configPath);
#endif
#endif

