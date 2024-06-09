

OpAddrBk.chm : *.htm OpAddrBk.hhp OpAddrBk.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" OpAddrBk


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F OpAddrBk.chm


Release/OpAddrBk.chm : OpAddrBk.chm
  copy $(MAKEDIR)\OpAddrBk.chm  $(MAKEDIR)\..\Release\OpAddrBk.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del OpAddrBk.chm
  cd $(MAKEDIR)


Debug/OpAddrBk.chm : OpAddrBk.chm
  copy $(MAKEDIR)\OpAddrBk.chm  $(MAKEDIR)\..\Debug\OpAddrBk.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del OpAddrBk.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/OpAddrBk.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/OpAddrBk.chm


