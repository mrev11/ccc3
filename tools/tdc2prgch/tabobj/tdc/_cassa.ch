
#define CASSA             (TABLE:_cassa)

#ifdef ARROW
#define CASSA_SOREGYEB             cassa->soregyeb            
#define CASSA_PENZTAROS            cassa->penztaros           
#define CASSA_SZAMLASZAM           cassa->szamlaszam          
#define CASSA_PENZTAR              cassa->penztar             
#define CASSA_SORBEFBIZ            cassa->sorbefbiz           
#define CASSA_SORKIFBIZ            cassa->sorkifbiz           
#define CASSA_SORKIVENG            cassa->sorkiveng           
#define CASSA_STATUS               cassa->status              
#define CASSA_SZLACSEKKV           cassa->szlacsekkv          
#define CASSA_SZLACSEKKE           cassa->szlacsekke          
#define CASSA_FEDVIZSG             cassa->fedvizsg            
#define CASSA_UGYFELAZON           cassa->ugyfelazon          
#else
#define CASSA_SOREGYEB             (FIELD:_cassa:1)
#define CASSA_PENZTAROS            (FIELD:_cassa:2)
#define CASSA_SZAMLASZAM           (FIELD:_cassa:3)
#define CASSA_PENZTAR              (FIELD:_cassa:4)
#define CASSA_SORBEFBIZ            (FIELD:_cassa:5)
#define CASSA_SORKIFBIZ            (FIELD:_cassa:6)
#define CASSA_SORKIVENG            (FIELD:_cassa:7)
#define CASSA_STATUS               (FIELD:_cassa:8)
#define CASSA_SZLACSEKKV           (FIELD:_cassa:9)
#define CASSA_SZLACSEKKE           (FIELD:_cassa:10)
#define CASSA_FEDVIZSG             (FIELD:_cassa:11)
#define CASSA_UGYFELAZON           (FIELD:_cassa:12)
#endif

