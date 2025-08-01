// Several String Classes


// String -- A wrapper of string with conversions to CString, Tchar* and other assorted functions
// rrvt 08/02/16


#include "pch.h"
#include "Strings.h"
#include <iomanip>
#include <sstream>
#include <memory>
#include <random>


Cstring::Cstring(String& s) : CString(s.str()) {}


void Cstring::clear() {try {Empty();   FreeExtra();} catch (...) { }}


// Expunge data, then clear string

void Cstring::expunge() {
static random_device       rd;
mt19937                    gen(rd());
uniform_int_distribution<> distribute(32, 127);
int                        n = length();
int                        i;

  for (i = 0; i < n; i++) Insert(i, (TCchar) distribute(gen));   clear();
  }


int Cstring::stoi( uint& i, int base) {
long   v;
Tchar*  endPtr;
TCchar* p = GetString();

  try {v = _tcstol(p, &endPtr, base);   i = (int) (endPtr-p);}
  catch(...) {v = 0; i = -1;}

  return v;
  }

Cstring& Cstring::operator= (String& s) {CString& cs = *this; cs = s.str(); return *this;}


Cstring& Cstring::operator= (variant_t& v)
               {CString& cs = *this;  if (v.vt == VT_BSTR) cs = (Tchar*) bstr_t(v);  return *this;}


Cstring& Cstring::operator= (int    v)
                                {String s = v;  CString& cs = *this;  cs = s.str();  return *this;}
Cstring& Cstring::operator= (long   v)
                                {String s = v;  CString& cs = *this;  cs = s.str();  return *this;}
Cstring& Cstring::operator= (ulong  v)
                                {String s = v;  CString& cs = *this;  cs = s.str();  return *this;}
Cstring& Cstring::operator= (double v)
                                {String s = v;  CString& cs = *this;  cs = s.str();  return *this;}


void String::expunge() {
static random_device       rd;
mt19937                    gen(rd());
uniform_int_distribution<> distribute(32, 127);
int                        n = length();
int                        i;

  for (i = 0; i < n; i++) (*this)[i] = (TCchar) distribute(gen);   clear();
  }


String& String::trim() {trimLeft(); return trimRight();}


String& String::trimLeft() {
tstring::iterator p;

  if (empty()) return *this;

  for (p = begin(); p < end(); p++) if (*p > ' ') break;

  erase(begin(), p);  return *this;
  }



String& String::trimRight() {
tstring::iterator p;

  if (empty()) return *this;

  for (p = end() - 1; p >= begin(); p--) {
    if (*p > ' ') {p++; break;}
    if (p == begin()) break;
    }

  erase(p, end());   return *this;
  }


String& String::upperCase() {
tstring& s   = *this;
int      lng = size();
int      i;
Tchar    ch;

  for (i = 0; i < lng; i++) {
    ch = s[i];
    if ('a' <= ch && ch <= 'z') s[i] = ch - 'a' + 'A';
    }

  return *this;
  }


String& String::lowerCase() {
tstring& s   = *this;
int      lng = size();
int      i;
Tchar    ch;

  for (i = 0; i < lng; i++) {ch = s[i];   if ('A' <= ch && ch <= 'Z') s[i] = ch - 'A' + 'a';}

  return *this;
  }


String& String::format(TCchar* fmt_str, ...) {
int              n = 64;
int              zeroSz = sizeof(Tchar);
int              noChars;
#ifdef Win2K
auto_ptr<Tchar>   formatted;
#else
unique_ptr<Tchar> formatted;
#endif

  va_list ap;

  loop {

    formatted.reset(new Tchar[n]);            /* Wrap the plain Tchar array into the unique_ptr */

    va_start(ap, fmt_str);
      noChars = _vsntprintf_s(formatted.get(), n, n-1, fmt_str, ap);
    va_end(ap);

    if (noChars >= 0) break;

    n += abs(noChars - n + zeroSz);
    }

  *this = formatted.get(); return *this;
  }



// Conversion to numbers, integer, unsigned long integer and double

