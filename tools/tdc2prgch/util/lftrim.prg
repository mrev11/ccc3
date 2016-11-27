

static CR_LF := (chr(13)+chr(10))
static LF    := (chr(10))


*********************************************************************
function lfTrim(aLine,lfToo)
// Leszedi a sor végéről az CR_LF-et. Ha az lfToo igaz, akkor
// az LF-et (chr(10)) is.
   if (right(aLine,2)==CR_LF)
      return left(aLine,len(aLine)-2)
   endif
   if (lfToo==.t. .and. right(aLine,1)==LF)
      return left(aLine,len(aLine)-1)
   endif
return aLine
