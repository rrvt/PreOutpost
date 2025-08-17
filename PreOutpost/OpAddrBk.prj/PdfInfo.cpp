// Show PDF Info Files


#include "pch.h"
#include "PdfInfo.h"
#include "Executable.h"
#include "FileName.h"
#include "FilePaths.h"
#include "FileSrch.h"
#include "IniFileEx.h"
#include "MessageBox.h"
#include "PDFappNamesDlg.h"
#include "StatusBar.h"


static TCchar* PdfSection       = _T("PDFsection");

static TCchar* pdfKeys[NoPDFs]  = {_T("MsgHndln"),
                                   _T("PktFreqs"),
                                   _T("FormRtng"),
                                   _T("RtngSlip"),
                                   _T("SubjLine"),
                                   _T("Check_In")
                                   };

static TCchar* srchKeys[NoPDFs] = {_T("Message_Handling"),
                                   _T("Packet-Freqs"),
                                   _T("Form_Routing"),
                                   _T("Routing_Slip"),
                                   _T("Pkt_Subj_Line"),
                                   _T("Packet_Check-In")
                                   };


PdfInfo::PdfInfo(TCchar* myPth) : myPath(myPth) {
#ifdef _DEBUG
  myPath += _T("..\\OpAddrDocs.prj\\");
#endif
  }


void PdfInfo::show(PDFfiles pdfFileX, StatusBar& statusBar) {
CFileStatus sts;

  if (!getAcroRd(statusBar)) return;
  if (pdfPaths[pdfFileX].isEmpty()) loadPDFs(pdfFileX);
  if (!CFile::GetStatus(pdfPaths[pdfFileX], sts)) reloadPDF(pdfFileX);
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


void PdfInfo::findPdfFiles(StatusBar& statusBar) {
FilePaths filePaths;
FPsIter   iter(filePaths);
String*   path;

  statusBar.setText(_T("Find Current PDF Files"));

  filePaths.findFiles(myPath.str(), _T("*.pdf"));

  for (path = iter(); path; path = iter++) savePdfPath(*path);

  statusBar.setText(_T("Find Current PDF Files Finished"));
  }


void PdfInfo::reloadPDF(int x) {
FilePaths filePaths;
FPsIter   iter(filePaths);
String*   path;

  filePaths.findFiles(myPath.str(), _T("*.pdf"));

  for (path = iter(); path; path = iter++) if (path->find(srchKeys[x]) > 0) savePdfPath(*path);
  }


void PdfInfo::savePdfPath(String& path) {
String name = getMainName(path);
int i;
int n = noElements(srchKeys);

  for (i = 0; i < n; i++) if (name.find(srchKeys[i]) >= 0)
                     {pdfPaths[i] = path;   iniFile.write(PdfSection, pdfKeys[i], path);   return;}
  }




