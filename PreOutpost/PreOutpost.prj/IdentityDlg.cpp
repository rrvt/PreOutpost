// IdentityDlg dialog
// IdentityDlg.cpp : implementation file


#include "pch.h"
#include "IdentityDlg.h"
#include "AboutDlgEx.h"
#include "BBSinfo.h"
#include "Date.h"
#include "Help.h"
#include "MessageBox.h"
#include "Outpost.h"
#include "PostSessionDlg.h"
#include "PreOutpost.h"
#include "BBSdlg.h"


IMPLEMENT_DYNAMIC(IdentityDlg, CDialogEx)


BEGIN_MESSAGE_MAP(IdentityDlg, CDialogEx)

  ON_BN_CLICKED(IDC_UseTactical,         &onUseTactical)
  ON_EN_KILLFOCUS(IDC_TacticalCallSign,  &onLeaveTacCallSign)

  ON_EN_KILLFOCUS(IDC_TacticalText,      &onLeaveTacText)
  ON_EN_KILLFOCUS(IDC_TacIDprefix,       &onLeaveTacIDprefix)
  ON_EN_KILLFOCUS(IDC_TacSignature,      &onLeaveTacIDSig)

  ON_EN_KILLFOCUS(IDC_UserCallSign,      &onLeaveUserCallSign)
  ON_EN_KILLFOCUS(IDC_UserName,          &onLeaveUserName)
  ON_EN_KILLFOCUS(IDC_UserIDPrefix,      &onLeaveUserIDprefix)
  ON_EN_KILLFOCUS(IDC_UserSignature,     &onLeaveUserSignature)

  ON_COMMAND(     ID_SetBBSsuffixes,     &OnSetBBSsuffixes)
  ON_COMMAND(     ID_PostSssnTxt,        &onPostSssnTxt)

  ON_COMMAND(     ID_About,             &OnAbout)
  ON_COMMAND(     ID_HELP_OVERVIEW,      &OnHelpOverview)
  ON_COMMAND(     ID_HELP_IDENTITY,      &OnHelpIdentity)
  ON_COMMAND(     ID_HELP_ADDRESSBOOK,   &OnHelpAddressbook)
  ON_COMMAND(     ID_HELP_DeleteMaster,  &OnHelpDeleteMaster)
  ON_COMMAND(     ID_HELP_SelNewMaster,  &OnHelpSelNewMaster)
  ON_COMMAND(     ID_HELP_SelectProfile, &OnHelpSelectProfile)
  ON_COMMAND(     ID_FindOutpost,        &OnFindOutpost)
  ON_COMMAND(     ID_IncludeAddrBook,    &OnIncludeAddrBook)

  ON_WM_MOVE()
//  ON_WM_SIZE()
END_MESSAGE_MAP()


IdentityDlg::IdentityDlg(CWnd* pParent) : CDialogEx(IdentityDlg::IDD, pParent),
  isInitialized(false),   isTacticalID(false),    tacDirty(false),
  userDirty(false),       includeAddrBook(false), tacCallSign(_T("")),
  tacText(_T("")),        tacIDprefix(_T("")),    tacSignature(_T("")),
  userCallSign(_T("")),   userName(_T("")),       userIDPrefix(_T("")),
  userSignature(_T("")),  postSssnTxt(_T("")),    subject(_T("")),
  handling(0),            profilesDesired(0) { }


IdentityDlg::~IdentityDlg() {winPos.~WinPos();}


BOOL IdentityDlg::OnInitDialog() {
CRect    winRect;
CEdit*   p;
CString  s;
CStatic* q;
Date     dt;

  CDialogEx::OnInitDialog();

  GetWindowRect(&winRect);   winPos.setDLUToPxls(winRect, DlgWidth, DlgDepth);

  SetWindowText(title);   winPos.initialPos(this, winRect);

  menu = GetMenu();

  CButton* tactical = (CButton*) GetDlgItem(IDC_UseTactical);

  initTactical(tactical, isTacticalID);

  p = (CEdit*) GetDlgItem(IDC_TacticalCallSign);  if (p) p->SetLimitText(6);
  p = (CEdit*) GetDlgItem(IDC_TacIDprefix);       if (p) p->SetLimitText(3);
  p = (CEdit*) GetDlgItem(IDC_UserIDPrefix);      if (p) p->SetLimitText(3);
  p = (CEdit*) GetDlgItem(IDC_State);             if (p) p->SetLimitText(2);

  dt.getToday();   s = dt.format(_T("%H:%M:%S"));

  q = (CStatic*) GetDlgItem(IDC_CurTime);           if (q) q->SetWindowText(s);

  setIncludeAddrBook();   SetWindowText(title);  GetWindowRect(&winRect);

  winPos.initialPos(this, winRect);   isInitialized = true;   return TRUE;
  }



void IdentityDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text( pDX, IDC_TacticalCallSign,  tacCallSign);
  DDX_Text( pDX, IDC_TacticalText,      tacText);
  DDX_Text( pDX, IDC_TacIDprefix,       tacIDprefix);
  DDX_Text( pDX, IDC_TacSignature,      tacSignature);

  DDX_Text( pDX, IDC_UserCallSign,      userCallSign);
  DDX_Text( pDX, IDC_UserName,          userName);
  DDX_Text( pDX, IDC_UserIDPrefix,      userIDPrefix);
  DDX_Text( pDX, IDC_UserSignature,     userSignature);

  DDX_Text( pDX, IDC_ReportID,          reportID);
  DDX_Text( pDX, IDC_ReportName,        reportName);

  DDX_Text( pDX, IDC_Organization,      organization);
  DDX_Text( pDX, IDC_City,              city);
  DDX_Text( pDX, IDC_County,            county);
  DDX_Text( pDX, IDC_State,             state);
  DDX_Text( pDX, IDC_TacLocation,       tacLocation);
  DDX_Text( pDX, IDC_TextVar2,          textVariable2);
  DDX_Text( pDX, IDC_TextVar3,          textVariable3);

  DDX_Radio(pDX, IDC_Immediate,         handling);
  DDX_Text( pDX, IDC_Subject,           subject);

  DDX_Radio(pDX, IDC_AllBBSes,          profilesDesired);
  }


void IdentityDlg::OnMove(int x, int y)
      {CRect winRect;   GetWindowRect(&winRect);   winPos.set(winRect);   CDialogEx::OnMove(x, y);}


void IdentityDlg::OnSize(UINT nType, int cx, int cy) {
CRect winRect;

  CDialogEx::OnSize(nType, cx, cy);

  if (!isInitialized) return;

  GetWindowRect(&winRect);   winPos.set(winRect);
  }



void IdentityDlg::OnFindOutpost() {outpost.choose();}


void IdentityDlg::OnIncludeAddrBook() {includeAddrBook = !includeAddrBook; setIncludeAddrBook();}


void IdentityDlg::setIncludeAddrBook() {
  if (includeAddrBook) menu->CheckMenuItem(ID_IncludeAddrBook, MF_CHECKED   | MF_BYCOMMAND);
  else                 menu->CheckMenuItem(ID_IncludeAddrBook, MF_UNCHECKED | MF_BYCOMMAND);
  }


void IdentityDlg::onPostSssnTxt() {
PostSessionDlg dlg;

  dlg.postSssnTxt = postSssnTxt;   if (dlg.DoModal() == IDOK) postSssnTxt = dlg.postSssnTxt;
  }


void IdentityDlg::OnSetBBSsuffixes() {bbsInfo.getSuffixes();}



// IdentityDlg message handlers


void IdentityDlg::onUseTactical() {
CButton* tactical = (CButton*) GetDlgItem(IDC_UseTactical);   if (!tactical) return;
int      state    = tactical->GetCheck();

  initTactical(tactical, state == BST_UNCHECKED);
  }



void IdentityDlg::onLeaveTacCallSign() {

  if (tacDirty) return;

CEdit*   callSign = (CEdit*) GetDlgItem(IDC_TacticalCallSign);   if (!callSign) return;
int      nBuf;
UsrData& tac = idInfo.tacData;
Tchar    buf[16];
String   s;

  nBuf = callSign->GetLine(0, buf, noElements(buf));    if (nBuf <= 0) return;

  buf[nBuf] = 0;   s = buf;

  if (tac.find(s)) {
    SetDlgItemText(IDC_TacticalText, tac.name);
    SetDlgItemText(IDC_TacIDprefix, tac.userID);
    SetDlgItemText(IDC_TacSignature, tac.signature);
    }
  }


