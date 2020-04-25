// BBSSuffix.cpp : implementation file
//

#include "stdafx.h"
#include "BBSSuffix.h"
#include "PreOutpost.h"
#include "ProgramFiles.h"
#include "SrchFile.h"


static TCchar* Section = _T("BBS");
static TCchar* Suffix  = _T("Suffix");
static TCchar* Cname   = _T("CName");



// BBSSuffix dialog

IMPLEMENT_DYNAMIC(BBSSuffix, CDialog)

BBSSuffix::BBSSuffix(CWnd* pParent /*=NULL*/) : CDialog(BBSSuffix::IDD, pParent) {  }


BBSSuffix::~BBSSuffix() { }



void BBSSuffix::getSuffixes() {

  if (DoModal() == IDOK) bbsInfo.save();

  bbsInfo.load();
  }



BOOL BBSSuffix::OnInitDialog() {
int      i;
CEdit*   p;
CWnd*    q;
BBSinfo  newInfo;
BBSdata* bbs;

  CDialog::OnInitDialog();

  SetWindowText(_T("Set Suffixes for BBSes"));

  findBBSfiles(newInfo);

  for (i = 0; bbs = newInfo.get(i); i++) {
    p = (CEdit*) GetDlgItem(IDC_EDIT20 + i);   if (p) {p->SetWindowText(bbs->suffix); p->SetLimitText(3);}
    q = (CWnd*)  GetDlgItem(IDC_STATIC10 + i); if (q) q->SetWindowText(bbs->cName);
    q = (CWnd*)  GetDlgItem(IDC_STATIC20 + i); if (q) q->SetWindowText(bbs->fName);
    }

  return TRUE;
  }



void BBSSuffix::findBBSfiles(BBSinfo& newInfo) {
String    bbsPath = outputPaths.profilePath + _T("bbs.d\\");
String    bbsArb  = bbsPath + _T("*.bbs");
BBSdata*  bbs;
BBSdata*  b;
CFileFind c;
String    bbsFile;
int       i;
BOOL      someLeft;
String    s;

  if (c.FindFile(bbsArb)) {
    newInfo.clear();

    for (i = 0, someLeft = true; newInfo.isNotFull() && someLeft; i++) {
      someLeft = c.FindNextFile();

      bbs = newInfo.put();

      if (someLeft || GetLastError() == ERROR_NO_MORE_FILES) {
        bbs->fName = c.GetFileTitle();

        SrchFile srchFile(c.GetFilePath());  srchFile.forValOf(_T("CName"), bbs->cName);  srchFile.Close();

        if (bbsInfo.find(bbs->cName, b)) bbs->suffix = b->suffix;
        }
      }
    }
  }


void BBSSuffix::DoDataExchange(CDataExchange* pDX) {
int      i;
BBSdata* bbs;

  CDialog::DoDataExchange(pDX);

  for (i = 0; bbs = bbsInfo.xch(i); i++) {
     DDX_Text(pDX, (IDC_EDIT20+i), bbs->suffix);
     DDX_Text(pDX, (IDC_STATIC10 + i), bbs->cName);
     DDX_Text(pDX, (IDC_STATIC20 + i), bbs->fName);
     }
  }


BEGIN_MESSAGE_MAP(BBSSuffix, CDialog)
END_MESSAGE_MAP()

