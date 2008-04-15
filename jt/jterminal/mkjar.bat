echo Main-Class: jterminal>manifest
 
jar cvfm jterminal.jar  manifest

jar uvf  jterminal.jar  *.class
jar uvf  jterminal.jar  getutil\*.class
jar uvf  jterminal.jar  images
jar uvf  jterminal.jar  icons\16
jar uvf  jterminal.jar  icons\22
jar uvf  jterminal.jar  icons\32
 
:default keystore: "d:\Documents and Settings\vermes\.keystore"
:jarsigner jterminal.jar vermes1
del manifest
 
copy jterminal.jar %CCCDIR%\usr\bin\%CCCUNAME%
 