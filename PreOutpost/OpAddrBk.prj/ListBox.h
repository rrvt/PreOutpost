// List Box used in the OpAddrDlg


#pragma once
#include "Addresses.h"


// ListBox

class ListBox : public CListBox {

DECLARE_DYNAMIC(ListBox)

CWnd*      wnd;
CFont*     font;
StatusBar& statusBar;

HACCEL     accelerators;

public:

CMenu  menu;
CMenu  sub;
                 ListBox(StatusBar& sts);
  virtual       ~ListBox() { }

          bool   create(DWORD style, RECT rect, CWnd* parent, uint id);
          void   moveWindow(RECT screenRect, bool rePaint = true);

  virtual BOOL   PreTranslateMessage(MSG* pMsg);

          void   load();

          void   add(Addr& addr);

          String selVirt();
          Addr*  findAddr();

protected:

  DECLARE_MESSAGE_MAP()

private:

  void screenToClient(RECT& rect) {::MapWindowPoints(0, wnd->m_hWnd, (POINT*)&rect, 2);}

  String parseListKey(TCchar* ts);

  ListBox() : statusBar(*(StatusBar*)0) { }

public:

  afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
  afx_msg void onCopyVirtAddr();
  afx_msg void onCopyActAddr();
  afx_msg void onCopyOrganization();
  afx_msg void onEditAddr();
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
};





//  void     copyVirt();
//  void     copyActual();
//  void     copyOrganization();

