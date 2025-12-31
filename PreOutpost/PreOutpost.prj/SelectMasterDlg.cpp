// Class that corresponds to the Dialog Box that allows the user to select the Master Profile when
// there are two or more Master Profiles

#include "pch.h"
#include "PreOutpost.h"
#include "Help.h"
#include "SelectMasterDlg.h"
#ifndef Win2K
#include "afxdialogex.h"
#endif
#include "AboutDlgEx.h"


// SelectMasterDlg dialog


IMPLEMENT_DYNAMIC(SelectMasterDlg, CDialogEx)

SelectMasterDlg::SelectMasterDlg(CWnd* pParent) : CDialogEx(SelectMasterDlg::IDD, pParent),
                                                  allProfiles(0) {listItems.init(this, IDC_SelectList);}


BOOL SelectMasterDlg::OnInitDialog() {

  CDialog::OnInitDialog();

  listItems.addToControl(); return TRUE;
  }


void SelectMasterDlg::DoDataExchange(CDataExchange* pDX) {

  CDialog::DoDataExchange(pDX);
  DDX_Radio(pDX, IDC_SelectMaster, allProfiles);
  }


BEGIN_MESSAGE_MAP(SelectMasterDlg, CDialog)
  ON_LBN_DBLCLK(IDC_SelectList,     &onSelectMaster)
  ON_COMMAND(ID_About,             &onAbout)
  ON_COMMAND(ID_HELP_OVERVIEW,      &OnHelpOverview)
  ON_COMMAND(ID_HELP_IDENTITY,      &OnHelpIdentity)
  ON_COMMAND(ID_HELP_ADDRESSBOOK,   &OnHelpAddressbook)
  ON_COMMAND(ID_HELP_MakeMaster,    &OnHelpMakeMaster)
  ON_COMMAND(ID_HELP_DeleteMaster,  &OnHelpDeleteMaster)
  ON_COMMAND(ID_HELP_SelNewMaster,  &OnHelpSelNewMaster)
  ON_COMMAND(ID_HELP_SelectProfile, &OnHelpSelectProfile)
  ON_BN_CLICKED(IDOK,        &OnOK)

  ON_WM_SIZE()
END_MESSAGE_MAP()


// SelectMasterDlg message handlers

void SelectMasterDlg::onSelectMaster() {OnOK();}
void SelectMasterDlg::OnOK() {selected = listItems.getSelected(); CDialog::OnOK();}


void SelectMasterDlg::onAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void SelectMasterDlg::OnHelpMakeMaster()    {help.createMaster(GetSafeHwnd());}
void SelectMasterDlg::OnHelpOverview()      {help.overview(GetSafeHwnd());}
void SelectMasterDlg::OnHelpIdentity()      {help.oneMaster(GetSafeHwnd());}
void SelectMasterDlg::OnHelpAddressbook()   {help.addressBook(GetSafeHwnd());}
void SelectMasterDlg::OnHelpDeleteMaster()  {help.deleteMaster(GetSafeHwnd());}
void SelectMasterDlg::OnHelpSelNewMaster()  {help.selectNewMaster(GetSafeHwnd());}
void SelectMasterDlg::OnHelpSelectProfile() {help.selectProfile(GetSafeHwnd());}


#ifdef DialogSizable04X

void SelectMasterDlg::OnSize(UINT nType, int cx, int cy) {

  CDialogEx::OnSize(nType, cx, cy);
  }
#endif

