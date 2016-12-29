
//készítette : Csiszár Levente
//javítás    : Vermes 1998.09.09

#include "scrstr.ch"

// Olyan rutinok, amikkel úgy írhatunk egy stringbe,
// mintha egy lap méretű képernyőre írnánk.
// Először a createScr()-el el kell készíteni a lapot,
// az scrOutPict()-el lehet írni, az scrPos()-al lehet a lapon
// mozogni. A lapot leíró stringet az scrStr()-el lehet megkapni.

// Megj: Az scrStr csak azokat a sorokat adja, amikbe írtunk.


*************************************************************************
// Csak egy lapot tud felírni!
*************************************************************************
#define SCR_NROW    1   //lap magassága
#define SCR_NCOL    2   //lap szélessége
#define SCR_ROW     3   //aktuláis sor
#define SCR_COL     4   //aktuális oszlop
#define SCR_STRT    5   //sorok tömbje 1-től az utolsó nemüresig

*************************************************************************
function createScr(nrow,ncol)
    return {nrow,ncol,0,0,{}}

*************************************************************************
function scrStr(scr,mogeNe)

// Azokat a sorokat adja, amikbe és amilyen hosszan írtunk.
// Ha a mogeNe igaz, akkor az utolsó sor után nem rak CR_LF-et.

local str:="",i,t:=scr[SCR_STRT]

    for i:=1 to len(t)-1
        str+=t[i]+CR_LF
    next

    if( len(t)>0 )
        str+=t[len(t)]
        if !(mogeNe==.t.)
            str+=CR_LF
        end
    end
    return str

*************************************************************************
function scrStrt(scr)

// Egy tömböt ad, ami azokat a sorokat tartalmazza, amikbe írtunk.

    return scr[SCR_STRT]

*************************************************************************
function scrApp(scr1,scr2)

// Az scr2-t az scr1 végéhez fűzi.
// Az aktuális pozíció nem változik.
// Ha kilóg valahol, levágja.

local t1,t2,nRow,nCol,n,i,w

    t1:=scr1[SCR_STRT]
    t2:=scr2[SCR_STRT]
    nRow:=scr1[SCR_NROW]
    nCol:=scr1[SCR_NCOL]
    
    n:=min(len(t2),nRow-len(t1)) //ennyit adunk hozzá, Vermes 98.09.09

    for i:=1 to n
        w:=t2[i]
        if( len(w)>nCol )
            w:=left(w,nCol)
        end
        aadd(t1,w)
    next

    return scr1

*************************************************************************
function scrPos(scr,row,col)

// Pozícionál az scr-en.

    scr[SCR_ROW]:=row
    scr[SCR_COL]:=col
    return scr

*************************************************************************
function scrOutPict(scr,str,pict)

// Az aktuális pozícióra beírja az str-t. 
// Ha a pict meg van adva, akkor megformáza. 
// Az aktuális pozíciót mozgatja.

local i,l,isCR_LF

    if (pict!=NIL)
        str:=transform(str,pict)
    end

    while(len(str)!=0)
        i:=at(CR_LF,str)
        if (i==0)
            i:=len(str)
            isCR_LF:=.f.
            l:=str
            str:=""
        else
            isCR_LF:=.t.
            l:=substr(str,1,i)
            str:=substr(str,i+3)
        end

        if (scr[SCR_ROW]>=scr[SCR_NROW])
            return scr
        end
   
        scr[SCR_STRT]:=xakieg(scr[SCR_STRT],scr[SCR_ROW]+1,"")

        scr[SCR_STRT][scr[SCR_ROW]+1]:=;
                    xreplStr( scr[SCR_STRT][scr[SCR_ROW]+1],;
                                    scr[SCR_COL]+1, l, scr[SCR_NCOL] )

        if (isCR_LF)
            scr[SCR_ROW]++
        end
    end
    return scr

*************************************************************************
static function xaKieg(tomb,size,def)

// Ha a tomb kisebb, akkor kiegészíti a size-re, 
// ha nagyobb vagy egyenlő, akkor nem csinál semmit.
// A kiegészitett elemek a def-et kapják értékül.

local l

    if(len(tomb)<size )
        l:=len(tomb)
        asize(tomb,size)
        for l:=l+1 to size
            tomb[l]:=def
        next
    end
    return tomb

*************************************************************************
static function xreplStr(str,pos,mivel,maxlen)

// Az str pos pozíciójára beírja a mivel-t, felülírással.
// Ha a string hosszabb lenne, mint a maxlen, akkor a végét levágja.
// A pos számolása 1-től indul.

    if( pos>maxlen )
        return str
    end

    if( pos+len(mivel)-1>maxlen )
        mivel:=left(mivel,maxlen+1-pos)
    end
    str:=padr(substr(str,1,pos-1),pos-1)+mivel+substr(str,pos+len(mivel))
    return str

*************************************************************************
static function toStr(val)

// A val-t stringgé alakítja

local type:=valType(val)

    if (type=="N")
        return allTrim(str(val))
    elseif (type=="D")
        return dtoc(val)
    elseif (type=="L")
        return if(val,"T","F")
    elseif (type=="C" .or. type=="M")
        return val
    elseif (val==NIL)
        return "NIL"
    end
    alert("toStr: Nem konvertálható típus: '"+type+"'")
    return ""

*************************************************************************
function xtrpadr(str,pict,len)

    if !(pict==NIL .or. valtype(pict)=="N")
        str:=transform(str,pict)
    end
    return padr(str,len)

*************************************************************************
function xtrpadl(str,pict,len)

    if !(pict==NIL .or. valtype(pict)=="N")
        str:=transform(str,pict)
    end
    return padl(str,len)

*************************************************************************
function xtrpadc(str,pict,len)

    if !(pict==NIL .or. valtype(pict)=="N")
        str:=transform(str,pict)
    end
    return padc(str,len)

*************************************************************************
