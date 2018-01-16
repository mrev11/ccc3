

#include <string.h>
#include <pcre.h>

#include <cccapi.h>

#ifdef WINDOWS  
  //Windows: sizeof(wchar_t)==16
  #define   pcre_WIDE           pcre16
  #define   pcre_extra_WIDE     pcre16_extra
  #define   PCRE_SPTR_WIDE      PCRE_SPTR16
  #define   PCRE_COMPILE2_WIDE  pcre16_compile2
  #define   PCRE_STUDY_WIDE     pcre16_study 
  #define   PCRE_EXEC_WIDE      pcre16_exec
#else 
  //Linux: sizeof(wchar_t)==32
  #define   pcre_WIDE           pcre32
  #define   pcre_extra_WIDE     pcre32_extra
  #define   PCRE_SPTR_WIDE      PCRE_SPTR32
  #define   PCRE_COMPILE2_WIDE  pcre32_compile2
  #define   PCRE_STUDY_WIDE     pcre32_study 
  #define   PCRE_EXEC_WIDE      pcre32_exec
#endif

DEFINE_METHOD(operation);
DEFINE_METHOD(description);
DEFINE_METHOD(subsystem);
DEFINE_METHOD(subcode);

extern void _clp_apperrornew(int);

namespace _nsp_pcre{

//----------------------------------------------------------------------------
struct pcreinfo
{
    int byte; // 1 vagy 4 bajtos karakterek

    union
    {
        pcre            *pcode;
        pcre_WIDE       *pcodew;
    } code;

