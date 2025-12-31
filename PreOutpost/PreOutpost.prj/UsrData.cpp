// Usr File Management
//$(LibraryPath)\; $(ProgramFiles)\Microsoft SDKs\Windows\v7.1A\Lib\

#include "pch.h"
#include "UsrData.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "IniFileEx.h"
#include "Outpost.h"
#include "PathDlgDsc.h"


/*
[USER DEFINITION]
VersionKey=3.8.10/25355:181445
MyCall=K6RWY
MyName=Bob
UserID=RWY
SigFlag=1
SigData=rrvt
SendTxt=rrvt 2
SendCtl=1
[END]
*/


static const String UserDefSect    = _T("USER DEFINITION");
static const String VersionKey     = _T("Version");
static const String MyCallKey      = _T("MyCall");
static const String MyNameKey      = _T("MyName");
static const String UserIDKey      = _T("UserID");
static const String SigFlagKey     = _T("SigFlag");
static const String SigDataKey     = _T("SigData");
static const String SendPSTKey     = _T("SendCTL");
static const String SendSssnTxtKey = _T("SendTxt");

static const String VerVal  = _T("3.8.10/25355:181445");


void UsrData::getUsrVer() {
String     path;   path = usrPath + _T("*");
PathDlgDsc dsc{_T("Get Usr File"), path, _T("usr"), _T("*.usr")};

  if (getOpenDlg(dsc, path)) {
    usrPPF.setPath(path);
    usrPPF.readString(UserDefSect, VersionKey, version);
    iniFile.write(UserDefSect, VersionKey, version);
    }
  }


void UsrData::initialize() {
  usrPath = outpost.getProfile() + _T("usr.d\\");

  iniFile.read(UserDefSect, VersionKey, version);
  }


bool UsrData::find(String& callSign) {
String    path = usrPath + callSign; path += _T("."); path += extension;
CFileFind ff;

  if (!ff.FindFile(path)) return false;

  load(callSign); return true;
  }



void UsrData::load(String& call) {
String path = usrPath + call;   path += _T(".");   path += extension;
String ver;

  usrPPF.setPath(path);
  usrPPF.read(UserDefSect, VersionKey,     ver);
  usrPPF.read(UserDefSect, MyCallKey,      callSign);
  usrPPF.read(UserDefSect, MyNameKey,      name);
  usrPPF.read(UserDefSect, UserIDKey,      userID);
  usrPPF.read(UserDefSect, SigFlagKey,     sigFlag, false);
  usrPPF.read(UserDefSect, SigDataKey,     signature);
  usrPPF.read(UserDefSect, SendPSTKey,     sendPST, false);   // Transmit Post Session Text
  usrPPF.read(UserDefSect, SendSssnTxtKey, postSssnTxt);      // Post Session Text -- Unused by SCC

  if (ver <= version) {usrPPF.write(UserDefSect, VersionKey, version);}
  }


void UsrData::store(String& call) {
String path = usrPath + call;   path += _T(".");   path += extension;

  if (version.empty()) version = VerVal;

  sigFlag = !signature.isEmpty();
  sendPST = !postSssnTxt.isEmpty();

  usrPPF.setPath(path);
  usrPPF.write(UserDefSect, VersionKey,     version);
  usrPPF.write(UserDefSect, MyCallKey,      callSign);
  usrPPF.write(UserDefSect, MyNameKey,      name);
  usrPPF.write(UserDefSect, UserIDKey,      userID);
  usrPPF.write(UserDefSect, SigFlagKey,     sigFlag);
  usrPPF.write(UserDefSect, SigDataKey,     signature);
  usrPPF.write(UserDefSect, SendPSTKey,     sendPST);
  usrPPF.write(UserDefSect, SendSssnTxtKey, postSssnTxt);
  }

