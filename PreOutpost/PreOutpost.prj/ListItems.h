// List Items for Selection in a Dialog Box List Box Control

#pragma once
#include "Expandable.h"
#include "IterT.h"


class ListItems;
typedef IterT<ListItems, String> LIIter;


class ListItems {

CDialog* myParent;
int      idc_control;

Expandable<String, 2> items;

public:

CString selected;

  ListItems() {myParent = 0; idc_control = 0;}
  ListItems(CDialog* parent, int idc) {init(parent, idc);}
  void init(CDialog* parent, int idc) {myParent = parent; idc_control = idc;}

  void addString(String& item) {items += item;}      //[items.end()] [items.end()]
  void addString(TCchar* item) {items.nextData() = item;}
  void addToControl();
  void getSelected();

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? &items[i] : 0;}       // or data[i].p

  int   nData()      {return items.end();}                 // returns number of data items in array

  friend typename LIIter;
  };
