// Create New Masters


#pragma once


class NewMaster {

public:

  NewMaster() { }

  void operator() ();

private:

  void selectNew();
  void deleteMaster(String& selected);
  };

