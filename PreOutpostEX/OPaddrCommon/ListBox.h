#pragma once
#include "Addresses.h"


// ListBox

class ListBox : public CListBox {

DECLARE_DYNAMIC(ListBox)

public:

CMenu      menu;
CMenu      sub;

           ListBox();
  virtual ~ListBox();

  void     copyVirt();
  void     copyActual();
  void     copyLoc();

  void     add(Addr& addr);

  Addr*    find();

protected:

  DECLARE_MESSAGE_MAP()

private:

  String parseListKey(TCchar* ts);

public:
  afx_msg void OnDblclkList();
  afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
  afx_msg void OnCopyvirtualaddr();
  afx_msg void OnCopylocation();
  afx_msg void OnCopyactualaddr();
  };


