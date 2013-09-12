
/*  A Bison parser, made from ucpop.y with Bison version GNU Bison version 1.22
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	DEFINE	258
#define	OPERATOR	259
#define	DOMAIN	260
#define	PROBLEM	261
#define	PARAMETERS	262
#define	PRECONDITION	263
#define	EFFECT	264
#define	LP	265
#define	RP	266
#define	FORALL	267
#define	EXISTS	268
#define	NOT	269
#define	AND	270
#define	OR	271
#define	WHEN	272
#define	CONSTANT	273
#define	VARIABLE	274
#define	INITS	275
#define	GOALS	276

#line 1 "ucpop.y"

/* -*- mode: fundamental -*- */
#include "objects.h"
#include "symtab.h"
#include "logic.h"
#include "parser.h"
#include "planner.h"
#include "list.h"
#include "slist.h"
  
  extern int LineNumber;
/* prevent mangling of names */
extern "C" {
  void yyerror(char*);
  int yyparse(void);
}

void
yyerror(char* s)
{
  fprintf(stderr, "%s at line %d.\n", s, LineNumber+1);
}
     
  
//extern DomainTemplate Domain;

//
// use bounded buffers for I/O of parser and planner;  will change if
// necessary
//
extern Parser parser;
extern Planner planner;

int numParams=0;
Context scope=0;
Buffer buf(20);
Buffer stepbuf(20);
Sym tmp;
Node* tmpNode;     // temporary "global" vairable passing around
Node* typedVar;
Sym stepName;
int NumExtVar=0;   // number of "extension" variables in forall's
char namebuf1[20]; // get around's for saving intermediate strings
char namebuf2[20];

List<Node> typedVarList;
SList<Sym> univVarList;
List<Node> univTypeVarList;
SITERATE_NO_INIT(var, snext, Sym);
ITERATE_NO_INIT(typevar, tnext, Node);

ostream& 
operator<<(ostream& os, const SymArray& s)
{
  os << "<";
  for(int i=0;i<s.GetCount();i++)
     os << s[i] << ",";
  os << ">";
  return os;
}

ostream& 
operator<<(ostream& os, const SList<Sym>& s)
{
  SITERATE(var, s, next, Sym);
  os << "<";
  SDOLIST(var, next) {
    os << var << " ";
  }
  os << ">";
  return os;
}

ostream& 
operator<<(ostream& os, const SList<SList<Sym> >& s)
{
  SITERATE(l, s, next, SList<Sym>);
  os << "<";
  SDOLIST(l, next) {
    os << l << " ";
  }
  os << ">";
  return os;
}



#line 89 "ucpop.y"
typedef union {
  char *ident;
  int  keyword;
  Node *node;
  List<Node>* nodelist;
  Sym sym;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		115
#define	YYFLAG		-32768
#define	YYNTBASE	22

#define YYTRANSLATE(x) ((unsigned)(x) <= 276 ? yytranslate[x] : 51)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     3,     4,    13,    16,    18,    21,    24,    25,    35,
    38,    40,    41,    46,    47,    50,    55,    57,    59,    62,
    65,    67,    69,    72,    73,    76,    78,    80,    81,    84,
    85,    91,    94,    96,    98,   102,   106,   110,   117,   124,
   126,   128,   132,   139,   141,   143,   145,   150,   152,   155,
   160,   164,   167,   169,   171
};

