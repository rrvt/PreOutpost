// OpAddrBk.h -- Template for a Dialog Box Application


#pragma once
#include "CApp.h"


class OpAddrBk : public CApp {
public:

UINT  m_nAppLook;

  OpAddrBk() noexcept;

public:

  virtual BOOL InitInstance();
  virtual int  ExitInstance();
  };


extern OpAddrBk theApp;
