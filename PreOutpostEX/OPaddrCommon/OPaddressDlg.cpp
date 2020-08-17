// OPaddressDlg.cpp : implementation file


#include "stdafx.h"
#include "OPaddressDlg.h"
#include "About.h"
//#include "Addresses.h"
#include "DeleteDlg.h"
#include "LoadScratchPad.h"
#include "MessageBox.h"
#include "OPaddress.h"
#include "Resources.h"
#include "SaveAddresses.h"
#include "WindowPos.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int OPaddressDlg::baseUnits = LOWORD(::GetDialogBaseUnits());



BEGIN_MESSAGE_MAP(OPaddressDlg, CDialogEx)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_COMMAND(ID_ABOUT,       &OPaddressDlg::OnAbout)
  ON_COMMAND(ID_Refresh,     &OPaddressDlg::OnRefresh)
  ON_WM_SIZE()
  ON_WM_MOVE()
  ON_COMMAND(ID_TEST,        &OPaddressDlg::OnTest)
  ON_COMMAND(ID_SaveAll,     &OPaddressDlg::OnSaveall)
  ON_COMMAND(ID_AddrDelete,  &OPaddressDlg::OnAddrdelete)
  ON_LBN_DBLCLK(IDC_LIST,    &OPaddressDlg::OnDblclkList)
  ON_COMMAND(ID_AddressEdit, &OPaddressDlg::OnAddressEdit)
  ON_COMMAND(ID_ADDRESS_NEW, &OPaddressDlg::OnAddressNew)
  ON_WM_CLOSE()
  ON_COMMAND(ID_ROUTING_FORM, &OPaddressDlg::OnRoutingForm)
  ON_COMMAND(ID_ROUTING_HELP, &OPaddressDlg::OnRoutingHelp)
END_MESSAGE_MAP()



OPaddressDlg::OPaddressDlg(CWnd* pParent) : CDialogEx(IDD_OPADDRESS_DIALOG, pParent) {

  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  }


BOOL OPaddressDlg::OnInitDialog() {

  CDialogEx::OnInitDialog();

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

  windowPos.set(this);

  return TRUE;                                    // return TRUE  unless you set the focus to a control
  }


void OPaddressDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST,   listBox);
  DDX_Control(pDX, IDC_Header, header);
  }



void OPaddressDlg::OnRefresh() {logFile.open();  logFile.process();  logFile.close();  loadAddresses();}


void OPaddressDlg::OnSaveall() {addresses.saveAll();}


void OPaddressDlg::OnAddrdelete() {
int     cur = listBox.GetCurSel();
Cstring cs;

  if (cur >= 0) {
    listBox.GetText(cur, cs);

    DeleteDlg delDlg(cs);

    if (delDlg.DoModal() == IDOK && addresses.delAddr(String(cs))) loadAddresses();
    }
  }




void OPaddressDlg::OnDblclkList() {listBox.OnDblclkList();}


void OPaddressDlg::OnAddressEdit() {
Addr* p = listBox.find();
String oldKey;
//Addr  oldAddr;
Addr  addr;

  if (p) {

    oldKey = p->key;   addr = *p;

    addr.edit(_T("Edit Address"), false);

    addresses.load(addr);

    p = addresses.find(oldKey);

    if (p->key != addr.key) {p->deleted = true;}

    loadAddresses();
    }
  }


void OPaddressDlg::OnAddressNew() {
Addr addr;

  addr.edit(_T("New Address"), true);
  addresses.load(addr);
  loadAddresses();
  }


void OPaddressDlg::OnTest() {
  }


