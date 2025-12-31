// Class that corresponds to Dialog box to select Master Profile

#include "pch.h"
#include "NewMasterDlg.h"
#include "AboutDlgEx.h"
#include "Help.h"
#include "PreOutpost.h"


// NewMasterDlg dialog

IMPLEMENT_DYNAMIC(NewMasterDlg, CDialog)

NewMasterDlg::NewMasterDlg(CWnd* pParent) :
                       CDialog(NewMasterDlg::IDD, pParent) {listItems.init(this, IDC_NewMstrList);}


BOOL NewMasterDlg::OnInitDialog() {

  CDialog::OnInitDialog();

  listItems.addToControl();

  return TRUE;  // return TRUE unless you set the focus to a control
  }             // EXCEPTION: OCX Property Pages should return FALSE


void NewMasterDlg::DoDataExchange(CDataExchange* pDX) {CDialog::DoDataExchange(pDX);}


BEGIN_MESSAGE_MAP(NewMasterDlg, CDialog)
  ON_LBN_DBLCLK(IDC_NewMstrList,    &onSelectNewMstr)
  ON_COMMAND(ID_About,             &onAbout)
  ON_COMMAND(ID_HELP_OVERVIEW,      &OnHelpOverview)
  ON_COMMAND(ID_HELP_IDENTITY,      &OnHelpIdentity)
  ON_COMMAND(ID_HELP_ADDRESSBOOK,   &OnHelpAddressbook)
  ON_COMMAND(ID_HELP_MakeMaster,    &OnHelpMakeMaster)
  ON_COMMAND(ID_HELP_DeleteMaster,  &OnHelpDeleteMaster)
  ON_COMMAND(ID_HELP_SelNewMaster,  &OnHelpSelNewMaster)
  ON_COMMAND(ID_HELP_SelectProfile, &OnHelpSelectProfile)
  ON_BN_CLICKED(IDOK,               &OnOK)
END_MESSAGE_MAP()


// NewMasterDlg message handlers


void NewMasterDlg::onSelectNewMstr() {OnOK();}


void NewMasterDlg::OnOK() {selected = listItems.getSelected(); CDialog::OnOK();}


void NewMasterDlg::onAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void NewMasterDlg::OnHelpMakeMaster()    {help.createMaster(GetSafeHwnd());}
void NewMasterDlg::OnHelpOverview()      {help.overview(GetSafeHwnd());}
void NewMasterDlg::OnHelpIdentity()      {help.oneMaster(GetSafeHwnd());}
void NewMasterDlg::OnHelpAddressbook()   {help.addressBook(GetSafeHwnd());}
void NewMasterDlg::OnHelpDeleteMaster()  {help.deleteMaster(GetSafeHwnd());}
void NewMasterDlg::OnHelpSelNewMaster()  {help.selectNewMaster(GetSafeHwnd());}
void NewMasterDlg::OnHelpSelectProfile() {help.selectProfile(GetSafeHwnd());}


#if 0
void NewMasterDlg::OnSize(UINT nType, int cx, int cy) {
CRect winRect;

  CDialogEx::OnSize(nType, cx, cy);

  if (!isInitialized) return;

  GetWindowRect(&winRect);
  winPos.set(winRect);   toolBar.move(winRect);   statusBar.move(winRect);
  }
#endif

