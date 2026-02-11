

PreOutpost.chm : *.html PreOutpost.hhp PreOutpost.hhc PreOutpost.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" PreOutpost


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist PreOutpost.chm del /F PreOutpost.chm


$(TgtFolder)/PreOutpost.chm : PreOutpost.chm
  copy $(MAKEDIR)\PreOutpost.chm  $(MAKEDIR)\..\$(TgtFolder)\PreOutpost.chm


$(TgtFolder)/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist PreOutpost.chm del /F PreOutpost.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/PreOutpost.chm



