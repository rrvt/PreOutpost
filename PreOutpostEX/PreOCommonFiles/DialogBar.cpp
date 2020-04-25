// Class that corresponds to Dialog box to select Master Profile

#include "stdafx.h"
#include "PreOutpost.h"
#include "DialogBar.h"
#ifndef Win2K
#include "afxdialogex.h"
#endif
#include "About.h"


// DialogBar dialog

IMPLEMENT_DYNAMIC(DialogBar, CDialog)

DialogBar::DialogBar(CWnd* pParent) :
                            CDialog(DialogBar::IDD, pParent) {listItems.init(this, IDC_LIST1);}


BOOL DialogBar::OnInitDialog() {

  CDialog::OnInitDialog();

  listItems.addToControl();

  return TRUE;  // return TRUE unless you set the focus to a control
  }             // EXCEPTION: OCX Property Pages should return FALSE


void DialogBar::DoDataExchange(CDataExchange* pDX) {CDialog::DoDataExchange(pDX);}


BEGIN_MESSAGE_MAP(DialogBar, CDialog)
  ON_BN_CLICKED(IDC_BUTTON1, &DialogBar::OnOK)
  ON_LBN_DBLCLK(IDC_LIST1,   &DialogBar::OnDblclkList1)
  ON_COMMAND(ID_ABOUT32780,  &DialogBar::OnAbout32780)
  ON_COMMAND(ID_HELP32779,   &DialogBar::OnHelp32779)
END_MESSAGE_MAP()


// DialogBar message handlers


void DialogBar::OnOK()          {listItems.getSelected(); CDialog::OnOK();}



void DialogBar::OnDblclkList1() {OnOK();}


DialogBar::~DialogBar() {}


void DialogBar::OnAbout32780() {CAboutDlg aboutDlg; aboutDlg.DoModal();}


void DialogBar::OnHelp32779() {
String topic;

  topic = theApp.helpFile; topic += _T(">SelectProfile");

  ::HtmlHelp(theApp.m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 20);
  }
