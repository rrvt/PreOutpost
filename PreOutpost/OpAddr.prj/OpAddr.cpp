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
Executable exe;
int        i;
ArgIter    iter(exe);
String*    arg;
String     args[5];

OpAddrDlg  dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  exe.procArgs(m_lpCmdLine);

  for (arg = iter(), i = 0; arg && i < noElements(args); i++, arg = iter++)
                                         {String& s = args[i];   s = *arg;   s.trim();   addBackSlash(s);}

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  outpost.initialize(args[0], args[1]);

  dlg.DoModal();   m_pMainWnd = 0;   return 0;
  }


void OpAddr::addBackSlash(String& path) {
int pos = path.length()-1;   if (pos < 0) return;

  if (path[pos] != _T('\\')) path += _T('\\');
  }


int OpAddr::ExitInstance() {return CWinApp::ExitInstance();}



#if 1
#else
  LPWSTR*    szArglist;
  int        nArgs;
  int        i;
  szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);

  if (szArglist ) for (i = 0; i < nArgs && i < noElements(args); i++)
                             {args[i] = szArglist[i];   args[i].trim();   addBackSlash(args[i]);}
  LocalFree(szArglist);
#endif

