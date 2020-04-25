// Search for Profile Path on the C drive
// First look for "Program*" directories
// Then look for "*Packet*" directory
// Then look for *Outpost* files

#pragma once


bool findProfilePaths(String& profilePath, String& outpostPath);  // Returns true if profile path is found

