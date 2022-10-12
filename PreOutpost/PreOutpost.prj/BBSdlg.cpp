// BBSdlg.cpp : implementation file


#include "pch.h"
#include "BBSdlg.h"


static TCchar* Section = _T("BBS");
static TCchar* Suffix  = _T("Suffix");
static TCchar* Cname   = _T("CName");


// BBSdlg dialog

IMPLEMENT_DYNAMIC(BBSdlg, CDialog)

BBSdlg::BBSdlg(CWnd* pParent) : CDialog(BBSdlg::IDD, pParent), nData(0) {
int n = noElements(data);
int i;

  for (i = 0; i < n; i++)
                    {BBSdlgDatum& d = data[i];  d.suffix.Empty();    d.fName.Empty();   d.cName.Empty();}
  }


BBSdlg::~BBSdlg() { }




BOOL BBSdlg::OnInitDialog() {
int          i;
CEdit*       p;
CWnd*        q;
BBSdlgDatum* d;

  CDialog::OnInitDialog();

  SetWindowText(_T("Set Suffixes for BBSes"));

  for (i = 0; i < nData; i++) {
    d = &data[i];
    p = (CEdit*) GetDlgItem(IDC_EDIT20   + i); if (p) {p->SetWindowText(d->suffix); p->SetLimitText(3);}
    q = (CWnd*)  GetDlgItem(IDC_STATIC10 + i); if (q)  q->SetWindowText(d->cName);
    q = (CWnd*)  GetDlgItem(IDC_STATIC20 + i); if (q)  q->SetWindowText(d->fName);
    }

  return TRUE;
  }


void BBSdlg::DoDataExchange(CDataExchange* pDX) {
int          i;

  CDialog::DoDataExchange(pDX);

  for (i = 0; i < nData; i++) {DDX_Text(pDX, (IDC_EDIT20+i), data[i].suffix);}
  }


BEGIN_MESSAGE_MAP(BBSdlg, CDialog)
END_MESSAGE_MAP()

