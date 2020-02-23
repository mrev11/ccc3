


//------------------------------------------------------------------------------
XCODE.readfile=function(ctrlid,x,mode) 
//------------------------------------------------------------------------------
{
    var ctrl=document.getElementById(ctrlid); //browse: <input type="file">
    var file=ctrl.files[x-1] // 0-tol indexel
    var reader = new FileReader();

    reader.onerror=function()
    {
        //üzenet: webconsole-ra
        var err="read error: "+reader.error.message;
        console.log(err);

        //üzenet: frmaux-ba        
        XCODE.frmaux.writeln('<span style="color: red;">'+err+'</span>');

        var x="<readfile>"+err+"</readfile>";
        XCODE.send(x);
    }

    reader.onload=function()
    {
        //console.log( reader.result );
        var x="<readfile>"
        x+=XCODE.cdataif(reader.result);
        x+="</readfile>";
        XCODE.send(x);
    }
    
    if( mode==null )
    {
        reader.readAsDataURL(file);
    }

    else if( mode=="dataurl" )
    {
        reader.readAsDataURL(file);
    }

    else if( mode=="binary" )
    {
        reader.readAsBinaryString(file);
    }

    else if( mode.indexOf("text")==0 )  // pl. "text-ISO-9959-2"
    {
        if( mode=="text" )
        {
            reader.readAsText(file); // UTF-8
        }
        else
        {
            var encoding=mode.substring(5);
            reader.readAsText(file,encoding);
        }
    }

    else
    {
        reader.readAsDataURL(file);
    }

}


