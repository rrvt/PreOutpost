// Outpost Addresses

#pragma once

#include "Expandable.h"
#include "IterT.h"


void makeKey(TCchar* name, TCchar* orgLoc, String& key);


struct Addr {

String key;

String virt;
String orgLoc;
String actual;
String cellPh;
String homePh;
String busPh;
String agency1Name;
String agency1Ph;
String agency2Name;
String agency2Ph;
String notes;
String moreNotes;

bool   dirty;
bool   deleted;

  Addr() : dirty(false), deleted(false) {}

  Addr(Addr& dsc) : dirty(false), deleted(false)  {copy(dsc, *this);}

  void    clear();

  String& getKey() {makeKey(virt, orgLoc, key); return key;}

  void    edit(TCchar* title, bool newAddr);

  Addr&   operator= (Addr& dsc) {copy(dsc, *this); return *this;}
  void    store(String& actual, bool modified);

  void    update();
  void    write(String& fileName);
  void    del(  String& filePath);

private:

  void copy(Addr& src, Addr& dst);
  };


class Addresses;
typedef IterT<Addresses, Addr> AddrIter;


class Addresses {

Expandable<Addr, 2> list;

public:

       Addresses() {}
      ~Addresses() {}

  void load();
  void load(Addr& addr);
  bool delAddr(String& s);
  bool anyChanges();
  void saveAll();

  Addr* find(String& key);
  int   noFound(String& key);

private:

  void insert(Addr& addr);

  // returns either a pointer to data (or datum) at index i in array or zero

  Addr* datum(int i) {return 0 <= i && i < nData() ? &list[i] : 0;}       // or &data[i]

  // returns number of data items in array
  int   nData()      {return list.end();}

  friend typename AddrIter;
  };


extern Addresses addresses;

