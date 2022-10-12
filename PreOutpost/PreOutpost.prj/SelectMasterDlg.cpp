// Class that corresponds to the Dialog Box that allows the user to select the Master Profile when there
// are two or more Master Profiles

#include "pch.h"
#include "PreOutpost.h"
#include "SelectMasterDlg.h"
#ifndef Win2K
#include "afxdialogex.h"
#endif
#include "AboutDlgEx.h"


// SelectMasterDlg dialog


IMPLEMENT_DYNAMIC(SelectMasterDlg, CDialog)

SelectMasterDlg::SelectMasterDlg(CWnd* pParent) : CDialog(SelectMasterDlg::IDD, pParent), allProfiles(0)
                                                                      {listItems.init(this, IDC_LIST1);}


BOOL SelectMasterDlg::OnInitDialog() {

  CDialog::OnInitDialog();

  listItems.addToControl(); return TRUE;
  }


void SelectMasterDlg::DoDataExchange(CDataExchange* pDX) {

  CDialog::DoDataExchange(pDX);
  DDX_Radio(pDX, IDC_RADIO5, allProfiles);
  }


BEGIN_MESSAGE_MAP(SelectMasterDlg, CDialog)
  ON_BN_CLICKED(IDC_BUTTON9,        &OnOK)
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



SelectMasterDlg::~SelectMasterDlg() { }



// SelectMasterDlg message handlers

void SelectMasterDlg::OnDblclkList1() {OnOK();}
void SelectMasterDlg::OnOK() {listItems.getSelected(); CDialog::OnOK();}


void SelectMasterDlg::onAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void SelectMasterDlg::OnHelpMakeMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">CreateMaster");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 20);
  }



void SelectMasterDlg::OnHelpOverview() {
String topic;

  topic = theApp.helpFile; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void SelectMasterDlg::OnHelpIdentity() {
String topic;

  topic = theApp.helpFile; topic += _T(">OneMaster");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void SelectMasterDlg::OnHelpAddressbook() {
String topic;

  topic = theApp.helpFile; topic += _T(">AddressBook");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void SelectMasterDlg::OnHelpDeleteMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">DeleteMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void SelectMasterDlg::OnHelpSelNewMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">SelectProfile");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void SelectMasterDlg::OnHelpSelectProfile() {
String topic;

  topic = theApp.helpFile; topic += _T(">TwoPlusMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }

