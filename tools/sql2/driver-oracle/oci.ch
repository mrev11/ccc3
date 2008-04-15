
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __OCI_CH__
#define __OCI_CH__
 
//ORACLE datatypes

#define SQLT_CHR       1     // ORANET TYPE  character string 
#define SQLT_NUM       2     // ORANET TYPE  oracle numeric 
#define SQLT_INT       3     // ORANET TYPE  integer 
#define SQLT_FLT       4     // ORANET TYPE  Floating point number 
#define SQLT_STR       5     // zero terminated string 
#define SQLT_VNU       6     // NUM with preceding length byte 
#define SQLT_PDN       7     // ORANET TYPE  Packed Decimal Numeric 
#define SQLT_LNG       8     // long 
#define SQLT_VCS       9     // Variable character string 
#define SQLT_NON      10     // Null/empty PCC Descriptor entry 
#define SQLT_RID      11     // rowid 
#define SQLT_DAT      12     // date in oracle format 
#define SQLT_VBI      15     // binary in VCS format 
#define SQLT_BIN      23     // binary data DTYBIN  
#define SQLT_LBI      24     // long binary 
#define SQLT_UIN      68     // unsigned integer 
#define SQLT_SLS      91     // Display sign leading separate 
#define SQLT_LVC      94     // Longer longs  char 
#define SQLT_LVB      95     // Longer long binary 
#define SQLT_AFC      96     // Ansi fixed char 
#define SQLT_AVC      97     // Ansi Var char 
#define SQLT_CUR     102     // cursor  type 
#define SQLT_RDD     104     // rowid descriptor 
#define SQLT_LAB     105     // label type 
#define SQLT_OSL     106     // oslabel type 
#define SQLT_NTY     108     // named object type 
#define SQLT_REF     110     // ref type 
#define SQLT_CLOB    112     // character lob 
#define SQLT_BLOB    113     // binary lob 
#define SQLT_BFILEE  114     // binary file lob 
#define SQLT_CFILEE  115     // character file lob 
#define SQLT_RSET    116     // result set type 
#define SQLT_NCO     122     // named collection type  varray or nested table  
#define SQLT_VST     155     // OCIString type 
#define SQLT_ODT     156     // OCIDate type 
 

//descriptor types

#define OCI_DTYPE_LOB                50  // lob  locator 
#define OCI_DTYPE_SNAP               51  // snapshot descriptor 
#define OCI_DTYPE_RSET               52  // result set descriptor 
#define OCI_DTYPE_PARAM              53  // a parameter descriptor obtained from ocigparm 
#define OCI_DTYPE_ROWID              54  // rowid descriptor 
#define OCI_DTYPE_COMPLEXOBJECTCOMP  55  // complex object retrieval descriptor */
#define OCI_DTYPE_FILE               56  // File Lob locator 
#define OCI_DTYPE_AQENQ_OPTIONS      57  // enqueue options 
#define OCI_DTYPE_AQDEQ_OPTIONS      58  // dequeue options 
#define OCI_DTYPE_AQMSG_PROPERTIES   59  // message properties 
#define OCI_DTYPE_AQAGENT            60  // aq agent 


//selectlist adatok

#define SEL_NAME          1
#define SEL_DATATYPE      2
#define SEL_DATASIZE      3
#define SEL_PRECISION     4
#define SEL_SCALE         5
#define SEL_ISNULL        6


//dbstruct adatok

#define COL_NAME          1   // oszlop(mező)név
#define COL_TYPE          2   // típus: C,N,D,L
#define COL_WIDTH         3   // mezőszélesség
#define COL_DEC           4   // tizedesjegyek (0, ha TYPE!="N")
//#define COL_PICT
#define COL_BLOCK         6   // mező olvasó/író block
#define COL_BUFFER        7   // mezőértéket tartalmzó buffer
#define COL_INDVAR        8   // indikátor változó (null értékek)
#define COL_SIZEOF        8
 

#define IND_NAME          1   // index azonosító
#define IND_FILE          2   // indexfájl neve (path és kiterjesztés nélkül)
#define IND_COL           3   // az indexet alkotó oszlopok nevének tömbje
#define IND_TYPE          4   // .f. állandó index, .t. ideiglenes index
#define IND_SIZEOF        4
 

#define OPEN_CLOSED       0   // nincs nyitva
#define OPEN_READONLY     1   // SHARED+READONLY (!)
#define OPEN_SHARED       2   // default
#define OPEN_EXCLUSIVE    3
#define OPEN_APPEND       4

 

//-------------------------------------------------------------------------------
// oci.h-ból
//-------------------------------------------------------------------------------
//
// 1. minden #include kiszedve
//
// 2. Clipperben nem értelmezhető konstrukciók kiszedve
//
// 3. azok a szimbólumok, amik Clipperből is kellenek
//    hexa helyett decimális értékkel vannak megadva
//
// 4. a módosított helyeket //! jelzi

//--- Modes ---------------------------------------------------------------------

#define OCI_DEFAULT        0 //! the default value for parameters and attributes 
#define OCI_THREADED       1 //! the application is in threaded environment 
#define OCI_OBJECT         2 //! the application is in object environment 
#define OCI_NON_BLOCKING   4 //! non blocking mode of operation 
#define OCI_ENV_NO_MUTEX   8 //! the environment handle will not be protected by a mutex internally 

//--- Handle Types --------------------------------------------------------------

#define OCI_HTYPE_FIRST                  1  // start value of handle type 
#define OCI_HTYPE_ENV                    1  // environment handle 
#define OCI_HTYPE_ERROR                  2  // error handle 
#define OCI_HTYPE_SVCCTX                 3  // service handle 
#define OCI_HTYPE_STMT                   4  // statement handle 
#define OCI_HTYPE_BIND                   5  // bind handle 
#define OCI_HTYPE_DEFINE                 6  // define handle 
#define OCI_HTYPE_DESCRIBE               7  // describe handle 
#define OCI_HTYPE_SERVER                 8  // server handle 
#define OCI_HTYPE_SESSION                9  // authentication handle 
#define OCI_HTYPE_TRANS                 10  // transaction handle 
#define OCI_HTYPE_COMPLEXOBJECT         11  // complex object retrieval handle 
#define OCI_HTYPE_SECURITY              12  // security handle 
#define OCI_HTYPE_LAST                  12  // last value of a handle type 

//--- Descriptor Types ----------------------------------------------------------

#define OCI_DTYPE_FIRST                 50  // start value of descriptor type 
#define OCI_DTYPE_LOB                   50  // lob  locator 
#define OCI_DTYPE_SNAP                  51  // snapshot descriptor 
#define OCI_DTYPE_RSET                  52  // result set descriptor 
#define OCI_DTYPE_PARAM                 53  // a parameter descriptor obtained from ocigparm 
#define OCI_DTYPE_ROWID                 54  // rowid descriptor 
#define OCI_DTYPE_COMPLEXOBJECTCOMP     55  // complex object retrieval descriptor 
#define OCI_DTYPE_FILE                  56  // File Lob locator 
#define OCI_DTYPE_AQENQ_OPTIONS         57  // enqueue options 
#define OCI_DTYPE_AQDEQ_OPTIONS         58  // dequeue options 
#define OCI_DTYPE_AQMSG_PROPERTIES      59  // message properties 
#define OCI_DTYPE_AQAGENT               60  // aq agent 
#define OCI_DTYPE_LAST                  60  // last value of a descriptor type 

//--- Object Ptr Types ----------------------------------------------------------

#define OCI_OTYPE_NAME      1  // object name 
#define OCI_OTYPE_REF       2  // REF to TDO 
#define OCI_OTYPE_PTR       3  // PTR to TDO 

//--- Attribute Types -----------------------------------------------------------

