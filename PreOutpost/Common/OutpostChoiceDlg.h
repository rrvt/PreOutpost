// Pick Outpost to use from PreOutpost


#pragma once
#include "IniFile.h"
#include "Resource.h"

// Outpost Choice dialog

class OutpostChoiceDlg : public CDialogEx {

  DECLARE_DYNAMIC(OutpostChoiceDlg)

public:

CListBox outpostList;
CString  outpostChoice;
String   confFilePath;
String   exeFilePath;

               OutpostChoiceDlg(CWnd* pParent = nullptr);
  virtual     ~OutpostChoiceDlg();

  virtual BOOL OnInitDialog();
  virtual void OnOK();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_OutpostChoice };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);

  DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedCancel();
};
