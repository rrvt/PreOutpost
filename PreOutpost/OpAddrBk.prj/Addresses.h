// Outpost Addresses

#pragma once

#include "ExpandableP.h"
#include "IterT.h"

class FileIO;
class StatusBar;

extern TCchar* AddrExt;


struct Addr {

String path;
String mainName;

String version;
String virt;
String organization;
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

  Addr&   operator=  (Addr& a) {copy(a); return *this;}
  bool    operator>= (Addr& d) {return virt >= d.virt;}               // Required for data = datum

  bool    operator== (TCchar* key) {return virt == key;}

  void    store(String& actual, bool modified);

  void    update(TCchar* addrPath);
  void    output(FileIO& file, int brk);

private:

  void copy(Addr& a);
  };


typedef DatumPtrT<Addr, TCchar*> AddrP;
class Addresses;
typedef IterT<Addresses, Addr> AddrIter;


class Addresses {
String              curVersion;
ExpandableP<Addr, TCchar*, AddrP, 2> data;

public:

        Addresses() { }
       ~Addresses() { }

  void  clear() {data.clear();   curVersion.clear();}

  void  newAddr(TCchar* addrPath);
  void  edit(   TCchar* key);

  void  load(TCchar* adrPath);                  // Load Address Files on adrPath to data array
  void  add( Addr&   addr);                     // Add a single Address Record to data array

  bool  anyChanges();
  void  saveAll(TCchar* addrPath, StatusBar& statusBar);
  void  saveData(StatusBar& statusBar);

  Addr* find(TCchar* name) {return data.find(name);}

private:

  void insert(Addr& addr);

  // returns either a pointer to data (or datum) at index i in array or zero

  Addr* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  int   nData()      {return data.end();}                  // returns number of data items in array

  friend typename AddrIter;
  };


extern Addresses addresses;





//  bool  delAddr(TCchar* key);

