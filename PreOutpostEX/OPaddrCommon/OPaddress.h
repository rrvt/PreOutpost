
// OPaddress.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
  #error _T("include 'stdafx.h' before including this file for PCH")
#endif

#include "resource.h"   // main symbols


// OPaddressApp:
// See OPaddress.cpp for the implementation of this class
//

class OPaddressApp : public CWinApp {
public:

String      myPath;                             // Path to this program when running
String      addrPath;                           // Path to Outpost address book directory
String      acroRd;
STARTUPINFO startUpInfo;

  OPaddressApp();

  virtual BOOL    InitInstance();
          void    getProfilePath();
          int     doDlg();

          String& getAcroRd();

// Implementation

  DECLARE_MESSAGE_MAP()

  afx_msg void OnOutpostFindPath();
  };


extern OPaddressApp theApp;
