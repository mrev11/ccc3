
1. Minimum GTK 2.8.x fejlesztő környezet kell.
   A GTK gyorsan változik, régebbi kiadásokból hiányoznak
   olyan API-k, amiket itt használunk.
   SuSE 9.0-ban levő GTK túl régi.
   SuSE 10.0-ban levő GTK megfelel.
   Ubuntu Breezy-ben levő GTK megfelel.
   Ubuntu Dapper-ben levő GTK megfelel.

2. Bemegyünk gtk/codegen-be,
   elindítjuk az m scriptet,
   lefordulnak a kódgeneráló programok.   

3. Még mindig gtk/codegen-ben
   elindítjuk az s scriptet,
   létrejön a gtk/code_generated directory,
   és abban kb. 1MB generált cpp és prg kód.

4. Átmegyünk a gtk/code_byhand directoryba,
   itt megtaláljuk a gtk-suse10.bld, gtk-breezy.bld, stb. filéket.
   Ezek az én gépeimen levő konfigurációt tükrözik.
   Meg kell írni ezek helyett a saját konfigurációnkhoz
   passzoló bld filét (azaz meg kell keresnünk, hogy hol
   vannak az include filék és a könyvtárak).
   Az aktualizált bld filé nevét be kell írni az m scriptbe.

5. Elindítjuk az előbb előkészített m scriptet,
   lefordul és installálódik a ccc3_gtk.so könyvtár.
   Itt kezdetben hibák adódhatnak, aminek valószínű oka, 
   hogy a bld-ben rosszul adtuk meg az include és lib directorykat.
   Később (amikor már csak CCC szinten dolgozunk) nincs szükség 
   a GTK környezet megadására, mert csak a ccc3_gtk.so-t kell 
   linkelni a CCC környezetből.

6. Kipróbáljuk a példaprogramokat.