    union
    {
        pcre_extra      *pextra;
        pcre_extra_WIDE *pextraw;
    } extra;
};

//----------------------------------------------------------------------------
static pcreinfo *pcreinfo_alloc()
{
    void *p=malloc(sizeof(pcreinfo));
    memset(p,0,sizeof(pcreinfo));
    return (pcreinfo *)p;
}

//----------------------------------------------------------------------------
static void pcreinfo_free(pcreinfo *info)
{
    if( info )
    {
        if( info->code.pcode )
        {
            pcre_free(info->code.pcode );
        }
        if( info->extra.pextra )
        {
            pcre_free_study(info->extra.pextra );
        }
        free(info);
    }
}

//----------------------------------------------------------------------------
void _clp_free(int argno) //pcre.free(pcreptr) -
{
    CCC_PROLOG("pcre.free",1);
    pcreinfo *info=ISNIL(1)?0:(pcreinfo*)_parp(1);
    pcreinfo_free(info);
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_compile(int argno) //pcre.compile(regex,flags) -> pcre
{
    CCC_PROLOG("pcre.compile",2);

    int options=ISNIL(2)?0:_parni(2);

    int study=1; //bedrotozott opcio: kell-e optimalizalni (nem fontos)
  
    int pcreErrorCode;
    const char *pcreErrorStr;
    int pcreErrorOffset;
    pcreinfo *info=pcreinfo_alloc();

#ifdef _CCC2_
    //printf("CCC2 string\n");
    char *regex=_parc(1);
    info->byte=1;
    info->code.pcode=pcre_compile2(regex,options,
                            &pcreErrorCode,&pcreErrorStr,&pcreErrorOffset,0);

#else
    if( base->type==TYPE_BINARY )
    {
        //printf("CCC3 binary\n");
        char *regex=_parb(1);
        info->byte=1;
        info->code.pcode=pcre_compile2(regex,options,
                            &pcreErrorCode,&pcreErrorStr,&pcreErrorOffset,0);
    }
    else if( base->type==TYPE_STRING )
    {
        //printf("CCC3 string\n");
        //CHAR* regex=_parc(1);
        PCRE_SPTR_WIDE regex=(PCRE_SPTR_WIDE)_parc(1);
        info->byte=4;
        info->code.pcodew=PCRE_COMPILE2_WIDE(regex,options,
                            &pcreErrorCode,&pcreErrorStr,&pcreErrorOffset,0);
    }
    else
    {
        error_arg("pcre.compile",base,2);
    }
#endif

    if(  info->code.pcode==0 )
    {
        //HIBA
        
        char errbuf[1024];
        unsigned len=snprintf(errbuf,sizeof(errbuf),"%s (offset %d)",pcreErrorStr,pcreErrorOffset+1);
        if( len>sizeof(errbuf) )
        {
            len=sizeof(errbuf);
        }

        pcreinfo_free(info);
        
        _clp_apperrornew(0);
        dup(); string(CHRLIT("pcre.compile"));_o_method_operation.eval(2);pop(); 
        dup(); stringsb(errbuf,len);_o_method_description.eval(2);pop();
        dup(); string(CHRLIT("pcre"));_o_method_subsystem.eval(2);pop(); 
        dup(); number(pcreErrorCode);_o_method_subcode.eval(2);pop();
        _clp_break(1);
        _ret();
    }
    else if( study )
    {
        //study: optiomalizalas
        
        if( info->byte==1 )
        {
            info->extra.pextra=pcre_study(info->code.pcode,0,&pcreErrorStr);
        }
        else
        {
            info->extra.pextraw=PCRE_STUDY_WIDE(info->code.pcodew,0,&pcreErrorStr);
        }

        if( pcreErrorStr!=0 )
        {
            //HIBA
        
            char errbuf[1024];
            unsigned len=snprintf(errbuf,sizeof(errbuf),"%s",pcreErrorStr);
            if( len>sizeof(errbuf) )
            {
                len=sizeof(errbuf);
            }

            pcreinfo_free(info);
        
            _clp_apperrornew(0);
            dup(); string(CHRLIT("pcre.compile(study)"));_o_method_operation.eval(2);pop(); 
            dup(); stringsb(errbuf,len);_o_method_description.eval(2);pop();
            dup(); string(CHRLIT("pcre"));_o_method_subsystem.eval(2);pop(); 
           _clp_break(1);
            _ret();
        }
    }

    pointer(info);
    _rettop();

    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_exec(int argno) //pcre.exe(rxinfo,txt,start,options) -> pcre
{
    CCC_PROLOG("pcre.exec",4);

    pcreinfo *info=(pcreinfo*)_parp(1);
    int options=ISNIL(4)?0:_parni(4);
    int start;
    int retval=-1;

    #define VECLEN 48 //3-mal oszthato!
    int subvec[VECLEN];
    memset(subvec,0,sizeof(subvec));

    if( info->byte==1 )
    {
        char *txt=_parb(2);
        int len=_parblen(2);
        start=ISNIL(3)?0:_parni(3)-1;
        retval=pcre_exec(   info->code.pcode,
                            info->extra.pextra,
                            txt,
                            len,
                            start,
                            options,
                            subvec,
                            VECLEN);
    }

    else if( info->byte==4 )
    {
        PCRE_SPTR_WIDE txt=(PCRE_SPTR_WIDE)_parc(2);
        int len=_parclen(2);
        start=ISNIL(3)?0:_parni(3)-1;
        retval=PCRE_EXEC_WIDE( info->code.pcodew,
                            info->extra.pextraw,
                            txt,
                            len,
                            start,
                            options,
                            subvec,
                            VECLEN);
    }

    else
    {
        //ha ervenytelen a pointer
        error_arg("pcre.exec(pointer)",base,4);
    }

    //for( int i=0; i<VECLEN; i++ )
    //{
    //    printf("\n !!%d  %d",i,subvec[i]);
    //}
    
    if( retval<-1 )
    {
        //HIBA
        _clp_apperrornew(0);
        dup(); string(CHRLIT("pcre"));_o_method_subsystem.eval(2);pop(); 
        dup(); string(CHRLIT("pcre.exec"));_o_method_operation.eval(2);pop(); 
        dup(); string(CHRLIT("pcre.exec failed"));_o_method_description.eval(2);pop();
        dup(); number(retval);_o_method_subcode.eval(2);pop();
       _clp_break(1);
        _ret();
    }
    else if( retval==PCRE_ERROR_NOMATCH )
    {
        //nincs illeszkedes
        _ret();
    }
    else 
    {
        if( retval==0 )
        {
            //nem volt eleg hely subvex-ban
            //max ennyi index par lehet benne:
            retval=VECLEN/3;

            //The first two-thirds of the vector is used to  pass  back  captured  sub‐
            //strings,  each substring using a pair of integers. The remaining third of
            //the vector is used as workspace by pcre_exec() while  matching  capturing
            //subpatterns,  and is not available for passing back information. The num‐
            //ber passed in ovecsize should always be a multiple of  three.  If  it  is
            //not, it is rounded down.
        }
        
        // "xxxxxxMMMMMMMMMMMMMxxxxxxxxxxxxxxxxxxx"
        //        ^            ^
        //    subvec[0]   subvec[1]  
        //
        // Mutatjak az illeszkedo substring hatarait.
        // A tovabbi indexek a regex reszeihez illeszkedo
        // subsubstringek hatarait mutatjak, ezek nehezen
        // ertelmezhetok, es altalaban nincs rajuk szukseg.

        retval*=2; //indexpar -> index

        for( int i=0; i<retval; i++ )
        {
            number(subvec[i]+1);
        }
        array(retval);
        _rettop();
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------------

}//namespace


