

OpAddrBk.chm : *.htm OpAddrBk.hhp OpAddrBk.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" OpAddrBk


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist OpAddrBk.chm del /F OpAddrBk.chm


$(TgtFolder)/OpAddrBk.chm : OpAddrBk.chm
  copy $(MAKEDIR)\OpAddrBk.chm  $(MAKEDIR)\..\$(TgtFolder)\OpAddrBk.chm


$(TgtFolder)/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist OpAddrBk.chm del /F OpAddrBk.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/OpAddrBk.chm



