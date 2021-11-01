// Class that corresponds to the Dialog Box that allows the user to select the Master Profile when there
// are two or more Master Profiles

#include "stdafx.h"
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
  ON_BN_CLICKED(IDC_BUTTON9, &SelectMasterDlg::OnOK)
  ON_LBN_DBLCLK(IDC_LIST1,   &SelectMasterDlg::OnDblclkList1)
  ON_COMMAND(ID_ABOUT32780,  &SelectMasterDlg::OnAbout32780)
  ON_COMMAND(ID_HELP32779,   &SelectMasterDlg::OnHelp32779)
END_MESSAGE_MAP()



SelectMasterDlg::~SelectMasterDlg() { }



// SelectMasterDlg message handlers

void SelectMasterDlg::OnDblclkList1() {OnOK();}
void SelectMasterDlg::OnOK() {listItems.getSelected(); CDialog::OnOK();}


void SelectMasterDlg::OnAbout32780() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void SelectMasterDlg::OnHelp32779() {
String topic;

  topic = theApp.helpFile; topic += _T(">TwoPlusMaster");

  ::HtmlHelp(theApp.m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 20);
  }
