// BBS Data


#pragma once
#include "Expandable.h"
#include "IterT.h"
#include "qsort.h"



struct BBSdata {

int    bbsNo;
String fName;
String cName;
String suffix;

  BBSdata() {}
  BBSdata(BBSdata& b) {bbsNo = b.bbsNo; fName = b.fName; cName = b.cName; suffix = b.suffix;}
 ~BBSdata() {}

// Requires the following operations for node N* p, N* q, N* s
//  *s = *p
//  *p == *q
//  *p >  *q
//  *p <= *q

  BBSdata& operator=
       (BBSdata& b) {bbsNo = b.bbsNo; fName = b.fName; cName = b.cName; suffix = b.suffix; return *this;}
  bool operator== (BBSdata& b) {return bbsNo == b.bbsNo;}
  bool operator>  (BBSdata& b) {return bbsNo >  b.bbsNo;}
  bool operator<= (BBSdata& b) {return bbsNo <= b.bbsNo;}
  };


class BBSinfo;
typedef IterT<BBSinfo, BBSdata> BBSIter;


class BBSinfo {

Expandable<BBSdata, 2> data;

public:

  BBSinfo() {}

  void     getSuffixes();

  void     findBBSfiles();

  void     load();
  void     save();
  void     clear();

private:

  BBSdata* find(int bbsNo);
  int      findBBSno(TCchar* name);

  // returns either a pointer to data (or datum) at index i in array or zero

  BBSdata* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  int   nData()      {return data.end();}                       // returns number of data items in array

  friend typename BBSIter;
  };


extern BBSinfo bbsInfo;
