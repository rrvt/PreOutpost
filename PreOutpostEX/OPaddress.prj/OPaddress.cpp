// OPaddress.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "OPaddress.h"
#include "FilePaths.h"
#include "filename.h"
#include "filesrch.h"
#include "IniFile.h"
#include "AddrDlg.h"
#include "ProgramFiles.h"
#include "resource.h"
#include "Resources.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static TCchar* PathSection = _T("Path");
static TCchar* ProfileKey  = _T("Profile");
static TCchar* OutpostKey  = _T("Outpost");
static TCchar* AcroRdKey   = _T("AcroRdPath");


// The one and only OPaddress object

OPaddress theApp;
IniFile   iniFile;                             // Implements Read/Write to Private Profile File


// OPaddress

BEGIN_MESSAGE_MAP(OPaddress, CWinAppEx)
  ON_COMMAND(ID_HELP,             &CWinApp::OnHelp)
  ON_COMMAND(ID_OUTPOST_FINDPATH, &OPaddress::OnOutpostFindPath)
END_MESSAGE_MAP()



// OPaddress initialization

BOOL OPaddress::InitInstance() {

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

  // Activate "Windows Native" visual manager for enabling themes in MFC controls

  CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

  GetStartupInfo(&startUpInfo);

  if (doDlg() == -1) {

    TRACE(traceAppMsg, 0,
                  _T("Warning: dialog creation failed, so application is terminating unexpectedly.\n"));
    TRACE(traceAppMsg, 0, _T("Warning: if you are using MFC controls on the dialog, ")
                                           _T("you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n"));
    }

  #if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
    ControlBarCleanUp();
  #endif

  // Since the dialog has been closed, return FALSE so that we exit the
  //  application, rather than start the application's message pump.

  return FALSE;
  }


String& OPaddress::getAcroRd() {
FilePaths filePaths;
FPsIter   iter(filePaths);
String*   path;

  if (!iniFile.readString(PathSection, AcroRdKey, acroRd)) {

    if (filePaths.findFiles(_T("C:"), _T("Program*"), _T("AcroRd32.exe"))) {
      for (path = iter(); path; path = iter++) {

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


int OPaddress::doDlg() {
AddrDlg dlg;

  addresses.load();

  m_pMainWnd = &dlg;   return dlg.DoModal();
  }




void OPaddress::OnOutpostFindPath() {
  outputPaths.choose();   addrPath = outputPaths.profilePath + _T("addr.d\\");
  }

