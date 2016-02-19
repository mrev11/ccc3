#!/bin/bash
echo TDS2OBJ.BAT $1 $2 

#rm -f error 
rm -f error--tds2prg-$1
rm -f error--outpre-$1
rm -f error--ppo2cpp-$1
rm -f error--outcpp-$1
mkdir -p ppo
 
rm -f ppo/$1.prg
cp -f $2/$1.tds ppo/$1.tmp
tds2prg.exe   ppo/$1.tmp  >ppo/tds2prg-$1
rm ppo/$1.tmp
if ! test -f ppo/$1.prg; then
    touch error
    mv ppo/tds2prg-$1 error--tds2prg-$1
    cat ppo/$1.prg.tmp >>error--tds2prg-$1  2>/dev/null
    echo 'tds2prg' $1 FAILED
    grep '^description:' error--tds2prg-$1
else
rm -f ppo/tds2prg-$1

# innen kezdve ugyanaz, mint prg2ppo
# kiveve hogy a prg-t a ppo-bol veszi

CMPOPT=ppo/prg2ppo-$1
rm -f $CMPOPT

echo $BUILD_PRE >>$CMPOPT
for i in $BUILD_INC; do echo -I$i >>$CMPOPT; done
 
echo -dARROW     >>$CMPOPT
echo -d_CCC_     >>$CMPOPT
echo -d_CCC3_    >>$CMPOPT
echo -d_UNIX_    >>$CMPOPT 
echo -d_LINUX_   >>$CMPOPT 
echo -ustd1.ch   >>$CMPOPT


#(1) Elofeldolgozas (prg-->ppo)

PRG2PPO_EXE=prg2ppo.exe

if ! $PRG2PPO_EXE ppo/$1.prg -oppo/$1.ppo @$CMPOPT >outpre-$1; then
#if ! $PRG2PPO_EXE $2/$1.prg -oppo/$1.ppo @$CMPOPT >outpre-$1; then
    touch error;
    cat outpre-$1;
    echo
    mv  outpre-$1  error--outpre-$1;

else
    rm outpre-$1;

    #(2) CCC forditas (ppo-->cpp)

    pushd ppo >/dev/null
    rm -f $1.cpp
    echo $2/$1.prg >ppo2cpp-$1
 
    if ! ppo2cpp.exe $1.ppo 2>>ppo2cpp-$1; then
        popd >/dev/null;
        touch error;
        cat ppo/ppo2cpp-$1;
        mv  ppo/ppo2cpp-$1 error--ppo2cpp-$1;

    else
        popd >/dev/null;
        rm -f ppo/ppo2cpp-$1;

        #(3) C++ forditas (cpp-->obj)
        $BUILD_BAT/_compile.b $1 ppo;
    fi;
fi;
fi;

echo ----------------------------------------------------------------


 