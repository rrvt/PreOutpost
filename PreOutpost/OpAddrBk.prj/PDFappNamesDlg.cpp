// PDFappNamesDlg.cpp : implementation file
//

#include "pch.h"
#include "PDFappNamesDlg.h"
#include "Executable.h"
#include "FilePaths.h"
#include "IniFile.h"
#include "StatusBar.h"


TCchar* PathSection = _T("Path");
TCchar* AcroRdKey   = _T("AcroRdPath");


// PDFappNamesDlg dialog

IMPLEMENT_DYNAMIC(PDFappNamesDlg, CDialogEx)


BEGIN_MESSAGE_MAP(PDFappNamesDlg, CDialogEx)
  ON_BN_CLICKED(IDC_FindPaths, &onClickedFindpaths)
  ON_LBN_DBLCLK(IDC_PathList,  &onDblClkPathlist)
  ON_BN_CLICKED(IDC_PDFfound,  &OnClickedPDFfound)
END_MESSAGE_MAP()


PDFappNamesDlg::PDFappNamesDlg(TCchar* path, StatusBar& stsBar, CWnd* pParent) :
       CDialogEx(IDD_FindPDFapp, pParent), myPath(path), statusBar(stsBar), pdfAppNames(_T("")) { }

PDFappNamesDlg::~PDFappNamesDlg() { }


void PDFappNamesDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(   pDX, IDC_PDFapps,  pdfAppNames);
  DDX_Control(pDX, IDC_PathList, pathListCtl);
  DDX_Control(pDX, IDC_PDFapps,  pdfAppNamesCtl);
  }



void PDFappNamesDlg::OnOK() {
  // TODO: Add your specialized code here and/or call the base class
  CDialogEx::OnOK();
  }


void PDFappNamesDlg::onClickedFindpaths() {String apps;   if (getLine(apps)) getPaths(apps);}


bool PDFappNamesDlg::getLine(String& apps) {
Tchar buf[256];
int   n;

  apps.clear();   n = pdfAppNamesCtl.GetLine(0, buf, noElements(buf));

  if (0 <= n && n < noElements(buf) - 1) {buf[n] = 0;  apps = buf;}

  return !apps.isEmpty();
  }



void PDFappNamesDlg::getPaths(TCchar* tc) {
String    line = tc;    line += _T(' ');   line.trimLeft();
int       pos;
FilePaths filePaths;
FPsIter   iter(filePaths);
String*   path;

  for (pos = line.find(_T(' '));  pos > 0; pos = line.find(_T(' '))) {
    String app = line.substr(0, pos);

    if (app.find(_T(".exe")) < 0) app += _T(".exe");

    filePaths.findFiles(_T("C:"), _T("Program*"), app);

    line = line.substr(pos+1);   line.trimLeft();
    }

  for (path = iter(); path; path = iter++) {pathListCtl.AddString(*path);}
  }



void PDFappNamesDlg::onDblClkPathlist() {
int        i = pathListCtl.GetCurSel();
Cstring    cs;
Executable pdfExe;
String     testPdf = myPath + _T("TestPDF.pdf");
String     s;

  if (i >= 0) {
    pathListCtl.GetText(i, cs);

    s = _T("Testing ") + cs;   statusBar.setText(s);

    if (pdfExe.start(2, cs.str(), testPdf.str())) {
      pdfReaderPath = cs;   pdfExe.wait();   statusBar.setText(_T("Testing Complete"));

      return;
      }
    }
  statusBar.setText(_T("Test Failed!"));   pdfReaderPath.clear();
  }


void PDFappNamesDlg::OnClickedPDFfound() {

  iniFile.writeString(PathSection, AcroRdKey, pdfReaderPath);

  EndDialog(IDOK);
  }





