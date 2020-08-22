// Class that corresponds to Dialog box to select Master Profile

#pragma once
#include "ListItems.h"
#include "resource.h"


// NewMasterDlg dialog

class NewMasterDlg : public CDialog {

  DECLARE_DYNAMIC(NewMasterDlg)

ListItems listItems;


public:

CString selected;

  NewMasterDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~NewMasterDlg();

  void   addListBoxItem(TCchar* item) {listItems.addString(item);}
  void   addListBoxItem(String&     item) {listItems.addString(item);}
  String getListBoxSelection()            {return listItems.selected;}

  enum { IDD = IDD_SelectMasterDialog };                       // Dialog Data

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnOK();
  virtual BOOL OnInitDialog();
  afx_msg void OnDblclkList1();
  afx_msg void OnAbout32780();
  afx_msg void OnHelp32779();
};
