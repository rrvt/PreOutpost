// Window Data
// Copyright Software Design & Engineering, Robert R. Van Tuyl, 2013.  All rights reserved.


#pragma once


struct PosSizeData {
int left;
int top;
int width;
int depth;

  PosSizeData() : left(0), top(0), width(0), depth(0) { }
 ~PosSizeData() { }

  PosSizeData& operator= (RECT& r)
           {left = r.left; top = r.top; width = r.right - r.left; depth = r.bottom - r.top; return *this;}

  void  toRect(RECT& r) {r.left = left; r.top = top; r.right = left + width; r.bottom = top + depth;}

  void load();

  void save();

  void normalize(int maxWidth, int maxDepth);
  };

