// Class corresponding to a Dialog Box to confirm deletion of a Master Profile

#pragma once
#include "resource.h"


// DelMasterDlg dialog

class DelMasterDlg : public CDialogEx {

  DECLARE_DYNAMIC(DelMasterDlg)

public:

CString MasterProfileName;

           DelMasterDlg(CWnd* pParent = NULL);            // standard constructor
  virtual ~DelMasterDlg();

// Dialog Data
  enum { IDD = IDD_DelMasterDlg };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:

  afx_msg void OnOK();
  afx_msg void OnCancel();
  afx_msg void OnAbout();
  afx_msg void OnHelpMakeMaster();
  afx_msg void OnHelpOverview();
  afx_msg void OnHelpIdentity();
  afx_msg void OnHelpAddressbook();
  afx_msg void OnHelpDeleteMaster();
  afx_msg void OnHelpSelNewMaster();
  afx_msg void OnHelpSelectProfile();
#ifdef DialogSizable01
  afx_msg void OnSize(UINT nType, int cx, int cy);
#endif
  };
