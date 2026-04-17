

//#define DEBUG

******************************************************************************************
function pson_parser(pson) // pson: string(konkatenált sorok) / array(külön sorok)

local request:=jsonobjectNew()
local req,line,n

    if( pson::valtype=="A" )
        req:=pson
    else
        req:=pson::split(chr(10))
    end

    for n:=1 to len(req)
        line:=req[n]::alltrim
        if( line::empty )
            // kihagy
        elseif( line::left(2)=="//" )
            // kihagy
        else
            pson_line(request,line,n)
        end
    next

    return request


******************************************************************************************
function pson_line(request,line,linecnt:=0)

local value
local path,px,tag
local stack:={},top,sx
local member,jsobj,attr,n
local pos:=at("-->",line)

    if( pos==0 )
        value:=NIL
        path:=line::alltrim::split(".")
    else
        value:=line::substr(pos+3)::alltrim
        path:=line::left(pos-1)::alltrim::split(".")
    end

    stack::aadd(jsonmemberNew(path[1],request))
    sx:=1

    #ifdef DEBUG
    ? "********** LINE",linecnt::str::alltrim,path
    if( value!=NIL )
        ?? " -->",value
    end
    #endif

    for px:=2 to len(path)
        #ifdef DEBUG
        print_stack(stack)
        ? "NEXT <"+path[px]+">"
        #endif

        tag:=path[px]

        top:=stack[sx]:value
        // stack[sx] tipusa: jsonmember
        // top       tipusa: (jsonobject|array|string)

        if( tag=="NEW" .or. tag=="{NEW}" )

            if( top::valtype!="A" )
                error_misplacednew(stack,linecnt)

            elseif( top[1]::valtype=="O" )
                if( tag=="NEW")
                    member:=jsonmemberNew("",jsonobjectNew())
                else
                    member:=jsonmemberNew("",{jsonobjectNew()})
                end
                jsobj:=jsonobjectNew()
                jsobj:add(member)
                top::aadd(jsobj)
                stack::aadd(member)
                sx+=1
            else
                // leaf
                top::aadd(NIL) // ideiglenesen NIL
            end

        elseif( tag[1..7]=="ATTRIB(" )
            attr:=attrib(tag)
            stack[sx]:value:array::aadd( jsonmemberNew(attr[1],attr[2]) )
            path::aadd("value")

        elseif( top::valtype=="A" )

            if( tag[1]=="{" )
                tag:=tag[2..len(tag)-1]::uncap

                jsobj:=top::atail
                member:=search_tag_among_members(jsobj:array,tag)
                if( member==NIL )
                    //?? "?"
                    member:=jsonmemberNew(tag,{jsonobjectNew()}) // {különbség}
                    jsobj:array::aadd(member)
                else
                    //?? " !aa: ", member
                    if( member:value::valtype=="O" )
                        stack::aadd(member)
                        error_nonarray(stack,linecnt)
                    end
                end
                stack::aadd(member)
                sx+=1

            else
                tag::=uncap
                jsobj:=top::atail
                member:=search_tag_among_members(jsobj:array,tag)
                if( member==NIL )
                    //?? "?"
                    member:=jsonmemberNew(tag,jsonobjectNew()) // különbség
                    jsobj:array::aadd(member)
                else
                    //?? " !ao: ", member
                    if( member:value::valtype=="A" )
                        stack::aadd(member)
                        error_array(stack,linecnt)
                    end
                end
                stack::aadd(member)
                sx+=1
            end

        elseif( top::valtype=="O" )

            if( tag[1]=="{" )
                tag:=tag[2..len(tag)-1]::uncap

                member:=search_tag_among_members(top:array,tag)
                if( member==NIL )
                    //?? "?"
                    member:=jsonmemberNew(tag,{jsonobjectNew()}) // {különbség}
                    top:add(member)
                else
                    //?? " !oa: ", member
                    if( member:value::valtype=="O" )
                        stack::aadd(member)
                        error_nonarray(stack,linecnt)
                    end

                end
                stack::aadd(member)
                sx+=1

            else
                tag::=uncap
                member:=search_tag_among_members(top:array,tag)
                if( member==NIL )
                    //?? "?"
                    member:=jsonmemberNew(tag,jsonobjectNew()) // különbség
                    top:add(member)
                else
                    //?? " !oo: ", member
                    if( member:value::valtype=="A" )
                        stack::aadd(member)
                        error_array(stack,linecnt)
                    end
                end
                stack::aadd(member)
                sx+=1
            end

        else
            // itt korábbi levelet írna felül
            error_leaf(stack,linecnt)
        end
    next


    //? "@@@", stack[sx]:value::valtype, stack[sx],value

    top:=stack[sx]:value
    if( value!=NIL )

        if( top::valtype=="O" )
            if( top:array::empty )
                stack[sx]:value:=value_from_string(value)
            else
                // korábban ez a node
                // nemlevél pozícióban fordult elő
                error_nonleaf(stack,linecnt)
            end

        elseif( top::valtype=="A" )
            top::apop
            top::apush(value_from_string(value))

        else
            // primitive
            stack[sx]:value:=value_from_string(value)
        end
    end

    #ifdef DEBUG
    print_stack(stack)
    json_print(request,.t.)
    ?
    #endif


