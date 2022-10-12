// Outpost Addresses

#pragma once

#include "Expandable.h"
#include "IterT.h"


extern TCchar* AddrExt;


struct Addr {

String path;
String mainName;

String version;
String virt;
String orgLoc;
String actual;
String notes;
String homePh;
String cellPh;
String busPh;
String agency1Name;
String agency1Ph;
String agency2Name;
String agency2Ph;
String moreNotes;

bool   dirty;
bool   deleted;

  Addr() : dirty(false), deleted(false) {}

  Addr(Addr& a) {copy(a);}

  void    clear();

  void    read(TCchar*  path);
  void    write();
  void    fixVirt();

  bool    edit(TCchar* title, bool newAddr = false);

  Addr&   operator= (Addr& a) {copy(a); return *this;}
  void    store(String& actual, bool modified);

  void    update(TCchar* addrPath);

private:

  void copy(Addr& a);
  };


class Addresses;
typedef IterT<Addresses, Addr> AddrIter;


class Addresses {
String              curVersion;
Expandable<Addr, 2> addrs;

public:

        Addresses() { }
       ~Addresses() { }

  void  newAddr(TCchar* addrPath);
  void  edit(TCchar* key);
  bool  delAddr(TCchar* key);

  void  load(TCchar* adrPath);
  void  load(Addr& addr);
  bool  anyChanges();
  void  saveAll(TCchar* addrPath);

  Addr* find(TCchar* name);

private:

  void insert(Addr& addr);

  // returns either a pointer to data (or datum) at index i in array or zero

  Addr* datum(int i) {return 0 <= i && i < nData() ? &addrs[i] : 0;}       // or &data[i]

  void  removeDatum(int i) {if (0 <= i && i < nData()) addrs.del(i);}

  // returns number of data items in array
  int   nData()      {return addrs.end();}

  friend typename AddrIter;
  };


extern Addresses addresses;

