// ListBox.cpp : implementation file
//

#include "stdafx.h"
#include "ListBox.h"
#include "LoadClipBoard.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(ListBox, CListBox)
  ON_LBN_DBLCLK(IDC_LIST, &ListBox::OnDblclkList)
  ON_WM_CONTEXTMENU()
  ON_COMMAND(ID_COPYVIRTUALADDR, &ListBox::OnCopyvirtualaddr)
  ON_COMMAND(ID_COPYLOCATION,    &ListBox::OnCopylocation)
  ON_COMMAND(ID_COPYACTUALADDR,  &ListBox::OnCopyactualaddr)
END_MESSAGE_MAP()



// ListBox

IMPLEMENT_DYNAMIC(ListBox, CListBox)



ListBox::ListBox() {

  sub.CreatePopupMenu();

  sub.AppendMenu(MF_STRING, ID_COPYVIRTUALADDR, _T("Copy &Virtual Addr\tCtrl+B"));
  sub.AppendMenu(MF_STRING, ID_COPYLOCATION,    _T("Copy &Location\tCtrl+L"));
  sub.AppendMenu(MF_STRING, ID_COPYACTUALADDR,  _T("Copy &Actual Addr\tCtrl+C"));

  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));        //

  sub.Detach();
  }


ListBox::~ListBox() { }




void ListBox::OnCopyvirtualaddr() {copyVirt();}
void ListBox::OnCopylocation()    {copyLoc();}
void ListBox::OnCopyactualaddr()  {copyActual();}

void ListBox::OnDblclkList()      {copyActual();}

void ListBox::copyActual() {Addr* addr = find();    if (addr) loadClipBoard(addr->actual);}
void ListBox::copyVirt()   {Addr* addr = find();    if (addr) loadClipBoard(addr->virt);}
void ListBox::copyLoc()    {Addr* addr = find();    if (addr) loadClipBoard(addr->orgLoc);}


void ListBox::add(Addr& addr) {String s = addr.virt + _T("\t") + addr.actual;   AddString(s);}



Addr* ListBox::find() {
int     x = GetCurSel();   if (x < 0) return 0;
CString cs;

  GetText(x, cs);

  String key = parseListKey(cs);

  return addresses.find(key);
  }




String ListBox::parseListKey(TCchar* ts) {
String listKey = ts;
int    pos;

  pos = listKey.find(_T('\t'));  if (pos < 0) return String(_T(""));

  return listKey.substr(0, pos);
  }



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
