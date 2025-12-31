// Interface to Help Files


#include "pch.h"
#include "Help.h"


Help help;

void Help::overview(HWND hwnd)        {htmlHelp(hwnd, _T(">Introduction"));}
void Help::createMaster(HWND hwnd)    {htmlHelp(hwnd, _T(">CreateMaster"));}
void Help::oneMaster(HWND hwnd)       {htmlHelp(hwnd, _T(">OneMaster"));}
void Help::deleteMaster(HWND hwnd)    {htmlHelp(hwnd, _T(">DeleteMaster"));}
void Help::addressBook(HWND hwnd)     {htmlHelp(hwnd, _T(">AddressBook"));}
void Help::selectNewMaster(HWND hwnd) {htmlHelp(hwnd, _T(">SelectProfile"));}
void Help::selectProfile(HWND hwnd)   {htmlHelp(hwnd, _T(">TwoPlusMaster"));}


void Help::htmlHelp(HWND hwnd, TCchar* topic)
                                 {String s = path + topic;  HtmlHelp(hwnd, s,  HH_DISPLAY_TOC, 0);}