void IdentityDlg::onLeaveUserCallSign() {

  if (userDirty) return;

CEdit*   callSign = (CEdit*) GetDlgItem(IDC_UserCallSign);   if (!callSign) return;
int      nBuf;
UsrData& usr = idInfo.usrData;
Tchar    buf[16];
String   s;

  nBuf = callSign->GetLine(0, buf, noElements(buf));    if (nBuf <= 0) return;

  buf[nBuf] = 0;  s = buf;

  if (usr.find(s)) {
    SetDlgItemText(IDC_UserName,      usr.name);
    SetDlgItemText(IDC_UserIDPrefix,  usr.userID);
    SetDlgItemText(IDC_UserSignature, usr.signature);
    }
  }


void IdentityDlg::onLeaveTacText()
                            {if (isNotEqual(tacText, IDC_TacticalText))     tacDirty = true;}
void IdentityDlg::onLeaveTacIDprefix()
                            {if (isNotEqual(tacIDprefix, IDC_TacIDprefix)) tacDirty = true;}
void IdentityDlg::onLeaveTacIDSig()
                            {if (isNotEqual(tacSignature, IDC_TacSignature))     tacDirty = true;}
void IdentityDlg::onLeaveUserName()
                          {if (isNotEqual(userName, IDC_UserName))            userDirty = true;}
void IdentityDlg::onLeaveUserIDprefix()
                          {if (isNotEqual(userIDPrefix, IDC_UserIDPrefix))    userDirty = true;}
void IdentityDlg::onLeaveUserSignature()
                          {if (isNotEqual(userSignature, IDC_UserSignature))  userDirty = true;}


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
  enableCtrl(IDC_CallSgnStc,       enable);
  enableCtrl(IDC_AdlTxtStc,        enable);
  enableCtrl(IDC_TacPrfxStc,          enable);
//  enableCtrl(IDC_STATIC5,          enable);
  enableCtrl(IDC_TacSigStc,          enable);
  enableCtrl(IDC_TacticalCallSign, enable);
  enableCtrl(IDC_TacticalText,     enable);
  enableCtrl(IDC_TacIDprefix,      enable);
  enableCtrl(IDC_TacSignature,     enable);
  }


void IdentityDlg::enableCtrl(int id, bool enable) {
CWnd* ctrl = (CWnd*) GetDlgItem(id); if (ctrl) ctrl->EnableWindow(enable);
  }


void IdentityDlg::OnAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void IdentityDlg::OnHelpOverview()      {help.overview(GetSafeHwnd());}
void IdentityDlg::OnHelpIdentity()      {help.oneMaster(GetSafeHwnd());}
void IdentityDlg::OnHelpAddressbook()   {help.addressBook(GetSafeHwnd());}
void IdentityDlg::OnHelpDeleteMaster()  {help.deleteMaster(GetSafeHwnd());}
void IdentityDlg::OnHelpSelNewMaster()  {help.selectNewMaster(GetSafeHwnd());}
void IdentityDlg::OnHelpSelectProfile() {help.selectProfile(GetSafeHwnd());}




///////////////---------------

//  ON_COMMAND(ID_SubjWSecurity,      &OnSubjWSecurity)
/*severity(0),, practiceDay(0)*/
//  DDX_Radio(pDX, IDC_EMERGENCY, severity);
//  DDX_Radio(pDX, IDC_MONDAY,    practiceDay);
//setSubjWSecurity();
#if 0
void IdentityDlg::setSubjWSecurity() {
  if (subjWSecurity) menu->CheckMenuItem(ID_SubjWSecurity, MF_CHECKED   | MF_BYCOMMAND);
  else               menu->CheckMenuItem(ID_SubjWSecurity, MF_UNCHECKED | MF_BYCOMMAND);

  GetDlgItem(IDC_EMERGENCY)->EnableWindow(subjWSecurity);
  GetDlgItem(IDC_URGENT)->EnableWindow(subjWSecurity);
  GetDlgItem(IDC_OTHER)->EnableWindow(subjWSecurity);
  }
#endif
//subjWSecurity(false),
//  DDX_Radio(pDX, IDC_Standard,              subjStyle);
#if 0
  //COleDateTime ctm;
  ctm = COleDateTime::GetCurrentTime();
  s = ctm.Format(_T("%H%M %x"));
  todaysDate = ctm.Format(_T("%x"));
#endif

//void IdentityDlg::OnSubjWSecurity() {subjWSecurity = !subjWSecurity; setSubjWSecurity();}

