#!/bin/bash
echo PRG2OBJ.BAT $1 $2 
 
rm error 2>/dev/null
mkdir ppo 2>/dev/null

#(1) Preprocesszor (prg-->ppo)
CMPOPT=ppo/prg2ppo
rm $CMPOPT 2>/dev/null

echo $BUILD_PRE >>$CMPOPT
for i in $BUILD_INC; do echo -I$i >>$CMPOPT; done
 
echo -dARROW     >>$CMPOPT
echo -d_CCC_     >>$CMPOPT
echo -d_CCC3_    >>$CMPOPT
echo -d_UNIX_    >>$CMPOPT 
echo -d_SOLARIS_ >>$CMPOPT 
echo -ustd1.ch   >>$CMPOPT

if [ "$CCC_USE_CCCPP" == "y" -o "$CCC_USE_CCCPP" == "yes" ]; then
   PRG2PPO_EXE="cccpp -p"
else
   PRG2PPO_EXE=prg2ppo.exe
fi

if $PRG2PPO_EXE $2/$1.prg -oppo/$1.ppo @$CMPOPT >outpre; then

    #(2) CCC fordítás (ppo-->cpp)

    pushd ppo >/dev/null
    rm $1.cpp 2>/dev/null
    echo $2/$1.prg >ppo2cpp
 
    if ppo2cpp.exe -q $1.ppo 2>>ppo2cpp; then
        popd >/dev/null;

        #(3) C++ fordítás (cpp-->obj)
        $BUILD_BAT/_compile.b $1 ppo;

    else
        cp ppo2cpp ../error;
        popd >/dev/null;
    fi;

else
    cp outpre error;
fi

echo ----------------------------------------------------------------


 