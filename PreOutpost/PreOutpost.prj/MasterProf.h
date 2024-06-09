// Master Profile Manipulation


#pragma once
#include "Expandable.h"
#include "IterT.h"
#include "NewMaster.h"
#include "qsort.h"


struct Master {
String name;
String path;

  Master() { }
  Master(Master& m) {name = m.name; path = m.path;}

  //  *s = *p
  //  *p == *q
  //  *p >  *q
  //  *p <= *q

  Master& operator=  (Master& m) {name = m.name; path = m.path; return *this;}
  bool    operator== (Master& m) {return name == m.name;}
  bool    operator>  (Master& m) {return name >  m.name;}
  bool    operator<= (Master& m) {return name <= m.name;}
  };


class MasterProf;
typedef IterT<MasterProf, Master> MPIter;


class MasterProf {

Expandable<Master, 1> masters;

bool allProfiles;

public:

String name;
String path;

  MasterProf() { }
 ~MasterProf() { }

  void    readIniFile();
  void    setMetaProfiles();

  bool    insertNewProfile(String& newProfile);

  Master* select();
  bool    process(Master* m);

  int     nMasters() {return masters.end();}

private:

  String getKey(int i);
  void   OnSelectMasterProfile();

  // returns either a pointer to data (or datum) at index i in array or zero

  Master* datum(int i) {return 0 <= i && i < nData() ? &masters[i] : 0;}       // or data[i].p

  int     nData()      {return masters.end();}             // returns number of data items in array

  friend typename MPIter;
  };


extern MasterProf masterProf;

