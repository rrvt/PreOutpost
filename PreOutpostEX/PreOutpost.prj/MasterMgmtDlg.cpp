// Class that corresponds to the Dialog Box that allows the user to create a new Master Profile or Delete
// a Master Profile.

#include "stdafx.h"
#include "PreOutpost.h"
#include "AboutDlgEx.h"
#include "MasterMgmtDlg.h"
#include "BBSinfo.h"


// MasterMgmtDlg dialog

IMPLEMENT_DYNAMIC(MasterMgmtDlg, CDialog)


MasterMgmtDlg::MasterMgmtDlg(CWnd* pParent) :
                  CDialog(MasterMgmtDlg::IDD, pParent) {listItems.init(this, IDC_LIST1);}


BOOL MasterMgmtDlg::OnInitDialog() {
  CDialog::OnInitDialog();
  listItems.addToControl();
  return TRUE;                                    // return TRUE unless you set the focus to a control
  }                                               // EXCEPTION: OCX Property Pages should return FALSE


void MasterMgmtDlg::DoDataExchange(CDataExchange* pDX) {CDialog::DoDataExchange(pDX);}


BEGIN_MESSAGE_MAP(MasterMgmtDlg, CDialog)
  ON_BN_CLICKED(IDC_BUTTON12,   &MasterMgmtDlg::createNew)
  ON_BN_CLICKED(IDC_BUTTON13,   &MasterMgmtDlg::delSelected)
  ON_BN_CLICKED(IDC_BUTTON1,    &MasterMgmtDlg::OnClickedButton1)

  ON_COMMAND(ID_SetBBSsuffixes, &MasterMgmtDlg::OnSetBBSsuffixes)
  ON_COMMAND(ID_ABOUT32775,     &MasterMgmtDlg::OnAbout32775)
  ON_COMMAND(ID_HELP32776,      &MasterMgmtDlg::OnHelp32776)
END_MESSAGE_MAP()


MasterMgmtDlg::~MasterMgmtDlg() { }



void MasterMgmtDlg::OnSetBBSsuffixes() {bbsInfo.getSuffixes();}


// MasterMgmtDlg message handlers


void MasterMgmtDlg::createNew() {listItems.getSelected(); EndDialog(CreateMaster);}


void MasterMgmtDlg::delSelected() {listItems.getSelected(); EndDialog(DeleteMaster);}


void MasterMgmtDlg::OnClickedButton1() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void MasterMgmtDlg::OnAbout32775() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void MasterMgmtDlg::OnHelp32776() {
String topic;

  topic = theApp.helpFile; topic += _T(">CreateMaster");

  ::HtmlHelp(theApp.m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 20);
  }
