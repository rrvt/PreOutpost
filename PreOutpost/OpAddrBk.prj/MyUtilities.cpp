// MyUtilities


#include "pch.h"
#include "MyUtilities.h"


MyUtilities utl;


void MyUtilities::display(TCchar* id, RECT& rect) {
String s;

  s.format(_T("%s (%i,%i,%i,%i) (%i,%i)"), id, rect.left, rect.top, rect.right, rect.bottom,
                                                   rect.right - rect.left, rect.bottom - rect.top);
  messageBox(s);
  }


void MyUtilities::addBackSlash(String& path) {
int pos = path.length()-1;   if (pos < 0) return;

  if (path[pos] != _T('\\')) path += _T('\\');
  }


