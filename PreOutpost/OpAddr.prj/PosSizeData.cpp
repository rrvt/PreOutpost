// Window Data
// Copyright Software Design & Engineering, Robert R. Van Tuyl, 2013.  All rights reserved.


#include "pch.h"
#include "PosSizeData.h"
#include "IniFile.h"


static TCchar* WindowPosData = _T("Window Position Data");
static TCchar* Left          = _T("Left");
static TCchar* Top           = _T("Top");
static TCchar* Width         = _T("Width");
static TCchar* Depth         = _T("Depth");


void PosSizeData::save() {
  iniFile.writeInt(WindowPosData, Left,  left);
  iniFile.writeInt(WindowPosData, Top,   top);
  iniFile.writeInt(WindowPosData, Width, width);
  iniFile.writeInt(WindowPosData, Depth, depth);
  }


void PosSizeData::load() {
  left   = iniFile.readInt(WindowPosData, Left,   100);   if (left   <  0) left  =  0;
  top    = iniFile.readInt(WindowPosData, Top,    100);   if (top    <  0) top   =  0;
  width  = iniFile.readInt(WindowPosData, Width, 1031);   if (width  < 50) width = 50;
  depth  = iniFile.readInt(WindowPosData, Depth,  923);   if (depth  < 50) depth = 50;
  }



void PosSizeData::normalize(int maxWidth, int maxDepth) {

  if (width        < 100 || maxWidth < width) width = 100;
  if (depth        < 100 || maxDepth < depth) depth = 100;
  if (left         < 0)                       left  = 0;
  if (left + width > maxWidth)                left  = maxWidth  - width;
  if (top          < 0)                       top   = 0;
  if (top  + depth > maxDepth)                top   = maxDepth - depth;
  }

