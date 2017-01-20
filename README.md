
# CCC is 20 years old

_M. Vermes_

September, 2016


  
According to changelists CCC is 20 years old: It is descended from Clipper, it
translates the source code into C and a stack machine implemented in C. It is
a program language and developing tool independent of platforms.

  * The name means "Clipper to C++ Compiler". 

  * Name spaces, threads, exceptions, objects, unicode ... 

  * XMLRPC, SQL inteface, GTK (Glade) interface, Java terminal ... 

  * Critical banking applications work with it. 

  * It can be downloaded in source code under LGPL. 

CCC extends the old Clipper. It is modern, it bears
comparison with languages like Python, Ruby, Pike. The atmospheres of CCC and
Python are especially similar, both are _practical_, concise, nevertheless
easy to read, they avoid the pedantry characteristic of Java.

I am accustomed to getting messages like these in forums: "Why to deal with
Clipper in the age of .NET?", "A time machine is also necessary for it.",
"What is a language itself good for without a class library?". First, there are
a few things in CCC. Second, it can be easier extended by inserts C, than the
languages mentioned above.

It is not recommended to extend Java by C. Portability gets lost, it is too
complicated, and an avarage programmer is not proficient in it. The situation
with Python is similar. The extensions necessary for the _application_ should
be carried out by modifications of the runtime environment or the interpreter. 
A class library including the whole universe of informatics is really essential
in these languages.

Whereas CCC (with translation into C) produces native binaries, that's why we
can submerge into C any time. The C moduls are translated automatically
together with Clipper. This way the class libraries have less importance,
because the infrastructure accesible from C is always available. This is the
philosophy of CCC.

[Linux Install](doc/install-linux.md)    
[Windows Install](doc/install-windows.md)    



These documents may be interesting for Hungarian readers:

[CCC belülről](doc/ccc-belulrol.md)    
[Programkészítés a Build-del](ccctools/buildp/build.md)    
[SQL2 1.1 interfész](tools/sql2/sql2.md)    
[CCC-GTK csatoló](gtk/cccgtk.md)    













<!-----------------------------------------------------------------
(it is annoying, that do not exist a common solution for Gollum and GitHub):
Links in Gollum (do not work in GitHub):    
[CCC belülről](doc/ccc-belulrol)    
[Programkészítés a Build-del](ccctools/buildp/build)    
[SQL2 1.1 interfész](tools/sql2/sql2)    
[CCC-GTK csatoló](gtk/cccgtk)    


WikiLink Syntax (do not work in GitHub):  
[[CCC belülről|doc/ccc-belulrol]]    
[[Programkészítés a Build-del|ccctools/buildp/build]]    
[[SQL2 1.1 interfész|tools/sql2/sql2]]    
[[CCC-GTK csatoló|gtk/cccgtk]]    

Links in GitHub (do not work in Gollum):    
------------------------------------------------------------------->
