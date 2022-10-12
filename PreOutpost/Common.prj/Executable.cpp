// Manipulate and exe process


#include "pch.h"
#include "Executable.h"
#include "MessageBox.h"

#include "FileIO.h"


static BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM targetId);


/*
BOOL CreateProcess(
  LPCSTR                lpApplicationName,
  LPSTR                 lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCSTR                lpCurrentDirectory,
  LPSTARTUPINFOA        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
  );
*/

// D:\Sources\PreOutpost\Debug\OpAddr.exe


bool Executable::start(TCchar* cmd, TCchar* arguments) {
String      s;
WCHAR       warg[1024];
STARTUPINFO info={sizeof(info)};

  s = cmd;     addQuotes(s);

  if (arguments) {s += _T(' ');   s += arguments;}

  if (CreateProcess(0, copy(s, warg, noElements(warg)), 0, 0, true, 0, 0, 0, &info, &procInfo))
                                                                                              return true;
  String err;   getError(GetLastError(), err);    messageBox(err);  return false;
  }


String& Executable::addQuotes(String& s) {
int pos;

  if (s[0] == _T('"')) return s;

  pos = s.length() - 1;

  if (s[pos] == _T('\\')) s = s.substr(0, pos);

  s = _T('"') + s + _T('"');

  return s;
  }


WCHAR* Executable::copy(TCchar* src, WCHAR* vector, int nChars) {
int i;
int n;

  if (!src) return 0;   n = _tcslen(src);   if (n >= nChars) return 0;

  for (i = 0; i < n; i++) vector[i] = *src++;   vector[i] = 0;

  return vector;
  }



void Executable::wait(DWORD timeout) {WaitForSingleObject(procInfo.hProcess, timeout);}


bool Executable::stop() {

  if (EnumWindows(EnumWindowsProcMy, procInfo.dwProcessId)) return true;

  String err;   getError(GetLastError(), err);    messageBox(err);  return false;
  }


// Called for each top-level window on the screen
// Turns out that an executable may have two or more HWNDs active when we wish to stop it.
// Messages only go to windows, so better send it to all windows with the target ID!

BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM targetId) {
DWORD processID;

  GetWindowThreadProcessId(hwnd, &processID);

  if (processID == targetId) SendMessage(hwnd, WM_CLOSE, 0, 0);

  return true;
  }



#if 1
#else
//WCHAR wc[256];
LPWSTR cl      = (LPWSTR) s.str();
String cDir    = curDir;   addQuotes(cDir);
#endif

//  copy(s, wc, noElements(wc));