static const short yyrhs[] = {    30,
    25,     0,     0,     3,     6,    18,    24,    11,    26,    27,
    11,     0,    25,    23,     0,    23,     0,    20,    44,     0,
    21,    43,     0,     0,     3,     4,    18,    29,    11,    31,
    37,    36,    11,     0,    30,    28,     0,    28,     0,     0,
     7,    10,    32,    11,     0,     0,    32,    34,     0,    10,
    18,    19,    11,     0,    19,     0,    33,     0,    35,    33,
     0,    35,    19,     0,    33,     0,    19,     0,     9,    44,
     0,     0,     8,    43,     0,    18,     0,    19,     0,     0,
    39,    38,     0,     0,    10,    18,    41,    39,    11,     0,
    42,    43,     0,    43,     0,    40,     0,    15,    42,    11,
     0,    16,    42,    11,     0,    14,    43,    11,     0,    12,
    10,    35,    11,    43,    11,     0,    13,    10,    35,    11,
    43,    11,     0,    50,     0,    48,     0,    15,    47,    11,
     0,    12,    10,    35,    11,    46,    11,     0,    48,     0,
    50,     0,    45,     0,    15,    46,    45,    11,     0,    44,
     0,    47,    44,     0,    17,    43,    49,    11,     0,    15,
    49,    11,     0,    49,    50,     0,    50,     0,    40,     0,
    14,    40,    11,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   131,   133,   133,   139,   140,   142,   144,   146,   148,   167,
   168,   172,   173,   177,   178,   181,   188,   189,   192,   195,
   198,   199,   203,   206,   207,   211,   212,   216,   217,   220,
   220,   228,   229,   232,   233,   234,   235,   236,   255,   258,
   259,   260,   261,   267,   268,   270,   271,   273,   274,   276,
   278,   279,   280,   282,   283
};

static const char * const yytname[] = {   "$","error","$illegal.","DEFINE","OPERATOR",
"DOMAIN","PROBLEM","PARAMETERS","PRECONDITION","EFFECT","LP","RP","FORALL","EXISTS",
"NOT","AND","OR","WHEN","CONSTANT","VARIABLE","INITS","GOALS","ucpopInput","problem",
"@1","problems","initials","goals","operator","@2","operators","params","parameters",
"typedvar","parameter","typedvarplus","effectspec","preconds","argument","arguments",
"term","@3","GDPlus","GD","effect","ueffect","ueffects","effects","ceffect",
"peffects","peffect",""
};
#endif

static const short yyr1[] = {     0,
    22,    24,    23,    25,    25,    26,    27,    29,    28,    30,
    30,    31,    31,    32,    32,    33,    34,    34,    35,    35,
    35,    35,    36,    37,    37,    38,    38,    39,    39,    41,
    40,    42,    42,    43,    43,    43,    43,    43,    43,    44,
    44,    44,    44,    45,    45,    46,    46,    47,    47,    48,
    49,    49,    49,    50,    50
};

static const short yyr2[] = {     0,
     2,     0,     8,     2,     1,     2,     2,     0,     9,     2,
     1,     0,     4,     0,     2,     4,     1,     1,     2,     2,
     1,     1,     2,     0,     2,     1,     1,     0,     2,     0,
     5,     2,     1,     1,     3,     3,     3,     6,     6,     1,
     1,     3,     6,     1,     1,     1,     4,     1,     2,     4,
     3,     2,     1,     1,     3
};

static const short yydefact[] = {     0,
     0,    11,     0,     0,     0,     5,     1,    10,     8,     0,
     0,     4,     0,     2,    12,     0,     0,    24,     0,    14,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    34,    25,     0,     0,     0,     0,     0,     0,    54,
     6,    41,    40,     0,     0,     0,    13,    17,    18,    15,
    30,     0,     0,     0,     0,    33,     0,    23,     9,     0,
     0,    48,     0,     0,     7,     3,     0,    28,    22,    21,
     0,     0,    37,    35,    32,    36,     0,    55,    42,    49,
     0,     0,    53,     0,     0,     0,    20,    19,     0,     0,
     0,    50,    52,    16,    31,    26,    27,    29,     0,     0,
     0,    46,     0,    44,    45,    51,    38,    39,     0,    43,
     0,    47,     0,     0,     0
};

static const short yydefgoto[] = {   113,
     6,    16,     7,    24,    45,     2,    13,     3,    18,    25,
    70,    50,    71,    35,    22,    98,    85,    40,    68,    55,
    56,    41,   102,   103,    63,    42,    82,    43
};

