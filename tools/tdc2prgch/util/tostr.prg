//*******************************************************************
// tostr.prg: Value -> string conversion for printing.
// 1998-2015, Levente Csiszár
//*******************************************************************

/*
   2015.06.08, Csiszár Levente

      - Handle Objects.

   2003.01.02, Csiszár Levente

      - New implementation. Handle recursive arrays. For unknown
        type, print '<Type: t>'

   2001.11.05, Csiszár Levente

      - English documentation.

   1998.05.21, Csiszár Levente
   
      - Kivéve a cslutils.prg -ből.
   
*/

//*******************************************************************
function toStr(val,quote,formatNum)
// Convert a value to a string for printing.

local str
local stack:={}
local i,w,t,j
local err
local sep
local anArray,anObject,aType
local vt:=valtype(val)

   if (!vt$'AO')
      return _toStr(val,valtype(val),!empty(quote),!empty(formatNum))
   endif

   if (vt=='O')
      str:="<"+val:classname+">{"
      anArray:=val:attrvals
      anObject:=val
   else
      str:="{"
      anArray:=val
      anObject:=val
   endif
   i:=1
   while(.t.)
      if (i>len(anArray))
         if (empty(stack))
            exit
         else
            i:=atail(stack)[1]+1
            anArray:=atail(stack)[2]
            anObject:=atail(stack)[3]
            asize(stack,len(stack)-1)
            str+="}"
            if (i>len(anArray))
               loop
            endif
         endif
      endif
      sep:=if(i==1,"",",")
      w:=anArray[i]
      t:=valtype(w)
      if ('A'==t)
         aadd(stack,{i,anArray,anObject})
         if (0==(j:=ascan(stack,{|x| valtype(x[3])==t .and. x[3]==w })))
            str+=sep+"{"
            i:=1
            anArray:=w
            anObject:=w
            loop
         else // Referencia
            if (j==1)
               str+=sep+"[<Array>]"
            elseif (j==2)
               str+=sep+"[<Array>"+alltrim(str(stack[1][1]))+"]"
            else
               str+=sep+"[<Array>"+alltrim(str(stack[1][1]))
               aeval(stack,{|x| str+=","+alltrim(str(x[1]))},2,j-2)
               str+="]"
            endif
            asize(stack,len(stack)-1)
         endif 
      elseif ('O'==t)
         aadd(stack,{i,anArray,anObject})
         if (0==(j:=ascan(stack,{|x| valtype(x[3])==t .and. x[3]==w })))
            str+=sep+"<"+w:classname+">{"
            i:=1
            anArray:=w:attrvals
            anObject:=w
            loop
         else // Referencia
            if (j==1)
               str+=sep+"[<Object>]"
            elseif (j==2)
               str+=sep+"[<Object>"+alltrim(str(stack[1][1]))+"]"
            else
               str+=sep+"[<Object>"+alltrim(str(stack[1][1]))
               aeval(stack,{|x| str+=","+alltrim(str(x[1]))},2,j-2)
               str+="]"
            endif
            asize(stack,len(stack)-1)
         endif 
      else
         str+=sep+_toStr(w,t,.t.,!empty(formatNum))
      endif
      i++
   end while

return str+"}"


//*******************************************************************
static function _toStr(val,t,quote,formatNum)

   if ('C'==t)
      return if (empty(quote),val,'"'+val+'"')
   elseif ('N'==t)
      return if (formatNum,_formatnum(val),alltrim(str(val)))
   elseif ('D'==t)
      return dtoc(val)
   elseif ('L'==t)
      return if(val,"T","F")
   elseif ('U'==t)
      return "nil"
   elseif ('O'==t)
      return "<Object>"
   elseif ('B'==t)
      return "<Block>"
   elseif ('A'==t)
      return "<Array>"
   endif

return "<Type: "+t+">"

//*******************************************************************
function toStrx(val)
return toStr(val)

//*******************************************************************
function _formatNum(num)
local s,retval,i,sign

   s:=alltrim(str(num))

   if (left(s,1)=='-')
      sign:="-"
      s:=substr(s,2)
   else
      sign:=""
   endif

   retval:=""

   if (0==(i:=at(".",s)))
      i:=len(s)
      retval:=""
   else
      retval:=substr(s,i)
      i--
   endif

   i-=3
   // outstd("_formatnum(1): ",i,"'"+retval+"'",endofline())
   while(i>0)
      // outstd("_formatnum(2): ",i,"'"+retval+"'",endofline())
      retval:=","+substr(s,i+1,3)+retval
      i-=3
   end while

   // outstd("_formatnum(3): ",i,"'"+retval+"'",endofline())
   retval:=sign+left(s,min(i+3,3))+retval

return retval
//*******************************************************************


