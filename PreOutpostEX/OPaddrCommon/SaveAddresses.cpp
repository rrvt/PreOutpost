// SaveAddresses.cpp : implementation file
//

#include "stdafx.h"
#include "OPaddress.h"
#include "SaveAddresses.h"
#include "afxdialogex.h"


// SaveAddresses dialog

IMPLEMENT_DYNAMIC(SaveAddresses, CDialogEx)

SaveAddresses::SaveAddresses(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

SaveAddresses::~SaveAddresses()
{
}

void SaveAddresses::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SaveAddresses, CDialogEx)
END_MESSAGE_MAP()


// SaveAddresses message handlers
