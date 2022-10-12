// Manage List Box in a Dialog Box

#include "pch.h"
#include "ListItems.h"


void ListItems::addToControl() {
CListBox* ctrl = (CListBox*) myParent->GetDlgItem(idc_control);
LIIter    iter(*this);
String*   p;

  for (p = iter(); p; p = iter++) ctrl->AddString(*p);

  ctrl->SetCurSel(0);
  }



void ListItems::getSelected() {
CListBox* ctrl = (CListBox*) myParent->GetDlgItem(idc_control);
int       i    = ctrl->GetCurSel();

  if (i >= 0) ctrl->GetText(i, selected);
  else selected = _T("");
  }

