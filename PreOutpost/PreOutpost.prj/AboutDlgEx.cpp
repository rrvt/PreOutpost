// About Dialog


#include "stdafx.h"
#include "AboutDlgEx.h"
#include "ExtraResource.h"
#include "FileIO.h"
#include "match.h"
#include "ProgramFiles.h"
#include "Resources.h"


static String verPath  = _T("C:\\PacFORMS\\Docs\\SCCo-Version.txt");
static String verPath1 = _T("C:\\PackItForms\\Outpost\\SCCo\\version.txt");


void AboutDlgEx::DoDataExchange(CDataExchange* pDX) {CDialogEx::DoDataExchange(pDX);}


BOOL AboutDlgEx::OnInitDialog() {
ResourceData res;
String       copyright;
String       companyName;
String       name;
String       prodName;
String       nameVer;
String       version;
bool         rslt;

  CDialogEx::OnInitDialog();

  if (useProdName) rslt = res.getProductName(prodName);
  else             rslt = res.getInternalName(prodName);

  if (!rslt) prodName = _T("Product");

  nameVer = prodName.trim();   prodName = _T("About ") + prodName;   SetWindowText(prodName);

  #ifdef WinXP
    nameVer += _T(" (WinXP)");
  #elif defined UNICODE
    nameVer += _T(" (UNI 7)");
  #else
    nameVer += _T(" (Win 7)");
  #endif

  if (!res.getVersion(version)) version = _T("0/0/0");

  res.threeSect(version);

  nameVer += _T(", Version ") + version;  nameVer.trim();

  if (!res.getCompanyName(name)) name = _T("Bob -- K6RWY");   name.trim();
  companyName = _T("Author:  ") + name;

  // Copyright (c) Bob -- K6RWY.  All rights reserved.
  copyright = _T("Copyright (c) ") + name + _T(".  All rights reserved.");

  SetDlgItemText(IDC_NameVer,     nameVer);
  SetDlgItemText(IDC_Copyright,   copyright);
  SetDlgItemText(IDC_CompanyName, companyName);

  getOutpostData();
  getPackItData();
  getPackFormsVerData();

  return TRUE;
  }


void AboutDlgEx::getOutpostData() {
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


void AboutDlgEx::getPackItData() {
FileIO file;
String line;
String v;

  if (file.open(verPath1, FileIO::Read)) {
    file.read(line);

    v = _T("PackItForms Version: ") + line.trim();  SetDlgItemText(IDC_PackItFormVer, v);   file.close();
    }
  }


void AboutDlgEx::getPackFormsVerData() {
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

