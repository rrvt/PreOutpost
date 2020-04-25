// Class that corresponds to the Dialog Box that allows the user to select the Master Profile when there
// are two or more Master Profiles

#pragma once
#include "ListItems.h"


// MasterProfile dialog

class MasterProfile : public CDialog {

  DECLARE_DYNAMIC(MasterProfile)

ListItems listItems;

public:

int       allMasterProfiles;

  MasterProfile(CWnd* pParent = NULL);   // standard constructor

  virtual ~MasterProfile();
  void   addListBoxItem(const char* item) {listItems.addString(item);}
  void   addListBoxItem(String&     item) {listItems.addString(item);}
  String getListBoxSelection()            {return listItems.selected;}


  enum { IDD = IDD_ProcessOneOrAllDialog };                       // Dialog Data

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
