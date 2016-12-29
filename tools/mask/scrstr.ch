#ifndef I_SCRSTR
#define I_SCRSTR

#command @ <row>, <col> SCREEN <scr> SAY <xpr>                          ;
                        [PICTURE <pic>]                                 ;
                        [COLOR <color>]                                 ;
                                                                        ;
      => scrPos( <scr>, <row>, <col> )                                  ;
       ; scrOutPict( <scr>, <xpr>, <pic> [, <color>] )


#define wrpict(i) if(pictlist==nil,nil,pictlist[i])

#define CR_LF chr(13)+chr(10)

#endif