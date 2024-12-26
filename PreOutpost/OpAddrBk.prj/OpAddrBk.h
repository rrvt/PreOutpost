// OpAddrBk.h -- Template for a Dialog Box Application


#pragma once
#include "CDialogApp.h"


class OpAddrBk : public CDialogApp {
public:

UINT  m_nAppLook;

  OpAddrBk() noexcept;

public:

  virtual BOOL InitInstance();
  virtual int  ExitInstance();
  };


extern OpAddrBk theApp;
