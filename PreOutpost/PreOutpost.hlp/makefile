

PreOutpost.chm : *.html PreOutpost.hhp PreOutpost.hhc PreOutpost.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" PreOutpost


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist PreOutpost.chm del /F PreOutpost.chm


Release/PreOutpost.chm : PreOutpost.chm
  copy $(MAKEDIR)\PreOutpost.chm  $(MAKEDIR)\..\Release\PreOutpost.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist PreOutpost.chm del /F PreOutpost.chm
  cd $(MAKEDIR)


Debug/PreOutpost.chm : PreOutpost.chm
  copy $(MAKEDIR)\PreOutpost.chm  $(MAKEDIR)\..\Debug\PreOutpost.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist PreOutpost.chm del /F PreOutpost.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/PreOutpost.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/PreOutpost.chm


