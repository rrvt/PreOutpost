// List Items for Selection in a Dialog Box List Box Control

#pragma once
#include "Expandable.h"


class ListItems {

CDialog*              myParent;
int                   idc_control;
int                   noItems;
Expandable<String, 2> items;

public:

CString               selected;

  ListItems() {noItems = 0; myParent = 0; idc_control = 0;}
  ListItems(CDialog* parent, int idc) {noItems = 0; init(parent, idc);}
  void init(CDialog* parent, int idc) {myParent = parent; idc_control = idc;}

  void addString(String& item)     {items[noItems++] = item;}
  void addString(const char* item) {items[noItems++] = item;}
  void addToControl();
  void getSelected();
  };
