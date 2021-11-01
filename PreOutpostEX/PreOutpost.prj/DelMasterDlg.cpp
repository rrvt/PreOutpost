// DelMasterDlg.cpp : implementation file

#include "stdafx.h"
#include "PreOutpost.h"
#include "AboutDlgEx.h"
#include "DelMasterDlg.h"
#include "filename.h"


// DelMasterDlg dialog

IMPLEMENT_DYNAMIC(DelMasterDlg, CDialog)


DelMasterDlg::DelMasterDlg(CWnd* pParent) : CDialog(DelMasterDlg::IDD, pParent),
                                                                            MasterProfileName(_T("")) { }

void DelMasterDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, MasterProfileName);
  }


BEGIN_MESSAGE_MAP(DelMasterDlg, CDialog)
  ON_BN_CLICKED(IDC_BUTTON1, &DelMasterDlg::OnOK)
  ON_BN_CLICKED(IDC_BUTTON2, &DelMasterDlg::OnCancel)
  ON_COMMAND(ID_ABOUT32778,  &DelMasterDlg::OnAbout32778)
  ON_COMMAND(ID_HELP32777,   &DelMasterDlg::OnHelp32777)
END_MESSAGE_MAP()


// DelMasterDlg message handlers


void DelMasterDlg::OnOK() {CDialog::OnOK();}


void DelMasterDlg::OnCancel() {CDialog::OnCancel();}



DelMasterDlg::~DelMasterDlg() { }


void DelMasterDlg::OnAbout32778() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void DelMasterDlg::OnHelp32777() {
String topic;

  topic = theApp.helpFile; topic += _T(">DeleteMaster");

  ::HtmlHelp(theApp.m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 20);
  }
