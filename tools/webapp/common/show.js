
function SHOW(obj) //this metódusa (this ~ [object Window] )
{
    document.write("<h3>"+ obj.toString() +"</h3>");

    var prop=[];
    for (var key in obj)
    {
        var x=key+" ~ ";
        if( key=="sessionStorage"){/*ezen elakad*/}
        else if( key=="innerHTML"){/*rekurzivitást okoz*/}
        else if( key=="textContent"){/*rekurzivitást okoz*/}
        else
        {
            var t=typeof(obj[key]);
            x+=t;
            if( t=="function" )
            {
            }
            else if( t=="string" )
            {
                x+=" "+obj[key]
            }
            else if( t=="number" )
            {
                x+=" "+obj[key]
            }
            else
            {
                x+=" "+obj[key];
            }
        }
        prop.push(x);
    }
    
    prop.sort()

    for (var n in prop)
    {
        document.write(prop[n]+"<br/>");
    }
    document.write("*<br/>");
}
