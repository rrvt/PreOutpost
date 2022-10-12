// Manipulate and exe process


#pragma once


class Executable {

//STARTUPINFO&        startupInfo;
PROCESS_INFORMATION procInfo;

public:

          Executable() { }
         ~Executable() { }

  String& addQuotes(String& s);       // Adds quotes if needed avoiding terminal backslash with a space

  bool    start(TCchar* cmd, TCchar* args);     // Each argument must be enclosed in double quotes,
                                                // it is optional to enclose cmd in double quotes
  void    wait(DWORD timeout = INFINITE);
  bool    stop();

private:

  WCHAR*  copy(TCchar* src, WCHAR* vector, int nChars);
//  Executable() : startupInfo(*(STARTUPINFO*)0) { }//
  };

