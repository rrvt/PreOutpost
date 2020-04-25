// BBS Data


#include "stdafx.h"
#include "BBSdata.h"
#include "PreOutpost.h"


static TCchar* section = _T("BBS");
static TCchar* Suffix  = _T("Suffix");
static TCchar* FName   = _T("FName");
static TCchar* CName   = _T("CName");
static TCchar* nBBS    = _T("nBBS");


BBSinfo bbsInfo;


void BBSinfo::clear() {
//IniFile& ini = iniFile;
int      i;

  for (i = 0; i < noElements(data); i++)
            {BBSdata& bbs = data[i];   bbs.suffix.Empty();   bbs.fName.Empty();   bbs.cName.Empty();}
  nData = 0;
  }


bool BBSinfo::find(CString& cN, BBSdata*& bbs) {
int      i;

  for (i = 0; i < nData; i++) {
#ifdef Win2K
    if (!strcmp(data[i].cName, cN)) {bbs = &data[i]; return true;}
#else
    if (!StrCmp(data[i].cName, cN)) {bbs = &data[i]; return true;}
#endif
    }

  bbs = 0; return false;
  }



void BBSinfo::load() {
//IniFile& ini = theApp.preIniFile;
int      i;
String   s;

  clear();

  nData = iniFile.readInt(nBBS, nBBS, 0);

  for (i = 0; i < nData; i++) {
    BBSdata& bbs = data[i];

    s = section; s += i;
    iniFile.readString(s, Suffix, bbs.suffix);
    iniFile.readString(s, FName,  bbs.fName);
    iniFile.readString(s, CName,  bbs.cName);
    }
  }


void BBSinfo::save() {
//IniFile& ini = theApp.preIniFile;
int      i;
int      j;
String   s;

  for (i = 0, j = 0; i < noElements(data); i++) {
    BBSdata& bbs = data[i];

    if (!bbs.suffix.IsEmpty()) {
      s = section; s += j;
      iniFile.writeString(s, Suffix, bbs.suffix);
      iniFile.writeString(s, FName,  bbs.fName);
      iniFile.writeString(s, CName,  bbs.cName);
      j++;
      }
    }

  iniFile.writeInt(nBBS, nBBS, j);

  for (i = j; i < noElements(data); i++) {
    s = section; s += i;
    iniFile.deleteString(s, Suffix);
    iniFile.deleteString(s, FName);
    iniFile.deleteString(s, CName);
    }
  }

