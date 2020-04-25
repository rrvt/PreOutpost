// Class that corresponds to the Dialog Box that allows the user to create a new Master Profile or Delete
// a Master Profile.

#include "stdafx.h"
#include "PreOutpost.h"
#include "ManageMasterProfiles.h"
#include "About.h"
#include "BBSSuffix.h"


#if 0

// ManageMasterProfiles dialog

IMPLEMENT_DYNAMIC(ManageMasterProfiles, CDialog)


ManageMasterProfiles::ManageMasterProfiles(CWnd* pParent) :
                  CDialog(ManageMasterProfiles::IDD, pParent), listItems(this, IDC_LIST1) { }


BOOL ManageMasterProfiles::OnInitDialog() {
  CDialog::OnInitDialog();
  listItems.addToControl();
  return TRUE;                                    // return TRUE unless you set the focus to a control
  }                                               // EXCEPTION: OCX Property Pages should return FALSE


void ManageMasterProfiles::DoDataExchange(CDataExchange* pDX) {CDialog::DoDataExchange(pDX);}


BEGIN_MESSAGE_MAP(ManageMasterProfiles, CDialog)
  ON_BN_CLICKED(IDC_BUTTON12,   &ManageMasterProfiles::createNewMaster)
  ON_BN_CLICKED(IDC_BUTTON13,   &ManageMasterProfiles::deleteSelectedMaster)
  ON_BN_CLICKED(IDC_BUTTON1,    &ManageMasterProfiles::OnClickedButton1)

  ON_COMMAND(ID_SetBBSsuffixes, &ManageMasterProfiles::OnSetBBSsuffixes)
  ON_COMMAND(ID_ABOUT32775,     &ManageMasterProfiles::OnAbout32775)

  ON_COMMAND(ID_HELP32776,      &ManageMasterProfiles::OnHelp32776)
END_MESSAGE_MAP()

#else

// ManageMasterProfiles dialog

IMPLEMENT_DYNAMIC(ManageMasterProfiles, CDialog)


ManageMasterProfiles::ManageMasterProfiles(CWnd* pParent) :
                  CDialog(ManageMasterProfiles::IDD, pParent) {listItems.init(this, IDC_LIST1);}


BOOL ManageMasterProfiles::OnInitDialog() {
  CDialog::OnInitDialog();
  listItems.addToControl();
  return TRUE;                                    // return TRUE unless you set the focus to a control
  }                                               // EXCEPTION: OCX Property Pages should return FALSE


void ManageMasterProfiles::DoDataExchange(CDataExchange* pDX) {CDialog::DoDataExchange(pDX);}


BEGIN_MESSAGE_MAP(ManageMasterProfiles, CDialog)
  ON_BN_CLICKED(IDC_BUTTON12,   &ManageMasterProfiles::createNewMaster)
  ON_BN_CLICKED(IDC_BUTTON13,   &ManageMasterProfiles::deleteSelectedMaster)
  ON_BN_CLICKED(IDC_BUTTON1,    &ManageMasterProfiles::OnClickedButton1)

  ON_COMMAND(ID_SetBBSsuffixes, &ManageMasterProfiles::OnSetBBSsuffixes)
  ON_COMMAND(ID_ABOUT32775,     &ManageMasterProfiles::OnAbout32775)
  ON_COMMAND(ID_HELP32776,      &ManageMasterProfiles::OnHelp32776)
END_MESSAGE_MAP()
#endif


ManageMasterProfiles::~ManageMasterProfiles() { }



void ManageMasterProfiles::OnSetBBSsuffixes() {BBSSuffix bbs;  bbs.getSuffixes();}


// ManageMasterProfiles message handlers


void ManageMasterProfiles::createNewMaster() {
  listItems.getSelected(); EndDialog(CreateMaster);
  }


void ManageMasterProfiles::deleteSelectedMaster() {
  listItems.getSelected(); EndDialog(DeleteMaster);
  }


void ManageMasterProfiles::OnClickedButton1() {CAboutDlg aboutDlg; aboutDlg.DoModal();}


void ManageMasterProfiles::OnAbout32775() {CAboutDlg aboutDlg; aboutDlg.DoModal();}


void ManageMasterProfiles::OnHelp32776() {
String topic;

  topic = theApp.helpFile; topic += _T(">CreateMaster");

  ::HtmlHelp(theApp.m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 20);
  }
