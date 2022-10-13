// OpAddr.h -- Template for a Dialog Box Application


#pragma once
#include "CApp.h"


class OpAddr : public CApp {

public:
               OpAddr() noexcept;

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

private:

  void addBackSlash(String& path);

  };


extern OpAddr theApp;
