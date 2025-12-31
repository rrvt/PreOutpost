// Interface to Help Files


#pragma once


class Help {

String path;

public:

  Help() { }
 ~Help() { }

  void init(TCchar* pth) {path = pth;}

  void overview(HWND hwnd);
  void createMaster(HWND hwnd);
  void oneMaster(HWND hwnd);
  void deleteMaster(HWND hwnd);
  void addressBook(HWND hwnd);
  void selectNewMaster(HWND hwnd);
  void selectProfile(HWND hwnd);

private:

  void htmlHelp(HWND hwnd, TCchar* topic);
  };

extern Help help;



