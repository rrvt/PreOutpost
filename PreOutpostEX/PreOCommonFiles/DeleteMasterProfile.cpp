// DeleteMasterProfile.cpp : implementation file

#include "stdafx.h"
#include "PreOutpost.h"
#include "DeleteMasterProfile.h"
#include "filename.h"
#include "About.h"


#if 0
// DeleteMasterProfile dialog

IMPLEMENT_DYNAMIC(DeleteMasterProfile, CDialog)


DeleteMasterProfile::DeleteMasterProfile(CWnd* pParent) :
                                  CDialog(DeleteMasterProfile::IDD, pParent),
                                  MasterProfileName(_T("")) { }


void DeleteMasterProfile::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, MasterProfileName);
  }


BEGIN_MESSAGE_MAP(DeleteMasterProfile, CDialog)
  ON_BN_CLICKED(IDC_BUTTON1, &DeleteMasterProfile::OnOK)
  ON_BN_CLICKED(IDC_BUTTON2, &DeleteMasterProfile::OnCancel)
  ON_COMMAND(ID_ABOUT32778, &DeleteMasterProfile::OnAbout32778)
  ON_COMMAND(ID_HELP32777, &DeleteMasterProfile::OnHelp32777)
END_MESSAGE_MAP()


// DeleteMasterProfile message handlers


void DeleteMasterProfile::OnOK() {CDialog::OnOK();}


void DeleteMasterProfile::OnCancel() {CDialog::OnCancel();}


BOOL DeleteMasterProfile::OnInitDialog() {
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
  }
#else

// DeleteMasterProfile dialog

IMPLEMENT_DYNAMIC(DeleteMasterProfile, CDialog)


DeleteMasterProfile::DeleteMasterProfile(CWnd* pParent) :
                                  CDialog(DeleteMasterProfile::IDD, pParent),
                                  MasterProfileName(_T("")) { }


void DeleteMasterProfile::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, MasterProfileName);
  }


BEGIN_MESSAGE_MAP(DeleteMasterProfile, CDialog)
  ON_BN_CLICKED(IDC_BUTTON1, &DeleteMasterProfile::OnOK)
  ON_BN_CLICKED(IDC_BUTTON2, &DeleteMasterProfile::OnCancel)
  ON_COMMAND(ID_ABOUT32778,  &DeleteMasterProfile::OnAbout32778)
  ON_COMMAND(ID_HELP32777,   &DeleteMasterProfile::OnHelp32777)
END_MESSAGE_MAP()


// DeleteMasterProfile message handlers


void DeleteMasterProfile::OnOK() {CDialog::OnOK();}


void DeleteMasterProfile::OnCancel() {CDialog::OnCancel();}


BOOL DeleteMasterProfile::OnInitDialog() {
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
  }
#endif


DeleteMasterProfile::~DeleteMasterProfile() { }


void DeleteMasterProfile::OnAbout32778() {CAboutDlg aboutDlg; aboutDlg.DoModal();}


void DeleteMasterProfile::OnHelp32777() {
String topic;

  topic = theApp.helpFile; topic += _T(">DeleteMaster");

  ::HtmlHelp(theApp.m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 20);
  }
