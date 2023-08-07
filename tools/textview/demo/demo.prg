
#include "box.ch"

function main()

local top:=10
local lef:=30
local bot:=20
local rig:=70

local x,tv,screen

    x:=memoread("demo.prg")
    tv:=textviewNew(x,top,lef,bot,rig)
    screen:=drawbox(top-1,lef-1,bot+1,rig+1,B_SINGLE)
    tv:loop

    restscreen(top-1,lef-1,bot+1,rig+1,screen)

    alert("Ok")

