

//------------------------------------------------------------------------------
XCODE.num2str=function(num,dec) //szamok formazasa
//------------------------------------------------------------------------------
// dec=undef: tizedesek nelkul, elvalaszto vesszok nelkul
// dec=0    : tizedesek nelkul, elvalaszto vesszokkel
// dec>=1   : tizedesekkel, elvalaszto vesszokkel

{
    var x;
    if( dec!=undefined  )
    {
        x=num.toLocaleString("en-US",{minimumFractionDigits:dec,maximumFractionDigits:dec});
    }
    else
    {
        x=num.toString();
    }
    return x;
} 

//------------------------------------------------------------------------------
XCODE.numsettlevalue=function(ctrl,dec)
//------------------------------------------------------------------------------
{
    if( ctrl.xreadvalue==undefined )
    {
        ctrl.xreadvalue=function()
        {
            return this.value.replace(/,/g,"").replace(/ /g,"");
        }
    }
    var text=ctrl.xreadvalue();
    var num=Number(text);
    ctrl.value=XCODE.num2str(num,dec);
}

//------------------------------------------------------------------------------
XCODE.numkeypress=function(e) 
//------------------------------------------------------------------------------
{
    var ctrl=e.target; //input mezo

    if( XCODE.evententer(e) && e.target.onblur!=undefined )
    {
        ctrl.onblur(ctrl);
    }
    else if( e.charCode==0 )
    {
        //del,bs,right,left,...
    }
    else
    {
        var x=ctrl.value; //tartalom az aktualis karakter nelkul
        var pos=ctrl.selectionStart; //caret pozicio
        var chr=String.fromCharCode(e.charCode); //aktualis karakter
        x=x.slice(0,pos)+chr+x.slice(pos); //karakter beillesztve
        
        if( !/^[+-]?[,0-9]*(\.[0-9]*)?$/.test(x) )
        {
            //beillesztes letiltva
            e.preventDefault();
        }
    }
}

//------------------------------------------------------------------------------
