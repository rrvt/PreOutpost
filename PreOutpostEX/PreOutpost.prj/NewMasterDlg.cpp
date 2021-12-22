// Class that corresponds to Dialog box to select Master Profile

#include "stdafx.h"
#include "NewMasterDlg.h"
#include "AboutDlgEx.h"
#include "PreOutpost.h"


// NewMasterDlg dialog

IMPLEMENT_DYNAMIC(NewMasterDlg, CDialog)

NewMasterDlg::NewMasterDlg(CWnd* pParent) :
                            CDialog(NewMasterDlg::IDD, pParent) {listItems.init(this, IDC_LIST1);}


BOOL NewMasterDlg::OnInitDialog() {

  CDialog::OnInitDialog();

  listItems.addToControl();

  return TRUE;  // return TRUE unless you set the focus to a control
  }             // EXCEPTION: OCX Property Pages should return FALSE


void NewMasterDlg::DoDataExchange(CDataExchange* pDX) {CDialog::DoDataExchange(pDX);}


BEGIN_MESSAGE_MAP(NewMasterDlg, CDialog)
  ON_BN_CLICKED(IDC_BUTTON1,        &OnOK)
  ON_LBN_DBLCLK(IDC_LIST1,          &OnDblclkList1)
  ON_COMMAND(ID_ABOUT4,             &onAbout)
  ON_COMMAND(ID_HELP_OVERVIEW,      &OnHelpOverview)
  ON_COMMAND(ID_HELP_IDENTITY,      &OnHelpIdentity)
  ON_COMMAND(ID_HELP_ADDRESSBOOK,   &OnHelpAddressbook)
  ON_COMMAND(ID_HELP_MakeMaster,    &OnHelpMakeMaster)
  ON_COMMAND(ID_HELP_DeleteMaster,  &OnHelpDeleteMaster)
  ON_COMMAND(ID_HELP_SelNewMaster,  &OnHelpSelNewMaster)
  ON_COMMAND(ID_HELP_SelectProfile, &OnHelpSelectProfile)
END_MESSAGE_MAP()


// NewMasterDlg message handlers


void NewMasterDlg::OnOK()          {listItems.getSelected(); CDialog::OnOK();}



void NewMasterDlg::OnDblclkList1() {OnOK();}


NewMasterDlg::~NewMasterDlg() {}


void NewMasterDlg::onAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}

#if 0
void NewMasterDlg::OnHelp32779() {
String topic;

  topic = theApp.helpFile; topic += _T(">SelectProfile");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 20);
  }
#endif


void NewMasterDlg::OnHelpMakeMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">CreateMaster");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 20);
  }



void NewMasterDlg::OnHelpOverview() {
String topic;

  topic = theApp.helpFile; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void NewMasterDlg::OnHelpIdentity() {
String topic;

  topic = theApp.helpFile; topic += _T(">OneMaster");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void NewMasterDlg::OnHelpAddressbook() {
String topic;

  topic = theApp.helpFile; topic += _T(">AddressBook");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void NewMasterDlg::OnHelpDeleteMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">DeleteMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void NewMasterDlg::OnHelpSelNewMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">SelectProfile");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }



void NewMasterDlg::OnHelpSelectProfile() {
String topic;

  topic = theApp.helpFile; topic += _T(">TwoPlusMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }

