// OpAddrBkDlg.cpp : implementation file
//

#include "pch.h"
#include "OpAddrBkDlg.h"
#include "Addresses.h"
#include "AboutDlg.h"
#include "ClipLine.h"
#include "FileName.h"
#include "History.h"
#include "MessageBox.h"
#include "Outpost.h"
#include "StatusBar.h"

#include "utilities.h"


static TCchar* DrillTraffic = _T("**** This is drill traffic ****");


IMPLEMENT_DYNAMIC(OpAddrBkDlg, CDialogEx)


BEGIN_MESSAGE_MAP(OpAddrBkDlg, CDialogEx)

  ON_COMMAND(      ID_NewAddr,        &onNewAddress)
  ON_COMMAND(      ID_EditAddr,       &onEditAddr)
  ON_COMMAND(      ID_Refresh,        &onRefresh)

  ON_CBN_SELCHANGE(ID_DocMenu,        &onDocDispatch)           // Send Command Message with ID_...
  ON_COMMAND(      ID_PacketFreqs,    &onPacketFreqs)
  ON_COMMAND(      ID_FormRouting,    &onFormRouting)
  ON_COMMAND(      ID_PktSubjLine,    &onPktSubjLine)
  ON_COMMAND(      ID_CheckInOut,     &onCheckInOut)
  ON_COMMAND(      ID_RoutingSlip,    &onRoutingSlip)

  ON_CBN_SELCHANGE(ID_OptMenu,        &onOptDispatch)           // Send Command Message with ID_...
  ON_COMMAND(      ID_FindPdfReader,  &onFindPdfReader)
  ON_COMMAND(      ID_FindPdfFiles,   &onFindPdfFiles)
  ON_COMMAND(      ID_DrillTraffic,   &onDrillTraffic)

  ON_COMMAND(      ID_SaveAll,        &onSaveAll)
  ON_COMMAND(      ID_Help,           &onHelp)
  ON_COMMAND(      ID_App_About,      &onAppAbout)
  ON_COMMAND(      ID_App_Exit,       &OnOK)

  ON_WM_CREATE()
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &OnResetToolBar)
  ON_NOTIFY_EX(    TTN_NEEDTEXT, 0, &OnTtnNeedText)         // Do ToolTips
  ON_WM_MOVE()
  ON_WM_SIZE()
END_MESSAGE_MAP()


OpAddrBkDlg::OpAddrBkDlg(TCchar* helpPth, CWnd* pParent) : CDialogEx(IDD_OpAddrBk, pParent),
                                       helpPath(helpPth), myPath(getPath(helpPath)), toolBar(),
                                       listBox(statusBar), statusBar(), listBoxRect({0,0,0,0}),
                                       isInitialized(false), pdfInfo(myPath) { }


OpAddrBkDlg::~OpAddrBkDlg() {winPos.~WinPos();}


int OpAddrBkDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {

  if (CDialogEx::OnCreate(lpCreateStruct) == -1) return -1;

  return 0;
  }


BOOL OpAddrBkDlg::OnInitDialog() {
CRect winRect;

  CDialogEx::OnInitDialog();

  GetWindowRect(&winRect);   winPos.setDLUToPxls(winRect, DlgWidth, DlgDepth);

  if (!toolBar.create(this, IDR_TOOLBAR)) return false;

  SetBackgroundColor(RGB(255,255,255));               // toolBar.move(winRect);

  if (!statusBar.create(this, IDC_StatusBar)) return false;

  statusBar.setReady();

  winPos.initialPos(this, winRect);   toolBar.move(winRect);   statusBar.move(winRect);

  adjustControls();

  addrPath = outpost.getProfile() + _T("addr.d\\");

  addresses.load(addrPath);   listBox.load();

  isInitialized = true;   return true;
  }


void OpAddrBkDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_Adresses, listBox);
  DDX_Control(pDX, IDC_Heading,  headingCtl);
  DDX_Control(pDX, IDC_Heading1, heading1Ctl);
  }


void OpAddrBkDlg::OnMove(int x, int y)
      {CRect winRect;   GetWindowRect(&winRect);   winPos.set(winRect);   CDialogEx::OnMove(x, y);}



void OpAddrBkDlg::OnSize(UINT nType, int cx, int cy) {
CRect r;

  GetWindowRect(&r);

  if (!isInitialized) {winPos.setInvBdrs(r, cx, cy);   return;}

  winPos.set(cx, cy);   toolBar.move(r);   statusBar.move(r);    adjustControls();

  CDialogEx::OnSize(nType, cx, cy);
  }


