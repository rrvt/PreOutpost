// Show PDF Info Files


#pragma once
#include "Executable.h"

class StatusBar;


enum PDFfiles {PktFreqPDF, FrmRtngPDF, SbjLnPDF, CheckInPDF, RtngSlipPDF, NoPDFs};


class PdfInfo {
String     myPath;
String     acroRd;
Executable pdfExe;

String     pdfPaths[NoPDFs];

public:

STARTUPINFO startUpInfo;

  PdfInfo(TCchar* myPth) : myPath(myPth) { }
 ~PdfInfo() { }

  void show(PDFfiles pdfFileX, StatusBar& statusBar);

  void findPdfReader(StatusBar& statusBar);
  void findPdfFiles( StatusBar& statusBar);

private:

  void loadPDFs(PDFfiles pdfFileX);
  bool getAcroRd(StatusBar& statusBar);
  void savePdfPath(String& path);

  PdfInfo() { }
  };