int String::stoi(uint& i, int base) {
long   v;
size_t j = i;

  try {
    #ifdef Win2K
      Tchar* endPtr;   v = _tcstol(this->c_str(), &endPtr, base);   i = endPtr-this->c_str();
    #else
      v = ::stoi(*this, &j, base);   i = j;
    #endif
    }
  catch(...) {v = 0; i = -1;} return v;
  }

ulong String::stoul(uint& i, int base) {
ulong v;
size_t j = i;

  try {
    #ifdef Win2K
      Tchar* endPtr;   v = strtoul(this->c_str(), &endPtr, base);   i = endPtr-this->c_str();
    #else
      v = ::stoul(*this, &j, base);   i = j;
    #endif
    }
  catch(...) {v = 0; i = -1;} return v;
  }

double String::stod(uint& i) {
double v;
size_t j = i;

  try {
    #ifdef Win2K
      Tchar* endPtr;   v = strtod(this->c_str(), &endPtr);   i = endPtr-this->c_str();
    #else
      v = ::stod(*this, &j);    i = j;
    #endif
    }
  catch(...) {v = 0; i = -1;}

  return v;
  }



// Returns pos of one of the characters in tc, priority left to right otherwise returns -1

int String::findOneOf(TCchar* tc, int offset) {
int i;
int pos;

  for (i = 0; tc[i]; i++) {pos = find(tc[i], offset);   if (pos >= 0) return pos;}

  return -1;
  }



//%[flags][width][.precision][size]type

String dblToString(double v, int width, int precision) {
String s;

  if      (precision && width) {s.format(_T("%*.*lg"), width, precision, v);   return s;}
  else if (precision)          {s.format(_T("%.*lg"),         precision, v);   return s;}
  else if (             width) {s.format(_T("%*lg"),   width,            v);   return s;}
                                s.format(_T("%lg"),                      v);   return s;
  }


String intToString(  long v, int width, int precision) {
String s;

  if      (precision && width) {s.format(_T("%*.*li"), width, precision, v);   return s;}
  else if (precision)          {s.format(_T("%.*li"),         precision, v);   return s;}
  else if (             width) {s.format(_T("%*li"),   width,            v);   return s;}
                                s.format(_T("%li"),                      v);   return s;
  }




String uintToString(ulong v, int width, int precision) {
String s;

  if      (precision && width) {s.format(_T("%*.*lu"), width, precision, v); return s;}
  else if (precision)          {s.format(_T("%.*lu"),         precision, v); return s;}
  else if (             width) {s.format(_T("%*lu"),   width,            v); return s;}
                                s.format(_T("%lu"),                      v); return s;
  }


String hexToString(ulong  v, int precision) {
String s;

  if (precision)          {s.format(_T("0x%.*lx"),         precision, v); return s;}
                           s.format(_T("0x%lx"),                      v); return s;
  }



// Returns next token in string defined by deliminter chars

bool TokenString::next(String& stg, TCchar* delim) {
int ePos;
  if (pos == string::npos) return false;
  pos  = (int) find_first_not_of(delim, pos);    if (pos == string::npos) return false;
  ePos = (int) find_first_of(delim, pos);
  stg  = substr(pos, ePos == string::npos ? ePos : ePos-pos);   pos  = ePos;
  return true;
  }


void ToAnsi::convert(TCchar* tp) {
NewArray(char);

  cnt = tp ? _tcslen(tp) : 0;    p = AllocArray(cnt+1);

  if (!tp) {*p = 0; return;}

  #ifdef _UNICODE

    if (WideCharToMultiByte(CP_ACP, 0, tp, cnt, (LPSTR) p, cnt+1, 0, 0)) {p[cnt] = 0; return;}

  #else

    _tcscpy_s(p, cnt, tp); return;

  #endif
  }


ToAnsi::~ToAnsi() {if (p) {NewArray(char); FreeArray(p);}}


void ToUniCode::convert(Cchar* tp) {

  cnt = tp ? strlen(tp) : 0;    p = new Tchar[cnt+1];

  if (!tp) {*p = 0; return;}

  #ifdef _UNICODE
  int i;

    for (i = 0; i < cnt; i++) p[i] = tp[i] & 0xff;   p[i] = 0;   return;

  #else

    strcpy_s(p, cnt, tp); return;

  #endif
  }


ToUniCode::~ToUniCode() {if (p) {delete [] p;}}


