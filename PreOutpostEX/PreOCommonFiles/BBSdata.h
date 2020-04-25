// BBS Data


#pragma once




struct BBSdata {

CString suffix;
CString fName;
CString cName;

  BBSdata(TCchar* sfx, TCchar* fnm, TCchar* cnm) : suffix(sfx), fName(fnm), cName(cnm) {}
  BBSdata() {}
 ~BBSdata() {}
  };


class BBSinfo {
int     nData;
BBSdata data[10];

public:

  BBSinfo() : nData(0) {}

  bool isAvailable() {return nData > 0;}

  void load();
  void save();
  void clear();

  BBSdata* get(int x)  {return x < nData ? &data[x] : 0;}
  bool     find(CString& cN, BBSdata*& bbs);
  bool     isNotFull() {return nData < noElements(data);}
  BBSdata* put()       {return nData < noElements(data) ? &data[nData++] : 0;}
  BBSdata* xch(int i)  {return i < noElements(data) ? &data[i] : 0;}
  };


extern BBSinfo bbsInfo;
