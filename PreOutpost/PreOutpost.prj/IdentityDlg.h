// IdentityDlg dialog


#pragma once
#include "resource.h"
#include "afxwin.h"



class IdentityDlg : public CDialog {

  DECLARE_DYNAMIC(IdentityDlg)

CMenu*  menu;

public:

String  title;
String  todaysDate;

bool    subjWSecurity;
bool    includeAddrBook;
bool    tacticalModified;

bool    isTacticalID;
CString tacticalCallSign;
CString tacticalText;
CString tacticalIDPrefix;
CString tacSignature;

bool    userModified;

CString userCallSign;
CString userName;
CString userIDPrefix;
CString userSignature;

int     profilesDesired;

// Report Settings
CString organization;
CString city;
CString county;
CString state;
CString tacticalLocation;
CString textVariable2;
CString textVariable3;
CString taskID;
CString taskName;
CString subject;
int     subjStyle;
int     practiceDay;
int     severity;
int     handling;

           IdentityDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~IdentityDlg();

// Dialog Data
  enum { IDD = IDD_IdentityDialog };

protected:

  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  void initTactical(CButton* tactical, bool state);
  void enableTactical(bool enable);
  void enableCtrl(int id, bool enable);

  bool isNotEqual(CString& s, int x);

  DECLARE_MESSAGE_MAP()

private:

  void setSubjWSecurity();
  void setIncludeAddrBook();

public:
  afx_msg void OnTacticalBnClicked();
  afx_msg void OnTacCallLoseFoc();
  afx_msg void OnTacCallModA();
  afx_msg void OnTacCallModB();
  afx_msg void OnTacCallModC();
  afx_msg void OnFCCCallLoseFoc();
  afx_msg void OnFCCCallModA();
  afx_msg void OnFCCCallModB();
  afx_msg void OnFCCCallModC();

  afx_msg void OnSetBBSsuffixes();

  afx_msg void OnAbout();
  afx_msg void OnHelpOverview();
  afx_msg void OnHelpIdentity();
  afx_msg void OnSubjWSecurity();
  afx_msg void OnFindOutpost();
  afx_msg void OnIncludeAddrBook();
  afx_msg void OnHelpAddressbook();
  afx_msg void OnHelpDeleteMaster();
  afx_msg void OnHelpSelNewMaster();
  afx_msg void OnHelpSelectProfile();
  };