static const short yypact[] = {     0,
     3,-32768,    14,    21,     7,-32768,    26,-32768,-32768,    33,
    38,-32768,    46,-32768,    54,    51,    53,    62,    56,-32768,
    99,    73,    69,    50,     9,    70,    83,   100,    99,    99,
    99,-32768,-32768,    69,   110,   113,   114,    69,    99,-32768,
-32768,-32768,-32768,    99,   115,   107,-32768,-32768,-32768,-32768,
-32768,    -5,    -5,   116,    85,-32768,    92,-32768,-32768,    -5,
   117,-32768,    63,    11,-32768,-32768,   111,-32768,-32768,-32768,
    35,    39,-32768,-32768,-32768,-32768,    45,-32768,-32768,-32768,
    11,   106,-32768,   118,    48,    99,-32768,-32768,    99,    75,
   108,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   120,   121,
    75,-32768,   122,-32768,-32768,-32768,-32768,-32768,    77,-32768,
   123,-32768,   135,   136,-32768
};

static const short yypgoto[] = {-32768,
   130,-32768,-32768,-32768,-32768,   137,-32768,-32768,-32768,-32768,
   -24,-32768,   -23,-32768,-32768,-32768,-32768,   -21,-32768,   112,
   -17,   -32,    29,    40,-32768,   -66,    58,   -49
};


#define	YYLAST		143


static const short yytable[] = {    32,
    49,    58,     1,    33,    46,    62,     4,    32,    32,    32,
     4,    54,    10,    69,    83,    61,     5,    32,    46,    47,
    26,    64,    32,   104,    37,    81,    65,    48,    11,    72,
    80,    83,    93,    32,   104,    32,    77,    75,     9,    75,
   105,    93,   104,    10,    46,    86,    88,    88,    46,    89,
    14,   105,    88,    87,    46,    90,    15,    87,    95,   105,
    17,    19,    20,    87,    32,    96,    97,    32,    99,    21,
    44,   100,    26,    79,    36,    23,    37,    38,    26,    39,
    36,    34,    37,    38,    26,    39,    26,    51,    37,   101,
    37,    39,    52,    39,    26,    74,    27,    28,    29,    30,
    31,    26,    76,    27,    28,    29,    30,    31,    26,    53,
    27,    28,    29,    30,    31,    26,    92,    26,   106,    37,
    59,    37,    60,    26,    67,    66,    73,    78,    94,    84,
   107,   108,   110,   112,   114,   115,    12,   111,    91,     8,
   109,     0,    57
};

