// BBSdlg dialog

#pragma once
#include "resource.h"


struct BBSdlgDatum {

CString suffix;
CString fName;
CString cName;
};


class BBSdlg : public CDialog {

  DECLARE_DYNAMIC(BBSdlg)

public:

int         nData;
BBSdlgDatum data[10];

// Dialog Data

enum { IDD = IDD_SuffixDlg };

           BBSdlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~BBSdlg();

protected:

  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