void OPaddressDlg::loadAddresses() {
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



void OPaddressDlg::positionHdr1() {
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




void OPaddressDlg::setTabStops() {
CDC*     dc  = listBox.GetDC();
CFont*   pf  = header.GetFont();   dc->SelectObject(pf);
AddrIter iter(addresses);
Addr*    addr;
CSize    sz;
int      dx  = 0;
int      tab;

  dx1 = 0;  listBox.SetTabStops();

  for (addr = iter(); addr; addr = iter++) {
    sz = dc->GetTextExtent(CString(addr->key));      if (sz.cx > dx)   dx  = sz.cx;
    sz = dc->GetTextExtent(CString(addr->actual));   if (sz.cx > dx1)  dx1 = sz.cx;
    }

  tab = (dx + baseUnits - 1) / baseUnits;   tab *= baseUnits;

  dataTab = tab * 4 / baseUnits;    listBox.SetTabStops(dataTab);

  listBox.ReleaseDC(dc);
  }



void OPaddressDlg::OnRoutingForm() {
  showPDF(_T("RoutingSlip.pdf"));
  }


void OPaddressDlg::OnRoutingHelp() {
  showPDF(_T("RoutingInfo.pdf"));
  }


void OPaddressDlg::showPDF(TCchar* name) {
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


void OPaddressDlg::OnAbout() {CAboutDlg dlgAbout;  dlgAbout.DoModal();}


void OPaddressDlg::OnSysCommand(UINT nID, LPARAM lParam) {

  if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
    }

  else {CDialogEx::OnSysCommand(nID, lParam);}
  }


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void OPaddressDlg::OnPaint() {
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

HCURSOR OPaddressDlg::OnQueryDragIcon() {return static_cast<HCURSOR>(m_hIcon);}


void OPaddressDlg::OnSize(UINT nType, int cx, int cy)
                                              {CDialogEx::OnSize(nType, cx, cy);   windowPos.getRect();}


void OPaddressDlg::OnMove(int x, int y) {CDialogEx::OnMove(x, y);  windowPos.getRect();}


BOOL OPaddressDlg::PreTranslateMessage(MSG* pMsg) {

  if (pMsg->message == WM_CHAR) {
    switch (pMsg->wParam) {
      case 2  : listBox.copyVirt();   return true;
      case 3  : listBox.copyActual(); return true;
      case 12 : listBox.copyLoc();    return true;
      }
    }

  return CDialogEx::PreTranslateMessage(pMsg);
  }




void OPaddressDlg::OnClose() {return OnCancel();}
void OPaddressDlg::OnOK()    {return OnCancel();}


void OPaddressDlg::OnCancel() {
SaveAddresses saveAddresses;

  if (addresses.anyChanges() && saveAddresses.DoModal() == IDOK) addresses.saveAll();

  CDialogEx::OnOK();
  }






#if 0
void OPaddressDlg::OnRButtonDown(UINT nFlags, CPoint point) {
CMenu mnuPopupSubmit;

  mnuPopupSubmit.LoadMenu(IDR_RightClick);

  CDialogEx::OnRButtonDown(nFlags, point);
  }

m_Menu.CreateMenu(); //Call this once only (I do it in PreSubclassWindow)

//class CMenuListCtrl : public CListCtrl
void CMenuListCtrl::OnContextMenu(CWnd *pWnd, CPoint ptMousePos)
{
    //Some people might use a keyboard and not the mouse
    if (ptMousePos.x == -1 && ptMousePos.y == -1)
    {
        auto nSelectedItem = GetSelectionMark(); //Get the selected item in the CListCtrl
        if (nSelectedItem == -1)
            return;

        //Find the position
        CRect itemRect;
        GetItemRect(nSelectedItem, &itemRect, LVIR_BOUNDS);
        ClientToScreen(&itemRect);
        ptMousePos.x = itemRect.left + (itemRect.Width() / 10); //Some offset to display the menu user-friendly
        ptMousePos.y = itemRect.top + itemRect.Height() / 2;
    }

    CPoint hitPoint = ptMousePos;
    ScreenToClient(&hitPoint);

    //Fix header pop-up bug
    CHeaderCtrl *pHeader = GetHeaderCtrl();
    HDHITTESTINFO hitTestHeader = {0};
    hitTestHeader.pt = hitPoint;

    //The header doesn't need a context-menu, the item does
    if (pHeader->HitTest(&hitTestHeader) != -1)
        return;

    UINT uFlags = 0;
    HitTest(hitPoint, &uFlags);
    if (uFlags & LVHT_NOWHERE)
        return;

    //Get the previously created menu
    CMenu *pPopUp = nullptr;
    pPopUp = m_Menu.GetSubMenu(0);

    if (pPopUp)
        pPopUp->TrackPopupMenu(TPM_LEFTALIGN, ptMousePos.x, ptMousePos.y, this);
}
#endif



#if 0
RECT rHdr;
int  xHdr;
int  yHdr;
int  cxHdr;
int  cyHdr;
//int  cxClt;
//int  cyClt;
//int  yBdrWidth;
//int  botBdrWidth;
//yBdrWidth   = cy - cltRect.right;
 //  cxClt = cx - xBdrWidth;  xHdr  = hdrRect.left;
 //  cyClt = cy - yBdrWidth;  yHdr  = hdrRect.top;
  cxHdr = hdrRect.right  - xHdr;
  cyHdr = hdrRect.bottom - yHdr;
  rHdr = hdrRect;
  ScreenToClient(&rHdr);
#endif
#if 0
  GetWindowRect(&dlgRect);
  GetClientRect(&cltRect);
  header.GetWindowRect(&hdrRect);

  int x  = hdrRect.left;
  int y  = hdrRect.top;
  int cx = hdrRect.right  - hdrRect.left;
  int cy = hdrRect.bottom - hdrRect.top;

  r.left   = 2*x + tab;                           // Absolute Kludge
  r.top    = y;
  r.right  = r.left + cx;
  r.bottom = r.top  + cy;    ScreenToClient(&r);

  if (!hdr1.m_hWnd) {hdr1.Create(_T(""), SS_LEFT | WS_CHILD | WS_VISIBLE, r, this);}
  else              {hdr1.MoveWindow(&r);}
#endif


#if 0
WINDOWINFO hdrInfo;
WINDOWINFO lstInfo;

  header.GetWindowInfo(&hdrInfo);    ScreenToClient(&hdrInfo.rcWindow);
  address.GetWindowInfo(&lstInfo);   ScreenToClient(&lstInfo.rcWindow);

  if (hdrInfo.rcWindow.left == lstInfo.rcWindow.left) {
    int x = 1;
    }
  if (hdrInfo.rcWindow.right - hdrInfo.rcWindow.left != tab + dx1) {
    double w = hdrInfo.rcWindow.right - hdrInfo.rcWindow.left;
    double lng = tab + dx1;
    double ratio = lng / w;

    String s; s.format(_T("Ratio = %.3f"), ratio);

    address.AddString(s);
    }
#endif


#if 0
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx {
public:
  CAboutDlg();

  // Dialog Data
  #ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
  #endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);            // DDX/DDV support

// Implementation
protected:
  DECLARE_MESSAGE_MAP()
public:
  CStatic nameVersion;
  virtual BOOL OnInitDialog();
};


CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) { }




BOOL CAboutDlg::OnInitDialog() {
ResourceData           res;
String cn;
String pn;
String ver;
String nameVer;

  if (!res.getProductName(pn)) nameVer = pn;

  CDialogEx::OnInitDialog();

#ifdef WinXP
  nameVer += _T(" (WinXP)");
#else
  nameVer += _T(" (Win 7)");
#endif

  if (!res.getVersion(ver)) nameVer += _T(", Version ") + ver;

  nameVersion.SetWindowText(nameVer);

  return TRUE;
  }



void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX); DDX_Control(pDX, IDC_NameVer, nameVersion);
  }


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
#endif

