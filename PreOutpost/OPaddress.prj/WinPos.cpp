// Manage Window Position and Size


#include "stdafx.h"
#include "WinPos.h"
#include "PosSizeData.h"


WinPos::WinPos() : window(0) {
RECT rsys;

  SystemParametersInfo(SPI_GETWORKAREA, 0, &rsys, 0);   maxWidth = rsys.right;   maxHeight = rsys.bottom;
  }


void WinPos::set() {

  posSz.load();

  posSz.normalize(maxWidth, maxHeight);

  window->SetWindowPos(0, posSz.left, posSz.top, posSz.width, posSz.depth, SWP_NOCOPYBITS | SWP_NOACTIVATE );
  }


void WinPos::getRect() {RECT r;   if (getWindow()) {window->GetWindowRect(&r);   posSz = r;}}

