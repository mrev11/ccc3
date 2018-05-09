//*******************************************************************
// tdc2prgch.prg: tdc -> .prg, .ch
//*******************************************************************

#define VERSION "v1.0.2"

//*******************************************************************
// #define DEBUG(x) x
#define DEBUG(x)

//*******************************************************************
#define MAXLEN_TABLENAME     23
#define MAXLEN_INDEXFILENAME 24
#define MAXLEN_FIELDNAME     20


//*******************************************************************
#include "fileio.ch"

//*******************************************************************
function main()
local a:=argv()
local i
local oTdc
local e
local wrprg:=.t.
local wrch:=.t.

   if (empty(a))
      outstd("tdc2prgch "+VERSION+": make .ch and .prg from .tdc file",endofline())
      quit
   endif
   for i:=1 to len(a)
      if( a[i]=="--prg" )
           wrprg:=.t.
           wrch:=.f.
      elseif( a[i]=="--ch"  )
           wrprg:=.f.
           wrch:=.t.
      else
         DEBUG(outstd("tdc: ",i::stra,addfext(a[i],".tdc"),endofline()))
         begin
            oTdc:=readtdc(a[i])
            DEBUG(outstd(oTdc::toStr,endofline()))
            writetdc(oTdc,wrprg,wrch)
         recover e <tdcerror>
            // Nem kell csinálni semmit.
         end
      end
   end for

return nil

