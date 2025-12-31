// Post Session Text Dialog


#pragma once
#include "Resource.h"


// PostSessionDlg dialog

class PostSessionDlg : public CDialogEx {
  DECLARE_DYNAMIC(PostSessionDlg)

public:
Cstring postSssnTxt;

           PostSessionDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~PostSessionDlg();

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_PostSession };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
