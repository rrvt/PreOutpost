// DeleteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OPaddress.h"
#include "DeleteDlg.h"
#include "afxdialogex.h"


// DeleteDlg dialog

IMPLEMENT_DYNAMIC(DeleteDlg, CDialogEx)

DeleteDlg::DeleteDlg(CWnd* pParent) : CDialogEx(IDD_DeleteDialog, pParent) { }


DeleteDlg::DeleteDlg(CString& tgt, CWnd* pParent) : CDialogEx(IDD_DeleteDialog, pParent)  {
  delAddr = tgt;
  }

DeleteDlg::~DeleteDlg() { }


BOOL DeleteDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();

  address.SetWindowText(delAddr);

  return TRUE;
  }


void DeleteDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_Address, address);
  }


BEGIN_MESSAGE_MAP(DeleteDlg, CDialogEx)
END_MESSAGE_MAP()

