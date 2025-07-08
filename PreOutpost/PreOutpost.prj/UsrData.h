// Usr File Management


#pragma once
#include "CfgFile.h"



struct UsrData {
String  version;
String  callSign;
String  name;
String  userID;
String  sigFlag;
String  signature;

CfgFile usrPPF;                                   // Private Profile File
String  usrPath;
String  extension;

  UsrData(TCchar* ext) {extension = ext;};

  void initialize();
  bool find(String& callSign);
  void load(String& callSign);
  void store(String& callSign);

private:

  UsrData() {}                                    // prevent null extension
  };

