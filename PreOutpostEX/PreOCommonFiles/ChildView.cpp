
// ChildView.cpp : implementation of the ChildView class
//

#include "stdafx.h"
#include "PreOutpost.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ChildView

ChildView::ChildView()
{
}

ChildView::~ChildView()
{
}


BEGIN_MESSAGE_MAP(ChildView, CWnd)
  ON_WM_PAINT()
  ON_COMMAND(ID_FILE_DIALOGBAR, &ChildView::OnSelectMasterProfile)
END_MESSAGE_MAP()



// ChildView message handlers

BOOL ChildView::PreCreateWindow(CREATESTRUCT& cs) {

  if (!CWnd::PreCreateWindow(cs)) return FALSE;

  cs.dwExStyle |= WS_EX_CLIENTEDGE;
  cs.style &= ~WS_BORDER;
  cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
    ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

  return TRUE;
  }


void ChildView::OnPaint() {
  CPaintDC dc(this); // device context for painting

  // TODO: Add your message handler code here

  // Do not call CWnd::OnPaint() for painting messages
  }



void ChildView::OnSelectMasterProfile() {
  // TODO: Add your command handler code here
  }
