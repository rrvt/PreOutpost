// Pick Outpost to use from PreOutpost


#pragma once
#include "IniFile.h"
#include "ProgramFiles.h"


// OutpostChoiceDlg dialog

class OutpostChoiceDlg : public CDialogEx {

  DECLARE_DYNAMIC(OutpostChoiceDlg)

ProgramFiles progFiles;

public:

CListBox outpostList;
CString  outpostChoice;

           OutpostChoiceDlg(CWnd* pParent = nullptr);
  virtual ~OutpostChoiceDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_OutpostChoice };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);

  DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  };
