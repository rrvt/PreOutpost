// OpAddr.h -- Template for a Dialog Box Application


#include "pch.h"
#include "OpAddr.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "OpAddrDlg.h"
#include "Outpost.h"
#include "ProgramFiles.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


OpAddr  theApp;                           // The one and only OpAddr object
IniFile iniFile;


// OpAddr construction

OpAddr::OpAddr() noexcept : CApp(this) { }


// OpAddr initialization -- Start the MFC Dialog Box
// OpAddr.exe \"C:\\Program Files (x86)\\SCCo Packet\\ \" \"D:\\SCCoPacket\\ \"

BOOL OpAddr::InitInstance() {
LPWSTR*   szArglist;
int       nArgs;
int       i;
OpAddrDlg dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);

  if (szArglist ) for (i = 0; i < nArgs && i < noElements(cmdLine); i++)
                             {cmdLine[i] = szArglist[i];   cmdLine[i].trim();   addBackSlash(cmdLine[i]);}
  LocalFree(szArglist);

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  outpost.initialize(cmdLine[1], cmdLine[2]);

  GetStartupInfo(&startUpInfo);

  dlg.DoModal();   m_pMainWnd = 0;   return 0;
  }


void OpAddr::addBackSlash(String& path) {
int pos = path.length()-1;

  if (path[pos] != _T('\\')) path += _T('\\');
  }


int OpAddr::ExitInstance() {return CWinApp::ExitInstance();}

