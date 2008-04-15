
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

#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

# ifndef YYSTYPE
#  define YYSTYPE int
#  define YYSTYPE_IS_TRIVIAL 1
# endif
# define	CHAR	257
# define	NUMBER	258
# define	SECTEND	259
# define	SCDECL	260
# define	XSCDECL	261
# define	NAME	262
# define	PREVCCL	263
# define	EOF_OP	264
# define	OPTION_OP	265
# define	OPT_OUTFILE	266
# define	OPT_PREFIX	267
# define	OPT_YYCLASS	268
# define	CCE_ALNUM	269
# define	CCE_ALPHA	270
# define	CCE_BLANK	271
# define	CCE_CNTRL	272
# define	CCE_DIGIT	273
# define	CCE_GRAPH	274
# define	CCE_LOWER	275
# define	CCE_PRINT	276
# define	CCE_PUNCT	277
# define	CCE_SPACE	278
# define	CCE_UPPER	279
# define	CCE_XDIGIT	280


extern YYSTYPE yylval;

#endif /* not BISON_Y_TAB_H */
