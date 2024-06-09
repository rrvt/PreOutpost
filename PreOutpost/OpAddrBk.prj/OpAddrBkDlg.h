// Main Dialog Box


#pragma once
#include "ListBox.h"
#include "LogFile.h"
#include "Resource.h"
#include "StatusBar.h"
#include "MyToolBar.h"
#include "PdfInfo.h"
#include "WinPos.h"

class StatusBar;


// OpAddrBkDlg dialog

class OpAddrBkDlg : public CDialogEx {

DECLARE_DYNAMIC(OpAddrBkDlg)

String    helpPath;
String    myPath;

MyToolBar toolBar;
CStatic   headingCtl;
CStatic   heading1Ctl;
ListBox   listBox;
StatusBar statusBar;
CRect     listBoxRect;
//int       topThruTB;
//int       headingHght;

bool      isInitialized;

String    addrPath;                               // Path to Outpost address book directory
PdfInfo   pdfInfo;

LogFile   logFile;

public:

           OpAddrBkDlg(TCchar* helpPth, CWnd* pParent = nullptr);
  virtual ~OpAddrBkDlg();

  virtual BOOL OnInitDialog();

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_OpAddrBk };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  void            setupToolBar();
  void            adjustControls();
  void            reposHdr(    CRect& winRect, int hdrHght, CRect& r);
  void            reposHdr1(   CRect& winRect, int hdrHght, CRect& r);
  int             hdrCalc(     CRect& winRect, int hdrHght, CRect& r);
  void            reposListBox(CRect& winRect, int hdrHght, CRect& r);

public:

  afx_msg void    onNewAddress();
  afx_msg void    onEditAddr() {listBox.onEditAddr();}
  afx_msg void    onRefresh();


  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnResetToolBar(WPARAM wParam, LPARAM lParam);
  afx_msg void    onAppAbout();
  afx_msg void    onHelp();

  afx_msg void    OnMove(int x, int y);
  afx_msg void    OnSize(UINT nType, int cx, int cy);

  afx_msg BOOL    OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);

  afx_msg void    onDocDispatch();
  afx_msg void    onPacketFreqs();
  afx_msg void    onFormRouting();
  afx_msg void    onPktSubjLine();
  afx_msg void    onCheckInOut();
  afx_msg void    onRoutingSlip();

  afx_msg void    onOptDispatch();
  afx_msg void    onFindPdfReader();
  afx_msg void    onFindPdfFiles();
  afx_msg void    onDrillTraffic();

  afx_msg void    onSaveAll();

  afx_msg void    onTBChange(NMHDR* pNMHDR, LRESULT* pResult);
  virtual void    OnOK();
};




#if 0
  afx_msg void    onTBEditBox();
  afx_msg void    changeReady();
  //  afx_msg void    onDispatch1();
//  afx_msg void    onX();
  afx_msg void    onOption11();
  afx_msg void    onOption12();
  afx_msg void    onCboBxChange();

  afx_msg void    onCboBx1Change();
  afx_msg void    onOption00();
  afx_msg void    onOption01();
  afx_msg void    onOption02();
#endif
