// Class that corresponds to the Dialog Box that allows the user to create a new Master Profile or
// Delete a Master Profile.

#include "pch.h"
#include "PreOutpost.h"
#include "AboutDlgEx.h"
#include "Help.h"
#include "MasterMgmtDlg.h"
#include "BBSinfo.h"


// MasterMgmtDlg dialog

IMPLEMENT_DYNAMIC(MasterMgmtDlg, CDialog)


BEGIN_MESSAGE_MAP(MasterMgmtDlg, CDialog)
  ON_BN_CLICKED(IDC_CreateNewMaster,       &createNew)
  ON_BN_CLICKED(IDC_DeleteMaster,       &delSelected)

  ON_COMMAND(ID_SetBBSsuffixes,     &OnSetBBSsuffixes)
  ON_COMMAND(ID_About,             &OnAbout)
  ON_COMMAND(ID_HELP_OVERVIEW,      &OnHelpOverview)
  ON_COMMAND(ID_HELP_IDENTITY,      &OnHelpIdentity)
  ON_COMMAND(ID_HELP_ADDRESSBOOK,   &OnHelpAddressbook)
  ON_COMMAND(ID_HELP_MakeMaster,    &OnHelpMakeMaster)
  ON_COMMAND(ID_HELP_DeleteMaster,  &OnHelpDeleteMaster)
  ON_COMMAND(ID_HELP_SelNewMaster,  &OnHelpSelNewMaster)
  ON_COMMAND(ID_HELP_SelectProfile, &OnHelpSelectProfile)

#ifdef DialogSizable02
  ON_WM_SIZE()
#endif


    ON_BN_CLICKED(IDC_GetUsrVer, &MasterMgmtDlg::onGetUsrVer)
END_MESSAGE_MAP()


MasterMgmtDlg::MasterMgmtDlg(CWnd* pParent) :
                       CDialog(MasterMgmtDlg::IDD, pParent) {listItems.init(this, IDC_MasterList);}


BOOL MasterMgmtDlg::OnInitDialog() {
  CDialog::OnInitDialog();
  listItems.addToControl();
  return TRUE;                                // return TRUE unless you set the focus to a control
  }                                           // EXCEPTION: OCX Property Pages should return FALSE


void MasterMgmtDlg::DoDataExchange(CDataExchange* pDX) {CDialog::DoDataExchange(pDX);}


MasterMgmtDlg::~MasterMgmtDlg() { }



void MasterMgmtDlg::OnSetBBSsuffixes() {bbsInfo.getSuffixes();}


// MasterMgmtDlg message handlers


void MasterMgmtDlg::createNew()   {listItems.getSelected(); EndDialog(CreateMaster);}


void MasterMgmtDlg::onGetUsrVer() {EndDialog(GetUsrVersion);}


void MasterMgmtDlg::delSelected() {listItems.getSelected(); EndDialog(DeleteMaster);}


void MasterMgmtDlg::OnClickedButton1() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void MasterMgmtDlg::OnAbout() {AboutDlgEx aboutDlg; aboutDlg.DoModal();}


void MasterMgmtDlg::OnHelpMakeMaster()    {help.createMaster(GetSafeHwnd());}
void MasterMgmtDlg::OnHelpOverview()      {help.overview(GetSafeHwnd());}
void MasterMgmtDlg::OnHelpIdentity()      {help.oneMaster(GetSafeHwnd());}
void MasterMgmtDlg::OnHelpAddressbook()   {help.addressBook(GetSafeHwnd());}
void MasterMgmtDlg::OnHelpDeleteMaster()  {help.deleteMaster(GetSafeHwnd());}
void MasterMgmtDlg::OnHelpSelNewMaster()  {help.selectNewMaster(GetSafeHwnd());}
void MasterMgmtDlg::OnHelpSelectProfile() {help.selectProfile(GetSafeHwnd());}


#ifdef DialogSizable02

void MasterMgmtDlg::OnSize(UINT nType, int cx, int cy) {
CRect winRect;

  CDialogEx::OnSize(nType, cx, cy);

  if (!isInitialized) return;

  GetWindowRect(&winRect);
  winPos.set(winRect);   toolBar.move(winRect);   statusBar.move(winRect);
  }
#endif


