// AddrDlg.cpp : implementation file


#include "stdafx.h"
#include "AddrDlg.h"
#include "AboutDlg.h"
#include "DeleteDlg.h"
#include "filename.h"
#include "LoadClipBoard.h"
#include "MessageBox.h"
#include "OPaddress.h"
#include "resource.h"
#include "Resources.h"
#include "SaveAddrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int AddrDlg::baseUnits = LOWORD(::GetDialogBaseUnits());



BEGIN_MESSAGE_MAP(AddrDlg, CDialogEx)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_COMMAND(ID_ABOUT,         &OnAbout)
  ON_COMMAND(ID_Refresh,       &OnRefresh)
  ON_COMMAND(ID_NewAddress,    &OnAddressNew)
  ON_COMMAND(ID_SaveAll,       &OnSaveall)
  ON_COMMAND(ID_AddrDelete,    &OnAddrdelete)
  ON_LBN_DBLCLK(IDC_LIST,      &OnDblclkList)
  ON_COMMAND(ID_AddressEdit,   &OnAddressEdit)
  ON_COMMAND(ID_ROUTING_FORM,  &OnRoutingForm)
  ON_COMMAND(ID_ROUTING_HELP,  &OnRoutingHelp)
  ON_COMMAND(ID_BBS_Assgnmnts, &OnBBS_Assgnmnts)
  ON_COMMAND(ID_CheckInOutFmt, &OnChkInOutFmt)

  ON_WM_SIZE()
  ON_WM_MOVE()
  ON_WM_CLOSE()
END_MESSAGE_MAP()



AddrDlg::AddrDlg(CWnd* pParent) :
          CDialogEx(IDD_AddrDlg, pParent) {m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);}

BOOL AddrDlg::OnInitDialog() {

  CDialogEx::OnInitDialog();

  winPos.onInit(this);

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

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

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog

  SetIcon(m_hIcon, TRUE);     // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon

  loadAddresses();

  winPos.set();

  return TRUE;                                    // return TRUE  unless you set the focus to a control
  }


void AddrDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST,   listBox);
  DDX_Control(pDX, IDC_Header, header);
  }



void AddrDlg::OnRefresh() {logFile.open();  logFile.process();  logFile.close();  loadAddresses();}


void AddrDlg::OnSaveall() {addresses.saveAll();}


void AddrDlg::OnDblclkList() {listBox.OnDblclkList();}


void AddrDlg::OnAddressNew() {
Addr addr;

  if (!addr.edit(_T("New Address"), true)) return;

  if (addr.virt.isEmpty()) return;

  addresses.load(addr);  loadAddresses();
  }


void AddrDlg::OnAddressEdit() {
Addr*  p = listBox.find();        if (!p) return;
String oldKey = p->virt;
Addr   addr;
String path;
String ext;

  addr = *p;     addr.edit(_T("Edit Address"));    addresses.load(addr);

  p = addresses.find(oldKey);

  if (p->virt != addr.virt)
            {p->deleted = true;    path = getPath(addr.path);    addr.path = path + addr.virt + AddrExt;}

  loadAddresses();
  }


void AddrDlg::OnAddrdelete() {
Addr*     addr = listBox.find();     if (!addr) return;
DeleteDlg dlg;

  dlg.delAddr = addr->virt;

  if (dlg.DoModal() == IDOK) {addr->deleted = true; loadAddresses();}
  }


void AddrDlg::loadAddresses() {
AddrIter iter(addresses);
Addr*    addr;
CFont*   font;

  setTabStops();   listBox.ResetContent();

  for (addr = iter(); addr; addr = iter++) if (!addr->deleted) listBox.add(*addr);

  positionHdr1();

  font = header.GetFont();

  hdr1.SetFont(font, false);   hdr1.SetWindowText(_T("Actual Addr"));

  header.SetFont(font, true);  header.SetWindowText(_T("Virtual Addr"));
  }



