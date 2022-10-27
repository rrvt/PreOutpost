// OpAddrDlg.cpp : implementation file
//

#include "pch.h"
#include "OpAddrDlg.h"
#include "AboutDlg.h"
#include "FileName.h"
#include "IniFile.h"
#include "OpAddr.h"
#include "Outpost.h"
#include "Resource.h"
#include "SaveAddrDlg.h"
#include "StatusBar.h"
#include "TBComboBox.h"


// OpAddrDlg dialog

IMPLEMENT_DYNAMIC(OpAddrDlg, CDialogEx)


BEGIN_MESSAGE_MAP(OpAddrDlg, CDialogEx)

  // Menu Commands
  ON_COMMAND(      ID_NewAddr,         &onNewAddress)
  ON_COMMAND(      ID_EditAddr,        &onEditAddress)
  ON_COMMAND(      ID_Refresh,         &onRefresh)
  ON_COMMAND(      ID_DelAddr,         &onDelAddress)
  ON_COMMAND(      ID_SaveAll,         &OnSaveall)
  ON_COMMAND(      ID_FindOutpostPath, &OnOutpostFindPath)

  ON_COMMAND(      ID_RoutingForm,     &OnRoutingForm)
  ON_COMMAND(      ID_RoutingHelp,     &OnRoutingHelp)
  ON_COMMAND(      ID_BBSAssnMnts,     &OnBBS_Assgnmnts)
  ON_COMMAND(      ID_CheckInOut,      &OnChkInOutFmt)

  ON_LBN_DBLCLK(   IDC_LIST,           &OnDblclkList)

  ON_COMMAND(      ID_HELP,            &OnHelp)
  ON_COMMAND(      ID_App_About,       &onAppAbout)
  ON_COMMAND(      ID_App_Exit,        &OnOK)

  ON_WM_MOVE()
  ON_WM_SIZE()

  ON_WM_SYSCOMMAND()
  ON_WM_CLOSE()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()

  // Initialization Messages
  ON_WM_CREATE()
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &OnResetToolBar)
  ON_NOTIFY_EX(TTN_NEEDTEXT, 0, &OnTtnNeedText)                     // Do ToolTips

END_MESSAGE_MAP()


OpAddrDlg::OpAddrDlg(TCchar* helpPth, CWnd* pParent) :
                      CDialogEx(IDD_OpAddr, pParent), isInitialized(false),
                      helpPath(helpPth), myPath(getPath(helpPth)), pdfInfo(myPath)
                      {m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);}


void OpAddrDlg::onNewAddress() {addresses.newAddr(addrPath);   listBox.load();}


void OpAddrDlg::onEditAddress() {String key = listBox.selVirt();   addresses.edit(key);   listBox.load();}


void OpAddrDlg::onRefresh() {logFile.open();  logFile.process();  logFile.close();  listBox.load();}


void OpAddrDlg::onDelAddress()
                          {String key = listBox.selVirt();   if (addresses.delAddr(key)) listBox.load();}


void OpAddrDlg::OnSaveall() {addresses.saveAll(addrPath);}


void OpAddrDlg::OnOutpostFindPath() {outpost.choose();}


void OpAddrDlg::OnDblclkList() {listBox.copyActual();}


void OpAddrDlg::OnRoutingForm() { pdfInfo.show(_T("RoutingSlip.190527.pdf"));}
void OpAddrDlg::OnRoutingHelp() { pdfInfo.show(_T("RoutingInfo.220618.pdf"));}
void OpAddrDlg::OnBBS_Assgnmnts(){pdfInfo.show(_T("BBS_Assignments.221215.pdf"));}
void OpAddrDlg::OnChkInOutFmt() { pdfInfo.show(_T("CheckInOutFormat.220323.pdf"));}


void OpAddrDlg::onAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}


int OpAddrDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {

  if (CDialogEx::OnCreate(lpCreateStruct) == -1) return -1;

  return 0;
  }


BOOL OpAddrDlg::OnInitDialog() {

  addrPath = outpost.getProfile() + _T("addr.d\\");   addresses.load(addrPath);

  winPos.onInit(this);   winPos.set();   GetWindowRect(&winRect);

  if (!toolBar.create(this, IDR_TOOLBAR)) return false;

  toolBar.move(winRect);   createHeader();   createListBox();   listBox.load();   createHeader1();

  CDialogEx::OnInitDialog();

  SetBackgroundColor(RGB(255,255,255));

  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);    // Add "About..." menu item to system menu.
  ASSERT(IDM_ABOUTBOX < 0xF000);                      // IDM_ABOUTBOX must be in the system command range.

  CMenu* pSysMenu = GetSystemMenu(FALSE);

  if (pSysMenu != nullptr) {
    BOOL bNameValid;
    CString strAboutMenu;
    bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
    ASSERT(bNameValid);
    if (!strAboutMenu.IsEmpty()) {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
      }
    }
                                                      // Set the icons for this dialog.
  SetIcon(m_hIcon, TRUE);                             // Set big icon
  SetIcon(m_hIcon, FALSE);                            // Set small icon

  isInitialized = true;   return true;
  }


