// Main Dialog Box


#pragma once
#include "ListBox.h"
#include "LogFile.h"
#include "PdfInfo.h"
#include "Resource.h"
#include "Static.h"
#include "StatusBar.h"
#include "TBBtnCtx.h"
#include "ToolBar.h"
#include "WinPos.h"

class StatusBar;


// OpAddrDlg dialog

class OpAddrDlg : public CDialogEx {

DECLARE_DYNAMIC(OpAddrDlg)

bool       isInitialized;

String     helpPath;
String     myPath;
String     addrPath;                              // Path to Outpost address book directory

ToolBar    toolBar;

WinPos     winPos;                                // Position of dialog box
CRect      winRect;

Static     header;
Static     header1;

ListBox    listBox;
HICON      m_hIcon;
PdfInfo    pdfInfo;

LogFile    logFile;

public:
           OpAddrDlg(TCchar* helpPth, CWnd* pParent = nullptr);
  virtual ~OpAddrDlg() { }

  virtual BOOL OnInitDialog();
  virtual BOOL PreTranslateMessage(MSG* pMsg);

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_OpAddr };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void OnCancel();
  virtual void OnOK();

  DECLARE_MESSAGE_MAP()

private:

  void     createHeader();
  void     createListBox();
  void     createHeader1();
  void     moveHeader();
  void     moveHeader1();
  void     moveListBox();
  void     getRect(CWnd& w,      CRect& rect);

  void     setupToolBar();
  void     setComboBox();

public:

  afx_msg void    onNewAddress();
  afx_msg void    onEditAddress();
  afx_msg void    onRefresh();
  afx_msg void    onDelAddress();
  afx_msg void    OnSaveall();
  afx_msg void    OnOutpostFindPath();
  afx_msg void    OnDblclkList();

  afx_msg void    onAppAbout();
  afx_msg void    onHelp();

  afx_msg void    OnRoutingForm();
  afx_msg void    OnRoutingHelp();
  afx_msg void    OnBBS_Assgnmnts();
  afx_msg void    OnChkInOutFmt();

  // Windows Messages

  afx_msg void    OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void    OnClose();
  afx_msg void    OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();

  // Initialization Messages

  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnResetToolBar(WPARAM wParam, LPARAM lParam);
  afx_msg BOOL    OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);

  afx_msg void    OnSize(UINT nType, int cx, int cy);
  afx_msg void    OnMove(int x, int y);
  };

