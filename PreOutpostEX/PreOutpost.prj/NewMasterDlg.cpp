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
  ON_BN_CLICKED(IDC_BUTTON1, &NewMasterDlg::OnOK)
  ON_LBN_DBLCLK(IDC_LIST1,   &NewMasterDlg::OnDblclkList1)
  ON_COMMAND(ID_ABOUT32780,  &NewMasterDlg::OnAbout32780)
  ON_COMMAND(ID_HELP32779,   &NewMasterDlg::OnHelp32779)
END_MESSAGE_MAP()


// NewMasterDlg message handlers


void NewMasterDlg::OnOK()          {listItems.getSelected(); CDialog::OnOK();}



void NewMasterDlg::OnDblclkList1() {OnOK();}


NewMasterDlg::~NewMasterDlg() {}


void NewMasterDlg::OnAbout32780() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void NewMasterDlg::OnHelp32779() {
String topic;

  topic = theApp.helpFile; topic += _T(">SelectProfile");

  ::HtmlHelp(theApp.m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 20);
  }
