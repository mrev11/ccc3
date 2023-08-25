#!/bin/bash
#set -x
echo TDC2OBJ.BAT $1 $2 

#rm -f error 
rm -f error--tdc2prg-$1
rm -f error--outpre-$1
rm -f error--ppo2cpp-$1
rm -f error--outcpp-$1
mkdir -p ppo

rm -f ppo/$1.prg
cp -f $2/$1.tdc ppo/$1.tmp-prg
tdc2prgch.exe --prg  ppo/$1.tmp-prg 2>ppo/tdc2prg-$1

if ! test -f ppo/$1.prg; then
    touch error
    mv ppo/tdc2prg-$1 error--tdc2prg-$1 
    cat error--tdc2prg-$1
    echo 'tdc2prg' $1 FAILED
else

rm -f ppo/$1.tmp-prg
rm -f ppo/tdc2prg-$1



# innen kezdve ugyanaz, mint prg2obj
# kiveve hogy a prg-t a ppo-bol veszi

CMPOPT=ppo/prg2ppo-$1
rm -f $CMPOPT

echo $BUILD_PRE >>$CMPOPT
for i in $BUILD_INC; do echo -I$i >>$CMPOPT; done
 
echo -dARROW            >>$CMPOPT
echo -d_CCC_            >>$CMPOPT
echo -d_CCC"$CCCVER"_   >>$CMPOPT
echo -d_UNIX_           >>$CMPOPT 
echo -d_FREEBSD_        >>$CMPOPT 
echo -ustd1.ch          >>$CMPOPT


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
 
    if ! ppo2cpp.exe -q $1.ppo 2>>ppo2cpp-$1; then
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

