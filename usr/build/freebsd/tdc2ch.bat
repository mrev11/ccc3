#!/bin/bash
#set -x
echo TDC2CH.BAT $1 $2

#rm -f error
rm -f error--tdc2ch-$1
mkdir -p ppo

rm -f ppo/$1.ch
cp -f $2/$1.tdc ppo/$1.tmp-ch
tdc2prgch.exe --ch  ppo/$1.tmp-ch 2>ppo/tdc2ch-$1

if ! test -f ppo/$1.ch; then
    touch error
    mv ppo/tdc2ch-$1 error--tdc2ch-$1
    cat error--tdc2ch-$1
    echo 'tdc2ch' $1 FAILED

else
    mv ppo/$1.ch $2/$1.ch

    rm -f ppo/$1.tmp-ch
    rm -f ppo/tdc2ch-$1
fi


echo ----------------------------------------------------------------
