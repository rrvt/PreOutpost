// Class that corresponds to the Dialog Box that allows the user to create a new Master Profile or Delete
// a Master Profile.

#pragma once
#include "ListItems.h"


enum {DeleteMaster = 0, CreateMaster = 1};


// ManageMasterProfiles dialog

class ManageMasterProfiles : public CDialog {

  DECLARE_DYNAMIC(ManageMasterProfiles)

ListItems listItems;

public:
  ManageMasterProfiles(CWnd* pParent = NULL);   // standard constructor
  virtual ~ManageMasterProfiles();

// Dialog Data
  enum { IDD = IDD_ManageMasterDialog };

  void   OnSetBBSsuffixes();

  void   addListBoxItem(const char* item) {listItems.addString(item);}
  void   addListBoxItem(String&     item) {listItems.addString(item);}
  String getListBoxSelection()           {return listItems.selected;}

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void createNewMaster();
  afx_msg void deleteSelectedMaster();
  virtual BOOL OnInitDialog();
  afx_msg void OnClickedButton1();
  afx_msg void OnAbout32775();
  afx_msg void OnHelp32776();
  };
