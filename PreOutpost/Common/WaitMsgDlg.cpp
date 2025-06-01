// WaitMsgDlg.cpp : implementation file
//

#include "pch.h"
#include "WaitMsgDlg.h"
#include "resource.h"


// WaitMsgDlg dialog

IMPLEMENT_DYNAMIC(WaitMsgDlg, CDialogEx)


WaitMsgDlg::WaitMsgDlg(CWnd* pParent) : CDialogEx(IDD_WaitMsg, pParent) { }


WaitMsgDlg::~WaitMsgDlg() { }


BOOL WaitMsgDlg::OnInitDialog()
       {CDialogEx::OnInitDialog();   thrd.set(m_hWnd, FinFindDir);   thrd.start(0);   return true;}


void WaitMsgDlg::DoDataExchange(CDataExchange* pDX) {CDialogEx::DoDataExchange(pDX);}


BEGIN_MESSAGE_MAP(WaitMsgDlg, CDialogEx)
  ON_MESSAGE(FinFindDir, &onFinFindDir)
END_MESSAGE_MAP()


LRESULT WaitMsgDlg::onFinFindDir(WPARAM wParam, LPARAM lParam) {OnOK();   return 0;}
