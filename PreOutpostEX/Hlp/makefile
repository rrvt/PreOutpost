

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


Debug/PreOutpost.chm : PreOutpost.chm
  copy $(MAKEDIR)\PreOutpost.chm  $(MAKEDIR)\..\Debug\PreOutpost.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del PreOutpost.chm
  cd $(MAKEDIR)


ReleaseUni7/Rebuild.rbd : ReleaseUni7/Clean.cln ReleaseUni7/PreOutpost.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/PreOutpost.chm


