A ccctools directoryban azok a programok vannak,
amik a rendszer fordításához, telepítéséhez kellenek:

build:
   Vezérli a fordítást, projekt generátor és make egyben.
   
ccomp:
   MinGW utilityket indít el @parfile-ből vett paraméterekkel.

mklink:
   Az exe filékhez csinál egy exe nélküli symlinket,
   így UNIX-on is elég a kiterjesztés nélküli nevet gépelni.

pack:
   Minden forrásba beírja a licencet,
   összepakkolja a bináris csomagot (zip),
   a csomagnevet kiegészíti a dátummal. 

ppo2cpp:
   Clipper (ppo) --> C++ (cpp) fordító.

prg2ppo:
   A Clipper preprocesszor CCC-s változata.
   
removecr:
   Leszedi a sorok végéről a CR-et. 
   A flex nem működik CR-eket tartalmazó filékkel.   
 