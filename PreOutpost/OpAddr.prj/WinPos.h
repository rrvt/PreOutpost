// Manage Window Position and Size


#pragma once
#include "PosSizeData.h"


class WinPos {

CWnd*       wnd;                                // App window
PosSizeData posSz;                              // App window position and size

int         maxWidth;                           // Maximum Screen width and height
int         maxHeight;

public:

  WinPos();
 ~WinPos() {save();}

  void onInit(CWnd* w) {wnd = w;}  // Call with "this" from end of MainFrame::OnCreate or OnInitDialog

  void setDefaultSize(int width, int depth) {posSz.width = width; posSz.depth = depth;}

  void set();               // initialize the window to the saved position and size, only call once

  void getRect(CRect& rect);// Call from ManFrame::OnMove and OnSize or CDialogEx::OnMove or OnSize to
                            // respond to messages:
                            //   ON_WM_SIZE()
private:                    //   ON_WM_MOVE()

  bool getWindow() {if (!wnd) wnd = AfxGetApp()->m_pMainWnd;  return wnd != 0;}

  void save() {posSz.save();}                     // Save the current position and size when app closes.
  };

