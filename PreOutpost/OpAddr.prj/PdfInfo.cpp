// Show PDF Info Files


#include "pch.h"
#include "PdfInfo.h"
#include "Executable.h"
#include "FileName.h"
#include "FilePaths.h"
#include "FileSrch.h"
#include "IniFile.h"
#include "MessageBox.h"


static TCchar* PathSection = _T("Path");
static TCchar* AcroRdKey   = _T("AcroRdPath");


void PdfInfo::show(TCchar* name) {
String pdfPath = myPath + name;

  if (!getAcroRd()) return;

  if (pdfExe.start(2, acroRd.str(), pdfPath.str())) {pdfExe.wait(); return;}
  }


bool PdfInfo::getAcroRd() {
FilePaths filePaths;
FPsIter   iter(filePaths);
String*   path;

  if (!acroRd.isEmpty()) return true;

  if (iniFile.readString(PathSection, AcroRdKey, acroRd) && !acroRd.isEmpty()) return true;

  filePaths.findFiles(_T("C:"), _T("Program*"), _T("AcroRd32.exe"));
  filePaths.findFiles(_T("C:"), _T("Program*"), _T("Acrobat*.exe"));

  for (path = iter(); path; path = iter++) {

    String   eula = getPath(path->str());
    FileSrch eulaPath;
    String   name;
    if (eulaPath.findFiles(eula, _T("*Eula.exe")) && eulaPath.getName(name)) {acroRd = *path; break;}
    }

  if (acroRd.isEmpty()) return false;

  iniFile.writeString(PathSection, AcroRdKey, acroRd);   return true;
  }

