// IdentityDlg dialog
// IdentityDlg.cpp : implementation file


#include "pch.h"
#include "IdentityDlg.h"
#include "AboutDlgEx.h"
#include "BBSinfo.h"
#include "HtmlHelp.h"
#include "MessageBox.h"
#include "Outpost.h"
#include "PreOutpost.h"
#include "ProgramFiles.h"
#include "BBSdlg.h"


IMPLEMENT_DYNAMIC(IdentityDlg, CDialogEx)


BEGIN_MESSAGE_MAP(IdentityDlg, CDialogEx)

  ON_BN_CLICKED(IDC_BUTTON4,        &OnTacticalBnClicked)
  ON_EN_KILLFOCUS(IDC_EDIT4,        &OnTacCallLoseFoc)
  ON_EN_KILLFOCUS(IDC_EDIT5,        &OnTacCallModA)
  ON_EN_KILLFOCUS(IDC_EDIT6,        &OnTacCallModB)
  ON_EN_KILLFOCUS(IDC_EDIT8,        &OnTacCallModC)
  ON_EN_KILLFOCUS(IDC_EDIT1,        &OnFCCCallLoseFoc)
  ON_EN_KILLFOCUS(IDC_EDIT2,        &OnFCCCallModA)
  ON_EN_KILLFOCUS(IDC_EDIT3,        &OnFCCCallModB)
  ON_EN_KILLFOCUS(IDC_EDIT7,        &OnFCCCallModC)
  ON_COMMAND(ID_SetBBSsuffixes,     &OnSetBBSsuffixes)
  ON_COMMAND(ID_ABOUT1,             &OnAbout)
  ON_COMMAND(ID_HELP_OVERVIEW,      &OnHelpOverview)
  ON_COMMAND(ID_HELP_IDENTITY,      &OnHelpIdentity)
  ON_COMMAND(ID_HELP_ADDRESSBOOK,   &OnHelpAddressbook)
  ON_COMMAND(ID_HELP_DeleteMaster,  &OnHelpDeleteMaster)
  ON_COMMAND(ID_HELP_SelNewMaster,  &OnHelpSelNewMaster)
  ON_COMMAND(ID_HELP_SelectProfile, &OnHelpSelectProfile)
  ON_COMMAND(ID_SubjWSecurity,      &OnSubjWSecurity)
  ON_COMMAND(ID_FindOutpost,        &OnFindOutpost)
  ON_COMMAND(ID_IncludeAddrBook,    &OnIncludeAddrBook)

  ON_WM_MOVE()
  ON_WM_SIZE()
END_MESSAGE_MAP()


IdentityDlg::IdentityDlg(CWnd* pParent /*=NULL*/) : CDialogEx(IdentityDlg::IDD, pParent),
  isInitialized(false), isTacticalID(false),   tacticalModified(false), userModified(false),
  subjWSecurity(false), includeAddrBook(false),
  tacticalCallSign(_T("")), tacticalText(_T("")), tacticalIDPrefix(_T("")), tacSignature(_T("")),
  userCallSign(_T("")), userName(_T("")), userIDPrefix(_T("")), userSignature(_T("")),
  subject(_T("")), severity(0), handling(0), subjStyle(0), profilesDesired(0), practiceDay(0) { }


IdentityDlg::~IdentityDlg() {  }


BOOL IdentityDlg::OnInitDialog() {
CRect        winRect;
CEdit*       p;                                          //{80,44,70,12};
CString      s;
CWnd*        q;
COleDateTime ctm;

  CDialogEx::OnInitDialog();

  GetWindowRect(&winRect);   winPos.setDLUToPxls(winRect, DlgWidth, DlgDepth);

  SetWindowText(title);   winPos.initialPos(this, winRect);

  menu = GetMenu(); setSubjWSecurity();

  CButton* tactical = (CButton*) GetDlgItem(IDC_BUTTON4);

  initTactical(tactical, isTacticalID);

  p = (CEdit*) GetDlgItem(IDC_EDIT4);  if (p) p->SetLimitText(6);
  p = (CEdit*) GetDlgItem(IDC_EDIT6);  if (p) p->SetLimitText(3);
  p = (CEdit*) GetDlgItem(IDC_EDIT3);  if (p) p->SetLimitText(3);
  p = (CEdit*) GetDlgItem(IDC_EDIT13); if (p) p->SetLimitText(2);

  ctm = COleDateTime::GetCurrentTime();
  s = ctm.Format(_T("%H%M %x"));
  todaysDate = ctm.Format(_T("%x"));

  q = (CWnd*) GetDlgItem(IDC_STATIC7); if (q) q->SetWindowText(s);

  setSubjWSecurity();   setIncludeAddrBook();

  SetWindowText(title);  // GetWindowRect(&winRect);

  winPos.initialPos(this, winRect);   isInitialized = true;   return TRUE;
  }



void IdentityDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text( pDX, IDC_EDIT1,     userCallSign);
  DDX_Text( pDX, IDC_EDIT2,     userName);
  DDX_Text( pDX, IDC_EDIT3,     userIDPrefix);
  DDX_Text( pDX, IDC_EDIT7,     userSignature);
  DDX_Text( pDX, IDC_EDIT4,     tacticalCallSign);
  DDX_Text( pDX, IDC_EDIT5,     tacticalText);
  DDX_Text( pDX, IDC_EDIT6,     tacticalIDPrefix);
  DDX_Text( pDX, IDC_EDIT8,     tacSignature);
  DDX_Text( pDX, IDC_EDIT10,    organization);
  DDX_Text( pDX, IDC_EDIT11,    city);
  DDX_Text( pDX, IDC_EDIT12,    county);
  DDX_Text( pDX, IDC_EDIT13,    state);
  DDX_Text( pDX, IDC_EDIT14,    tacticalLocation);
  DDX_Text( pDX, IDC_EDIT15,    textVariable2);
  DDX_Text( pDX, IDC_EDIT16,    textVariable3);
  DDX_Text( pDX, IDC_EDIT17,    taskID);
  DDX_Text( pDX, IDC_EDIT18,    taskName);
  DDX_Radio(pDX, IDC_RADIO1,    profilesDesired);
  DDX_Radio(pDX, IDC_EMERGENCY, severity);
  DDX_Radio(pDX, IDC_IMMEDIATE, handling);
  DDX_Radio(pDX, IDC_WEEKLY,    subjStyle);
  DDX_Radio(pDX, IDC_MONDAY,    practiceDay);
  DDX_Text( pDX, IDC_EDIT40,    subject);
  }


void IdentityDlg::OnMove(int x, int y)
      {CRect winRect;   GetWindowRect(&winRect);   winPos.set(winRect);   CDialogEx::OnMove(x, y);}


void IdentityDlg::OnSize(UINT nType, int cx, int cy) {
CRect winRect;

  CDialogEx::OnSize(nType, cx, cy);

  if (!isInitialized) return;

  GetWindowRect(&winRect);   winPos.set(winRect);
  }


void IdentityDlg::OnSubjWSecurity() {subjWSecurity = !subjWSecurity; setSubjWSecurity();}


void IdentityDlg::OnFindOutpost() {outpost.choose();}


void IdentityDlg::OnIncludeAddrBook() {includeAddrBook = !includeAddrBook; setIncludeAddrBook();}


void IdentityDlg::setSubjWSecurity() {
  if (subjWSecurity) menu->CheckMenuItem(ID_SubjWSecurity, MF_CHECKED   | MF_BYCOMMAND);
  else               menu->CheckMenuItem(ID_SubjWSecurity, MF_UNCHECKED | MF_BYCOMMAND);

  GetDlgItem(IDC_EMERGENCY)->EnableWindow(subjWSecurity);
  GetDlgItem(IDC_URGENT)->EnableWindow(subjWSecurity);
  GetDlgItem(IDC_OTHER)->EnableWindow(subjWSecurity);
  }


void IdentityDlg::setIncludeAddrBook() {
  if (includeAddrBook) menu->CheckMenuItem(ID_IncludeAddrBook, MF_CHECKED   | MF_BYCOMMAND);
  else                 menu->CheckMenuItem(ID_IncludeAddrBook, MF_UNCHECKED | MF_BYCOMMAND);
  }


void IdentityDlg::OnSetBBSsuffixes() {bbsInfo.getSuffixes();}



// IdentityDlg message handlers


void IdentityDlg::OnTacticalBnClicked() {
CButton* tactical = (CButton*) GetDlgItem(IDC_BUTTON4);   if (!tactical) return;
int      state    = tactical->GetCheck();

  initTactical(tactical, state == BST_UNCHECKED);
  }



