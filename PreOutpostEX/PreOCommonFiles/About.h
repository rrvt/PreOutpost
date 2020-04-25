// Display About Dialog Box

#pragma once
#include "Resource.h"

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog {

public:

  CAboutDlg();

// Dialog Data

  enum { IDD = IDD_ABOUTBOX };

protected:

  virtual BOOL OnInitDialog();

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation

protected:
  DECLARE_MESSAGE_MAP()

private:

  void setVersions();
  void getOutpostData();
  void getPackItData();
  void getPackFormsVerData();

public:
  CStatic nameVersion;
};

