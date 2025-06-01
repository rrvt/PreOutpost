// Outpost Folders -- Just a list of all of them


#pragma once
#include "Expandable.h"
#include "IterT.h"


class OutpostFolders;
typedef IterT<OutpostFolders, String> OpfIter;


class OutpostFolders {

Expandable<String, 2> data;

public:

  OutpostFolders() { }
 ~OutpostFolders() { }

  void add(TCchar* path) {data.nextData() = path;}

  int  nData()      {return data.end();}                // Returns number of data items in array,
                                                        // not necessarily private
private:

  // returns either a pointer to datum at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}
  void    removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename OpfIter;
  };

