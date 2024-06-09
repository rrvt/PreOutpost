// My ToolBar


#include "pch.h"
#include "MyToolBar.h"
#include "Resource.h"


static int NoOfButtonControls =  6;
static int NoOfButtons        = 13;


#ifdef ButtonDefs

MyToolBar::MyToolBar() : docMenu(ID_DocMenu), optMenu(ID_OptMenu)
                        {toolBarDim.initialize(NoOfButtonControls, NoOfButtons);}
#else

MyToolBar::MyToolBar() {toolBarDim.initialize(NoOfButtonControls, NoOfButtons);}

#endif


bool MyToolBar::addButton( uint id, TCchar* caption) {
#if 0
  return add(button,  id, caption);
#endif
  return false;
  }


bool MyToolBar::addEditBox(uint id, int noChars)              {
#if 0
  return add(editBox, id, noChars);
#endif
  return false;
  }


CString MyToolBar::getText(uint id) {
#if 0
  if (id == editBox.getId()) {return ToolBarBase::getText(editBox);}
#endif
  return 0;
  }

#ifdef DocViewTB

bool MyToolBar::addMenu(uint id, int idr, TCchar* caption) {
#ifdef ButtonDefs
int menuID  = menu.getId();
int menu1ID = menu1.getId();
int saveID  = saveMenu.getId();

  if (id == menuID)  return add(menu,     id, idr, caption);
  if (id == menu1ID) return add(menu1,    id, idr, caption);
  if (id == saveID)  return add(saveMenu, id, idr, caption);
#endif
  return false;
  }


bool MyToolBar::addMenu(uint id, int idr, int index) {
#ifdef ButtonDefs
int menuID  = menu.getId();
int menu1ID = menu1.getId();
int saveID  = saveMenu.getId();

  if (id == menuID)  return add(menu,     id, idr, index);
  if (id == menu1ID) return add(menu1,    id, idr, index);
  if (id == saveID)  return add(saveMenu, id, idr, index);
#endif
  return false;
  }


bool MyToolBar::addMenu(uint id, CbxItem cbxItem[], int n, TCchar* caption) {
#ifdef ButtonDefs
  return add(menu1, id, cbxItem, n, caption);
#endif
  return false;
  }

#else


bool MyToolBar::addMenu(uint id, int idr, TCchar* caption) {

  if (docMenu.getId() == id) return add(docMenu, id, idr, caption);
  if (optMenu.getId() == id) return add(optMenu, id, idr, caption);
  return false;
  }


bool MyToolBar::addMenu(uint id, CbxItem cbxItem[], int n, TCchar* caption) {
#if 0
  return add(cbxMenu1, id, cbxItem, n, caption);
#endif
  }


void MyToolBar::dispatch(uint id) {
  if (docMenu.getId() == id)  ToolBarBase::dispatch(docMenu);
  if (optMenu.getId() == id)  ToolBarBase::dispatch(optMenu);
  }

#endif




bool MyToolBar::addCBx(uint id) {
#if 0
  return add(cboBx,  id, 10);
#endif
  return false;
  }


bool MyToolBar::addCBx(uint id, int idr, TCchar* caption) {
#if 0
  return add(cboBx,  id, idr, caption);
#endif
  return false;
  }


bool MyToolBar::addCbxItem(uint id, TCchar* txt, int data) {
#if 0
int cbxID = cboBx.getId();

  if (id == cbxID) {return addItem(cboBx, txt, data);}
#endif
  return false;
  }


bool MyToolBar::addCBx(uint id, CbxItem cbxItem[], int n, TCchar* caption) {
#if 0
  return add(cboBx1,  id, cbxItem, n, caption);
#endif
  return false;
  }


bool MyToolBar::addCbxItemSorted(uint id, TCchar* txt, int data) {
#if 0
int cbxID = cboBx.getId();

  if (id == cbxID) {return addItemSorted(cboBx, txt, data);}
#endif
  return false;
  }


void MyToolBar::setCaption(uint id, TCchar* caption) {
#if 0
int cbxID = cboBx.getId();

  if (id == cbxID) ToolBarBase::setCaption(cboBx, caption);
#endif
  }


void MyToolBar::setWidth(uint id) {
#if 0
int cbxID = cboBx.getId();

  if (id == cbxID) ToolBarBase::setWidth(cboBx);
#endif
  }


void MyToolBar::setHeight( uint id) {
#if 0
int cbxID = cboBx.getId();

  if (id == cbxID) ToolBarBase::setHeight(cboBx);
#endif
  }


#ifdef DocViewTB

bool MyToolBar::getCurSel( uint id, String& s, int& data) {
#ifdef ButtonDefs
int cbxID = cboBx.getId();

  if (id == cbxID) return ToolBarBase::getCurSel(cboBx, s, data);
#endif
  return false;
  }

#else

bool MyToolBar::getCurSel( uint id, String& s, int& data) {
#if 0
int cbxID  = cboBx.getId();
int cbxID1 = cboBx1.getId();

  if (id == cbxID)  return ToolBarBase::getCurSel(cboBx,  s, data);
  if (id == cbxID1) return ToolBarBase::getCurSel(cboBx1, s, data);
#endif
  return false;
  }

#endif




#if 0
editBox(ID_EditBox),
cbxMenu1(ID_PopupMenu1),
//uint cbxId1 = cbxMenu1.getId();
//  if (id == cbxId1) ToolBarBase::dispatch(cbxMenu1);
cboBx(ID_CboBx), cboBx1(ID_CboBx1)11
#endif

