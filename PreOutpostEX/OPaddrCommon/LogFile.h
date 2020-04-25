// Log File Operations


#pragma once
#include "FileIO.h"
#include "Addresses.h"




class LogFile {
enum Code      {Nil, Modm, Jnos, SC, SP, Virt, VLoc, Form, EndForm, MsgNo, Bye, Rcv, From, FromV, FLocV};
enum State     {Modem, JNOS};
enum Direction {RcvDir, SndDir};

CTime     curTime;
String    path;
String    target;
String    name;
FileIO    fileIO;

String    line;
Code      code;
State     state;

Direction direction;
bool      isForm;
Addr      addr;

public:
  LogFile();
 ~LogFile() {}

  bool open();
  void close() {fileIO.close();}

  void process();

private:

  bool find();
  Code getCode();
  void processModem();
  void processJNOS();
  bool getData(String& s);
  bool getData(String& s, int pos);
  };