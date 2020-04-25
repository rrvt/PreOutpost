// OPaddress.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "OPaddress.h"
#include "FilePaths.h"
#include "filename.h"
#include "filesrch.h"
//#include "FindProfilePath.h"
#include "IniFile.h"
#include "OPaddressDlg.h"
#include "ProgramFiles.h"
#include "Resources.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static TCchar* PathSection = _T("Path");
static TCchar* ProfileKey  = _T("Profile");
static TCchar* OutpostKey  = _T("Outpost");
static TCchar* AcroRdKey   = _T("AcroRdPath");


// The one and only OPaddressApp object

OPaddressApp theApp;
IniFile      iniFile;                             // Implements Read/Write to Private Profile File


// OPaddressApp

BEGIN_MESSAGE_MAP(OPaddressApp, CWinApp)
  ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
  ON_COMMAND(ID_OUTPOST_FINDPATH, &OPaddressApp::OnOutpostFindPath)
END_MESSAGE_MAP()


// OPaddressApp Construction

OPaddressApp::OPaddressApp() {
ResourceData res;
String       appID;

  if (res.getAppID(appID)) SetAppID(appID);

  m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
  }


// OPaddressApp initialization

BOOL OPaddressApp::InitInstance() {

//  helpFile   = getPath(m_pszHelpFilePath);  helpFile += _T("PreOutpost.chm");

  iniFile.getAppDataPath(m_pszHelpFilePath);

  myPath = getPath(m_pszHelpFilePath);

  outputPaths.getProfilePath();   addrPath = outputPaths.profilePath + _T("addr.d\\");

  // InitCommonControlsEx() is required on Windows XP if an application
  // manifest specifies use of ComCtl32.dll version 6 or later to enable
  // visual styles.  Otherwise, any window creation will fail.

  INITCOMMONCONTROLSEX InitCtrls;
  InitCtrls.dwSize = sizeof(InitCtrls);

  // Set this to include all the common control classes you want to use
  // in your application.

  InitCtrls.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx(&InitCtrls);

  CWinApp::InitInstance();

  AfxEnableControlContainer();

  // Create the shell manager, in case the dialog contains
  // any shell tree view or shell list view controls.

  CShellManager *pShellManager = new CShellManager;

  // Activate "Windows Native" visual manager for enabling themes in MFC controls

  CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

  GetStartupInfo(&startUpInfo);

  if (doDlg() == -1) {

    TRACE(traceAppMsg, 0,
                  _T("Warning: dialog creation failed, so application is terminating unexpectedly.\n"));
    TRACE(traceAppMsg, 0, _T("Warning: if you are using MFC controls on the dialog, ")
                                           _T("you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n"));
    }

  // Delete the shell manager created above.
  if (pShellManager != nullptr) {delete pShellManager;}

  #if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
    ControlBarCleanUp();
  #endif

  // Since the dialog has been closed, return FALSE so that we exit the
  //  application, rather than start the application's message pump.

  return FALSE;
  }


String& OPaddressApp::getAcroRd() {
FilePaths filePaths;
String*   path;

  if (!iniFile.readString(PathSection, AcroRdKey, acroRd)) {

    if (filePaths.findFiles(_T("C:"), _T("Program*"), _T("AcroRd32.exe"))) {
      for (path = filePaths.startLoop(); path; path = filePaths.nextPath()) {

        String   eula = getPath(path->str());
        FileSrch eulaPath;
        String   name;
        if (eulaPath.findFiles(eula, _T("*Eula.exe")) && eulaPath.getName(name)) {acroRd = *path; break;}
        }
      }

    if (!acroRd.isEmpty()) iniFile.writeString(PathSection, AcroRdKey, acroRd);
    }

  return acroRd;
  }


int OPaddressApp::doDlg() {
OPaddressDlg dlg;

  addresses.load();

  m_pMainWnd = &dlg;   return dlg.DoModal();
  }




void OPaddressApp::OnOutpostFindPath() {
  outputPaths.choose();   addrPath = outputPaths.profilePath + _T("addr.d\\");
  }



#if 0
                        findDir(_T("C:"),    _T("Program*"), _T("*Adobe\\\\"),    adobePath)  &&
        findDir(adobePath,   _T("*Reader*"), _T("*Reader\\\\"),   readerPath) &&
//      findDir(readerPath,  _T("*"),        _T("*Reader\\\\"),   readerPath) &&
#endif


#if 0
// We've already opened the INI file for PreOutpost.  See if we've found the paths to the Outpost
// Executable and Profiles stored them in the INI file.  If not, then find the paths and store them.
// The paths are stored in the PreOutpost object.

void OPaddressApp::getProfilePath() {
  if (!iniFile.readString(PathSection, ProfileKey, profilePath)  ||
      !iniFile.readString(PathSection, OutpostKey, outpostPath)) {
    if (findProfilePaths(profilePath, outpostPath)) {
      iniFile.writeString(PathSection, ProfileKey, profilePath);
      iniFile.writeString(PathSection, OutpostKey, outpostPath);
      }
    }
  profilePath += _T('\\');
  }
#endif

