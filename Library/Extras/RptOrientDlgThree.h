// Set Report Printer Orientation


#pragma once
#include "PrintMgr.h"
#include "ResourceExtra.h"


class RptOrietnDlg : public CDialogEx {

  DECLARE_DYNAMIC(RptOrietnDlg)

public:

String     lbl00;
String     Lbl01;
String     Lbl02;

Cstring    ntpd;
Cstring    rpt1;
Cstring    rpt2;

CComboBox  ntpdCtl;
CComboBox  rpt1Ctl;
CComboBox  rpt2Ctl;

               RptOrietnDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual     ~RptOrietnDlg();

  virtual BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Orientation };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  void initOrietn(CComboBox& ctl, Cstring& orietn);
  };

