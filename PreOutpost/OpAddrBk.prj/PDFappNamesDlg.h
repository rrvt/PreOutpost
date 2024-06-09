// Find path to PDF applications suitable to displaying pdf files



#pragma once
#include "Resource.h"

class StatusBar;


extern TCchar* PathSection;
extern TCchar* AcroRdKey;


class PDFappNamesDlg : public CDialogEx {

  DECLARE_DYNAMIC(PDFappNamesDlg)

String     myPath;
StatusBar& statusBar;
public:

CString    pdfAppNames;
CEdit      pdfAppNamesCtl;
CListBox   pathListCtl;
String     pdfReaderPath;

           PDFappNamesDlg(TCchar* path, StatusBar& stsBar, CWnd* pParent = nullptr);
  virtual ~PDFappNamesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_FindPDFapp };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  bool getLine(String& apps);
  void getPaths(TCchar* tc);

public:

  virtual void OnOK();
  afx_msg void onClickedFindpaths();
  afx_msg void onDblClkPathlist();
  afx_msg void OnClickedPDFfound();
  };
