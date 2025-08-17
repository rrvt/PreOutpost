// Show PDF Info Files


#pragma once
#include "Executable.h"

class StatusBar;


enum PDFfiles {MsgHndlPDF, PktFreqPDF, FrmRtngPDF, RtngSlipPDF, SbjLnPDF, CheckInPDF, NoPDFs};


class PdfInfo {
String     myPath;
String     acroRd;
Executable pdfExe;

String     pdfPaths[NoPDFs];

public:

STARTUPINFO startUpInfo;

  PdfInfo(TCchar* myPth);
 ~PdfInfo() { }

  void show(PDFfiles pdfFileX, StatusBar& statusBar);

  void findPdfReader(StatusBar& statusBar);
  void findPdfFiles( StatusBar& statusBar);

private:

  void loadPDFs(PDFfiles pdfFileX);
  bool getAcroRd(StatusBar& statusBar);
  void reloadPDF(int x);
  void savePdfPath(String& path);

  PdfInfo() { }
  };

