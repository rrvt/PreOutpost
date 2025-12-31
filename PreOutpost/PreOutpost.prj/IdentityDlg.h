// IdentityDlg dialog


#pragma once
#include "resource.h"
#include "afxwin.h"
#include "WinPos.h"



class IdentityDlg : public CDialogEx {

  DECLARE_DYNAMIC(IdentityDlg)

CMenu*  menu;

bool    isInitialized;
WinPos  winPos;                                // Position of dialog box

public:

String  title;

bool    includeAddrBook;

bool    isTacticalID;
CString tacCallSign;
CString tacText;
CString tacIDprefix;
CString tacSignature;

CString userCallSign;
CString userName;
CString userIDPrefix;
CString userSignature;
CString postSssnTxt;

bool    tacDirty;
bool    userDirty;

// Report Settings
CString reportID;
CString reportName;

CString organization;
CString city;
CString county;
CString state;
CString tacLocation;
CString textVariable2;
CString textVariable3;

CString subject;
int     handling;

int     profilesDesired;

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

  void setIncludeAddrBook();

public:

  afx_msg void onUseTactical();
  afx_msg void onLeaveTacCallSign();
  afx_msg void onLeaveTacText();

  afx_msg void onLeaveTacIDprefix();
  afx_msg void onLeaveTacIDSig();
  afx_msg void onLeaveUserCallSign();
  afx_msg void onLeaveUserName();
  afx_msg void onLeaveUserIDprefix();
  afx_msg void onLeaveUserSignature();

  afx_msg void OnSetBBSsuffixes();
  afx_msg void onPostSssnTxt();

  afx_msg void OnAbout();
  afx_msg void OnHelpOverview();
  afx_msg void OnHelpIdentity();
  afx_msg void OnFindOutpost();
  afx_msg void OnIncludeAddrBook();
  afx_msg void OnHelpAddressbook();
  afx_msg void OnHelpDeleteMaster();
  afx_msg void OnHelpSelNewMaster();
  afx_msg void OnHelpSelectProfile();

  afx_msg void OnMove(int x, int y);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  };



/////////-------------------

//int     practiceDay;
//int     severity;
//  void setSubjWSecurity();
//  afx_msg void OnSubjWSecurity();
//bool    subjWSecurity;
//int     subjStyle;
//String  todaysDate;

