#pragma once
#include "BBSdata.h"
#include "resource.h"


// BBSSuffix dialog

class BBSSuffix : public CDialog {

  DECLARE_DYNAMIC(BBSSuffix)

public:

// Dialog Data

enum { IDD = IDD_DIALOG2 };

           BBSSuffix(CWnd* pParent = NULL);   // standard constructor
  virtual ~BBSSuffix();

      void getSuffixes();

protected:

  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  void findBBSfiles(BBSinfo& newInfo);
  };
