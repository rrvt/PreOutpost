// EditAddrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OPaddress.h"
#include "Addresses.h"
#include "EditAddrDlg.h"
#include "match.h"


static TCchar* BadChars = _T("*** May only contain letters, digits, periods and underscores ***");
static TCchar* Exists   = _T("Address with Name and Organization already exists");


// EditAddrDlg dialog

IMPLEMENT_DYNAMIC(EditAddrDlg, CDialogEx)



BEGIN_MESSAGE_MAP(EditAddrDlg, CDialogEx)
//  ON_EN_KILLFOCUS(IDC_EDIT1, &EditAddrDlg::OnLeaveName)
//  ON_EN_KILLFOCUS(IDC_EDIT2, &EditAddrDlg::OnLeaveOrgLoc)
  ON_BN_CLICKED(IDOK, &EditAddrDlg::OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, &EditAddrDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


EditAddrDlg::EditAddrDlg(CWnd* pParent) : CDialogEx(IDD_EditAddress, pParent), title(_T("Edit Address")),
                                          name(_T("")),   orgLoc(_T("")), actual(_T("")),
                                          cellPhone(_T("")), homePhone(_T("")), businessPhone(_T("")),
                                          agency1Name(_T("")), agency1Phone(_T("")),
                                          agency2Name(_T("")), agency2Phone(_T("")),
                                          notes(_T("")), moreNotes(_T("")), msgSeen(false),
                                          newAddr(false) {  }


EditAddrDlg::~EditAddrDlg() { }



BOOL EditAddrDlg::OnInitDialog() {

  CDialogEx::OnInitDialog();

  SetWindowText(title);  return TRUE;
  }


void EditAddrDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, name);
  DDX_Text(pDX, IDC_EDIT2, orgLoc);
  DDX_Text(pDX, IDC_EDIT3, actual);
  DDX_Text(pDX, IDC_EDIT5, cellPhone);
  DDX_Text(pDX, IDC_EDIT4, homePhone);
  DDX_Text(pDX, IDC_EDIT6, businessPhone);
  DDX_Text(pDX, IDC_EDIT7, agency1Name);
  DDX_Text(pDX, IDC_EDIT8, agency1Phone);
  DDX_Text(pDX, IDC_EDIT9, agency2Name);
  DDX_Text(pDX, IDC_EDIT10, agency2Phone);
  DDX_Text(pDX, IDC_EDIT11, notes);
  DDX_Text(pDX, IDC_EDIT12, moreNotes);
  DDX_Control(pDX, IDC_EDIT1, nameCtrl);
  DDX_Control(pDX, IDC_Message, MessageCtrl);
  DDX_Control(pDX, IDC_EDIT2, orgLocCtrl);
}


static RegExpr re = _T("^[a-zA-Z0-9_.]*$");


void EditAddrDlg::OnLeaveName() {

  if (msgSeen == true) return;

  nameCtrl.GetWindowText(name);
  orgLocCtrl.GetWindowText(orgLoc);

  if (!re.match(name)) {showMsg(BadChars);  nameCtrl.SetFocus(); return;}

  if (newAddr && !orgLoc.GetLength() && checkKey()) {showMsg(Exists);  nameCtrl.SetFocus(); return;}

  hideMsg();
  }


void EditAddrDlg::OnLeaveOrgLoc() {

  if (msgSeen == true) return;

  nameCtrl.GetWindowText(name);
  orgLocCtrl.GetWindowText(orgLoc);

  if (!re.match(orgLoc)) {showMsg(BadChars);  orgLocCtrl.SetFocus(); return;}

  if (newAddr && checkKey()) {showMsg(Exists);  orgLocCtrl.SetFocus(); return;}

  hideMsg();
  }


void EditAddrDlg::showMsg(TCchar* msg) {

  MessageCtrl.SetWindowText(msg);   MessageCtrl.ModifyStyle(0, WS_VISIBLE);  Invalidate();

  if (!msgSeen) Beep(750, 300);   msgSeen = true;
  }


void EditAddrDlg::hideMsg() {if (msgSeen) MessageCtrl.ModifyStyle(WS_VISIBLE, 0);  Invalidate();}


bool EditAddrDlg::checkKey() {
String key;

  makeKey(name, orgLoc, key);
  key = orgLoc.GetLength() ? name + _T('.') + orgLoc : name;

  return addresses.find(key);
  }


void EditAddrDlg::OnBnClickedOk() {
String key;
int    n;

  nameCtrl.GetWindowText(name);
  orgLocCtrl.GetWindowText(orgLoc);

  makeKey(name, orgLoc, key);   n = addresses.noFound(key);

  if (newAddr) {
    if (n) {
      showMsg(_T("Not a new address, please change name or organization."));
      }
    }
  else if (n > 1) {
    showMsg(_T("Address is ambiguous, please change name or organization."));
    nameCtrl.SetFocus(); return;
    }

  CDialogEx::OnOK();
  }


void EditAddrDlg::OnBnClickedCancel() {


  CDialogEx::OnCancel();
  }
