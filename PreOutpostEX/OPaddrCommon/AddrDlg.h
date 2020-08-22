// This is the main window of the program


#pragma once
#include "ListBox.h"
#include "LogFile.h"


// AddrDlg dialog

class AddrDlg : public CDialogEx {

static int baseUnits;

int     dataTab;
int     dx1;
RECT    dlgRect;
RECT    cltRect;
RECT    hdrRect;
RECT    r;

public:

LogFile logFile;
CString virtAddr;
CString realAddr;

CStatic header;

CStatic hdr1;
ListBox listBox;

  AddrDlg(CWnd* pParent = nullptr);

  virtual BOOL PreTranslateMessage(MSG* pMsg);
  virtual void OnCancel();
  virtual void OnOK();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_AddrDlg };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support

protected:

HICON m_hIcon;

  virtual BOOL OnInitDialog();

  DECLARE_MESSAGE_MAP()

private:

  void setTabStops();
  void loadAddresses();
  void positionHdr1();
  void showPDF(TCchar* name);

public:

  afx_msg void    OnAbout();
  afx_msg void    OnRefresh();
  afx_msg void    OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void    OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg void    OnSize(UINT nType, int cx, int cy);
  afx_msg void    OnMove(int x, int y);
  afx_msg void    OnSaveall();
  afx_msg void    OnAddrdelete();
  afx_msg void    OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
  afx_msg void    OnDblclkList();
  afx_msg void    OnAddressEdit();
  afx_msg void    OnAddressNew();
  afx_msg void    OnClose();
  afx_msg void    OnRoutingForm();
  afx_msg void    OnRoutingHelp();
  };



