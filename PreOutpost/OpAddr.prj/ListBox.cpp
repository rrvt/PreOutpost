// ListBox.cpp : implementation file


#include "stdafx.h"
#include "ListBox.h"
#include "ClipLine.h"
#include "resource.h"

#include "MessageBox.h"


static int baseUnits = LOWORD(::GetDialogBaseUnits());


BEGIN_MESSAGE_MAP(ListBox, CListBox)
  ON_WM_CONTEXTMENU()
  ON_COMMAND(ID_CopyVirtAddr, &onCopyVirtAddr)
  ON_COMMAND(ID_CopyLoc,      &onCopyLoc)
  ON_COMMAND(ID_CopyActAddr,  &onCopyActAddr)

  ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// ListBox

IMPLEMENT_DYNAMIC(ListBox, CListBox)


ListBox::ListBox() : wnd(0), font(0) {

  sub.CreatePopupMenu();

  sub.AppendMenu(MF_STRING, ID_CopyVirtAddr, _T("Copy &Virtual Addr\tCtrl+B"));
  sub.AppendMenu(MF_STRING, ID_CopyLoc,      _T("Copy &Location\tCtrl+L"));
  sub.AppendMenu(MF_STRING, ID_CopyActAddr,  _T("Copy &Actual Addr\tCtrl+C"));

  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));        //

  sub.Detach();
  }


bool ListBox::create(DWORD style, RECT rect, CWnd* parent, uint id) {
bool rslt;

  wnd = parent;   if (!wnd) return false;

  screenToClient(rect);   rslt = Create(style, rect, wnd, id);

  font = wnd->GetFont(); SetFont(font);   return rslt;
  }


void ListBox::moveWindow(RECT screenRect, bool rePaint) {

  screenToClient(screenRect);   MoveWindow(&screenRect, rePaint);
  }


void ListBox::load() {
AddrIter iter(addresses);
Addr*    addr;
CDC*     dc;
CSize    sz;
int      dx;
int      dataTab;


  ResetContent();

  dc  = GetDC();

    dc->SelectObject(font);

    for (addr = iter(), dx = 0; addr; addr = iter++) if (!addr->deleted)
         {add(*addr);   sz = dc->GetTextExtent(CString(addr->virt));   if (sz.cx > dx) dx  = sz.cx;}

    tab = (dx + baseUnits - 1) / baseUnits;   tab *= baseUnits;

    dataTab = tab * 4 / baseUnits;  SetTabStops(dataTab);   tab = tab * 11284 / 10000;

  ReleaseDC(dc);
  }


void ListBox::add(Addr& addr) {String s = addr.virt + _T("\t") + addr.actual;   AddString(s);}


void ListBox::OnContextMenu(CWnd* , CPoint point) {
CRect  rect;
CMenu* popup;
CWnd*  pWndPopupOwner = this;

  if (point.x == -1 && point.y == -1)
            {GetClientRect(rect);  ClientToScreen(rect);  point = rect.TopLeft();  point.Offset(5, 5);}

  popup = menu.GetSubMenu(0);   if (!popup) return;

  while (pWndPopupOwner->GetStyle() & WS_CHILD) pWndPopupOwner = pWndPopupOwner->GetParent();

  popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
  }


void ListBox::OnLButtonDblClk(UINT nFlags, CPoint point)
                                              {copyActual();   CListBox::OnLButtonDblClk(nFlags, point);}

void ListBox::onCopyVirtAddr() {copyVirt();}
void ListBox::onCopyLoc()      {copyLoc();}
void ListBox::onCopyActAddr()  {copyActual();}

void ListBox::copyActual() {Addr* addr = findAddr();    if (addr) loadClipBoard(addr->actual);}
void ListBox::copyVirt()   {Addr* addr = findAddr();    if (addr) loadClipBoard(addr->virt);}
void ListBox::copyLoc()    {Addr* addr = findAddr();    if (addr) loadClipBoard(addr->orgLoc);}


Addr* ListBox::findAddr() {
#if 1
String key = selVirt();
#else
int     x = GetCurSel();   if (x < 0) return 0;
CString cs;

  GetText(x, cs);

  String key = parseListKey(cs);
#endif
  return addresses.find(key);
  }


String ListBox::selVirt() {
int     x = GetCurSel();   if (x < 0) return _T("");
CString cs;

  GetText(x, cs);

  String key = parseListKey(cs);   return key;
  }


String ListBox::parseListKey(TCchar* ts) {
String listKey = ts;
int    pos;

  pos = listKey.find(_T('\t'));  if (pos < 0) return String(_T(""));

  return listKey.substr(0, pos);
  }