void IdentityDlg::OnTacCallLoseFoc() {

  if (tacticalModified) return;

CEdit*   callSign = (CEdit*) GetDlgItem(IDC_EDIT4);   if (!callSign) return;
int      nBuf;
UsrData& tac = idInfo.tacData;
Tchar    buf[16];
String   s;

  nBuf = callSign->GetLine(0, buf, noElements(buf));    if (nBuf <= 0) return;

  buf[nBuf] = 0;   s = buf;

  if (tac.find(s)) {
    SetDlgItemText(IDC_EDIT5, tac.name);
    SetDlgItemText(IDC_EDIT6, tac.userID);
    SetDlgItemText(IDC_EDIT8, tac.signature);
    }
  }


void IdentityDlg::OnFCCCallLoseFoc() {

  if (userModified) return;

CEdit*   callSign = (CEdit*) GetDlgItem(IDC_EDIT1);   if (!callSign) return;
int      nBuf;
UsrData& usr = idInfo.usrData;
Tchar    buf[16];
String   s;

  nBuf = callSign->GetLine(0, buf, noElements(buf));    if (nBuf <= 0) return;

  buf[nBuf] = 0;  s = buf;

  if (usr.find(s)) {
    SetDlgItemText(IDC_EDIT2, usr.name);
    SetDlgItemText(IDC_EDIT3, usr.userID);
    SetDlgItemText(IDC_EDIT7, usr.signature);
    }
  }


void IdentityDlg::OnTacCallModA()
                            {if (isNotEqual(tacticalText, IDC_EDIT5))     tacticalModified = true;}
void IdentityDlg::OnTacCallModB()
                            {if (isNotEqual(tacticalIDPrefix, IDC_EDIT6)) tacticalModified = true;}
void IdentityDlg::OnTacCallModC()
                            {if (isNotEqual(tacSignature, IDC_EDIT8))     tacticalModified = true;}
void IdentityDlg::OnFCCCallModA()
                            {if (isNotEqual(userName, IDC_EDIT2))         userModified     = true;}
void IdentityDlg::OnFCCCallModB()
                            {if (isNotEqual(userIDPrefix, IDC_EDIT3))     userModified     = true;}
void IdentityDlg::OnFCCCallModC()
                            {if (isNotEqual(userSignature, IDC_EDIT7))    userModified     = true;}


bool IdentityDlg::isNotEqual(CString& s, int x) {
int   n;
Tchar t[128];

  try {n = GetDlgItemText(x, t, noElements(t));} catch (...) {n = 0;}
  t[n] = 0;
  return String(t) != s;
  }


void IdentityDlg::initTactical(CButton* tactical, bool state) {
  if (!tactical) return;

  tactical->SetCheck(state ? BST_CHECKED : BST_UNCHECKED);

  isTacticalID = state;  enableTactical(isTacticalID);
  }


void IdentityDlg::enableTactical(bool enable) {
  enableCtrl(IDC_STATIC1, enable);
  enableCtrl(IDC_STATIC2, enable);
  enableCtrl(IDC_STATIC3, enable);
  enableCtrl(IDC_STATIC4, enable);
  enableCtrl(IDC_STATIC5, enable);
  enableCtrl(IDC_STATIC6, enable);
  enableCtrl(IDC_EDIT4,   enable);
  enableCtrl(IDC_EDIT5,   enable);
  enableCtrl(IDC_EDIT6,   enable);
  enableCtrl(IDC_EDIT8,   enable);
  }


void IdentityDlg::enableCtrl(int id, bool enable) {
CWnd* ctrl = (CWnd*) GetDlgItem(id); if (ctrl) ctrl->EnableWindow(enable);
  }


void IdentityDlg::OnAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void IdentityDlg::OnHelpOverview() {
String topic;

  topic = theApp.helpFile; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void IdentityDlg::OnHelpIdentity() {
String topic;

  topic = theApp.helpFile; topic += _T(">OneMaster");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void IdentityDlg::OnHelpAddressbook() {
String topic;

  topic = theApp.helpFile; topic += _T(">AddressBook");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void IdentityDlg::OnHelpDeleteMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">DeleteMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void IdentityDlg::OnHelpSelNewMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">SelectProfile");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void IdentityDlg::OnHelpSelectProfile() {
String topic;

  topic = theApp.helpFile; topic += _T(">TwoPlusMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }

