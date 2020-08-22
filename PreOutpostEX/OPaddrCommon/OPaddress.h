// OPaddress.h : main header file for the PROJECT_NAME application


#pragma once


class OPaddress : public CWinApp {
public:

String      myPath;                             // Path to this program when running
String      addrPath;                           // Path to Outpost address book directory
String      acroRd;
STARTUPINFO startUpInfo;

  OPaddress();

  virtual BOOL    InitInstance();
          void    getProfilePath();
          int     doDlg();

          String& getAcroRd();

  DECLARE_MESSAGE_MAP()

  afx_msg void OnOutpostFindPath();
  };


extern OPaddress theApp;
