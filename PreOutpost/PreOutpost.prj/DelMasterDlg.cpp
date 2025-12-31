// DelMasterDlg.cpp : implementation file

#include "pch.h"
#include "PreOutpost.h"
#include "AboutDlgEx.h"
#include "DelMasterDlg.h"
#include "filename.h"
#include "Help.h"


// DelMasterDlg dialog

IMPLEMENT_DYNAMIC(DelMasterDlg, CDialogEx)


DelMasterDlg::DelMasterDlg(CWnd* pParent) : CDialogEx(DelMasterDlg::IDD, pParent),
                                                                      MasterProfileName(_T("")) { }

void DelMasterDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_MasterProfile, MasterProfileName);
  }


BEGIN_MESSAGE_MAP(DelMasterDlg, CDialog)
  ON_COMMAND(ID_About,              &OnAbout)
  ON_COMMAND(ID_HELP_OVERVIEW,      &OnHelpOverview)
  ON_COMMAND(ID_HELP_IDENTITY,      &OnHelpIdentity)
  ON_COMMAND(ID_HELP_ADDRESSBOOK,   &OnHelpAddressbook)
  ON_COMMAND(ID_HELP_MakeMaster,    &OnHelpMakeMaster)
  ON_COMMAND(ID_HELP_DeleteMaster,  &OnHelpDeleteMaster)
  ON_COMMAND(ID_HELP_SelNewMaster,  &OnHelpSelNewMaster)
  ON_COMMAND(ID_HELP_SelectProfile, &OnHelpSelectProfile)
  ON_BN_CLICKED(IDOK,               &OnOK)
  ON_BN_CLICKED(IDCANCEL,           &OnCancel)

#ifdef DialogSizable01
  ON_WM_SIZE()
#endif

END_MESSAGE_MAP()


// DelMasterDlg message handlers


void DelMasterDlg::OnOK() {CDialog::OnOK();}


void DelMasterDlg::OnCancel() {CDialog::OnCancel();}



DelMasterDlg::~DelMasterDlg() { }


void DelMasterDlg::OnAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void DelMasterDlg::OnHelpMakeMaster()    {help.createMaster(GetSafeHwnd());}
void DelMasterDlg::OnHelpOverview()      {help.overview(GetSafeHwnd());}
void DelMasterDlg::OnHelpIdentity()      {help.oneMaster(GetSafeHwnd());}
void DelMasterDlg::OnHelpAddressbook()   {help.addressBook(GetSafeHwnd());}
void DelMasterDlg::OnHelpDeleteMaster()  {help.deleteMaster(GetSafeHwnd());}
void DelMasterDlg::OnHelpSelNewMaster()  {help.selectNewMaster(GetSafeHwnd());}
void DelMasterDlg::OnHelpSelectProfile() {help.selectProfile(GetSafeHwnd());}



#ifdef DialogSizable01

void DelMasterDlg::OnSize(UINT nType, int cx, int cy) {
CRect winRect;

  CDialogEx::OnSize(nType, cx, cy);

  if (!isInitialized) return;

  GetWindowRect(&winRect);

  winPos.set(winRect);   toolBar.move(winRect);   statusBar.move(winRect);
  }
#endif

