// Log File Operations


#pragma once
#include "FileIO.h"


class LogFile {


enum Code {Nil, Modm, Jnos, SP, SC, SndAct, SndLstAct, EX,
           Form, PIFO,

           Rcv, To, ToVaddr, ToVloc, ToVaddr3, ToVloc3,
           From, FVaddr, FVloc, FVaddr3, FVloc3,

           Subject, EndRcv,

           MsgNo, EndForm, Bye};

enum State     {ModemSt, JNOSSt, ReceiveSt, TransmitSt, RawSt, Not213St, ICS213St};

State     state;
String    line;
Code      code;

String    to;
String    from;
String    subject;
String    virtAddr;
String    virtLoc;

int       rcvCnt;
CTime     curTime;
FileIO    fileIO;

public:

  LogFile();
 ~LogFile() {}

  bool open();
  void close() {fileIO.close();}

  void process();

private:

  void clear();

  bool find(String& name);
  Code getCode();

  void doJNOS();
  void doReceive();
  void doTransmit();
  void doRawMsg();
  void doNot213();
  void doICS213();

  void install();

  String get();
  String getBrktd();
  void   sanitize(String& name);
  };