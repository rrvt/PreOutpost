// ListBox.cpp : implementation file


#include "pch.h"
#include "ListBox.h"
#include "Addresses.h"
#include "ClipLine.h"
#include "resource.h"
#include "StatusBar.h"

#include "MessageBox.h"


static int baseUnits = LOWORD(::GetDialogBaseUnits());


BOOL ListBox::PreTranslateMessage(MSG* pMsg) {

  if (accelerators && pMsg && ::TranslateAccelerator(pMsg->hwnd, accelerators, pMsg)) return TRUE;

  return CListBox::PreTranslateMessage(pMsg);
  }


BEGIN_MESSAGE_MAP(ListBox, CListBox)
  ON_WM_CONTEXTMENU()
  ON_COMMAND(ID_CopyVirtAddr, &onCopyVirtAddr)
  ON_COMMAND(ID_Organization, &onCopyOrganization)
  ON_COMMAND(ID_CopyActAddr,  &onCopyActAddr)
  ON_COMMAND(ID_EditAddr,     &onEditAddr)

  ON_WM_LBUTTONDBLCLK()
  ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()


// ListBox

IMPLEMENT_DYNAMIC(ListBox, CListBox)


ListBox::ListBox(StatusBar& sts) : wnd(0), font(0), statusBar(sts) {

  sub.CreatePopupMenu();

  sub.AppendMenu(MF_STRING, ID_CopyVirtAddr, _T("Copy &Virtual Addr\tCtrl+B"));
  sub.AppendMenu(MF_STRING, ID_Organization, _T("Copy &Organization\tCtrl+O"));
  sub.AppendMenu(MF_STRING, ID_CopyActAddr,  _T("Copy &Actual Addr\tCtrl+C"));
  sub.AppendMenu(MF_STRING, ID_EditAddr,     _T("Edit Address\tCtrl+E"));

  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));        //

  accelerators = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDD_OpAddrBk));

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
int      tab;


  ResetContent();

  dc  = GetDC();

    dc->SelectObject(font);

    for (addr = iter(), dx = 0; addr; addr = iter++) if (!addr->deleted)
        {add(*addr);   sz = dc->GetTextExtent(CString(addr->virt));   if (sz.cx > dx) dx  = sz.cx;}

    tab = (dx + 4 * baseUnits - 1) / baseUnits;   SetTabStops(tab * 4);

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
                                     {onCopyActAddr();   CListBox::OnLButtonDblClk(nFlags, point);}

void ListBox::onCopyVirtAddr() {
Addr*  addr = findAddr();
String s;

  if (addr) {s = _T('+') + addr->virt; loadClipBoard(s);}
  }


void ListBox::onCopyActAddr()  {Addr* addr = findAddr();    if (addr) loadClipBoard(addr->actual);}
void ListBox::onCopyOrganization()
                          {Addr* addr = findAddr();   if (addr) loadClipBoard(addr->organization);}



void ListBox::OnMButtonDown(UINT nFlags, CPoint point) {
  onEditAddr();

  CListBox::OnMButtonDown(nFlags, point);
  }


void ListBox::onEditAddr() {
String key = selVirt();
String s   = _T("Editing ") + key;

  statusBar.setText(s);   addresses.edit(key);   load();   statusBar.setText(_T("Ready"));
  }


Addr* ListBox::findAddr() {String key = selVirt();   return addresses.find(key);}


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





//void ListBox::copyActual() {Addr* addr = findAddr();    if (addr) loadClipBoard(addr->actual);}
//void ListBox::copyVirt()   {Addr* addr = findAddr();    if (addr) loadClipBoard(addr->virt);}
//void ListBox::copyOrganization()
  //                      {Addr* addr = findAddr();    if (addr) loadClipBoard(addr->organization);}
#if 1
#else
int     x = GetCurSel();   if (x < 0) return 0;
CString cs;

  GetText(x, cs);

  String key = parseListKey(cs);
#endif


#if 0
  void ListBox::onSelChangePathList()   {
    // TODO: Add your control notification handler code here
    }
#endif



// tab *= baseUnits;   dataTab = tab * 4 / baseUnits;
//    dx += 3 * baseUnits;
//int      dataTab;
//ON_LBN_SELCHANGE(IDC_PathList, &ListBox::onSelChangePathList)

