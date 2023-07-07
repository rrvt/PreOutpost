// Class that corresponds to the Dialog Box that allows the user to create a new Master Profile or Delete
// a Master Profile.

#include "pch.h"
#include "PreOutpost.h"
#include "AboutDlgEx.h"
#include "MasterMgmtDlg.h"
#include "BBSinfo.h"


// MasterMgmtDlg dialog

IMPLEMENT_DYNAMIC(MasterMgmtDlg, CDialog)


BEGIN_MESSAGE_MAP(MasterMgmtDlg, CDialog)
  ON_BN_CLICKED(IDC_BUTTON12,       &createNew)
  ON_BN_CLICKED(IDC_BUTTON13,       &delSelected)
  ON_BN_CLICKED(IDC_BUTTON1,        &OnClickedButton1)

  ON_COMMAND(ID_SetBBSsuffixes,     &OnSetBBSsuffixes)
  ON_COMMAND(ID_ABOUT1,             &OnAbout)
  ON_COMMAND(ID_HELP_OVERVIEW,      &OnHelpOverview)
  ON_COMMAND(ID_HELP_IDENTITY,      &OnHelpIdentity)
  ON_COMMAND(ID_HELP_ADDRESSBOOK,   &OnHelpAddressbook)
  ON_COMMAND(ID_HELP_MakeMaster,    &OnHelpMakeMaster)
  ON_COMMAND(ID_HELP_DeleteMaster,  &OnHelpDeleteMaster)
  ON_COMMAND(ID_HELP_SelNewMaster,  &OnHelpSelNewMaster)
  ON_COMMAND(ID_HELP_SelectProfile, &OnHelpSelectProfile)

#ifdef DialogSizable02
  ON_WM_SIZE()
#endif


END_MESSAGE_MAP()


MasterMgmtDlg::MasterMgmtDlg(CWnd* pParent) :
                  CDialog(MasterMgmtDlg::IDD, pParent) {listItems.init(this, IDC_LIST1);}


BOOL MasterMgmtDlg::OnInitDialog() {
  CDialog::OnInitDialog();
  listItems.addToControl();
  return TRUE;                                    // return TRUE unless you set the focus to a control
  }                                               // EXCEPTION: OCX Property Pages should return FALSE


void MasterMgmtDlg::DoDataExchange(CDataExchange* pDX) {CDialog::DoDataExchange(pDX);}


MasterMgmtDlg::~MasterMgmtDlg() { }



void MasterMgmtDlg::OnSetBBSsuffixes() {bbsInfo.getSuffixes();}


// MasterMgmtDlg message handlers


void MasterMgmtDlg::createNew() {listItems.getSelected(); EndDialog(CreateMaster);}


void MasterMgmtDlg::delSelected() {listItems.getSelected(); EndDialog(DeleteMaster);}


void MasterMgmtDlg::OnClickedButton1() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void MasterMgmtDlg::OnAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void MasterMgmtDlg::OnHelpMakeMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">CreateMaster");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 20);
  }



void MasterMgmtDlg::OnHelpOverview() {
String topic;

  topic = theApp.helpFile; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void MasterMgmtDlg::OnHelpIdentity() {
String topic;

  topic = theApp.helpFile; topic += _T(">OneMaster");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void MasterMgmtDlg::OnHelpAddressbook() {
String topic;

  topic = theApp.helpFile; topic += _T(">AddressBook");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void MasterMgmtDlg::OnHelpDeleteMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">DeleteMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void MasterMgmtDlg::OnHelpSelNewMaster() {
String topic;

  topic = theApp.helpFile; topic += _T(">SelectProfile");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


void MasterMgmtDlg::OnHelpSelectProfile() {
String topic;

  topic = theApp.helpFile; topic += _T(">TwoPlusMaster");

  ::HtmlHelp(GetSafeHwnd(), topic, HH_DISPLAY_TOC, 0);
  }


#ifdef DialogSizable02

void MasterMgmtDlg::OnSize(UINT nType, int cx, int cy) {
CRect winRect;

  CDialogEx::OnSize(nType, cx, cy);

  if (!isInitialized) return;

  GetWindowRect(&winRect);   winPos.set(winRect);   toolBar.move(winRect);   statusBar.move(winRect);
  }
#endif



