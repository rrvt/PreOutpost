
// PreOutpost.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PreOutpost.h"
#include "MainFrm.h"
#include "BBSinfo.h"
#include "filesrch.h"
#include "filename.h"
#include "IdentityDlg.h"
#include "DelMasterDlg.h"
#include "LoadScratchPad.h"
#include "MasterProf.h"
#include "MasterMgmtDlg.h"
#include "MessageBox.h"
#include "NewMaster.h"
#include "OutpostChoiceDlg.h"
#include "Resources.h"
#include <TlHelp32.h>


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

BOOL PreOutpost::InitInstance() {

  makeMaster = !StrCmp(m_lpCmdLine, _T("/MakeMaster")) || !StrCmp(m_lpCmdLine, _T("-MakeMaster"));

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
  masterProf.readIniFile();

  idInfo.usrData.initialize(outputPaths.profilePath);
  idInfo.tacData.initialize(outputPaths.profilePath);

  bbsInfo.load();

  if (makeMaster || !masterProf.nMasters()) {NewMaster newMaster;  newMaster();}

  startOutpost();

  return false;

  // Apparently opening multiple dialog boxes requires at least the semblance of a windows program.
  // However, we don't actually need to show the window...

  pFrame->SetWindowPos(&CWnd::wndTopMost, 200, 200, 600, 600, SWP_NOMOVE);

  pFrame->ShowWindow(SW_SHOW); pFrame->UpdateWindow();

  return TRUE;
  }



// Collect ID and Report information from the user in the dialog box and create new Outpost Profiles
// from the information.  If there is no Master Profile, create one.  If there is only one Master Profile
// then collect the identity info and start Outpost.  If there are two or more, then select one or all
// Master Profiles.  One additional choice is included with the ID and Report Information, whether
// profiles for all six BBSes or just W1XSC should be created.

void PreOutpost::startOutpost() {
String              outpostDir;
PROCESS_INFORMATION processInfo;

  if (!masterProf.process(masterProf.select())) return;

  idInfo.createSubjLine(subjectLine);

  if (idInfo.includeAddrBook) startOPaddress();

  outpostDir = getPath(outputPaths.outpostPath);

  loadScratchPad(subjectLine);

  if (!CreateProcess(outputPaths.outpostPath, 0, 0, 0, false, NORMAL_PRIORITY_CLASS, 0,
                                                              outpostDir, &startUpInfo, &processInfo)) {
    String err;

    getError(GetLastError(), err);  messageBox(err); return;
    }
  WaitForSingleObject(processInfo.hProcess, INFINITE);


  idInfo.clearOldProfiles(String(_T("*")));

  if (idInfo.includeAddrBook) killOPaddress();
  }



bool PreOutpost::startOPaddress() {
String cmdName    = myPath;
String outpostDir = getPath(outputPaths.outpostPath);

  cmdName += _T("OPaddress.exe");

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


// Just exit.

int PreOutpost::ExitInstance() {return CWinApp::ExitInstance();}

