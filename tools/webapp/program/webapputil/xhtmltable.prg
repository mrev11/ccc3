
************************************************************************************************
* xhtmltable
************************************************************************************************
class xhtmltable(xhtmlnode)
    
    attrib  colinfo

    method  initialize
    method  addcolumn
    method  addrow
    method  getrow

    method  thead           {|this|this:content[1]}
    method  tbody           {|this|this:content[2]}
    method  tfoot           {|this|this:content[3]}

    method  clear           {|this|this:tbody:content::asize(0)}

************************************************************************************************
static function xhtmltable.initialize(this,id)

    this:(xhtmlnode)initialize("table")
    
    this:addcontent( xhtmlnodeNew("thead") )
    this:addcontent( xhtmlnodeNew("tbody") )
    this:addcontent( xhtmlnodeNew("tfoot") )
    
    this:colinfo:={}

    this:setattrib( xhtmlnode.attrib("cellspacing","0") )
    this:setattrib( xhtmlnode.attrib("cellpadding","5") )
    this:setattrib( xhtmlnode.attrib("width","100%") )
    this:setattrib( xhtmlnode.attrib("border","0") )
    
    if( id!=NIL )
        this:setattrib( xhtmlnode.attrib("id",id) )
    end

    return this


************************************************************************************************
static function xhtmltable.addcolumn(this,h,p,s)
local colinfo,th

    if( valtype(h)=="O" )
        colinfo:=h  //kész colinfo objektum
    else
        colinfo:=xhtmltable.colinfoNew(h,p,s)
    end
    this:colinfo::aadd(colinfo)
    
    th:=xhtmlnodeNew("th")
    th:addtext(colinfo:header)
    this:thead:addcontent(th)
    
    return colinfo


************************************************************************************************
static function xhtmltable.addrow(this,row)
local tr,rowcnt,rowid,td,n

    tr:=xhtmlnodeNew("tr")
    this:tbody:addcontent(tr)
    rowcnt:=this:tbody:content::len
    rowid:="ROWID"+rowcnt::str::alltrim

    tr:setattrib( xhtmlnode.attrib("id",rowid) )
    tr:setattrib( xhtmlnode.attrib("class",if(rowcnt%2==0,"even","odd" )))
    tr:setattrib( xhtmlnode.attrib("onclick","CODE.onclick_row(this)"))

    for n:=1 to len(row)
        td:=xhtmlnodeNew("td")
        tr:addcontent(td)
        
        if( this:colinfo[n]:picture==NIL )
            td:addtext(row[n])
        else
            td:addtext(row[n]::transform(this:colinfo[n]:picture) )
        end
        if( this:colinfo[n]:style!=NIL )
            td:setattrib( xhtmlnode.attrib("style",this:colinfo[n]:style) )
        end
    next


************************************************************************************************
static function xhtmltable.getrow(this,rowid)
local x
    if( empty(rowid) .or. !"ROWID"$rowid )
        return NIL
    end
    x:=ascan(this:tbody:content,{|r|r:getattrib("id")==rowid})
    if( x<=0 )
        return NIL
    end
    return this:tbody:content[x]


************************************************************************************************
class xhtmltable.colinfo(object)
    attrib  header
    attrib  picture
    attrib  style
    method  initialize

static function xhtmltable.colinfo.initialize(this,h,p,s)
    this:header :=h
    this:picture:=p
    this:style  :=s
    return this


************************************************************************************************
function xhtmltable.rowid(x)
    return "ROWID"+x::str::alltrim


************************************************************************************************
