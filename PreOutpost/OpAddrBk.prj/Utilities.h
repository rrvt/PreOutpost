// Utilities


#pragma once
#include "MessageBox.h"


class Utilities {

public:

  void display(TCchar* id, RECT& rect);

  void addBackSlash(String& path);
  };


extern Utilities utl;
