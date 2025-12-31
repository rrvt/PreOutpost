// Post Session Text Dialog


#include "pch.h"
#include "PostSessionDlg.h"


// PostSessionDlg dialog

IMPLEMENT_DYNAMIC(PostSessionDlg, CDialogEx)

PostSessionDlg::PostSessionDlg(CWnd* pParent) : CDialogEx(IDD_PostSession, pParent) { }

PostSessionDlg::~PostSessionDlg() { }


void PostSessionDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_PostSssnTxt, postSssnTxt);
  }


BEGIN_MESSAGE_MAP(PostSessionDlg, CDialogEx)
END_MESSAGE_MAP()
