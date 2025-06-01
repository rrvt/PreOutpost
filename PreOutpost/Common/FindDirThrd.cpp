


#include "pch.h"
#include "FindDirThrd.h"
#include "ProgramFiles.h"


FindDirThrd findDirThrd;        // The single object of this class

TCchar* PacketPat  = _T("*Packet*");
TCchar* OutpostPat = _T("*Outpost*");


int WINAPI findDirFn(void* param) {

  programFiles.loadOutputFldrs(PacketPat);
  programFiles.loadOutputFldrs(OutpostPat);

  return programFiles.nData();
  }
