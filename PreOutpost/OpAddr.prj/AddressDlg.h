#pragma once


// AddressDlg dialog

class AddressDlg : public CDialogEx {

  DECLARE_DYNAMIC(AddressDlg)

CStatic versionCtl;
CStatic MessageCtrl;
CEdit   nameCtrl;
CEdit   orgLocCtrl;
bool    msgSeen;

public:

String  path;                                                   // Path to files, needed to verify name
bool    isNewAddr;

CString version;
CString title;
CString name;
CString orgLoc;
CString actual;
CString notes;
CString cellPhone;
CString homePhone;
CString businessPhone;
CString agency1Name;
CString agency1Phone;
CString agency2Name;
CString agency2Phone;
CString moreNotes;

               AddressDlg(CWnd* pParent = nullptr);            // standard constructor
  virtual     ~AddressDlg();

  virtual BOOL OnInitDialog();

          void showMsg(TCchar* msg);
          void hideMsg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Address };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onLeaveName();
  afx_msg void OnBnClickedOk();
  };
