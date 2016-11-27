***********************************************************
function afn(fileDir,fileName)
   if (empty(fileDir))
      return fileName
   elseif (right(filedir,1)==":" .or.;
           right(filedir,1)=="\" .or.;
           right(filedir,1)=="/")
      return fileDir+fileName
   endif
return fileDir+dirsep()+fileName
***********************************************************