#define OCI_ATTR_FNCODE                  1
#define OCI_ATTR_OBJECT                  2
#define OCI_ATTR_NONBLOCKING_MODE        3
#define OCI_ATTR_SQLCODE                 4
#define OCI_ATTR_ENV                     5
#define OCI_ATTR_SERVER                  6
#define OCI_ATTR_SESSION                 7
#define OCI_ATTR_TRANS                   8
#define OCI_ATTR_ROW_COUNT               9
#define OCI_ATTR_SQLFNCODE              10
#define OCI_ATTR_PREFETCH_ROWS          11
#define OCI_ATTR_NESTED_PREFETCH_ROWS   12
#define OCI_ATTR_PREFETCH_MEMORY        13
#define OCI_ATTR_NESTED_PREFETCH_MEMORY 14
#define OCI_ATTR_CHAR_COUNT             15  // this specifies the bind and define size in characters 
#define OCI_ATTR_PDSCL                  16
#define OCI_ATTR_PDFMT                  17
#define OCI_ATTR_PARAM_COUNT            18
#define OCI_ATTR_ROWID                  19
#define OCI_ATTR_CHARSET                20
#define OCI_ATTR_NCHAR                  21
#define OCI_ATTR_USERNAME               22  // username attribute 
#define OCI_ATTR_PASSWORD               23  // password attribute 
#define OCI_ATTR_STMT_TYPE              24  // statement type 
#define OCI_ATTR_INTERNAL_NAME          25
#define OCI_ATTR_EXTERNAL_NAME          26
#define OCI_ATTR_XID                    27
#define OCI_ATTR_TRANS_LOCK             28
#define OCI_ATTR_TRANS_NAME             29
#define OCI_ATTR_HEAPALLOC              30  // memory allocated on the heap 
#define OCI_ATTR_CHARSET_ID             31  // Character Set ID 
#define OCI_ATTR_CHARSET_FORM           32  // Character Set Form 
#define OCI_ATTR_MAXDATA_SIZE           33  // Maximumsize of data on the server  
#define OCI_ATTR_CACHE_OPT_SIZE         34  // object cache optimal size 
#define OCI_ATTR_CACHE_MAX_SIZE         35  // object cache maximum size percentage 
#define OCI_ATTR_PINOPTION              36  // object cache default pin option 
#define OCI_ATTR_ALLOC_DURATION         37  // object cache default allocation duration 
#define OCI_ATTR_PIN_DURATION           38  // object cache default pin duration 
#define OCI_ATTR_FDO                    39  // Format Descriptor object attribute 
#define OCI_ATTR_POSTPROCESSING_CALLBACK 40  // Callback to process outbind data 
#define OCI_ATTR_POSTPROCESSING_CONTEXT 41  // Callback context to process outbind data 
#define OCI_ATTR_ROWS_RETURNED          42  // Number of rows returned in current iter - for Bind handles 
#define OCI_ATTR_FOCBK                  43  // Failover Callback attribute 
#define OCI_ATTR_IN_V8_MODE             44  // is the server/service context in V8 mode 
#define OCI_ATTR_LOBEMPTY               45
#define OCI_ATTR_SESSLANG               46  // session language handle 

//--- Enqueue Options -----------------------------------------------------------

#define OCI_ATTR_VISIBILITY             47  // visibility 
#define OCI_ATTR_RELATIVE_MSGID         48  // relative message id 
#define OCI_ATTR_SEQUENCE_DEVIATION     49  // sequence deviation 

//--- Dequeue Options -----------------------------------------------------------

#define OCI_ATTR_CONSUMER_NAME          50  // consumer name 
#define OCI_ATTR_DEQ_MODE               51  // dequeue mode 
#define OCI_ATTR_NAVIGATION             52  // navigation 
#define OCI_ATTR_WAIT                   53  // wait 
#define OCI_ATTR_DEQ_MSGID              54  // dequeue message id 

//--- Message Properties --------------------------------------------------------

#define OCI_ATTR_PRIORITY               55  // priority 
#define OCI_ATTR_DELAY                  56  // delay 
#define OCI_ATTR_EXPIRATION             57  // expiration 
#define OCI_ATTR_CORRELATION            58  // correlation id 
#define OCI_ATTR_ATTEMPTS               59  // # of attempts 
#define OCI_ATTR_RECIPIENT_LIST         60  // recipient list 
#define OCI_ATTR_EXCEPTION_QUEUE        61  // exception queue name 
#define OCI_ATTR_ENQ_TIME               62  // enqueue time (only OCIAttrGet) 
#define OCI_ATTR_MSG_STATE              63  // message state (only OCIAttrGet) 

//--- AQ Agent ------------------------------------------------------------------

