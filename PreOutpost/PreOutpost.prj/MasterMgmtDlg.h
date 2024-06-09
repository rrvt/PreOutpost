// Class that corresponds to the Dialog Box that allows the user to create a new Master Profile or
// Delete a Master Profile.

#pragma once
#include "ListItems.h"
#include "resource.h"


enum {DeleteMaster = 0, CreateMaster = 1};


// MasterMgmtDlg dialog

class MasterMgmtDlg : public CDialog {

  DECLARE_DYNAMIC(MasterMgmtDlg)

ListItems listItems;

public:
  MasterMgmtDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~MasterMgmtDlg();

  virtual BOOL OnInitDialog();

// Dialog Data
  enum { IDD = IDD_ManageMasterDialog };

  void   OnSetBBSsuffixes();

  void   addListBoxItem(TCchar* item) {listItems.addString(item);}
  void   addListBoxItem(String& item) {listItems.addString(item);}
  String getListBoxSelection()        {return listItems.selected;}

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void createNew();
  afx_msg void delSelected();
  afx_msg void OnClickedButton1();
  afx_msg void OnAbout();
  afx_msg void OnHelpMakeMaster();
  afx_msg void OnHelpOverview();
  afx_msg void OnHelpIdentity();
  afx_msg void OnHelpAddressbook();
  afx_msg void OnHelpDeleteMaster();
  afx_msg void OnHelpSelNewMaster();
  afx_msg void OnHelpSelectProfile();
#ifdef DialogSizable02
  afx_msg void OnSize(UINT nType, int cx, int cy);
#endif
  };