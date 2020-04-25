// Manage List Box in a Dialog Box

#include "stdafx.h"
#include "ListItems.h"


void ListItems::addToControl() {
CListBox* p = (CListBox*) myParent->GetDlgItem(idc_control);
int i;
int rslt;

  for (i = 0; i < noItems; i++) {
    rslt = p->AddString(items[i]);
    if (rslt != i) {
      int x = 1;
      }
    }

  rslt = p->SetCurSel(0);
  if (rslt == LB_ERR) {
    int y = 1;
    }
  }



void ListItems::getSelected() {
CListBox* p = (CListBox*) myParent->GetDlgItem(idc_control);
int       i = p->GetCurSel();

  if (i >= 0) p->GetText(i, selected);
  else selected = _T("");
  }

