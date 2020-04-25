// Display About Dialog Box


#include "stdafx.h"
#include "About.h"
#include "Expandable.h"
#include "FileIO.h"
#include "match.h"
#include "PreOutpost.h"
#include "ProgramFiles.h"
#include "Resources.h"


static String verPath  = _T("C:\\PacFORMS\\Docs\\SCCo-Version.txt");
static String verPath1 = _T("C:\\PackItForms\\Outpost\\SCCo\\version.txt");


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX); DDX_Control(pDX, IDC_NameVer, nameVersion);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog() {CDialog::OnInitDialog();  setVersions();  return TRUE;}


void CAboutDlg::setVersions() {
ResourceData res;
//String       nameVer = res.getAboutNameVer();
String       copyright;
String       companyName;
String       name;
String       aboutName;

  if (!res.getProductName(aboutName)) aboutName = _T("Product");    aboutName = _T("About ") + aboutName;
  aboutName.trim();

  if (!res.getCompanyName(name)) name = _T("Bob -- K6RWY");   name.trim();
  companyName = _T("Author:  ") + name;

  // Copyright (c) Bob -- K6RWY.  All rights reserved.
  copyright = _T("Copyright (c) ") + name + _T(".  All rights reserved.");

  SetWindowText( aboutName);
  SetDlgItemText(IDC_NameVer,     res.getAboutNameVer());
  SetDlgItemText(IDC_Copyright,   copyright);
  SetDlgItemText(IDC_CompanyName, companyName);

//  nameVersion.SetWindowText(nameVer);

  getOutpostData();
  getPackItData();
  getPackFormsVerData();
  }


void CAboutDlg::getOutpostData() {
ResourceData res(outputPaths.outpostPath);
String       t;
String       v;
FileIO       file;
CTime        tm;
String       dt;


  if (res.getVersion(t))
    {v = _T("Outpost Version: ") + t.trim();      SetDlgItemText(IDC_OutpostVersion, v);}

  if (res.getCopyRight(t))
    {v = _T("Outpost Copyright: ") + t.trim();    SetDlgItemText(IDC_OutpostCopyRight, v);}

  if (file.open(outputPaths.outpostPath, FileIO::Read)) {
    if (file.getModifiedTime(tm)) dt = tm.Format(_T("%e %B %y"));

    if (!dt.trim().isEmpty()) {v = _T("Build Date: ") + dt;  SetDlgItemText(IDC_BuildDate, v);}

    file.close();
    }
  res.getCompanyName(t);
  res.getFileDescription(t);
  res.getFileVersion(t);
  res.getInternalName(t);
  res.getOriginalFilename(t);
  res.getProductName(t);
  res.getProductVersion(t);
  }


void CAboutDlg::getPackItData() {
FileIO file;
String line;
String v;

  if (file.open(verPath1, FileIO::Read)) {
    file.read(line);

    v = _T("PackItForms Version: ") + line.trim();  SetDlgItemText(IDC_PackItFormVer, v);   file.close();
    }
  }


void CAboutDlg::getPackFormsVerData() {
FileIO  file;
String  line;
RegExpr formRE(_T("PacRELEASE:"));
RegExpr installRE(_T("Install:"));
int     pos;
String  v;

  if (!file.open(verPath, FileIO::Read)) return;

  while (file.read(line)) {
    TCchar* cs = line;
    String  s;

    if (formRE.match(cs)) {
      pos = line.find(_T(':'));
      s = line.substr(pos+1).trim();   if (s[0] == _T('v')) s = s.substr(1);
      v = _T("PacForms Version: ") + s;
      SetDlgItemText(IDC_FormsVersion,   v); continue;
      }

    if (installRE.match(cs)) {
      pos = line.find(_T(':'));
      s = line.substr(pos+1).trim();   if (s[0] == _T('v')) s = s.substr(1);
      v = _T("Installation Version: ") + s;
      SetDlgItemText(IDC_InstallVersion, v); continue;
      }
    }
  }


#if 0
bool CAboutDlg::oldVersions() {
ResourceData res(theApp.outpostPath);
CTime        tm;
String       dt;
FileIO       file;
//int          n;
//int          i;
RegExpr      outpostRE(_T("Outpost:"));
RegExpr      formRE(_T("PacRELEASE:"));
RegExpr      installRE(_T("Install:"));
RegExpr      buildDateRE(_T("Build Date:"));
int          pos;
String       v;
String       ver;
String       line;

  if (res.getVersion(ver))
    {v = _T("Outpost Version: ") + ver.trim();      SetDlgItemText(IDC_OutpostVersion, v);}

  if (file.open(verPath1, FileIO::Read)) {
    file.read(line);

    v = _T("PackItForms Version: ") + line.trim();  SetDlgItemText(IDC_PackItFormVer, v);   file.close();
    }

  if (!file.open(verPath, FileIO::Read)) return false;

  while (file.read(line)) {
    TCchar* cs = line;
    String  s;

    if (formRE.match(cs)) {
      pos = line.find(_T(':'));
      s = line.substr(pos+1).trim();   if (s[0] == _T('v')) s = s.substr(1);
      v = _T("PacForms Version: ") + s;
      SetDlgItemText(IDC_FormsVersion,   v); continue;
      }

    if (installRE.match(cs)) {
      pos = line.find(_T(':'));
      s = line.substr(pos+1).trim();   if (s[0] == _T('v')) s = s.substr(1);
      v = _T("Installation Version: ") + s;
      SetDlgItemText(IDC_InstallVersion, v); continue;
      }
    }

  return true;
  }


// New Packit Version strings

void CAboutDlg::newVersions() {
ResourceData res(theApp.outpostPath);
FileIO  file;
String  line;
String  v;
String  ver;
CTime   tm;
String  dt;
CString cs;

  if (res.getVersion(ver))
                      {v = _T("Outpost Version: ") + ver.trim();  SetDlgItemText(IDC_OutpostVersion, v);}


  if (file.open(verPath1, FileIO::Read)) {
    file.read(line);

    v = _T("PackItForms Version: ") + line.trim();  SetDlgItemText(IDC_PackItFormVer, v);   file.close();
    }

String t;
  res.getCompanyName(t);
  res.getFileDescription(t);
  res.getFileVersion(t);
  res.getInternalName(t);
  res.getCopyRight(t);
  res.getOriginalFilename(t);
  res.getProductName(t);
  res.getProductVersion(t);
  }
#endif