#define OCI_ATTR_AGENT_NAME             64  // agent name 
#define OCI_ATTR_AGENT_ADDRESS          65  // agent address 
#define OCI_ATTR_AGENT_PROTOCOL         66  // agent protocol 

//--- Parameter Attribute Types--------------------------------------------------

#define OCI_ATTR_UNK                   101  // unknown attribute 
#define OCI_ATTR_NUM_COLS              102  // number of columns 
#define OCI_ATTR_LIST_COLUMNS          103  // parameter of the column list 
#define OCI_ATTR_RDBA                  104  // DBA of the segment header 
#define OCI_ATTR_CLUSTERED             105  // whether the table is clustered 
#define OCI_ATTR_PARTITIONED           106  // whether the table is partitioned 
#define OCI_ATTR_INDEX_ONLY            107  // whether the table is index only 
#define OCI_ATTR_LIST_ARGUMENTS        108  // parameter of the argument list 
#define OCI_ATTR_LIST_SUBPROGRAMS      109  // parameter of the subprogram list 
#define OCI_ATTR_REF_TDO               110  // REF to the type descriptor 
#define OCI_ATTR_LINK                  111  // the database link name 
#define OCI_ATTR_MIN                   112  // minimum value 
#define OCI_ATTR_MAX                   113  // maximum value 
#define OCI_ATTR_INCR                  114  // increment value 
#define OCI_ATTR_CACHE                 115  // number of sequence numbers cached 
#define OCI_ATTR_ORDER                 116  // whether the sequence is ordered 
#define OCI_ATTR_HW_MARK               117  // high-water mark 
#define OCI_ATTR_TYPE_SCHEMA           118  // type's schema name 
#define OCI_ATTR_TIMESTAMP             119  // timestamp of the object 
#define OCI_ATTR_NUM_ATTRS             120  // number of sttributes 
#define OCI_ATTR_NUM_PARAMS            121  // number of parameters 
#define OCI_ATTR_OBJID                 122  // object id for a table or view 
#define OCI_ATTR_PTYPE                 123  // type of info described by 
#define OCI_ATTR_PARAM                 124  // parameter descriptor 
#define OCI_ATTR_OVERLOAD_ID           125  // overload ID for funcs and procs 
#define OCI_ATTR_TABLESPACE            126  // table name space 
#define OCI_ATTR_TDO                   127  // TDO of a type 

//--- Credential Types ----------------------------------------------------------

#define OCI_CRED_RDBMS      1  // database username/password 
#define OCI_CRED_EXT        2  // externally provided credentials 

//--- Error Return Values -------------------------------------------------------

#define OCI_SUCCESS                 0   // maps to SQL_SUCCESS of SAG CLI 
#define OCI_SUCCESS_WITH_INFO       1   // maps to SQL_SUCCESS_WITH_INFO 
#define OCI_NO_DATA               100   // maps to SQL_NO_DATA 
#define OCI_ERROR                  -1   // maps to SQL_ERROR 
#define OCI_INVALID_HANDLE         -2   // maps to SQL_INVALID_HANDLE 
#define OCI_NEED_DATA              99   // maps to SQL_NEED_DATA 
#define OCI_STILL_EXECUTING     -3123   // OCI would block error 
#define OCI_CONTINUE           -24200   // Continue with the body of the OCI function 

//--- Parsing Syntax Types ------------------------------------------------------

#define OCI_V7_SYNTAX           2  // V7 language 
#define OCI_V8_SYNTAX           3  // V8 language 
#define OCI_NTV_SYNTAX          1  // Use what so ever is the native lang of server 

//--- Scrollable Cursor Options -------------------------------------------------

#define OCI_FETCH_NEXT          2  //! 0x02  
#define OCI_FETCH_FIRST         4  //! 0x04
#define OCI_FETCH_LAST          8  //! 0x08
#define OCI_FETCH_PRIOR        16  //! 0x10
#define OCI_FETCH_ABSOLUTE     32  //! 0x20
#define OCI_FETCH_RELATIVE     64  //! 0x40

//--- Bind and Define Options ---------------------------------------------------

