// BBS Data


#include "pch.h"
#include "BBSinfo.h"
#include "BBSdlg.h"
#include "filesrch.h"
#include "filename.h"
#include "IniFileEx.h"
#include "Outpost.h"
#include "SrchFile.h"


static TCchar* Section = _T("BBS");
static TCchar* Suffix  = _T("Suffix");
static TCchar* NoBBS   = _T("NoBBS");




void BBSinfo::clear() {
BBSIter  iter(*this)  ;
BBSdata* b;

  for (b = iter(); b; b = iter++)
                            {b->bbsNo = -1, b->cName.clear(); b->fName.clear(); b->suffix.clear();}
  data.clear();
  }


bool BBSinfo::load() {
BBSIter  iter(*this);
BBSdata* b;
int      n;
int      i;
String   key;
bool     notEmpty = false;

  clear();   if (!findBBSfiles()) return false;

  n = iniFile.readInt(Section, NoBBS, 0);    if (!n && !getSuffixes()) return false;

  for (b = iter(), i = 1; b != 0 && i <= n; b = iter++, i++) {
    key = Suffix; key += i;   notEmpty |= !b->suffix.isEmpty();
    iniFile.readString(Section, key, b->suffix);
    }

  return notEmpty;
  }


bool BBSinfo::getSuffixes() {
BBSdlg   dlg;
BBSIter  iter(*this);
BBSdata* d;
int      i;
bool     notEmpty = false;

  for (d = iter(), dlg.nData = 0; d; d = iter++, dlg.nData++) {
    BBSdlgDatum& dlgD = dlg.data[dlg.nData];

    dlgD.cName = d->cName; dlgD.fName = d->fName;  dlgD.suffix = d->suffix;
    }

  if (dlg.DoModal() == IDOK) {

    for (d = iter(), i = 0; d; d = iter++, i++) {
      BBSdlgDatum& dlgD = dlg.data[i];

      d->suffix = dlgD.suffix;   notEmpty |= !d->suffix.isEmpty();
      }

    if (notEmpty) bbsInfo.save();
    }

  if (notEmpty) bbsInfo.load();    return notEmpty;
  }


void BBSinfo::save() {
BBSIter  iter(*this);
BBSdata* d;
int      n;
String   key;

  for (d = iter(), n = 0; d; d = iter++, n++)
                   {key = Suffix; key += d->bbsNo;   iniFile.writeString(Section, key, d->suffix);}

  iniFile.writeInt(Section, NoBBS, n);
  }


bool BBSinfo::findBBSfiles() {
String    bbsPath = outpost.getProfile() + _T("bbs.d\\");
String    bbsArb  = _T("X*.bbs");
FileSrch  srch;
String    path;
String    fName;
CString   cName;
String    bbsFile;
int       bbsNo;

  if (!srch.findFiles(bbsPath, bbsArb)) return false;

  while (srch.getName(path)) {

    fName = getMainName(path);

    SrchFile srchFile(path);

      srchFile.forValOf(_T("CName"), cName);

    srchFile.Close();

    bbsNo = findBBSno(fName);    if (bbsNo < 1 || bbsNo > 9) continue;

    BBSdata& p = data.nextData();   p.bbsNo = bbsNo;  p.cName = cName;  p.fName = fName;
    }

  qsort(&data[0], &data[data.end()-1]);

  return nData() > 0;
  }


BBSdata* BBSinfo::find(int bbsNo) {
BBSIter  iter(*this);
BBSdata* b;

  for (b = iter(); b; b = iter++) if (bbsNo == b->bbsNo) return b;

  return 0;
  }


int BBSinfo::findBBSno(TCchar* name) {
String s = name;
int    n = s.length();
int    i;

  for (i = 0; i < n; i++) {
    Tchar ch = s[i];
    if (_T('0') <= ch && ch <= _T('9')) return ch - _T('0');
    }

  return -1;
  }

