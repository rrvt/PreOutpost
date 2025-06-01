


#pragma once
#include "findDirThrd.h"
#include "resource.h"


class WaitMsgDlg : public CDialogEx {

  DECLARE_DYNAMIC(WaitMsgDlg)

FindDirThrd thrd;

public:

           WaitMsgDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~WaitMsgDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_WaitMsg };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg LRESULT onFinFindDir(WPARAM wParam, LPARAM lParam);
  virtual BOOL OnInitDialog();
};