#define OCI_SB2_IND_PTR         0x01  
#define OCI_DATA_AT_EXEC        0x02
#define OCI_DYNAMIC_FETCH       0x02
#define OCI_PIECEWISE           0x04

//--- Execution Modes -----------------------------------------------------------

#define OCI_BATCH_MODE           1  //! 0x01  
#define OCI_EXACT_FETCH          2  //! 0x02
#define OCI_KEEP_FETCH_STATE     4  //! 0x04
#define OCI_SCROLLABLE_CURSOR    8  //! 0x08
#define OCI_DESCRIBE_ONLY       16  //! 0x10
#define OCI_COMMIT_ON_SUCCESS   32  //! 0x20

//--- Authentication Modes ------------------------------------------------------

#define OCI_MIGRATE             0x0001  // migratable auth context 
#define OCI_SYSDBA              0x0002  // for SYSDBA authorization 
#define OCI_SYSOPER             0x0004  // for SYSOPER authorization 
#define OCI_PRELIM_AUTH         0x0008  // for preliminary authorization 

//--- Piece Information ---------------------------------------------------------

#define OCI_PARAM_IN            0x01  
#define OCI_PARAM_OUT           0x02

//--- Transaction Start/End Flags -----------------------------------------------

#define OCI_TRANS_OLD           0x00000000
#define OCI_TRANS_NEW           0x00000001
#define OCI_TRANS_JOIN          0x00000002
#define OCI_TRANS_RESUME        0x00000004
#define OCI_TRANS_STARTMASK     0x000000ff
#define OCI_TRANS_READONLY      0x00000100
#define OCI_TRANS_READWRITE     0x00000200
#define OCI_TRANS_SERIALIZABLE  0x00000400
#define OCI_TRANS_ISOLMASK      0x0000ff00
#define OCI_TRANS_LOOSE         0x00010000
#define OCI_TRANS_TIGHT         0x00020000
#define OCI_TRANS_TYPEMASK      0x000f0000
#define OCI_TRANS_NOMIGRATE     0x00100000
#define OCI_TRANS_TWOPHASE      0x01000000
 
//--- Visibility flags ----------------------------------------------------------

#define OCI_ENQ_IMMEDIATE           1
#define OCI_ENQ_ON_COMMIT           2

//--- Dequeue mode flags --------------------------------------------------------

#define OCI_DEQ_BROWSE              1
#define OCI_DEQ_LOCKED              2
#define OCI_DEQ_REMOVE              3

//--- Dequeue navigation flags --------------------------------------------------

#define OCI_DEQ_FIRST_MSG           1
#define OCI_DEQ_NEXT_MSG            3
#define OCI_DEQ_NEXT_TRANSACTION    2

//--- Message states ------------------------------------------------------------

#define OCI_MSG_WAITING             1
#define OCI_MSG_READY               0
#define OCI_MSG_PROCESSED           2
#define OCI_MSG_EXPIRED             3

//--- Sequence deviation --------------------------------------------------------

#define OCI_ENQ_BEFORE              2
#define OCI_ENQ_TOP                 3

//--- Visibility flags ----------------------------------------------------------

#define OCI_DEQ_IMMEDIATE           1
#define OCI_DEQ_ON_COMMIT           2

//--- Wait ----------------------------------------------------------------------

#define OCI_DEQ_WAIT_FOREVER       -1
#define OCI_DEQ_NO_WAIT             0

//--- Delay ---------------------------------------------------------------------

#define OCI_MSG_NO_DELAY            0

//--- Expiration ----------------------------------------------------------------

#define OCI_MSG_NO_EXPIRATION      -1

//--- Object Types --------------------------------------------------------------

#define OCI_OTYPE_UNK               0
#define OCI_OTYPE_TABLE             1
#define OCI_OTYPE_VIEW              2
#define OCI_OTYPE_SYN               3
#define OCI_OTYPE_PROC              4
#define OCI_OTYPE_FUNC              5
#define OCI_OTYPE_PKG               6
#define OCI_OTYPE_STMT              7

//--- Describe Handle Parameter Attributes --------------------------------------

