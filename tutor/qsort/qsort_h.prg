
// Hoare-fele particionalas


#include "qsort.ch"


****************************************************************************
function qsort_h(*)
    ?? "qsort_h"::padr(16)
    qsort(*)


****************************************************************************
static function qsort(a,p:=1,r:=len(a),blk)

// a    : array to sort
// p    : start index
// r    : final index
// blk  : compare block

local q

    while( p+ISORT_TRESHOLD<r )
        q:=qsplit(a,p,r,blk)
        if( q-p<r-q)
            qsort(a,p,q,blk)
            p:=q+1
        else
            qsort(a,q+1,r,blk)
            r:=q
        end
    end

    if( p<r )
        isort(a,p,r,blk)
    end


****************************************************************************
static function qsplit(a,p,r,blk) // Hoare-fele particionalas

local i:=p-1
local j:=r+1
local pivot:=pivot(a,p,r-1,blk) // utolso kihagyva!

    while( .t. )
        while( 0>compare(a[++i],pivot,blk) ); end
        while( 0<compare(a[--j],pivot,blk) ); end

        if( i>=j )
            return j
        end
        swap(a,i,j)
    next

// Mire kell figyelni, hogy ne essen vegtelen ciklusba?
//
// Akkor esik vegtelen ciklusba, ha a felosztassal kapott reszek
// nagyobbikanak hossza nem kisebb, mint az eredeti array hossza.
// Ketfele veszelyes helyzetet kell nezni:
//
//   1) j index p-ig csokken (p-1-ig nem tud)
//   2) i index r-ig novekszik
//
// Az 1-es eset jo, mert a rekurzio {p,p} es {p+1,r} szakaszokkal
// folytatodik. Az elso szakasz 1 elemu (rendezett), a masodik
// szakasz pedig rovidebb, mint a teljes array.
//
// A 2-es eset veszelyes. Ha a pivot a jobb szelso elem, es minden
// mas elem kisebb a pivotnal, akkor i es j egyarant a pivot elemen
// akad meg, azaz i==j==r-et kapunk, es {p,r} es {r+1,r} szakaszokkal
// folytatodna a (vegtelen) rekurzio.  Ha azonban a jobb szelso
// (utolso) elemet kihagyjuk a pivot keresesbol, akkor belathato,
// hogy a j index az r-rol legalabb meg egyet lep.


****************************************************************************
