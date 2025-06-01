// OutpostChoiceDlg.cpp : implementation file


#include "pch.h"
#include "OutpostChoiceDlg.h"
#include "FileName.h"
#include "MessageBox.h"
#include "ProgramFiles.h"


BEGIN_MESSAGE_MAP(OutpostChoiceDlg, CDialogEx)
  ON_LBN_DBLCLK(IDC_OutpostList, &OnOK)
  ON_BN_CLICKED(IDCANCEL,        &OnBnClickedCancel)
END_MESSAGE_MAP()


// OutpostChoiceDlg dialog

IMPLEMENT_DYNAMIC(OutpostChoiceDlg, CDialogEx)

OutpostChoiceDlg::OutpostChoiceDlg(CWnd* pParent) :
                                   CDialogEx(IDD_OutpostChoice, pParent), outpostChoice(_T("")) { }

OutpostChoiceDlg::~OutpostChoiceDlg() { }


BOOL OutpostChoiceDlg::OnInitDialog() {
OpfIter iter(programFiles.getFolders());
String* s;

  CDialogEx::OnInitDialog();

  for (s = iter(); s; s = iter++) {
    String path = getPath(*s);   if (path.find(_T("PreOutpost")) >= 0) continue;

    outpostList.AddString(path);
    }

  return TRUE;
  }


void OutpostChoiceDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control( pDX, IDC_OutpostList, outpostList);
  DDX_LBString(pDX, IDC_OutpostList, outpostChoice);
  }


void OutpostChoiceDlg::OnOK() {
String path;

  CDialogEx::OnOK();      path = outpostChoice;

  if (path.isEmpty()) {CDialogEx::OnCancel();   return;}

  confFilePath = programFiles.getProfilePath(path);
  exeFilePath  = programFiles.findFile(path, _T("*.exe"));
  }


void OutpostChoiceDlg::OnBnClickedCancel() {CDialogEx::OnCancel();}


////----------------

#if 1
#else
int     i;
  for (i = 0; i < progFiles.outpDirs.end(); i++) {

    String& pth = progFiles.outpDirs[i].path;

    if (pth.find(_T("PreOutpost")) >= 0) continue;

    TCchar* path = progFiles.outpDirs[i].path;

    outpostList.AddString(pth);
    }
#endif