#define OCI_ATTR_DATA_SIZE                   1
#define OCI_ATTR_DATA_TYPE                   2
#define OCI_ATTR_DISP_SIZE                   3
#define OCI_ATTR_NAME                        4
#define OCI_ATTR_PRECISION                   5
#define OCI_ATTR_SCALE                       6
#define OCI_ATTR_IS_NULL                     7
#define OCI_ATTR_TYPE_NAME                   8
#define OCI_ATTR_SCHEMA_NAME                 9
#define OCI_ATTR_SUB_NAME                   10
#define OCI_ATTR_POSITION                   11

//--- complex object retrieval parameter attributes -----------------------------

#define OCI_ATTR_COMPLEXOBJECTCOMP_TYPE           50
#define OCI_ATTR_COMPLEXOBJECTCOMP_TYPE_LEVEL     51
#define OCI_ATTR_COMPLEXOBJECT_LEVEL              52
#define OCI_ATTR_COMPLEXOBJECT_COLL_OUTOFLINE     53

//--- Only Columns --------------------------------------------------------------

#define OCI_ATTR_DISP_NAME                 100

//--- Only Stored Procs ---------------------------------------------------------

#define OCI_ATTR_OVERLOAD                  210
#define OCI_ATTR_LEVEL                     211
#define OCI_ATTR_HAS_DEFAULT               212
#define OCI_ATTR_IOMODE                    213
#define OCI_ATTR_RADIX                     214
#define OCI_ATTR_NUM_ARGS                  215

//--- only user-defined Type's --------------------------------------------------

#define OCI_ATTR_TYPECODE                  216
#define OCI_ATTR_COLLECTION_TYPECODE       217
#define OCI_ATTR_VERSION                   218
#define OCI_ATTR_IS_INCOMPLETE_TYPE        219
#define OCI_ATTR_IS_SYSTEM_TYPE            220
#define OCI_ATTR_IS_PREDEFINED_TYPE        221
#define OCI_ATTR_IS_TRANSIENT_TYPE         222
#define OCI_ATTR_IS_SYSTEM_GENERATED_TYPE  223
#define OCI_ATTR_HAS_NESTED_TABLE          224
#define OCI_ATTR_HAS_LOB                   225
#define OCI_ATTR_HAS_FILE                  226
#define OCI_ATTR_COLLECTION_ELEMENT        227
#define OCI_ATTR_NUM_TYPE_ATTRS            228
#define OCI_ATTR_LIST_TYPE_ATTRS           229
#define OCI_ATTR_NUM_TYPE_METHODS          230
#define OCI_ATTR_LIST_TYPE_METHODS         231
#define OCI_ATTR_MAP_METHOD                232
#define OCI_ATTR_ORDER_METHOD              233

//--- only collection element ---------------------------------------------------

#define OCI_ATTR_NUM_ELEMS                 234

//--- only type methods ---------------------------------------------------------

#define OCI_ATTR_ENCAPSULATION             235
#define OCI_ATTR_IS_SELFISH                236
#define OCI_ATTR_IS_VIRTUAL                237
#define OCI_ATTR_IS_INLINE                 238
#define OCI_ATTR_IS_CONSTANT               239
#define OCI_ATTR_HAS_RESULT                240
#define OCI_ATTR_IS_CONSTRUCTOR            241
#define OCI_ATTR_IS_DESTRUCTOR             242
#define OCI_ATTR_IS_OPERATOR               243
#define OCI_ATTR_IS_MAP                    244
#define OCI_ATTR_IS_ORDER                  245
#define OCI_ATTR_IS_RNDS                   246
#define OCI_ATTR_IS_RNPS                   247
#define OCI_ATTR_IS_WNDS                   248
#define OCI_ATTR_IS_WNPS                   249

//--- describing public objects -------------------------------------------------

#define OCI_ATTR_DESC_PUBLIC               250


//--- ocicpw Modes --------------------------------------------------------------

#define OCI_AUTH    0x08  // Change the password but donot login 


//--- Other Constants -----------------------------------------------------------

#define OCI_MAX_FNS             100  // max number of OCI Functions 
#define OCI_SQLSTATE_SIZE       5 
#define OCI_ERROR_MAXMSG_SIZE   1024
#define OCI_LOBMAXSIZE          MINUB4MAXVAL
#define OCI_ROWID_LEN           23

