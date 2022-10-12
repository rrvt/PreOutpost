// Show PDF Info Files


#pragma once
#include "Executable.h"


class PdfInfo {

String     myPath;
String     acroRd;
Executable pdfExe;

public:

STARTUPINFO startUpInfo;

  PdfInfo(TCchar* myPth) : myPath(myPth) { }
 ~PdfInfo() { }

  void show(TCchar* name);

private:

  bool getAcroRd();

  PdfInfo() { }
  };