void AddrDlg::positionHdr1() {
int  x;
int  y;
int  cx;
int  cy;
int  xClt;
int  yClt;
int  xBdrWidth;
int  topBdrWidth;
RECT rHdr0;
RECT r;
int  t;

  GetWindowRect(       &dlgRect);             // Get Screen Coordinates
  GetClientRect(       &cltRect);
  header.GetWindowRect(&hdrRect);

  x  = dlgRect.left;                          // Dialog Box screen coordinates
  y  = dlgRect.top;
  cx = dlgRect.right  - x;                    // Width & depth
  cy = dlgRect.bottom - y;

  xBdrWidth   = cx - cltRect.right;
  topBdrWidth = hdrRect.top - y;              // Header has a zero client position on purpose

  xClt  = x + xBdrWidth / 2;
  yClt  = y + topBdrWidth;

  rHdr0.left   = hdrRect.left - xClt;                           // Get Client position of header 0
  rHdr0.top    = hdrRect.top  - yClt;
  rHdr0.right  = rHdr0.left + (hdrRect.right - hdrRect.left);
  rHdr0.bottom = rHdr0.top  + (hdrRect.bottom - hdrRect.top);

  t = dataTab * 3250 / 1440;

  r.left   = rHdr0.left + t;                                    // Client position of header 1
  r.top    = rHdr0.top;                                         // Based on header 0's position and
  r.right  = r.left + rHdr0.right - rHdr0.left;                 // tab computation above
  r.bottom = rHdr0.bottom;

  if (!hdr1.m_hWnd) {hdr1.Create(_T(""), SS_LEFT | WS_CHILD | WS_VISIBLE, r, this);}
  else              {hdr1.MoveWindow(&r);}
  }




void AddrDlg::setTabStops() {
CDC*     dc  = listBox.GetDC();
CFont*   pf  = header.GetFont();   dc->SelectObject(pf);
AddrIter iter(addresses);
Addr*    addr;
CSize    sz;
int      dx  = 0;
int      tab;

  dx1 = 0;  listBox.SetTabStops();

  for (addr = iter(); addr; addr = iter++) {
    sz = dc->GetTextExtent(CString(addr->virt));     if (sz.cx > dx)   dx  = sz.cx;
    sz = dc->GetTextExtent(CString(addr->actual));   if (sz.cx > dx1)  dx1 = sz.cx;
    }

  tab = (dx + baseUnits - 1) / baseUnits;   tab *= baseUnits;

  dataTab = tab * 4 / baseUnits;    listBox.SetTabStops(dataTab);

  listBox.ReleaseDC(dc);
  }



void AddrDlg::OnRoutingForm() {  showPDF(_T("RoutingSlip.pdf"));}
void AddrDlg::OnRoutingHelp() {  showPDF(_T("RoutingInfo.pdf"));}
void AddrDlg::OnBBS_Assgnmnts() {showPDF(_T("BBS_Assgnmnts.pdf"));}
void AddrDlg::OnChkInOutFmt() {  showPDF(_T("CheckInOutFormat.pdf"));}


void AddrDlg::showPDF(TCchar* name) {
String              acroRd  = theApp.getAcroRd();
String              pdfPath = theApp.myPath + name;
String              cmdLine;
DWORD               flags = NORMAL_PRIORITY_CLASS;  //CREATE_PRESERVE_CODE_AUTHZ_LEVEL |
PROCESS_INFORMATION processInfo;

  cmdLine  = _T("\"") + acroRd;     cmdLine += _T("\"");
  cmdLine += _T(" \"") + pdfPath;   cmdLine += _T("\"");

  if (!CreateProcess(acroRd.str(), (Tchar*) cmdLine.str(), 0, 0, false, flags, 0,
                                                     theApp.myPath, &theApp.startUpInfo, &processInfo)) {
    String err;   getError(GetLastError(), err);   messageBox(err); return;
    }

  WaitForSingleObject(processInfo.hProcess, INFINITE);
  }


void AddrDlg::OnAbout() {AboutDlg dlgAbout;  dlgAbout.DoModal();}


void AddrDlg::OnSysCommand(UINT nID, LPARAM lParam) {

  if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
    AboutDlg dlgAbout;
    dlgAbout.DoModal();
    }

  else {CDialogEx::OnSysCommand(nID, lParam);}
  }


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void AddrDlg::OnPaint() {
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

HCURSOR AddrDlg::OnQueryDragIcon() {return static_cast<HCURSOR>(m_hIcon);}


void AddrDlg::OnSize(UINT nType, int cx, int cy) {CDialogEx::OnSize(nType, cx, cy);   winPos.getRect();}


void AddrDlg::OnMove(int x, int y) {CDialogEx::OnMove(x, y);  winPos.getRect();}


BOOL AddrDlg::PreTranslateMessage(MSG* pMsg) {

  if (pMsg->message == WM_CHAR) {
    switch (pMsg->wParam) {
      case 2  : listBox.copyVirt();   return true;
      case 3  : listBox.copyActual(); return true;
      case 12 : listBox.copyLoc();    return true;
      }
    }

  return CDialogEx::PreTranslateMessage(pMsg);
  }




void AddrDlg::OnClose() {return OnCancel();}

void AddrDlg::OnOK()    {return OnCancel();}


void AddrDlg::OnCancel() {
SaveAddrDlg saveAddresses;

  if (addresses.anyChanges() && saveAddresses.DoModal() == IDOK) addresses.saveAll();

  CDialogEx::OnOK();
  }


