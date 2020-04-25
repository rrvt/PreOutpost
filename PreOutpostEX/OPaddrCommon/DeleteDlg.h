#pragma once


// DeleteDlg dialog

class DeleteDlg : public CDialogEx {

  DECLARE_DYNAMIC(DeleteDlg)

public:
CString delAddr;
CStatic address;

  DeleteDlg(CWnd* pParent = nullptr);   // standard constructor
  DeleteDlg(CString& tgt, CWnd* pParent = nullptr);
  virtual ~DeleteDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DeleteDialog };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
};