//--- Fail Over Events ----------------------------------------------------------

#define OCI_FO_END              0x00000001
#define OCI_FO_ABORT            0x00000002   
#define OCI_FO_REAUTH           0x00000004
#define OCI_FO_BEGIN            0x00000008 

//--- Fail Over Types -----------------------------------------------------------

#define OCI_FO_NONE             0x00000001
#define OCI_FO_SESSION          0x00000002
#define OCI_FO_SELECT           0x00000004
#define OCI_FO_TXNAL            0x00000008

//--- Function Codes ------------------------------------------------------------

#define OCI_FNCODE_INITIALIZE           1
#define OCI_FNCODE_HANDLEALLOC          2
#define OCI_FNCODE_HANDLEFREE           3
#define OCI_FNCODE_DESCRIPTORALLOC      4
#define OCI_FNCODE_DESCRIPTORFREE       5
#define OCI_FNCODE_ENVINIT              6
#define OCI_FNCODE_SERVERATTACH         7
#define OCI_FNCODE_SERVERDETACH         8

// unused 9 

#define OCI_FNCODE_SESSIONBEGIN         10
#define OCI_FNCODE_SESSIONEND           11
#define OCI_FNCODE_PASSWORDCHANGE       12
#define OCI_FNCODE_STMTPREPARE          13
#define OCI_FNCODE_STMTBINDBYPOS        14
#define OCI_FNCODE_STMTBINDBYNAME       15

// unused 16 

#define OCI_FNCODE_BINDDYNAMIC          17
#define OCI_FNCODE_BINDOBJECT           18
#define OCI_FNCODE_BINDARRAYOFSTRUCT    20
#define OCI_FNCODE_STMTEXECUTE          21

// unused 22, 23 

#define OCI_FNCODE_DEFINE               24
#define OCI_FNCODE_DEFINEOBJECT         25
#define OCI_FNCODE_DEFINEDYNAMIC        26
#define OCI_FNCODE_DEFINEARRAYOFSTRUCT  27
#define OCI_FNCODE_STMTFETCH            28
#define OCI_FNCODE_STMTGETBIND          29

// unused 30, 31

#define OCI_FNCODE_DESCRIBEANY          32
#define OCI_FNCODE_TRANSSTART           33
#define OCI_FNCODE_TRANSDETACH          34
#define OCI_FNCODE_TRANSCOMMIT          35

// unused 36

#define OCI_FNCODE_ERRORGET             37
#define OCI_FNCODE_LOBOPENFILE          38
#define OCI_FNCODE_LOBCLOSEFILE         39
#define OCI_FNCODE_LOBCREATEFILE        40
#define OCI_FNCODE_LOBDELFILE           41
#define OCI_FNCODE_LOBCOPY              42
#define OCI_FNCODE_LOBAPPEND            43
#define OCI_FNCODE_LOBERASE             44
#define OCI_FNCODE_LOBLENGTH            45
#define OCI_FNCODE_LOBTRIM              46
#define OCI_FNCODE_LOBREAD              47
#define OCI_FNCODE_LOBWRITE             48

// unused 49 

#define OCI_FNCODE_SVCCTXBREAK          50
#define OCI_FNCODE_SERVERVERSION        51

// unused 52, 53 

#define OCI_FNCODE_ATTRGET              54
#define OCI_FNCODE_ATTRSET              55
#define OCI_FNCODE_PARAMSET             56
#define OCI_FNCODE_PARAMGET             57
#define OCI_FNCODE_STMTGETPIECEINFO     58
#define OCI_FNCODE_LDATOSVCCTX          59
#define OCI_FNCODE_RESULTSETTOSTMT      60
#define OCI_FNCODE_STMTSETPIECEINFO     61
#define OCI_FNCODE_TRANSFORGET          62
#define OCI_FNCODE_TRANSPREPARE         63
#define OCI_FNCODE_TRANSROLLBACK        64

#define OCI_FNCODE_DEFINEBYPOS          65
#define OCI_FNCODE_BINDBYPOS            66
#define OCI_FNCODE_BINDBYNAME           67

#define OCI_FNCODE_LOBASSIGN            68
#define OCI_FNCODE_LOBISEQUAL           69
#define OCI_FNCODE_LOBISINIT            70