static const short yycheck[] = {    21,
    25,    34,     3,    21,    10,    38,     4,    29,    30,    31,
     4,    29,     6,    19,    64,    37,     3,    39,    10,    11,
    10,    39,    44,    90,    14,    15,    44,    19,     3,    53,
    63,    81,    82,    55,   101,    57,    60,    55,    18,    57,
    90,    91,   109,     6,    10,    11,    71,    72,    10,    11,
    18,   101,    77,    19,    10,    11,    11,    19,    11,   109,
     7,    11,    10,    19,    86,    18,    19,    89,    86,     8,
    21,    89,    10,    11,    12,    20,    14,    15,    10,    17,
    12,     9,    14,    15,    10,    17,    10,    18,    14,    15,
    14,    17,    10,    17,    10,    11,    12,    13,    14,    15,
    16,    10,    11,    12,    13,    14,    15,    16,    10,    10,
    12,    13,    14,    15,    16,    10,    11,    10,    11,    14,
    11,    14,    10,    10,    18,    11,    11,    11,    11,    19,
    11,    11,    11,    11,     0,     0,     7,   109,    81,     3,
   101,    -1,    31
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/uns/lib/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#define YYLEX		yylex(&yylval, &yylloc)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_bcopy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 184 "/uns/lib/bison.simple"
int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 2:
#line 133 "ucpop.y"
{strcpy(namebuf1, yyvsp[0].ident);;
    break;}
case 3:
#line 134 "ucpop.y"
{
//	cerr << "Problem: " << ($6)->GetList() << ($7)->GetList() << endl;
	planner.AddProblem(*new Problem(namebuf1, *(yyvsp[-2].node), *(yyvsp[-1].node)));
;
    break;}
case 6:
#line 142 "ucpop.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 7:
#line 144 "ucpop.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 8:
#line 146 "ucpop.y"
{stepName=parser.symtab.AddOp(yyvsp[0].ident); 
				    /* have to do this,  otherwise name will be corrupted */;
    break;}
case 9:
#line 149 "ucpop.y"
{ 
//  cerr << "HERE::::::::"; parser.PrintNodes(*($7)); cerr << endl;
  tmpNode=new Node(stepbuf, stepName);
  /* have to make a new list and pass it,  because the list is mangled later.*/
  parser.CreateOperator(*tmpNode, 
			typedVarList + *(yyvsp[-2].nodelist), 
			*(yyvsp[-1].nodelist), 
			scope, 
			numParams);
//  parser.PrintNodes(typedVarList + *($7));
  /* reset all global variables */
  typedVarList.FreeUp();
  stepbuf.Reset(); 
  buf.Reset();
  numParams=0;
  scope=0;
;
    break;}
case 15:
#line 178 "ucpop.y"
{ numParams++; scope++; ;
    break;}
case 16:
#line 182 "ucpop.y"
{ 
	  yyval.sym=parser.symtab.FindVar(yyvsp[-1].ident);
	  typedVar = new Node(parser.symtab.FindPred(yyvsp[-2].ident), yyval.sym);
	;
    break;}
case 17:
#line 188 "ucpop.y"
{tmp=parser.symtab.AddVar(yyvsp[0].ident); stepbuf+=tmp;;
    break;}
case 18:
#line 189 "ucpop.y"
{stepbuf+=yyvsp[0].sym; typedVarList += typedVar; ;
    break;}
case 19:
#line 192 "ucpop.y"
{ univVarList += yyvsp[0].sym; 
				       univTypeVarList += typedVar; 
				     ;
    break;}
case 20:
#line 195 "ucpop.y"
{ univVarList += parser.symtab.FindVar(yyvsp[0].ident); 
				  cerr << "*" << parser.symtab.FindVar(yyvsp[0].ident) << "*";
				;
    break;}
case 21:
#line 198 "ucpop.y"
{ univVarList += yyvsp[0].sym; univTypeVarList += typedVar; ;
    break;}
case 22:
#line 199 "ucpop.y"
{ univVarList += parser.symtab.FindVar(yyvsp[0].ident); 
/*		     cerr << "*" << parser.symtab.FindVar($1) << "*"; */
		   ;
    break;}
case 23:
#line 203 "ucpop.y"
{yyval.nodelist=new List<Node>; *(yyval.nodelist)+= *(yyvsp[0].node);;
    break;}
case 24:
#line 206 "ucpop.y"
{ yyval.nodelist=NULL; ;
    break;}
case 25:
#line 207 "ucpop.y"
{ yyval.nodelist=new List<Node>; 
			    *(yyval.nodelist)+= *(yyvsp[0].node); ;
    break;}
case 26:
#line 211 "ucpop.y"
{ tmp=parser.symtab.FindConst(yyvsp[0].ident); buf+=tmp; ;
    break;}
case 27:
#line 212 "ucpop.y"
{ tmp=parser.symtab.LookupVar(yyvsp[0].ident); buf+=tmp; ;
    break;}
case 30:
#line 220 "ucpop.y"
{strcpy(namebuf2, yyvsp[0].ident);;
    break;}
case 31:
#line 221 "ucpop.y"
{ 
	    tmpNode=new Node(buf, parser.symtab.FindPred(namebuf2));
            buf.Reset(); 
	    yyval.node=tmpNode;
	  ;
    break;}
case 32:
#line 228 "ucpop.y"
{*(yyvsp[-1].nodelist)+= *(yyvsp[0].node); yyval.nodelist=yyvsp[-1].nodelist;;
    break;}
case 33:
#line 229 "ucpop.y"
{yyval.nodelist=new List<Node>; *(yyval.nodelist)+= *(yyvsp[0].node);;
    break;}
case 34:
#line 232 "ucpop.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 35:
#line 233 "ucpop.y"
{yyval.node=new Node(*(yyvsp[-1].nodelist), And);;
    break;}
case 36:
#line 234 "ucpop.y"
{yyval.node=new Node(*(yyvsp[-1].nodelist), Or);;
    break;}
case 37:
#line 235 "ucpop.y"
{yyval.node=new Node(*(yyvsp[-1].node), Not);;
    break;}
case 38:
#line 236 "ucpop.y"
{	  
	  List<Node> tmp;
	  tmp += yyvsp[-1].node;
	  // special treatment for untyped variables
	  // all univTypeVarList elems are in univVarList,  but no v.v.
	  snext=univVarList;
	  tnext=univTypeVarList;
	  SDOLIST(var, snext) {
	    tnext.Reset();
	    DOLIST(typevar, tnext) {
	      if (var != typevar->GetVariable())
		 univTypeVarList += new Node(0, var);
	    }
	  }
	  // now univTypeVarList should have no duplicates!
	  yyval.node=new Node(tmp, univTypeVarList, Universal);
	  univVarList.FreeUp();
	  univTypeVarList.FreeUp();
	;
    break;}
case 39:
#line 255 "ucpop.y"
{cerr << "Not yet implemented\n";;
    break;}
case 40:
#line 258 "ucpop.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 41:
#line 259 "ucpop.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 42:
#line 260 "ucpop.y"
{yyval.node=new Node(*(yyvsp[-1].nodelist), And);;
    break;}
case 43:
#line 261 "ucpop.y"
{
	  yyval.node=new Node(univVarList, univTypeVarList + *(yyvsp[-1].nodelist), scope, numParams);
	  univVarList.FreeUp();
	  univTypeVarList.FreeUp();
	;
    break;}
case 44:
#line 267 "ucpop.y"
{ yyval.node=yyvsp[0].node; ;
    break;}
case 45:
#line 268 "ucpop.y"
{ yyval.node=yyvsp[0].node; ;
    break;}
case 46:
#line 270 "ucpop.y"
{ yyval.nodelist=new List<Node>; *(yyval.nodelist)+= yyvsp[0].node;;
    break;}
case 47:
#line 271 "ucpop.y"
{ *(yyval.nodelist)+=new Node(*(yyvsp[-2].nodelist), And); ;
    break;}
case 48:
#line 273 "ucpop.y"
{ yyval.nodelist=new List<Node>; *(yyval.nodelist)+= *(yyvsp[0].node); ;
    break;}
case 49:
#line 274 "ucpop.y"
{ *(yyvsp[-1].nodelist) += *(yyvsp[0].node); yyval.nodelist=yyvsp[-1].nodelist; ;
    break;}
case 50:
#line 276 "ucpop.y"
{ yyval.node=new Node(yyvsp[-2].node, yyvsp[-1].nodelist); ;
    break;}
case 51:
#line 278 "ucpop.y"
{ yyval.nodelist=yyvsp[-1].nodelist; ;
    break;}
case 52:
#line 279 "ucpop.y"
{ *(yyvsp[-1].nodelist)+= yyvsp[0].node; yyval.nodelist=yyvsp[-1].nodelist; ;
    break;}
case 53:
#line 280 "ucpop.y"
{ yyval.nodelist=new List<Node>; *(yyval.nodelist)+= (yyvsp[0].node); ;
    break;}
case 54:
#line 282 "ucpop.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 55:
#line 283 "ucpop.y"
{(yyvsp[-1].node)->Negate(); yyval.node=yyvsp[-1].node;;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 465 "/uns/lib/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 285 "ucpop.y"

#include "lex.yy.cc"




