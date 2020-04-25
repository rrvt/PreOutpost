// OPaddressDlg.h : header file


#pragma once
//#include "Addresses.h"
#include "ListBox.h"
#include "LogFile.h"


// OPaddressDlg dialog

class OPaddressDlg : public CDialogEx {

static int baseUnits;

int        dataTab;
int        dx1;
RECT       dlgRect;
RECT       cltRect;
RECT       hdrRect;
RECT       r;

public:

LogFile    logFile;
CString    virtAddr;
CString    realAddr;

CStatic    header;


CStatic    hdr1;
ListBox listBox;

  OPaddressDlg(CWnd* pParent = nullptr);  // standard constructor

  // Dialog Data
  #ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_OPADDRESS_DIALOG };
  #endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support

// Implementation

protected:
  HICON m_hIcon;

  // Generated message map functions
  virtual BOOL OnInitDialog();


  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnAbout();
  afx_msg void OnRefresh();

private:

  void setTabStops();
  void loadAddresses();
  void positionHdr1();
  void showPDF(TCchar* name);


public:
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnMove(int x, int y);
  afx_msg void OnTest();
  afx_msg void OnSaveall();
  afx_msg void OnAddrdelete();
  afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
  afx_msg void OnDblclkList();
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  afx_msg void OnAddressEdit();
  afx_msg void OnAddressNew();
  virtual void OnCancel();
  virtual void OnOK();
  afx_msg void OnClose();
  afx_msg void OnRoutingForm();
  afx_msg void OnRoutingHelp();
};



