// DelMasterDlg.cpp : implementation file

#include "pch.h"
#include "PreOutpost.h"
#include "AboutDlgEx.h"
#include "DelMasterDlg.h"
#include "filename.h"


// DelMasterDlg dialog

IMPLEMENT_DYNAMIC(DelMasterDlg, CDialogEx)


DelMasterDlg::DelMasterDlg(CWnd* pParent) : CDialogEx(DelMasterDlg::IDD, pParent),
                                                                            MasterProfileName(_T("")) { }

void DelMasterDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, MasterProfileName);
  }


BEGIN_MESSAGE_MAP(DelMasterDlg, CDialog)
  ON_BN_CLICKED(IDC_BUTTON1,        &OnOK)
  ON_BN_CLICKED(IDC_BUTTON2,        &OnCancel)
  ON_COMMAND(ID_ABOUT3,             &OnAbout)
  ON_COMMAND(ID_HELP_OVERVIEW,      &OnHelpOverview)
  ON_COMMAND(ID_HELP_IDENTITY,      &OnHelpIdentity)
  ON_COMMAND(ID_HELP_ADDRESSBOOK,   &OnHelpAddressbook)
  ON_COMMAND(ID_HELP_MakeMaster,    &OnHelpMakeMaster)
  ON_COMMAND(ID_HELP_DeleteMaster,  &OnHelpDeleteMaster)
  ON_COMMAND(ID_HELP_SelNewMaster,  &OnHelpSelNewMaster)
  ON_COMMAND(ID_HELP_SelectProfile, &OnHelpSelectProfile)

#ifdef DialogSizable01
  ON_WM_SIZE()
#endif

END_MESSAGE_MAP()


// DelMasterDlg message handlers


void DelMasterDlg::OnOK() {CDialog::OnOK();}


void DelMasterDlg::OnCancel() {CDialog::OnCancel();}



DelMasterDlg::~DelMasterDlg() { }


void DelMasterDlg::OnAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void DelMasterDlg::OnHelpMakeMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">CreateMaster");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 20);
  }


void DelMasterDlg::OnHelpOverview() {
String topic;

  topic = theApp.helpFile; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void DelMasterDlg::OnHelpIdentity() {
String topic;

  topic = theApp.helpFile; topic += _T(">OneMaster");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void DelMasterDlg::OnHelpAddressbook() {
String topic;

  topic = theApp.helpFile; topic += _T(">AddressBook");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void DelMasterDlg::OnHelpDeleteMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">DeleteMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void DelMasterDlg::OnHelpSelNewMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">SelectProfile");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void DelMasterDlg::OnHelpSelectProfile() {
String topic;

  topic = theApp.helpFile; topic += _T(">TwoPlusMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }



#ifdef DialogSizable01

void DelMasterDlg::OnSize(UINT nType, int cx, int cy) {
CRect winRect;

  CDialogEx::OnSize(nType, cx, cy);

  if (!isInitialized) return;

  GetWindowRect(&winRect);   winPos.set(winRect);   toolBar.move(winRect);   statusBar.move(winRect);
  }
#endif

