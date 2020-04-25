// Class corresponding to a Dialog Box to confirm deletion of a Master Profile

#pragma once


// DeleteMasterProfile dialog

class DeleteMasterProfile : public CDialog {

  DECLARE_DYNAMIC(DeleteMasterProfile)

public:
  DeleteMasterProfile(CWnd* pParent = NULL);   // standard constructor
  virtual ~DeleteMasterProfile();

// Dialog Data
  enum { IDD = IDD_DeleteMasterDialog };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  CString MasterProfileName;

  afx_msg void OnOK();
  afx_msg void OnCancel();
  virtual BOOL OnInitDialog();
  afx_msg void OnAbout32778();
  afx_msg void OnHelp32777();
};