******************************************************************************************
static function value_from_string(x)

    if( x[1]=='"' )
        return x[2..len(x)-1]

    elseif( isnumber(x) )
        return val(x)

    elseif( isdate(x) )
        return x
        return epoch(x)

        // tapasztalat:
        // bemenetként a java elfogadja a dátumidőt
        //   epoch (szám) formátumban is
        //   XMLGregorianCalendar formátumú stringként is
        // kimenetként a java mindig
        //   epoch (szám) formátumot ír

    elseif( x=="null" )
        return NIL

    elseif( x=="false" )
        return .f.

    elseif( x=="true" )
        return .t.
    end

    return x


******************************************************************************************
static function isnumber(text)
static rx:=pcre2.compile("[+\-]{0,1}[0-9]+(\.[0-9]+){0,1}")
local match:=pcre2.match(rx,text)
    return match::len>=2 .and. match[1]==1 .and. match[2]>len(text)


******************************************************************************************
static function isdate(text)
local rx:=pcre2.compile("(20|19)[0-9]{2}-[0-1][0-9]-[0-3][0-9]T[0-2][0-9]:[0-5][0-9]:[0-5][0-9]")
local match:=pcre2.match(rx,text)
    return match::len>=2 .and. match[1]==1 .and. match[2]>len(text)


******************************************************************************************
static function epoch(x)
// yyyy-mm-ddThh:mm:ss
// 1234567890123456789
    return date2epoch( val(x[ 1.. 4]), val(x[ 6.. 7]), val(x[ 9..10]),;
                       val(x[12..13]), val(x[15..16]), val(x[18..19]) ) *1000 // millis

******************************************************************************************
static function search_tag_among_members(arr,nm) // -> jsonmember
local x
    if( !empty(arr) .and. empty(arr[1]:name) )
        // ez a NEW-val készített member
        arr[1]:name:=nm
        return arr[1]
    end
    for x:=1 to len(arr)
        if( arr[x]:name==nm )
            return arr[x]
        end
    next
    return NIL


******************************************************************************************
static function attrib(attr)
    attr:=attr[8..len(attr)-1]
    attr::=split("=")
    attr[1]::=uncap
    return attr


******************************************************************************************
static function uncap( name )
local uncap:="",n
    for n:=1 to len(name)
        if( name[n]::isupper )
            uncap+=name[n]::lower
        else
            exit
        end
    next
    uncap+=name[n..]
    return uncap


******************************************************************************************
static function print_stack(stack)
local n,member,name,value
    for n:=1 to len(stack)
        member:=stack[n]
        name:=member:name
        value:=member:value
        ? ">>>", name, if(value::valtype=="A","[]","")
    next


******************************************************************************************
static function error_nonleaf(stack,linecnt)
    ? "ERROR:"+errorline(linecnt)+errorpath(stack)+" defined earlier as nonleaf"
    callstack()
    ?
    quit

static function error_leaf(stack,linecnt)
    ? "ERROR:"+errorline(linecnt)+errorpath(stack)+" defined earlier as leaf"
    callstack()
    ?
    quit

static function error_nonarray(stack,linecnt)
    ? "ERROR:"+errorline(linecnt)+" tail of "+errorpath(stack)+" defined earlier as nonarray"
    callstack()
    ?
    quit

static function error_array(stack,linecnt)
    ? "ERROR:"+errorline(linecnt)+" tail of "+errorpath(stack)+" defined earlier as array"
    callstack()
    ?
    quit

static function error_misplacednew(stack,linecnt)
    ? "ERROR:"+errorline(linecnt)+errorpath(stack)+"NEW is not feasible here"
    callstack()
    ?
    quit

static function errorline(linecnt)
local line:=" line(LINE) "
    line::=strtran("LINE",linecnt::str::alltrim)
    return line

static function errorpath(stack)
local path:="",sx
    for sx:=1 to len(stack)
        if(sx>1)
            path+="."
        end
        path+=stack[sx]:name
    next
    return " ["+path+"] "


******************************************************************************************
