// Class that corresponds to Dialog box to select Master Profile

#pragma once
#include "ListItems.h"
#include "resource.h"


// NewMasterDlg dialog

class NewMasterDlg : public CDialog {

  DECLARE_DYNAMIC(NewMasterDlg)

ListItems listItems;

public:

Cstring selected;

           NewMasterDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~NewMasterDlg() { }

  void     addListBoxItem(TCchar* item) {listItems.addString(item);}
  void     addListBoxItem(String& item) {listItems.addString(item);}
//String   getListBoxSelection()        {return listItems.selected;}

  enum { IDD = IDD_NewMasterDlg };                       // Dialog Data

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnOK();
  virtual BOOL OnInitDialog();
  afx_msg void onSelectNewMstr();
  afx_msg void onAbout();
  afx_msg void OnHelpMakeMaster();
  afx_msg void OnHelpOverview();
  afx_msg void OnHelpIdentity();
  afx_msg void OnHelpAddressbook();
  afx_msg void OnHelpDeleteMaster();
  afx_msg void OnHelpSelNewMaster();
  afx_msg void OnHelpSelectProfile();
  };