static const DWORD hStyle = SS_LEFT | WS_CHILD | WS_VISIBLE;

void OpAddrDlg::createHeader() {
CRect  tbrRect;
CRect  rect;

  getRect(toolBar, tbrRect);

  rect.top  = tbrRect.top  + 28;   rect.bottom = rect.top  +  22;
  rect.left = winRect.left + 24;   rect.right  = rect.left + 150;;

  header.create(_T("Virtual Address"), hStyle, rect, this);
  }


static const DWORD lbStyle = LBS_SORT | LBS_HASSTRINGS | LBS_USETABSTOPS | LBS_NOINTEGRALHEIGHT |
                              WS_DLGFRAME | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP;

void OpAddrDlg::createListBox() {
CRect  hdrRect;
CRect  rect;

  getRect(header,  hdrRect);

  rect.top    = hdrRect.bottom +  2;    rect.bottom = winRect.bottom - 24;
  rect.left   = winRect.left   + 24;    rect.right  = winRect.right  - 24;

  listBox.create(lbStyle, rect, this, IDC_LIST);
  }


void OpAddrDlg::createHeader1() {
CRect  rect;
int    tabX;

  getRect(header,rect);

  tabX = listBox.tab;   rect.left += tabX;   rect.right += tabX;

  header1.create(_T("Actual Address"), hStyle, rect, this);
  }


void OpAddrDlg::OnMove(int x, int y) {CDialogEx::OnMove(x, y);  winPos.getRect(winRect);}


void OpAddrDlg::OnSize(UINT nType, int cx, int cy) {
  CDialogEx::OnSize(nType, cx, cy);   winPos.getRect(winRect);

  if (!isInitialized) return;

  toolBar.move(winRect);  moveHeader();   moveHeader1();   moveListBox();
  }


void OpAddrDlg::moveHeader() {
CRect  tbrRect;
CRect  rect;

  getRect(toolBar, tbrRect);

  rect.top  = tbrRect.top  + 28;   rect.bottom = rect.top  +  22;
  rect.left = winRect.left + 24;   rect.right  = rect.left + 150;;

  header.moveWindow(rect);
  }


void OpAddrDlg::moveHeader1() {
CRect rect;
int   tabX;

  getRect(header, rect);

  tabX = listBox.tab;   rect.left += tabX;   rect.right += tabX;

  header1.moveWindow(rect);
  }


void OpAddrDlg::moveListBox() {
CRect  hdrRect;
CRect  rect;

  getRect(header,  hdrRect);

  rect.top    = hdrRect.bottom +  2;    rect.bottom = winRect.bottom - 24;
  rect.left   = winRect.left   + 24;    rect.right  = winRect.right  - 24;

  listBox.moveWindow(rect);
  }


void OpAddrDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  }


BOOL OpAddrDlg::PreTranslateMessage(MSG* pMsg) {

  if (pMsg->message == WM_CHAR) {
    switch (pMsg->wParam) {
      case 2  : listBox.copyVirt();   return true;
      case 3  : listBox.copyActual(); return true;
      case 12 : listBox.copyLoc();    return true;
      }
    }

  return CDialogEx::PreTranslateMessage(pMsg);
  }


// MainFrame message handlers

LRESULT OpAddrDlg::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar();  return 0;}


// Do ToolTips

BOOL OpAddrDlg::OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
                                                                  {return toolBar.OnTtnNeedText(pNMHDR);}


void OpAddrDlg::setupToolBar() {
CRect winRect;

  GetWindowRect(&winRect);   winRect.bottom = winRect.top + 22;    toolBar.initialize(winRect);

  toolBar.installBtn(ID_RoutingForm, _T(" Routing Form "));
  toolBar.installBtn(ID_RoutingHelp, _T(" Routing Help "));
  toolBar.installBtn(ID_BBSAssnMnts, _T(" BBS Assignments "));
  toolBar.installBtn(ID_CheckInOut,  _T(" Check In/Out "));
  }


void OpAddrDlg::getRect(CWnd& w, CRect& rect) {w.GetWindowRect(&rect);}


void OpAddrDlg::onHelp() {
String topic = helpPath; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void OpAddrDlg::OnPaint() {

  if (IsIconic()) {

    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
    }

  else {CDialogEx::OnPaint();}
  }


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.

HCURSOR OpAddrDlg::OnQueryDragIcon() {return static_cast<HCURSOR>(m_hIcon);}


void OpAddrDlg::OnSysCommand(UINT nID, LPARAM lParam) {

  if ((nID & 0xFFF0) == IDM_ABOUTBOX) onAppAbout();
  else                                CDialogEx::OnSysCommand(nID, lParam);
  }


void OpAddrDlg::OnClose() {return OnCancel();}

void OpAddrDlg::OnOK()    {return OnCancel();}


void OpAddrDlg::OnCancel() {
SaveAddrDlg saveAddresses;

  if (addresses.anyChanges() && saveAddresses.DoModal() == IDOK) addresses.saveAll(addrPath);

  CDialogEx::OnOK();
  }


