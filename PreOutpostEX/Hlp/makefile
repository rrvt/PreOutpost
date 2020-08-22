

PreOutpost.chm : *.html PreOutpost.hhp PreOutpost.hhc PreOutpost.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" PreOutpost


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F PreOutpost.chm


ReleaseUni7/PreOutpost.chm : PreOutpost.chm
  copy $(MAKEDIR)\PreOutpost.chm  $(MAKEDIR)\..\ReleaseUni7\PreOutpost.chm


ReleaseUni7/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\ReleaseUni7
  del PreOutpost.chm
  cd $(MAKEDIR)


DebugUni7/PreOutpost.chm : PreOutpost.chm
  copy $(MAKEDIR)\PreOutpost.chm  $(MAKEDIR)\..\DebugUni7\PreOutpost.chm


DebugUni7/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\DebugUni7
  del PreOutpost.chm
  cd $(MAKEDIR)


ReleaseUni7/Rebuild.rbd : ReleaseUni7/Clean.cln ReleaseUni7/PreOutpost.chm


DebugUni7/Rebuild.rbd   : DebugUni7/Clean.cln DebugUni7/PreOutpost.chm