//*******************************************************************
static function chfext(filename,ext)
// Change the extension of a filename
local iDot:=0
local iPS:=0

   if (0==(iDot:=rat(".",filename)))
      return filename+ext
   endif

   iPS::=max(rat(":",filename))
   iPS::=max(rat("/",filename))
   iPS::=max(rat("\",filename))

return if(iPS>iDot,filename,left(filename,iDot-1))+ext

//*******************************************************************
static function addfext(filename,ext)
// Add an extension to a filename if it has no extension.
return if (chfext(filename,"")==filename,filename+ext,filename)

//*******************************************************************
static function getPathFromFilename(filename)
local iPS:=0

   iPS::=max(rat(":",filename))
   iPS::=max(rat("/",filename))
   iPS::=max(rat("\",filename))

return if(iPS==0,"",left(filename,iPS))

//*******************************************************************
static function sprefix(s,p)
return if(left(s,len(p))==p,substr(s,len(p)+1),nil)

//*******************************************************************
class oTdc(Object)

   attrib filename
   attrib table
   attrib path
   attrib owner
   attrib version
   attrib hIndexes
   attrib fields
   attrib hFields

   method initialize {|this|;
      this:hIndexes:=simpleHashNew(),;
      this:fields:={},;
      this:hFields:=simpleHashNew(),;
      this}

//*******************************************************************
class oIndex(Object)
   attrib ixName
   attrib ixFilename
   attrib ixFields
   attrib iLine

   method initialize {|this| this:ixFields:={},this}
   
//*******************************************************************
class oField(Object)
   attrib fname
   attrib ftype
   attrib flen
   attrib fdec
   attrib iLine
   
//*******************************************************************
static function readtdc(tdcfilename)
local fid
local cLine,iLine,w,t
local o:=oTdcNew()
local oi,of
local idxItem,i
local erdln

   tdcfilename::=addfext(".tdc")

   o:filename:=tdcfilename
   DEBUG(outstd("readtdc",endofline()))

   if (-1==(fid:=fopen(tdcfilename,FO_READ)))
      perr(tdcfilename+": open error: "+ferror()::stra,endofline())
      return nil
   endif

   iLine:=0
   erdln:=ereadlineNew(fid)
   // while(nil<>(cLine:=xlreadline(fid,@buffer,.t.,@hiba)))
   DEBUG(outstd("readtdc: readline start",endofline()))
   while(nil<>(cLine:=erdln:readline))
      if (erdln:errno<>0)
         DEBUG(outstd("readtdc: errno: "+erdln:errno::stra,endofline()))
         exit
      endif
      iLine++
      cLine::=bin2str::lftrim(.t.)
      // DEBUG(outstd("cLine: ",iLine::stra,":",cLine,endofline()))
      if (!cLine::left(1)=='!')
         // Drop
      elseif (nil<>(w:=cLine::sprefix("!table")))
         if (" "$(w::=alltrim)); perrline(tdcfilename,iLine,"Syntax error"); endif
         if (o:table<>nil)
            perrline(fid,tdcfilename,iLine,"Duplicate !table: "+cLine)
         endif
         w::=alltrim
         if (len(w)>MAXLEN_TABLENAME)
            perrline(fid,tdcfilename,iLine,"Table name too long(max: "+MAXLEN_TABLENAME::stra+": "+w)
         endif
         o:table:=w
      elseif (nil<>(w:=cLine::sprefix("!path")))
         if (" "$(w::=alltrim)); perrline(fid,tdcfilename,iLine,"Syntax error"); endif
         if (o:path<>nil)
            perrline(fid,tdcfilename,iLine,"Duplicate !path: "+cLine)
         endif
         o:path:=w::lower // Because ddict do it.
      elseif (nil<>(w:=cLine::sprefix("!owner")))
         if (" "$(w::=alltrim)); perrline(fid,tdcfilename,iLine,"Syntax error"); endif
         if (o:owner<>nil)
            perrline(fid,tdcfilename,iLine,"Duplicate !owner: "+cLine)
         endif
         o:owner:=w
      elseif (nil<>(w:=cLine::sprefix("!version")))
         if (" "$(w::=alltrim)); perrline(fid,tdcfilename,iLine,"Syntax error"); endif
         if (o:version<>nil)
            perrline(fid,tdcfilename,iLine,"Duplicate !version: "+cLine)
         endif
         o:version:=w
      elseif (nil<>(w:=cLine::sprefix("!index")))
         t:=splitsp(w)
         // DEBUG(outstd("index: ",t,endofline()))
         if (len(w)<3); perrline(fid,tdcfilename,iLine,"Syntax error"); endif
         t[1]::=lower
         if (!empty(o:hIndexes[t[1]]))
            perrline(fid,tdcfilename,iLine,"Duplicate index name: "+t[1])
         endif
         if (len(t[2])>MAXLEN_INDEXFILENAME)
            perrline(fid,tdcfilename,iLine,"Index file name too long (max: "+MAXLEN_INDEXFILENAME::stra+"): "+t[2])
         endif
         oi:=oIndexNew()
         oi:ixName:=t[1]
         oi:ixFilename:=t[2]::lower
         oi:ixFields:=t[3..];aieval(oi:ixFields,{|x,i|oi:ixFields[i]:=x::lower})
         oi:iline:=iLine
         o:hIndexes[oi:ixName]:=oi
         oi:=nil
      elseif (nil<>(w:=cLine::sprefix("!field")))
         t:=splitsp(w)
         // DEBUG(outstd("field: ",t,endofline()))
         if !(len(t)==3 .or. len(t)==4); perrline(fid,tdcfilename,iLine,"Syntax error"); endif
         of:=oFieldNew()
         of:fname:=t[1]::lower
         if (!empty(o:hFields[of:fname]))
            perrline(fid,tdcfilename,iLine,"Duplicate field name: "+of:fname)
         endif
         if (len(of:fname)>MAXLEN_FIELDNAME)
            perrline(fid,tdcfilename,iLine,"Field name too long (max: "+MAXLEN_FIELDNAME::stra+"): "+of:fname)
         endif
         of:ftype:=t[2]::upper
         if !(len(of:ftype)==1 .and. of:ftype$"CNDL")
            perrline(fid,tdcfilename,iLine,"Unknown field type("+of:ftype+"): "+cLine)
         endif
         of:flen:=t[3]
         if !(consistOf(of:flen,"0123456789"))
            perrline(fid,tdcfilename,iLine,"Field len is not a number("+of:flen+"): "+cLine)
         endif
         if (len(t)<=3)
            of:fdec:=0
         elseif !(consistOf(of:fdec:=t[4],"0123456789"))
            perrline(fid,tdcfilename,iLine,"Field dec is not a number("+of:fdec+"): "+cLine)
         endif
         of:iline:=iLine
         aadd(o:fields,of)
         o:hFields[of:fname]:=of
         of:=nil
      else
         perrline(fid,tdcfilename,iLIne,"Unknown tdc keyword: "+cLine)
      endif
   end while
   if (erdln:errno<>0)
      fclose(fid)
      perr(tdcfilename+": read error: "+erdln:errno::stra)
      return nil
   endif

   if (empty(o:table))
      perrline(fid,tdcfilename,iLine,"Missing !table")
   endif

   // Check field names in indexes.
   idxItem:=o:hIndexes:firstvalue
   while(idxItem<>nil)
      for i:=1 to len(idxItem:ixFields)
         if (empty(o:hfields[idxItem:ixFields[i]]))
            perrline(fid,tdcfilename,idxItem:iLine,"Field in index expression does not exist: "+idxItem:ixFields[i])
         endif
      end for
      idxItem:=o:hIndexes:nextvalue
   end while

   if (empty(o:owner)); o:owner:="guest"; endif 
   if (o:version==nil); o:version:="0"; endif

   fclose(fid)
   
return o

//*******************************************************************
static function stra(s)
return s::str::alltrim

//*******************************************************************
class tdcError(appError)

//*******************************************************************
function perr(s)
local e:=tdcErrorNew()

   outerr(s,endofline())
   break(e)

return nil

//*******************************************************************
function perrline(fid,tdcfilename,iLine,s)
  fclose(fid)
return perr(tdcfilename+": "+iLine::stra+": "+s)

//*******************************************************************
static function hGetValueArray(h) // Get the value array from hash
local item:=h:firstvalue
local t:={}

   while(item<>nil)
      aadd(t,item)
      item:=h:nextvalue
   end while

return t

//*******************************************************************
static function pString(s)
return '"'+s+'"'

//*******************************************************************
static function writetdc(o,wrprg:=.t.,wrch:=.t.)
local tIndexes
local sCh:="",sPrg:=""
// A DBM-et is kell majd kezelni, lásd ddict2 forrás.
local eol:=endofline()
local filepath:=afn(o:filename::getpathFromFilename,"_"+o:table::lower)
local f,i,idx
local tab:=space(4)
local w

   // Indexes must be sorted by file name, because ddict2 uses this
   // sorting and ctree driver is sensible of the order (uhhh...).
   tIndexes:=o:hIndexes::hGetValueArray

   asort(tIndexes,,,{|x,y| x:ixFilename<y:ixFilename})
   DEBUG(outstd(tIndexes,endofline()))

   sCh+=eol
   sCh+="#define "+o:table::upper+"             (TABLE:_"+o:table+")"+eol
   sCh+=eol

   sCh+="#ifdef ARROW"+eol

   for i:=1 to len(o:fields)
      f:=o:fields[i]
      sCh+="#define "+o:table::upper+"_"+f:fname::upper::padr(MAXLEN_FIELDNAME)+" "+;
           o:table::lower+"->"+f:fname::lower::padr(MAXLEN_FIELDNAME)+eol
   end for

   sCh+="#else"+eol;

   for i:=1 to len(o:fields)
      f:=o:fields[i]
      sCh+="#define "+o:table::upper+"_"+f:fname::upper::padr(MAXLEN_FIELDNAME)+" "+;
           "(FIELD:_"+o:table::lower+":"+i::stra+")"+eol
   end for

   sCh+="#endif"+eol

   sCh+=eol

   DEBUG(outstd(".ch file: "+filepath+".ch",endofline()))
   DEBUG(outstd(sCh))

   // Print .prg

   sPrg+="function _"+o:table::upper+"(col,exp)"+eol

   sPrg+="static dbf"+eol
   sPrg+=tab+"if(empty(dbf))"+eol
   sPrg+=tab+tab+"dbf:=tabNew("+'"'+o:table::upper+'"'+")"+eol
   if (!empty(o:path))
      sPrg+=tab+tab+"tabPath(dbf,"+pString(o:path::upper+"\")+")"+eol
   endif

   // DEBUG(outstd(o:fields,endofline()))
   for i:=1 to len(o:fields)
      f:=o:fields[i]
      sPrg+=tab+tab+"tabAddColumn(dbf,{"+f:fname::upper::pString::padr(MAXLEN_FIELDNAME)+","+;
           f:ftype::pString+","+f:flen::padl(3)+","+f:fdec::padl(2)+"})"+eol
   end for

   for i:=1 to len(tIndexes)
      idx:=tIndexes[i]
      sPrg+=tab+tab+"tabAddIndex(dbf,{"+;
            idx:ixName::upper::pString+","+;
            idx:ixFilename::upper::pString+","

      sPrg+="{"+idx:ixFields[1]::upper::pString
      aeval(idx:ixFields,{|x| sPrg+=","+x::upper::pString},2)
      sPrg+="}})"+eol
   end for

   sPrg+=tab+"end"+eol
   sPrg+=tab+"if(col==NIL)"+eol
   sPrg+=tab+tab+"return dbf"+eol
   sPrg+=tab+"end"+eol
   sPrg+=tab+"return tabEvalColumn(dbf,col,exp)"+eol
   sPrg+=eol

   DEBUG(outstd(".prg file: "+filepath+".prg",endofline()))
   DEBUG(outstd(sPrg))

if(wrch)
   if (nil<>(w:=fmemowrite(filepath+".ch",sCh)))
      perr(w)
   endif
end

if(wrprg)
   if (nil<>(w:=fmemowrite(filepath+".prg",sPrg)))
      perr(w)
   endif
end

return nil

//*******************************************************************
static function fmemowrite(filename,s)
local fid,ferr

   if (-1==(fid:=fcreate(filename)))
      return filename+": create error: "+ferror()::stra
   endif

   if (len(s)<>fwrite(fid,s,len(s)))
      ferr:=ferror()
      fclose(fid)
      return filename+": create error: "+ferr::stra
   endif

   fclose(fid)

return nil

//*******************************************************************
