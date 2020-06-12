// Replaces CArchive to allow for Unicode internally and ansi in external files
// Copyright Bob -- K6RWY, 2019


#pragma once
#include "FileIO.h"
#include "ManipT.h"

class CDoc;

class Archive;

typedef ManipT<Archive> ArchManip;



class Archive {

bool   opened;
bool   storing;
FileIO fil;

public:

  Archive(String& fileName, FileIO::OpenParms mode) : opened(false), storing(false) {
    opened = fil.open(fileName, mode); storing = mode & (FileIO::Create | FileIO::Write);
    initialize();
    }

 ~Archive()                              {fil.close();}

  bool     isStoring()                   {return storing;}
  bool     isLoading()                   {return !storing;}

  bool     isOpen()                      {return opened;}

  bool     write(String&       s)        {return fil.write(s);}             // interprets \n or \r
  bool     write(TCchar*      ts)        {return fil.write(ts);}
  bool     write(Tchar        ch)        {return fil.write(ch);}

  bool     write(int           x)        {return write(&x, sizeof(x));}     // no interpretation of \n or
                                                                            // \r
  bool     write(const void* blk, int n) {return fil.write((void*) blk, n);}
  bool     write(Byte          v)        {return fil.write(v);}

  void     setTabSize(int nSpaces)       {fil.setTabSize(nSpaces);}        // Set tab size for output
  void     tab(       int nTabs)         {fil.tab(nTabs);}
  void     spaces(    int nSpaces)       {fil.spaces(nSpaces);}
  void     crlf()                        {fil.crlf();}

  Archive& operator<< (String&    s)     {write(s);  return *this;}
  Archive& operator<< (TCchar*    p)     {write(p);  return *this;}
  Archive& operator<< (Tchar     ch)     {write(ch); return *this;}
  Archive& operator<< (int        x)     {write(x);  return *this;}
  Archive& operator<< (ArchManip& m)     {return m.func(*this);}

  bool     read(String&        s)        {return fil.read(s);}             // Interpretation of \n or \r
  bool     read(String& s, int n)        {return fil.read(s, n);}          // Read n chars into a string
  bool     read(Tchar&        ch)        {return fil.read(ch);}

  bool     read(int&           x)        {return read(&x, sizeof(x));}     // No interpretation of \n or
  bool     read(void* blk, int n)        {return fil.read(blk, n);}        // \r
  bool     read(Byte&          v)        {return fil.read(v);}

  Tchar*   getLastError()                {return fil.getLastError();}      // Returns last error

private:

  void initialize();
  static Archive& doCrlf(Archive& n) {n.crlf(); return n;}
  };


extern ArchManip aCrlf;       // add to stream to terminate a line on display: ar << "xyz" << nCrlf;

