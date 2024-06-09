// AddressDlg.cpp : implementation file
//

#include "pch.h"
#include "Addresses.h"
#include "AddressDlg.h"
#include "RegExpr.h"
#include "resource.h"


enum MsgEnum {BadCharsMsg, ExistsMsg, DeletedMsg};

static TCchar* MsgVctr[] = {
                      _T("*** Name may only contain letters, digits, periods and underscores ***"),
                      _T("*** Address with Name already exists, change name or edit Address ***"),
                      _T("*** This item will be marked to be deleted ***")
                      };

// AddressDlg dialog

IMPLEMENT_DYNAMIC(AddressDlg, CDialogEx)


BEGIN_MESSAGE_MAP(AddressDlg, CDialogEx)
  ON_COMMAND(     IDOK,       &OnOK)
  ON_BN_CLICKED(  IDCANCEL,   &OnCancel)
  ON_EN_KILLFOCUS(IDC_Name,   &onLeaveName)
  ON_BN_CLICKED(  IDC_Delete, &onDelete)
END_MESSAGE_MAP()


AddressDlg::AddressDlg(CWnd* pParent) : CDialogEx(IDD_Address, pParent), title(_T("Edit Address")),
                                          name(_T("")),   organization(_T("")), actual(_T("")),
                                          cellPhone(_T("")), homePhone(_T("")), businessPhone(_T("")),
                                          agency1Name(_T("")), agency1Phone(_T("")),
                                          agency2Name(_T("")), agency2Phone(_T("")),
                                          notes(_T("")), moreNotes(_T("")),
                                          msgSeen(NilMsg), isNewAddr(false), isDeleted(false) {  }


AddressDlg::~AddressDlg() { }


BOOL AddressDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();   versionCtl.SetWindowText(version);   SetWindowText(title);

  return TRUE;
  }


void AddressDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(   pDX, IDC_Name,      name);
  DDX_Text(   pDX, IDC_OrgLoc,    organization);
  DDX_Text(   pDX, IDC_ActAdr,    actual);
  DDX_Text(   pDX, IDC_Notes,     notes);
  DDX_Text(   pDX, IDC_CellPh,    cellPhone);
  DDX_Text(   pDX, IDC_HomePh,    homePhone);
  DDX_Text(   pDX, IDC_BsnsPh,    businessPhone);
  DDX_Text(   pDX, IDC_Agcy1Name, agency1Name);
  DDX_Text(   pDX, IDC_Agcy1Ph,   agency1Phone);
  DDX_Text(   pDX, IDC_Agcy2Name, agency2Name);
  DDX_Text(   pDX, IDC_Agcy2Ph,   agency2Phone);
  DDX_Text(   pDX, IDC_MoreNotes, moreNotes);

  DDX_Control(pDX, IDC_Version,   versionCtl);
  DDX_Control(pDX, IDC_Name,      nameCtrl);
  DDX_Control(pDX, IDC_Message,   MessageCtrl);
  DDX_Control(pDX, IDC_OrgLoc,    orgLocCtrl);
  }


static RegExpr re = _T("^[A-Z0-9_.]*$");


void AddressDlg::onLeaveName() {

  nameCtrl.GetWindowText(name);

  if (!re.match(name))                   {if (showMsg(BadCharsMsg)) nameCtrl.SetFocus();   return;}
  if (isNewAddr && addresses.find(name)) {if (showMsg(ExistsMsg))   nameCtrl.SetFocus();   return;}

  hideMsg();
  }


void AddressDlg::OnOK() {

  onLeaveName();   if (msgSeen != NilMsg) return;

  CDialogEx::OnOK();
  }


void AddressDlg::onDelete() {

  if (isNewAddr) return;

  isDeleted ^= true;

  if (isDeleted) showMsg(DeletedMsg);
  else           hideMsg();
  }


void AddressDlg::OnCancel() {CDialogEx::OnCancel();}


bool AddressDlg::showMsg(MsgEnum x) {

  if (x == msgSeen || x >= NilMsg) return false;

  MessageCtrl.SetWindowText(MsgVctr[x]);   MessageCtrl.ModifyStyle(0, WS_VISIBLE);  Invalidate();

  Beep(750, 300);   msgSeen = x;   return true;
  }


void AddressDlg::hideMsg()
         {if (msgSeen) MessageCtrl.ModifyStyle(WS_VISIBLE, 0);   msgSeen = NilMsg;   Invalidate();}
