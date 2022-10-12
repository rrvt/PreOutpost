// AddressDlg.cpp : implementation file
//

#include "pch.h"
#include "Addresses.h"
#include "AddressDlg.h"
#include "match.h"
#include "resource.h"


static TCchar* BadChars = _T("*** May only contain letters, digits, periods and underscores ***");
static TCchar* Exists   = _T("*** Address with Name already exists, change name or edit Address ***");


// AddressDlg dialog

IMPLEMENT_DYNAMIC(AddressDlg, CDialogEx)



BEGIN_MESSAGE_MAP(AddressDlg, CDialogEx)
  ON_BN_CLICKED(  IDOK,      &AddressDlg::OnBnClickedOk)
  ON_EN_KILLFOCUS(IDC_Name,  &AddressDlg::onLeaveName)
END_MESSAGE_MAP()


AddressDlg::AddressDlg(CWnd* pParent) : CDialogEx(IDD_Address, pParent), title(_T("Edit Address")),
                                          name(_T("")),   orgLoc(_T("")), actual(_T("")),
                                          cellPhone(_T("")), homePhone(_T("")), businessPhone(_T("")),
                                          agency1Name(_T("")), agency1Phone(_T("")),
                                          agency2Name(_T("")), agency2Phone(_T("")),
                                          notes(_T("")), moreNotes(_T("")),
                                          isNewAddr(false) {  }


AddressDlg::~AddressDlg() { }



BOOL AddressDlg::OnInitDialog()
  {CDialogEx::OnInitDialog();   versionCtl.SetWindowText(version);   SetWindowText(title);   return TRUE;}


void AddressDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_Name, name);
  DDX_Text(pDX, IDC_OrgLoc, orgLoc);
  DDX_Text(pDX, IDC_ActAdr, actual);
  DDX_Text(pDX, IDC_Notes, notes);
  DDX_Text(pDX, IDC_CellPh, cellPhone);
  DDX_Text(pDX, IDC_HomePh, homePhone);
  DDX_Text(pDX, IDC_BsnsPh, businessPhone);
  DDX_Text(pDX, IDC_Agcy1Name, agency1Name);
  DDX_Text(pDX, IDC_Agcy1Ph, agency1Phone);
  DDX_Text(pDX, IDC_Agcy2Name, agency2Name);
  DDX_Text(pDX, IDC_Agcy2Ph, agency2Phone);
  DDX_Text(pDX, IDC_MoreNotes, moreNotes);

  DDX_Control(pDX, IDC_Version, versionCtl);
  DDX_Control(pDX, IDC_Name, nameCtrl);
  DDX_Control(pDX, IDC_Message, MessageCtrl);
  DDX_Control(pDX, IDC_OrgLoc, orgLocCtrl);
  }


static RegExpr re = _T("^[A-Z0-9_.]*$");


void AddressDlg::onLeaveName() {

  nameCtrl.GetWindowText(name);

  if (!re.match(name))      {showMsg(BadChars);  nameCtrl.SetFocus(); return;}
  if (isNewAddr && addresses.find(name)) {showMsg(Exists);    nameCtrl.SetFocus(); return;}

  hideMsg();
  }


void AddressDlg::showMsg(TCchar* msg) {

  MessageCtrl.SetWindowText(msg);   MessageCtrl.ModifyStyle(0, WS_VISIBLE);  Invalidate();

  if (!msgSeen) Beep(750, 300);   msgSeen = true;
  }


void AddressDlg::hideMsg()
                  {if (msgSeen) MessageCtrl.ModifyStyle(WS_VISIBLE, 0); msgSeen = false;  Invalidate();}


void AddressDlg::OnBnClickedOk() {CDialogEx::OnOK();}
