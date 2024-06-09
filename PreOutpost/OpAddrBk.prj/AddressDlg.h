#pragma once


// AddressDlg dialog

class AddressDlg : public CDialogEx {

  DECLARE_DYNAMIC(AddressDlg)

enum    MsgEnum {BadCharsMsg, ExistsMsg, DeletedMsg, NilMsg};

CStatic versionCtl;
CStatic MessageCtrl;
CEdit   nameCtrl;
CEdit   orgLocCtrl;
MsgEnum msgSeen;

public:

String  path;                                              // Path to files, needed to verify name
bool    isNewAddr;
bool    isDeleted;

CString version;
CString title;
CString name;
CString organization;
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

          bool showMsg(MsgEnum x);
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
  afx_msg void onDelete();
  virtual void OnOK();
  virtual void OnCancel();
  };
