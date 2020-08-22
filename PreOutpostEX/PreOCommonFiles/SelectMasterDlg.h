// Class that corresponds to the Dialog Box that allows the user to select the Master Profile when there
// are two or more Master Profiles

#pragma once
#include "ListItems.h"
#include "resource.h"


// SelectMasterDlg dialog

class SelectMasterDlg : public CDialog {

  DECLARE_DYNAMIC(SelectMasterDlg)

ListItems listItems;

public:

int       allProfiles;

  SelectMasterDlg(CWnd* pParent = NULL);   // standard constructor

  virtual ~SelectMasterDlg();
  virtual BOOL OnInitDialog();
  void    addListBoxItem(TCchar* item) {listItems.addString(item);}
  void    addListBoxItem(String&     item) {listItems.addString(item);}
  String  getListBoxSelection()            {return listItems.selected;}


  enum { IDD = IDD_ProcessOneOrAllDialog };                       // Dialog Data

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnOK();
  afx_msg void OnDblclkList1();
  afx_msg void OnAbout32780();
  afx_msg void OnHelp32779();
};
