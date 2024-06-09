// OpAddrBk.h -- Template for a Dialog Box Application


#include "pch.h"
#include "OpAddrBk.h"
#include "Executable.h"
#include "OpAddrBkDlg.h"
#include "Outpost.h"
#include "IniFile.h"
#include "Utilities.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


OpAddrBk theApp;                         // The one and only OpAddrBk object
IniFile   iniFile;


// OpAddrBk construction

OpAddrBk::OpAddrBk() noexcept : CApp(this) { }


// OpAddrBk initialization -- Start the MFC Dialog Box

BOOL OpAddrBk::InitInstance() {
Executable  exe;

int         i;
ArgIter     iter(exe);
String*     arg;
String      args[5];

OpAddrBkDlg dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  exe.procArgs(m_lpCmdLine);

  for (arg = iter(), i = 0; arg && i < noElements(args); i++, arg = iter++)
                              {String& s = args[i];   s = *arg;   s.trim();   utl.addBackSlash(s);}

  outpost.initialize(args[0], args[1]);

  dlg.DoModal();

  m_pMainWnd = 0;   return 0;
  }


int OpAddrBk::ExitInstance() {return CWinApp::ExitInstance();}

