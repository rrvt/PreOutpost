// My ToolBar


#pragma once

#define ButtonDefs



#include "TBCbxMenu.h"
#include "ToolBarBase.h"

struct CbxItem;


class MyToolBar : public ToolBarBase {

TBCbxMenu docMenu;
TBCbxMenu optMenu;

public:

  MyToolBar();
 ~MyToolBar() { }

  bool    addButton( uint id, TCchar* caption);
  bool    addEditBox(uint id, int     noChars);
  CString getText(uint id);

  bool    addMenu(   uint id, int     idr, TCchar* caption);
  bool    addMenu(   uint id, CbxItem cbxItem[], int n, TCchar* caption);
  void    dispatch(uint id);

  bool    addCBx(    uint id);
  bool    addCBx(    uint id, int     idr, TCchar* caption);
  bool    addCbxItem(uint id, TCchar* txt, int data = 0);
  bool    addCBx(    uint id, CbxItem cbxItem[], int n, TCchar* caption);
  bool    addCbxItemSorted(uint id, TCchar* txt, int data = 0);

  void    setCaption(uint id, TCchar* caption);
  void    setWidth(  uint id);
  void    setHeight( uint id);
  bool    getCurSel( uint id, String& s, int& data);
  };



#if 0
TBEditBox editBox;
TBCbxMenu cbxMenu1;

TBCboBx   cboBx;
TBCboBx   cboBx1;
#if 0
//#define DocViewTB
#include "TBButton.h"
#include "TBEditBox.h"
#ifdef DocViewTB
#include "TBMenu.h"
#else
#endif
#include "TBCboBx.h"
#endif
#endif
#if 0

//TBButton  button;

#ifdef DocViewTB

TBMenu    menu;
TBMenu    menu1;

#else

#endif

#ifdef DocViewTB

TBMenu    saveMenu;

#else


#endif
#endif
#if 0

  bool    addMenu(   uint id, int     idr, TCchar* caption);
  bool    addMenu(   uint id, int     idr, int     index);
  bool    addMenu(   uint id, CbxItem cbxItem[], int n, TCchar* caption);

#endif

