// Show PDF Info Files


#include "pch.h"
#include "PdfInfo.h"
#include "Executable.h"
#include "FileName.h"
#include "FilePaths.h"
#include "FileSrch.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "PDFappNamesDlg.h"
#include "StatusBar.h"


static TCchar* PdfSection       = _T("PDFsection");

static TCchar* pdfKeys[NoPDFs]  = {_T("PktFreqs"),
                                   _T("FormRtng"),
                                   _T("SubjLine"),
                                   _T("Check_In"),
                                   _T("RtngSlip")
                                   };


void PdfInfo::show(PDFfiles pdfFileX, StatusBar& statusBar) {

  if (!getAcroRd(statusBar)) return;
  if (pdfPaths[pdfFileX].isEmpty()) loadPDFs(pdfFileX);
  if (pdfPaths[pdfFileX].isEmpty()) findPdfFiles(statusBar);
  if (pdfPaths[pdfFileX].isEmpty()) return;

  statusBar.setText(0, pdfPaths[pdfFileX]);

  pdfExe.start(2, acroRd.str(), pdfPaths[pdfFileX].str());
  }


void PdfInfo::loadPDFs(PDFfiles pdfFileX)
                                 {iniFile.read(PdfSection, pdfKeys[pdfFileX], pdfPaths[pdfFileX]);}



bool PdfInfo::getAcroRd(StatusBar& statusBar) {

  if (!acroRd.isEmpty()) return true;

  if (iniFile.readString(PathSection, AcroRdKey, acroRd) && !acroRd.isEmpty()) return true;

  findPdfReader(statusBar);   return !acroRd.isEmpty();
  }


void PdfInfo::findPdfReader(StatusBar& statusBar) {
PDFappNamesDlg dlg(myPath, statusBar);

  statusBar.setText(_T("Find PDF Reader"));

  if (dlg.DoModal() != IDOK) return;

  acroRd = dlg.pdfReaderPath;
  }


static TCchar* srchKeys[NoPDFs] = {_T("packet-freqs"),
                                   _T("Form_Routing"),
                                   _T("Subj_Line"),
                                   _T("Check-In"),
                                   _T("Routing_Slip")
                                   };



void PdfInfo::findPdfFiles(StatusBar& statusBar) {
FilePaths filePaths;
FPsIter   iter(filePaths);
String*   path;

  statusBar.setText(_T("Find Current PDF Files"));

  filePaths.findFiles(myPath.str(), _T("*.pdf"));

  for (path = iter(); path; path = iter++) savePdfPath(*path);

  statusBar.setText(_T("Find Current PDF Files Finished"));
  }


void PdfInfo::savePdfPath(String& path) {
String name = getMainName(path);
int i;
int n = noElements(srchKeys);

  for (i = 0; i < n; i++) if (name.find(srchKeys[i]) >= 0)
                     {pdfPaths[i] = path;   iniFile.write(PdfSection, pdfKeys[i], path);   return;}
  }




