
// ez windowson erdekes, dll helyett static konyvtarat hasznal
#define PCRE2_STATIC

// PCRE2_CODE_UNIT_WIDTH must be defined before including pcre2.h
// use 8, 16, or 32; or 0 for a multi-width application
// ha 0, akkor mindenhol explicite meg kell adni a meretet
#define PCRE2_CODE_UNIT_WIDTH 0

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdint.h> //2019-05-22 korabban ez nem kellett
#include <pcre2.h>


int main()
{
    PCRE2_SPTR32 pattern=(const unsigned int*) L"A";
    PCRE2_SPTR32 subject=(const unsigned int*) L"______A___";

    //compile the regular expression

    int errornumber;
    PCRE2_SIZE erroroffset;

    pcre2_code_32 *re= pcre2_compile_32(
            pattern,                // the pattern 
            PCRE2_ZERO_TERMINATED,  // indicates pattern is zero-terminated 
            PCRE2_UTF+PCRE2_NO_UTF_CHECK, // compile options 
            &errornumber,           // for error number 
            &erroroffset,           // for error offset 
            NULL);                  // default compile context 

    if( re == NULL )
    {
        // compilation failed
        PCRE2_UCHAR8 buffer[256];
        pcre2_get_error_message_8(errornumber,buffer,sizeof(buffer));
        printf("PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset, buffer);
        return 1;
    }


    //data block for holding the result

    pcre2_match_data_32 *match_data=pcre2_match_data_create_from_pattern_32(re, NULL);

    //running the match

    int rc = pcre2_match_32(
            re,                     // the compiled pattern 
            subject,                // the subject string 
            wcslen((wchar_t*)subject), // the length of the subject 
            0,                      // start at offset 0 in the subject 
            PCRE2_NO_UTF_CHECK,     // match options 
            match_data,             // block for storing the result 
            NULL);                  // use default match context 


    if( rc<0 )
    {
        // match failed

        switch(rc)
        {
            case PCRE2_ERROR_NOMATCH: 
                printf("No match\n"); 
                break;

            default: 
                printf("Matching error %d\n", rc); 
                break;
        }

        // clean up

        pcre2_match_data_free_32(match_data);
        pcre2_code_free_32(re);
        return 1;
    }

    // show results

    printf("pattern: \"%ls\"\n",(wchar_t*)pattern);
    printf("subject: \"%ls\"\n",(wchar_t*)subject);
    printf("          01234567890123456789012345678901234567890\n");
    printf("          0         1         2         3         4\n");

    PCRE2_SIZE *ovector = pcre2_get_ovector_pointer_32(match_data);

    for(int i=0; i<rc; i++)
    {
        int    ss_offset = (int)ovector[2*i];
        int    ss_length = (int)ovector[2*i+1] - ss_offset;
        wchar_t* ss_start= (wchar_t*)subject + ss_offset; 

        printf("%2d: %3d(%d)  %.*ls\n", 
                i, ss_offset, ss_length, ss_length, ss_start );

        // itt
        // az i=0 sor a teljes illeszkedo substringet mutatja
        // az i=1 sor a pattern elso zarojeles kifejezesehez illeszkedo reszt mutatja
        // az i=2 sor a pattern masodik zarojeles kifejezesehez illeszkedo reszt mutatja
    }

    // clean up

    pcre2_match_data_free_32(match_data);
    pcre2_code_free_32(re);
    return 0;
}


