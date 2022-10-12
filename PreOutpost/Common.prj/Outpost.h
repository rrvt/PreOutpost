// Outpost Data


#pragma once


class Outpost {

String exePath;                             // Full path to Outpost executable including file name
String dataPath;                            // Path to directory where Outpost stores its profiles

public:

         Outpost() { }
        ~Outpost() { }

  void   initialize(TCchar* path, TCchar* profile);
  void   getProfilePath();                                // Little function to find profile and path

  String getPath()    {return exePath;}
  String getProfile() {return dataPath;}
  void   choose();

  void   saveOutpostPath(String& path, String& profile);

private:

  void   setOutpost(TCchar* path);
  void   setProfile(TCchar* path);
  };


extern Outpost outpost;

