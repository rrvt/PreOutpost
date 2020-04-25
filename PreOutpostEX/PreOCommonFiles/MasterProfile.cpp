// Class that corresponds to the Dialog Box that allows the user to select the Master Profile when there
// are two or more Master Profiles

#include "stdafx.h"
#include "PreOutpost.h"
#include "MasterProfile.h"
#ifndef Win2K
#include "afxdialogex.h"
#endif
#include "About.h"


// MasterProfile dialog


IMPLEMENT_DYNAMIC(MasterProfile, CDialog)

MasterProfile::MasterProfile(CWnd* pParent) : CDialog(MasterProfile::IDD, pParent), allMasterProfiles(0)
                                                                      {listItems.init(this, IDC_LIST1);}


BOOL MasterProfile::OnInitDialog() {

  CDialog::OnInitDialog();

  listItems.addToControl(); return TRUE;
  }


void MasterProfile::DoDataExchange(CDataExchange* pDX) {

  CDialog::DoDataExchange(pDX);
  DDX_Radio(pDX, IDC_RADIO5, allMasterProfiles);
  }


BEGIN_MESSAGE_MAP(MasterProfile, CDialog)
  ON_BN_CLICKED(IDC_BUTTON9, &MasterProfile::OnOK)
  ON_LBN_DBLCLK(IDC_LIST1,   &MasterProfile::OnDblclkList1)
  ON_COMMAND(ID_ABOUT32780,  &MasterProfile::OnAbout32780)
  ON_COMMAND(ID_HELP32779,   &MasterProfile::OnHelp32779)
END_MESSAGE_MAP()



MasterProfile::~MasterProfile() { }



// MasterProfile message handlers

void MasterProfile::OnDblclkList1() {OnOK();}
void MasterProfile::OnOK() {listItems.getSelected(); CDialog::OnOK();}


void MasterProfile::OnAbout32780() {CAboutDlg aboutDlg; aboutDlg.DoModal();}


void MasterProfile::OnHelp32779() {
String topic;

  topic = theApp.helpFile; topic += _T(">TwoPlusMaster");

  ::HtmlHelp(theApp.m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 20);
  }
