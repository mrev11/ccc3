
XCODE.xlib.combo={}

XCODE.xlib.combo.show=function(input_id) //input-onclick
{
    //console.log("show",input_id);
    var combo_id=input_id+"-combo";
    var input=document.getElementById(input_id);
    var combo=document.getElementById(combo_id);
    combo.style.display="block";
    XCODE.xlib.combo.findrow(combo,input.value);
}

XCODE.xlib.combo.clear=function(combo_id) //input-onblur
{
    //console.log("clear",combo_id);
    var combo=document.getElementById(combo_id)
    combo.style.display="none";
}


XCODE.xlib.combo.pick=function(ctrl) //click on a <tr> element
{
    //console.log("pick",ctrl.textContent.trim().replace(/\n/g,';'));
    var input=XCODE.xlib.combo.getinput(ctrl);
    input.value=ctrl.textContent.trim().split('\n')[0];
    input.dispatchEvent(new Event('change'));
}


XCODE.xlib.combo.keyup=function(event)  //editalas
{ 
    var input=event.target; //input mezo
    var combo_id=input.id+"-combo";
    var combo=document.getElementById(combo_id);

    //console.log(event,input.value);

    if( event.key.length==1 )
    {
        combo.style.display="block";
        XCODE.xlib.combo.findrow(combo,input.value);
    }
}


XCODE.xlib.combo.keydown=function(event)  //navigalas
{
    var input=event.target; //input mezo
    var combo_id=input.id+"-combo";
    var combo=document.getElementById(combo_id);

    //console.log(event,input.value);

    if( event.key=='Enter' /* || event.key=='Tab' */ )
    {
        var row=null;
        if( combo.style.display!='none' )
        {
            row=XCODE.xlib.combo.findselectedrow(combo);
        }
        if( !row )
        {
            row=XCODE.xlib.combo.findrow(combo,input.value);
        }

        if( row )
        {
            var v=row.textContent.trim().split('\n')[0];  
            if( input.value!=v )
            {
                input.value=v;
                input.dispatchEvent(new Event('change'));
            }
            input.dispatchEvent(new Event('blur'));
        }
    }

    else if( event.key=="ArrowDown" )
    {
        if( combo.style.display=='none' )
        {
            combo.style.display="block";
            XCODE.xlib.combo.findrow(combo,input.value);
        }
        else
        {
            var row=XCODE.xlib.combo.findselectedrow(combo);

            if( row )
            {
                var num1=Number(row.id.substr(5,row.id.length))+1;
                var rowid1='ROWID'+num1;
                var row1=XCODE.xlib.combo.findrowid(combo,rowid1);
                if( row1 )
                {
                    var cls=row.getAttribute('class');
                    var cls1=row1.getAttribute('class');
                    row.setAttribute('class',cls.replace('X',''));
                    row1.setAttribute('class',cls1+"X");
        
                    var rrect=row1.getBoundingClientRect();
                    var crect=combo.getBoundingClientRect();
                    if( rrect.bottom>crect.bottom )
                    {
                        row1.scrollIntoView(false);
                    }
                }
            }
            else
            {
                XCODE.xlib.combo.findrow(combo,input.value);
            }
        }
    }

    else if( event.key=="ArrowUp" )
    {
        if( combo.style.display=='none' )
        {
            combo.style.display="block";
            XCODE.xlib.combo.findrow(combo,input.value);
        }
        else
        {
            var row=XCODE.xlib.combo.findselectedrow(combo);

            if( row  )
            {
                var num1=Number(row.id.substr(5,row.id.length))-1;
                var rowid1='ROWID'+num1;
                var row1=XCODE.xlib.combo.findrowid(combo,rowid1);
                if( row1 )
                {
                    var cls=row.getAttribute('class');
                    var cls1=row1.getAttribute('class');
                    row.setAttribute('class',cls.replace('X',''));
                    row1.setAttribute('class',cls1+"X");
        
                    var rrect=row1.getBoundingClientRect();
                    var crect=combo.getBoundingClientRect();
                    if( rrect.top<crect.top )
                    {
                        row1.scrollIntoView();
                    }
                }
            }
            else
            {
                XCODE.xlib.combo.findrow(combo,input.value);
            }
        }
    }
}


XCODE.xlib.combo.findrow=function(node,value) //input.value egyezes alapjan keres
{
    var row=null;
    var ch=node.childNodes;
    for(var n=0; n<ch.length; n++)
    {
        var ch1=ch[n];
        if( ch1.tagName=="TR" )
        {
            var txt=ch1.textContent.trim(); 
            var cls=ch1.getAttribute('class');
            //console.log(cls,txt);
            if( cls )
            {
                cls=cls.replace('X','');
                if( txt.substr(0,value.length)==value )
                {
                    cls+='X';
                    value='???'+value;
                    ch1.scrollIntoView();
                    row=ch1;
                }
                ch1.setAttribute('class',cls);
            }
        }
        else
        {
            ch1=XCODE.xlib.combo.findrow(ch1,value);
            if( !row )
            {
                row=ch1;
            }
        }
    }
    return row;
}


XCODE.xlib.combo.findselectedrow=function(node) // class='oddX/evenX'-et keres
{
    var ch=node.childNodes;
    for(var n=0; n<ch.length; n++)
    {
        var ch1=ch[n];
        if( ch1.tagName=="TR" )
        {
            var cls=ch1.getAttribute('class');
            //console.log("cls",cls);
            if( cls=="oddX" || cls=="evenX" )
            {
                //console.log(ch1);
                return ch1;
            }
        }
        else
        {
            ch1=XCODE.xlib.combo.findselectedrow(ch1);
            if( ch1 )
            {
                return ch1;
            }
        }
    }
}


XCODE.xlib.combo.findrowid=function(node,rowid) //ROWID<n>-et keres
{
    var ch=node.childNodes;
    for(var n=0; n<ch.length; n++)
    {
        var ch1=ch[n];
        if( ch1.tagName=="TR" )
        {  
            //console.log(ch1.getAttribute('id'));
            if( ch1.getAttribute('id')==rowid )
            {
                return ch1;
            }
        }
        else
        {
            ch1=XCODE.xlib.combo.findrowid(ch1,rowid);
            if( ch1 )
            {
                return ch1;
            }
        }
    }
}


XCODE.xlib.combo.getpicker=function(ctrl)
{
    while( ctrl!=null )
    {
        //console.log(ctrl.nodeName,ctrl.className);
        if( ctrl.className=="combo" )
        {
            var input_id=ctrl.id.replace("-combo","");
            var input=document.getElementById(input_id);
            return ctrl;
        }
        ctrl=ctrl.parentNode;
    }
}

XCODE.xlib.combo.getinput=function(ctrl)
{
    while( ctrl!=null )
    {
        //console.log(ctrl.nodeName,ctrl.className);
        if( ctrl.className=="combo" )
        {
            var input_id=ctrl.id.replace("-combo","");
            var input=document.getElementById(input_id);
            return input;
        }
        ctrl=ctrl.parentNode;
    }
}


XCODE.xlib.combo.gettable=function(combo)
{
    var children=combo.childNodes;
    for( var n=0; n<children.length; n++ )
    {
        if( children[n].tagName=="TABLE" )
        {
            return children[n];
        }
    }
}