// 71 was lob locator size in beta2 

#define OCI_FNCODE_LOBENABLEBUFFERING   71
#define OCI_FNCODE_LOBCHARSETID         72 
#define OCI_FNCODE_LOBCHARSETFORM       73
#define OCI_FNCODE_LOBFILESETNAME       74
#define OCI_FNCODE_LOBFILEGETNAME       75

#define OCI_FNCODE_LOGON                76
#define OCI_FNCODE_LOGOFF               77

#define OCI_FNCODE_LOBDISABLEBUFFERING  78
#define OCI_FNCODE_LOBFLUSHBUFFER       79
#define OCI_FNCODE_LOBLOADFROMFILE 80

//--- Piece Definitions ---------------------------------------------------------

// if ocidef.h is being included in the app, ocidef.h should precede oci.h 
 
#ifndef OCI_FLAGS
#define OCI_FLAGS
#define OCI_ONE_PIECE           0
#define OCI_FIRST_PIECE         1
#define OCI_NEXT_PIECE          2
#define OCI_LAST_PIECE          3
#endif

//--- FILE open modes -----------------------------------------------------------

#define OCI_FILE_READONLY       1  // readonly mode open for FILE types 

//--- LOB Buffering Flush Flags -------------------------------------------------

#define OCI_LOB_BUFFER_FREE     1
#define OCI_LOB_BUFFER_NOFREE   2

//--- OCI Statement Types -------------------------------------------------------

#define  OCI_STMT_SELECT        1  // select statement 
#define  OCI_STMT_UPDATE        2  // update statement 
#define  OCI_STMT_DELETE        3  // delete statement 
#define  OCI_STMT_INSERT        4  // Insert Statement 
#define  OCI_STMT_CREATE        5  // create statement 
#define  OCI_STMT_DROP          6  // drop statement 
#define  OCI_STMT_ALTER         7  // alter statement 
#define  OCI_STMT_BEGIN         8  // begin ... (pl/sql statement)
#define  OCI_STMT_DECLARE       9  // declare .. (pl/sql statement ) 

//--- OCI Parameter Types -------------------------------------------------------

#define OCI_PTYPE_UNK           0  // unknown   
#define OCI_PTYPE_TABLE         1  // table     
#define OCI_PTYPE_VIEW          2  // view      
#define OCI_PTYPE_PROC          3  // procedure 
#define OCI_PTYPE_FUNC          4  // function  
#define OCI_PTYPE_PKG           5  // package   
#define OCI_PTYPE_TYPE          6  // user-defined type 
#define OCI_PTYPE_SYN           7  // synonym   
#define OCI_PTYPE_SEQ           8  // sequence  
#define OCI_PTYPE_COL           9  // column    
#define OCI_PTYPE_ARG          10  // argument  
#define OCI_PTYPE_LIST         11  // list      
#define OCI_PTYPE_TYPE_ATTR    12  // user-defined type's attribute 
#define OCI_PTYPE_TYPE_COLL    13  // collection type's element 
#define OCI_PTYPE_TYPE_METHOD  14  // user-defined type's method 
#define OCI_PTYPE_TYPE_ARG     15  // user-defined type method's argument 
#define OCI_PTYPE_TYPE_RESULT  16  // user-defined type method's result 

//--- OCI List Types ------------------------------------------------------------

#define OCI_LTYPE_UNK           0  // unknown   
#define OCI_LTYPE_COLUMN        1  // column list 
#define OCI_LTYPE_ARG_PROC      2  // procedure argument list 
#define OCI_LTYPE_ARG_FUNC      3  // function argument list 
#define OCI_LTYPE_SUBPRG        4  // subprogram list 
#define OCI_LTYPE_TYPE_ATTR     5  // type attribute 
#define OCI_LTYPE_TYPE_METHOD   6  // type method 
#define OCI_LTYPE_TYPE_ARG_PROC 7  // type method w/o result argument list 
#define OCI_LTYPE_TYPE_ARG_FUNC 8  // type method w/result argument list 

//-------------------------------------------------------------------------------
 
#endif  // __OCI_CH__ 

 
