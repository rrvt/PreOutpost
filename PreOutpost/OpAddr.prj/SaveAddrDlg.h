// Save Addresses that have changed


#pragma once


// SaveAddrDlg dialog

class SaveAddrDlg : public CDialogEx {

  DECLARE_DYNAMIC(SaveAddrDlg)

public:

           SaveAddrDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~SaveAddrDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_SaveAddr };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
