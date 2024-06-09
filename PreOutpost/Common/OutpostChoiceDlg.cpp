// OutpostChoiceDlg.cpp : implementation file


#include "pch.h"
#include "OutpostChoiceDlg.h"


BEGIN_MESSAGE_MAP(OutpostChoiceDlg, CDialogEx)
  ON_LBN_DBLCLK(IDC_OutpostList, &OutpostChoiceDlg::OnOK)
END_MESSAGE_MAP()


// OutpostChoiceDlg dialog

IMPLEMENT_DYNAMIC(OutpostChoiceDlg, CDialogEx)

OutpostChoiceDlg::OutpostChoiceDlg(CWnd* pParent) :
                                   CDialogEx(IDD_OutpostChoice, pParent), outpostChoice(_T("")) { }

OutpostChoiceDlg::~OutpostChoiceDlg() { }


BOOL OutpostChoiceDlg::OnInitDialog() {
int i;

  CDialogEx::OnInitDialog();

  progFiles.findOutpostDirs(_T("*Packet*"));
  progFiles.findOutpostDirs(_T("*Outpost*"));

  for (i = 0; i < progFiles.outpDirs.end(); i++) {

    String& pth = progFiles.outpDirs[i].path;

    if (pth.find(_T("PreOutpost")) >= 0) continue;

    TCchar* path = progFiles.outpDirs[i].path;

    outpostList.AddString(pth);
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

  confFilePath = progFiles.getProfilePath(path);
  exeFilePath  = progFiles.findExeFile(path);
  }

