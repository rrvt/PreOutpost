#pragma once


// SaveAddresses dialog

class SaveAddresses : public CDialogEx {

  DECLARE_DYNAMIC(SaveAddresses)

public:

           SaveAddresses(CWnd* pParent = nullptr);   // standard constructor
  virtual ~SaveAddresses();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG1 };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
