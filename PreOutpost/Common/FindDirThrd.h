// Find Directories



#pragma once


#include "ThreadBase.h"


int WINAPI findDirFn(void* param);

extern TCchar* PacketPat;
extern TCchar* OutpostPat;


class FindDirThrd : public ThreadBase {

public:

  FindDirThrd() { }

  void start(int param) {ThreadBase::start(findDirFn, (void*) param);}
  void stop()           {ThreadBase::stop();}
  };


extern FindDirThrd findDirThrd;