void OpAddrBkDlg::adjustControls() {
CRect winRect;
CRect r;
int   toolBarBottom;
int   headingBottom;

             GetWindowRect(&winRect);
     toolBar.GetWindowRect(&r);     toolBarBottom = r.bottom - winRect.top;
  headingCtl.GetWindowRect(&r);     headingBottom = r.bottom - r.top + toolBarBottom;

  reposHdr(    winRect, toolBarBottom, r);    headingCtl.MoveWindow(&r);
  reposHdr1(   winRect, toolBarBottom, r);   heading1Ctl.MoveWindow(&r);
  reposListBox(winRect, headingBottom, r);       listBox.MoveWindow(&r);
  }


void OpAddrBkDlg::reposHdr(    CRect& winRect, int hdrHght, CRect& r)
               {int width = hdrCalc(winRect, hdrHght, r);   r.right -= width;   ScreenToClient(r);}


void OpAddrBkDlg::reposHdr1(   CRect& winRect, int hdrHght, CRect& r)
               {int width = hdrCalc(winRect, hdrHght, r);   r.left += width;    ScreenToClient(r);}


int OpAddrBkDlg::hdrCalc(CRect& winRect, int hdrHght, CRect& r) {
int delta  = winPos.dluToScreen(7);
int height = winPos.dluToScreen(11, false);
int width  = (winRect.right - winRect.left) / 2 - delta;

  r.top    = winRect.top   + hdrHght;
  r.bottom = r.top         + height;
  r.left   = winRect.left  + delta;
  r.right  = winRect.right - delta;
  return width;
  }


void OpAddrBkDlg::reposListBox(CRect& winRect, int hdrHght, CRect& r) {
int   hDelta = winPos.dluToScreen(7);
int   vDelta = winPos.dluToScreen(15, false);

  r.top    = winRect.top    + hdrHght;
  r.bottom = winRect.bottom - vDelta;
  r.left   = winRect.left   + hDelta;
  r.right  = winRect.right  - hDelta;

  ScreenToClient(r);
  }


// Message Handlers


void OpAddrBkDlg::onNewAddress() {addresses.newAddr(addrPath);   listBox.load();}


void OpAddrBkDlg::onSaveAll() {addresses.saveAll(addrPath, statusBar);}


void OpAddrBkDlg::onRefresh()
                      {logFile.open();  logFile.process();  logFile.close();  listBox.load();}


LRESULT OpAddrBkDlg::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar();  return 0;}


void OpAddrBkDlg::setupToolBar() {
CRect winRect;   GetWindowRect(&winRect);   toolBar.set(winRect);

  toolBar.addMenu(ID_DocMenu, IDR_DocMenu,    _T("Packet Docs"));
  toolBar.addMenu(ID_OptMenu, IDR_OptionMenu, _T("Options"));
  }


void OpAddrBkDlg::onTBChange(NMHDR* pNMHDR, LRESULT* pResult) {

  LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

  *pResult = 0;
  }


void OpAddrBkDlg::onDocDispatch()   {toolBar.dispatch(ID_DocMenu);}

void OpAddrBkDlg::onPacketFreqs()   {pdfInfo.show(PktFreqPDF,  statusBar);}
void OpAddrBkDlg::onFormRouting()   {pdfInfo.show(FrmRtngPDF,  statusBar);}
void OpAddrBkDlg::onPktSubjLine()   {pdfInfo.show(SbjLnPDF,    statusBar);}
void OpAddrBkDlg::onCheckInOut()    {pdfInfo.show(CheckInPDF,  statusBar);}
void OpAddrBkDlg::onRoutingSlip()   {pdfInfo.show(RtngSlipPDF, statusBar);}

void OpAddrBkDlg::onOptDispatch()   {toolBar.dispatch(ID_OptMenu);}
void OpAddrBkDlg::onFindPdfReader() {pdfInfo.findPdfReader(statusBar);}
void OpAddrBkDlg::onFindPdfFiles()  {pdfInfo.findPdfFiles(statusBar);}
void OpAddrBkDlg::onDrillTraffic() {loadClipBoard(DrillTraffic);  statusBar.setText(DrillTraffic);}


// Do ToolTips

BOOL OpAddrBkDlg::OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
                                                            {return toolBar.OnTtnNeedText(pNMHDR);}


void OpAddrBkDlg::onHelp() {
String topic = helpPath; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void OpAddrBkDlg::onAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}


void OpAddrBkDlg::OnOK() {

  if (addresses.anyChanges() && msgChoiceBox(_T("Save Address Files?")) == IDOK) onSaveAll();

  CDialogEx::OnOK();
  }




