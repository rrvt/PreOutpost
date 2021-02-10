// Usr File Management
//$(LibraryPath)\; $(ProgramFiles)\Microsoft SDKs\Windows\v7.1A\Lib\

#include "stdafx.h"
#include "UsrData.h"
#include "filename.h"


static const String Section = _T("USER DEFINITION");
static const String Version = _T("Version");
static const String Call    = _T("MyCall");
static const String Name    = _T("MyName");
static const String ID      = _T("UserID");
static const String SigFlag = _T("SigFlag");
static const String SigData = _T("SigData");

static const String VerVal  = _T("3.2.118/18232:113207");


void UsrData::initialize(String& profilePath) {
usrPath = profilePath;

  usrPath += _T("usr.d\\");
  }


bool UsrData::find(String& callSign) {
String    path = usrPath + callSign; path += _T("."); path += extension;
CFileFind ff;

  if (!ff.FindFile(path)) return false;

  load(callSign); return true;
  }



void UsrData::load(String& call) {
String path = usrPath + call;   path += _T(".");   path += extension;

  usrPPF.setPath(path);
  usrPPF.readString(Section, Version, version);
  usrPPF.readString(Section, Call,    callSign);
  usrPPF.readString(Section, Name,    name);
  usrPPF.readString(Section, ID,      userID);
  usrPPF.readString(Section, SigData, signature);
  sigFlag = !signature.empty();
  }


void UsrData::store(String& call) {
String path = usrPath + call;   path += _T(".");   path += extension;

  if (version.empty()) version = VerVal;

  usrPPF.setPath(path);
  usrPPF.writeString(Section, Version, version);
  usrPPF.writeString(Section, Call,    callSign);
  usrPPF.writeString(Section, Name,    name);
  usrPPF.writeString(Section, ID,      userID);
  usrPPF.writeInt(   Section, SigFlag, signature.empty() ? false : true);
  usrPPF.writeString(Section, SigData, signature);
  }



