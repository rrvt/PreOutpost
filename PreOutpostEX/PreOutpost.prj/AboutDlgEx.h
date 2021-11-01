// About Dialog


#pragma once
#include "resource.h"


// AboutDlg dialog used for App About

class AboutDlgEx : public CDialogEx {
bool useProdName;
public:

enum { IDD = IDD_ABOUTBOX };     // Dialog Data

  AboutDlgEx(bool useInternalName) : useProdName(!useInternalName), CDialogEx(AboutDlgEx::IDD) { }
  AboutDlgEx()                     : useProdName(true),             CDialogEx(AboutDlgEx::IDD) { }

  virtual BOOL OnInitDialog();

protected:

  void getOutpostData();
  void getPackItData();
  void getPackFormsVerData();

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  };

