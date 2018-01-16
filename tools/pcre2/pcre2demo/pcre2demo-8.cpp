
// ez windowson erdekes, dll helyett static konyvtarat hasznal
#define PCRE2_STATIC

// PCRE2_CODE_UNIT_WIDTH must be defined before including pcre2.h
// use 8, 16, or 32; or 0 for a multi-width application
#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <string.h>
#include <pcre2.h>


int main()
{
    PCRE2_SPTR pattern=(const unsigned char*) "(^|[^A])A{2,3}($|[^A])";
    PCRE2_SPTR subject=(const unsigned char*) "AAAA__A____xAAyAAAA_AAAAAAA___AAA";


    //compile the regular expression

    int errornumber;
    PCRE2_SIZE erroroffset;

    pcre2_code *re= pcre2_compile(
            pattern,                // the pattern 
            PCRE2_ZERO_TERMINATED,  // indicates pattern is zero-terminated 
            0,                      // default options 
            &errornumber,           // for error number 
            &erroroffset,           // for error offset 
            NULL);                  // use default compile context 

    if( re == NULL )
    {
        // compilation failed
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errornumber,buffer,sizeof(buffer));
        printf("PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset, buffer);
        return 1;
    }


    //data block for holding the result

    pcre2_match_data *match_data=pcre2_match_data_create_from_pattern(re, NULL);

    //running the match

    int rc = pcre2_match(
            re,                     // the compiled pattern 
            subject,                // the subject string 
            strlen((char*)subject), // the length of the subject 
            0,                      // start at offset 0 in the subject 
            0,                      // default options 
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

        pcre2_match_data_free(match_data);
        pcre2_code_free(re);
        return 1;
    }

    // show results

    printf("pattern: \"%s\"\n",pattern);
    printf("subject: \"%s\"\n",subject);
    printf("          01234567890123456789012345678901234567890\n");
    printf("          0         1         2         3         4\n");

    PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);

    for(int i=0; i<rc; i++)
    {
        int    ss_offset = (int)ovector[2*i];
        int    ss_length = (int)ovector[2*i+1] - ss_offset;
        char*  ss_start  = (char*)subject + ss_offset; 

        printf("%2d: %3d(%d)  %.*s\n", 
                i, ss_offset, ss_length, ss_length, ss_start );

        // itt
        // az i=0 sor a teljes illeszkedo substringet mutatja
        // az i=1 sor a pattern elso zarojeles kifejezesehez illeszkedo reszt mutatja
        // az i=2 sor a pattern masodik zarojeles kifejezesehez illeszkedo reszt mutatja
    }

    // clean up

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
    return 0;
}


