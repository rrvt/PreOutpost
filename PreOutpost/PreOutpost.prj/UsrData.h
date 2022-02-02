// Usr File Management


#pragma once
#include "IniFile.h"



struct UsrData {
String  version;
String  callSign;
String  name;
String  userID;
String  sigFlag;
String  signature;

IniFile usrPPF;                                   // Private Profile File
String  usrPath;
String  extension;

  UsrData(Tchar* ext) {extension = ext;};

  void initialize(String& profilePath);
  bool find(String& callSign);
  void load(String& callSign);
  void store(String& callSign);
private:
  UsrData() {}                                    // prevent null extension
  };

