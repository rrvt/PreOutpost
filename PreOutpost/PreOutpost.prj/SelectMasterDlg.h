// Class that corresponds to the Dialog Box that allows the user to select the Master Profile when
// there are two or more Master Profiles

#pragma once
#include "ListItems.h"
#include "resource.h"


// SelectMasterDlg dialog

class SelectMasterDlg : public CDialogEx {

  DECLARE_DYNAMIC(SelectMasterDlg)

ListItems listItems;

public:

Cstring   selected;
int       allProfiles;

           SelectMasterDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~SelectMasterDlg() { }

  virtual BOOL   OnInitDialog();
          void   addListBoxItem(TCchar* item) {listItems.addString(item);}
          void   addListBoxItem(String& item) {listItems.addString(item);}
//          String getListBoxSelection()        {return listItems.selected;}

  enum { IDD = IDD_SelectMasterDlg };                       // Dialog Data

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnOK();
  afx_msg void onSelectMaster();
  afx_msg void onAbout();
  afx_msg void OnHelpMakeMaster();
  afx_msg void OnHelpOverview();
  afx_msg void OnHelpIdentity();
  afx_msg void OnHelpAddressbook();
  afx_msg void OnHelpDeleteMaster();
  afx_msg void OnHelpSelNewMaster();
  afx_msg void OnHelpSelectProfile();
#ifdef DialogSizable04X
  afx_msg void OnSize(UINT nType, int cx, int cy);
#endif
  };

