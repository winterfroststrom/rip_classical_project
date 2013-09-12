
# line 2 "ucpop.y"
/* -*- mode: fundamental -*- */
#include "list.h"
#include "slist.h"
#include "objects.h"
#include "symtab.h"
#include "logic.h"
#include "parser.h"
#include "planner.h"

/* prevent mangling of names */
extern "C" {
  void yyerror(char*);
  int yyparse(void);
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



# line 81 "ucpop.y"
typedef union  {
  char *ident;
  int  keyword;
  Node *node;
  List<Node>* nodelist;
  Sym sym;
} YYSTYPE;
# define DEFINE 257
# define OPERATOR 258
# define DOMAIN 259
# define PROBLEM 260
# define PARAMETERS 261
# define PRECONDITION 262
# define EFFECT 263
# define LP 264
# define RP 265
# define FORALL 266
# define EXISTS 267
# define NOT 268
# define AND 269
# define OR 270
# define WHEN 271
# define CONSTANT 272
# define VARIABLE 273
# define INITS 274
# define GOALS 275
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256

# line 277 "ucpop.y"

#include "lex.yy.cc"




short yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 56
# define YYLAST 210
short yyact[]={

  36,  80,  44,  45,  43,  41,  42,  36,  79,  44,
  45,  43,  41,  42,  36,  68,  32,  27,  34,  31,
  36,  35,  44,  45,  43,  41,  42, 102,  67,  93,
  67,  92,  67,  87, 103, 104,  94,  86, 113,  86,
 111,  86,  67,  63,  22,  36,  67,  32,  84,  34,
  31,  65,  35,  36,  38,  72,  54,  34,  97,  36,
  35, 110,  14,  34,  13,  36,  35,  36, 100,  34,
  75,  34,  36,  88, 108, 107,  34,  81,  73,  55,
  47,  18,  17,  62,  61,  36,  51,  25,  24,  20,
   9,  12,  12,   9,  11,   8,   4,  29,  30,  96,
  33,  95,  74,  70,  58,   7,  71,  28,  77,  57,
   3,  10,  91,   6,  64,  46,  19,  15,  16,   5,
   2,   1,  26,  21,  37,  40,  49,  23,  40,  39,
 101,   0,  48,   0,   0,  52,  40,   0,   0,  50,
  53,   0,  40,  40,  40,   0,  56,   0,  60,   0,
   0,  76,  59,  66,   0,   0,   0,  69,  40,   0,
  40,   0,  78,   0,  78,  82,  83,   0,   0,   0,
   0,   0,  89,  76,   0,   0,   0,  85,  90,   0,
   0,   0,   0,   0,   0,  99,  98,   0,  89,  85,
  85,   0,   0,  40,  40,  99,  98, 105, 106, 109,
   0,   0,   0,   0,   0,   0,   0,  99,  98, 112 };
short yypact[]={

-161,-1000,-162,-1000,-165,-163,-1000,-1000,-168,-208,
-1000,-169,-210,-1000,-1000,-183,-184,-172,-230,-174,
-177,-258,-219,-209,-244,-1000,-185,-244,-1000,-1000,
-1000,-219,-178,-1000,-179,-244,-216,-186,-219,-1000,
-1000,-244,-244,-244,-180,-181,-222,-1000,-1000,-250,
-1000,-218,-187,-199,-1000,-1000,-1000,-257,-1000,-264,
-188,-218,-218,-1000,-1000,-1000,-1000,-224,-1000,-1000,
-232,-1000,-1000,-1000,-192,-199,-1000,-1000,-1000,-1000,
-1000,-1000,-234,-236,-237,-1000,-1000,-211,-1000,-1000,
-197,-238,-244,-244,-190,-191,-1000,-211,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-204,-225,-1000,-1000,-205,
-1000,-1000,-227,-1000 };
short yypgo[]={

   0, 130, 100, 104, 109, 127,  99, 101,  97, 102,
  98, 106, 126, 107, 124, 123, 122, 121, 120, 119,
 105, 118, 110, 117, 116, 115, 114, 103, 112, 108 };
short yyr1[]={

   0,  17,  21,  20,  19,  19,  15,  16,  23,  22,
  18,  18,  24,  24,  25,  25,  11,  26,  26,  27,
  27,  27,  27,  14,   5,   5,   1,   1,  28,  28,
  29,   2,   4,   4,   3,   3,   3,   3,   3,   3,
  13,  13,  13,  13,   6,   6,   7,   7,  12,  12,
  10,   9,   9,   9,   8,   8 };
short yyr2[]={

   0,   2,   0,   8,   2,   1,   2,   2,   0,   9,
   2,   1,   0,   4,   0,   2,   4,   1,   1,   2,
   2,   1,   1,   2,   0,   2,   1,   1,   0,   2,
   0,   5,   2,   1,   1,   3,   3,   3,   6,   6,
   1,   1,   3,   6,   1,   1,   1,   4,   1,   2,
   4,   3,   2,   1,   1,   3 };
short yychk[]={

-1000, -17, -18, -22, 257, -19, -22, -20, 257, 258,
 -20, 257, 260, 272, 272, -23, -21, 265, 265, -24,
 261, -15, 274,  -5, 262, 264, -16, 275, -13,  -8,
 -10, 269, 266,  -2, 268, 271, 264, -14, 263,  -3,
  -2, 269, 270, 268, 266, 267, -25, 265,  -3, -12,
 -13, 264,  -2,  -3, 272, 265, -13,  -4,  -3,  -4,
  -3, 264, 264, 265, -26, 273, -11, 264, 265, -13,
 -27, -11, 273, 265,  -9, 269,  -8, -29,  -3, 265,
 265, 265, -27, -27, 272, -11, 273, 265, 265,  -8,
  -9, -28, 265, 265, 273,  -7,  -6, 269, -10,  -8,
 265,  -1, 265, 272, 273,  -3,  -3, 265, 265,  -7,
 265, 265,  -6, 265 };
short yydef[]={

   0,  -2,   0,  11,   0,   1,  10,   5,   0,   0,
   4,   0,   0,   8,   2,   0,   0,  12,   0,  24,
   0,   0,   0,   0,   0,  14,   0,   0,   6,  40,
  41,   0,   0,  54,   0,   0,   0,   0,   0,  25,
  34,   0,   0,   0,   0,   0,   0,   3,   7,   0,
  48,   0,   0,   0,  30,   9,  23,   0,  33,   0,
   0,   0,   0,  13,  15,  17,  18,   0,  42,  49,
   0,  21,  22,  55,   0,   0,  53,  28,  32,  35,
  36,  37,   0,   0,   0,  19,  20,   0,  50,  52,
   0,   0,   0,   0,   0,   0,  46,   0,  44,  45,
  51,  29,  31,  26,  27,   0,   0,  16,  43,   0,
  38,  39,   0,  47 };
#ifndef lint
static char yaccpar_sccsid[] = "@(#)yaccpar	4.1	(Berkeley)	2/11/83";
#endif

#
# define YYFLAG -1000
# define YYERROR goto yyerrlab
# define YYACCEPT return(0)
# define YYABORT return(1)

/*	parser for yacc output	*/

#ifdef YYDEBUG
int yydebug = 0; /* 1 for debugging */
#endif
YYSTYPE yyv[YYMAXDEPTH]; /* where the values are stored */
int yychar = -1; /* current input token number */
int yynerrs = 0;  /* number of errors */
short yyerrflag = 0;  /* error recovery flag */

yyparse() {

	short yys[YYMAXDEPTH];
	short yyj, yym;
	register YYSTYPE *yypvt;
	register short yystate, *yyps, yyn;
	register YYSTYPE *yypv;
	register short *yyxi;

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyps= &yys[-1];
	yypv= &yyv[-1];

 yystack:    /* put a state and value onto the stack */

#ifdef YYDEBUG
	if( yydebug  ) printf( "state %d, char 0%o\n", yystate, yychar );
#endif
		if( ++yyps> &yys[YYMAXDEPTH] ) { yyerror( "yacc stack overflow" ); return(1); }
		*yyps = yystate;
		++yypv;
		*yypv = yyval;

 yynewstate:

	yyn = yypact[yystate];

	if( yyn<= YYFLAG ) goto yydefault; /* simple state */

	if( yychar<0 ) if( (yychar=yylex())<0 ) yychar=0;
	if( (yyn += yychar)<0 || yyn >= YYLAST ) goto yydefault;

	if( yychk[ yyn=yyact[ yyn ] ] == yychar ){ /* valid shift */
		yychar = -1;
		yyval = yylval;
		yystate = yyn;
		if( yyerrflag > 0 ) --yyerrflag;
		goto yystack;
		}

 yydefault:
	/* default state action */

	if( (yyn=yydef[yystate]) == -2 ) {
		if( yychar<0 ) if( (yychar=yylex())<0 ) yychar = 0;
		/* look through exception table */

		for( yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=yystate) ; yyxi += 2 ) ; /* VOID */

		while( *(yyxi+=2) >= 0 ){
			if( *yyxi == yychar ) break;
			}
		if( (yyn = yyxi[1]) < 0 ) return(0);   /* accept */
		}

	if( yyn == 0 ){ /* error */
		/* error ... attempt to resume parsing */

		switch( yyerrflag ){

		case 0:   /* brand new error */

			yyerror( "syntax error" );
		yyerrlab:
			++yynerrs;

		case 1:
		case 2: /* incompletely recovered error ... try again */

			yyerrflag = 3;

			/* find a state where "error" is a legal shift action */

			while ( yyps >= yys ) {
			   yyn = yypact[*yyps] + YYERRCODE;
			   if( yyn>= 0 && yyn < YYLAST && yychk[yyact[yyn]] == YYERRCODE ){
			      yystate = yyact[yyn];  /* simulate a shift of "error" */
			      goto yystack;
			      }
			   yyn = yypact[*yyps];

			   /* the current yyps has no shift onn "error", pop stack */

#ifdef YYDEBUG
			   if( yydebug ) printf( "error recovery pops state %d, uncovers %d\n", *yyps, yyps[-1] );
#endif
			   --yyps;
			   --yypv;
			   }

			/* there is no state on the stack with an error shift ... abort */

	yyabort:
			return(1);


		case 3:  /* no shift yet; clobber input char */

#ifdef YYDEBUG
			if( yydebug ) printf( "error recovery discards char %d\n", yychar );
#endif

			if( yychar == 0 ) goto yyabort; /* don't discard EOF, quit */
			yychar = -1;
			goto yynewstate;   /* try again in the same state */

			}

		}

	/* reduction by production yyn */

#ifdef YYDEBUG
		if( yydebug ) printf("reduce %d\n",yyn);
#endif
		yyps -= yyr2[yyn];
		yypvt = yypv;
		yypv -= yyr2[yyn];
		yyval = yypv[1];
		yym=yyn;
			/* consult goto table to find next state */
		yyn = yyr1[yyn];
		yyj = yypgo[yyn] + *yyps + 1;
		if( yyj>=YYLAST || yychk[ yystate = yyact[yyj] ] != -yyn ) yystate = yyact[yypgo[yyn]];
		switch(yym){
			
case 2:
# line 125 "ucpop.y"
{strcpy(namebuf1, yypvt[-0].ident);} break;
case 3:
# line 126 "ucpop.y"
{
//	cerr << "Problem: " << (yypvt[-2].node)->GetList() << (yypvt[-1].node)->GetList() << endl;
	planner.AddProblem(*new Problem(namebuf1, *(yypvt[-2].node), *(yypvt[-1].node)));
} break;
case 6:
# line 134 "ucpop.y"
{yyval.node=yypvt[-0].node;} break;
case 7:
# line 136 "ucpop.y"
{yyval.node=yypvt[-0].node;} break;
case 8:
# line 138 "ucpop.y"
{stepName=parser.symtab.AddOp(yypvt[-0].ident); 
				    /* have to do this,  otherwise name will be corrupted */} break;
case 9:
# line 141 "ucpop.y"
{ 
//  cerr << "HERE::::::::"; parser.PrintNodes(*(yypvt[-2].nodelist)); cerr << endl;
  tmpNode=new Node(stepbuf, stepName);
  /* have to make a new list and pass it,  because the list is mangled later.*/
  parser.CreateOperator(*tmpNode, 
			typedVarList + *(yypvt[-2].nodelist), 
			*(yypvt[-1].nodelist), 
			scope, 
			numParams);
//  parser.PrintNodes(typedVarList + *(yypvt[-2].nodelist));
  /* reset all global variables */
  typedVarList.FreeUp();
  stepbuf.Reset(); 
  buf.Reset();
  numParams=0;
  scope=0;
} break;
case 15:
# line 170 "ucpop.y"
{ numParams++; scope++; } break;
case 16:
# line 174 "ucpop.y"
{ 
	  yyval.sym=parser.symtab.FindVar(yypvt[-1].ident);
	  typedVar = new Node(parser.symtab.FindPred(yypvt[-2].ident), yyval.sym);
	} break;
case 17:
# line 180 "ucpop.y"
{tmp=parser.symtab.AddVar(yypvt[-0].ident); stepbuf+=tmp;} break;
case 18:
# line 181 "ucpop.y"
{stepbuf+=yypvt[-0].sym; typedVarList += typedVar; } break;
case 19:
# line 184 "ucpop.y"
{ univVarList += yypvt[-0].sym; 
				       univTypeVarList += typedVar; 
				     } break;
case 20:
# line 187 "ucpop.y"
{ univVarList += parser.symtab.FindVar(yypvt[-0].ident); 
				  cerr << "*" << parser.symtab.FindVar(yypvt[-0].ident) << "*";
				} break;
case 21:
# line 190 "ucpop.y"
{ univVarList += yypvt[-0].sym; univTypeVarList += typedVar; } break;
case 22:
# line 191 "ucpop.y"
{ univVarList += parser.symtab.FindVar(yypvt[-0].ident); 
		     cerr << "*" << parser.symtab.FindVar(yypvt[-0].ident) << "*";
		   } break;
case 23:
# line 195 "ucpop.y"
{yyval.nodelist=new List<Node>; *(yyval.nodelist)+= *(yypvt[-0].node);} break;
case 24:
# line 198 "ucpop.y"
{ yyval.nodelist=NULL; } break;
case 25:
# line 199 "ucpop.y"
{ yyval.nodelist=new List<Node>; 
			    *(yyval.nodelist)+= *(yypvt[-0].node); } break;
case 26:
# line 203 "ucpop.y"
{ tmp=parser.symtab.FindConst(yypvt[-0].ident); buf+=tmp; } break;
case 27:
# line 204 "ucpop.y"
{ tmp=parser.symtab.LookupVar(yypvt[-0].ident); buf+=tmp; } break;
case 30:
# line 212 "ucpop.y"
{strcpy(namebuf2, yypvt[-0].ident);} break;
case 31:
# line 213 "ucpop.y"
{ 
	    tmpNode=new Node(buf, parser.symtab.FindPred(namebuf2));
            buf.Reset(); 
	    yyval.node=tmpNode;
	  } break;
case 32:
# line 220 "ucpop.y"
{*(yypvt[-1].nodelist)+= *(yypvt[-0].node); yyval.nodelist=yypvt[-1].nodelist;} break;
case 33:
# line 221 "ucpop.y"
{yyval.nodelist=new List<Node>; *(yyval.nodelist)+= *(yypvt[-0].node);} break;
case 34:
# line 224 "ucpop.y"
{yyval.node=yypvt[-0].node;} break;
case 35:
# line 225 "ucpop.y"
{yyval.node=new Node(*(yypvt[-1].nodelist), And);} break;
case 36:
# line 226 "ucpop.y"
{yyval.node=new Node(*(yypvt[-1].nodelist), Or);} break;
case 37:
# line 227 "ucpop.y"
{yyval.node=new Node(*(yypvt[-1].node), Not);} break;
case 38:
# line 228 "ucpop.y"
{	  
	  List<Node> tmp;
	  tmp += yypvt[-1].node;
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
	} break;
case 39:
# line 247 "ucpop.y"
{cerr << "Not yet implemented\n";} break;
case 40:
# line 250 "ucpop.y"
{yyval.node=yypvt[-0].node;} break;
case 41:
# line 251 "ucpop.y"
{yyval.node=yypvt[-0].node;} break;
case 42:
# line 252 "ucpop.y"
{yyval.node=new Node(*(yypvt[-1].nodelist), And);} break;
case 43:
# line 253 "ucpop.y"
{
	  yyval.node=new Node(univVarList, univTypeVarList + *(yypvt[-1].nodelist), scope, numParams);
	  univVarList.FreeUp();
	  univTypeVarList.FreeUp();
	} break;
case 44:
# line 259 "ucpop.y"
{ yyval.node=yypvt[-0].node; } break;
case 45:
# line 260 "ucpop.y"
{ yyval.node=yypvt[-0].node; } break;
case 46:
# line 262 "ucpop.y"
{ yyval.nodelist=new List<Node>; *(yyval.nodelist)+= yypvt[-0].node;} break;
case 47:
# line 263 "ucpop.y"
{ *(yyval.nodelist)+=new Node(*(yypvt[-2].nodelist), And); } break;
case 48:
# line 265 "ucpop.y"
{ yyval.nodelist=new List<Node>; *(yyval.nodelist)+= *(yypvt[-0].node); } break;
case 49:
# line 266 "ucpop.y"
{ *(yypvt[-1].nodelist) += *(yypvt[-0].node); yyval.nodelist=yypvt[-1].nodelist; } break;
case 50:
# line 268 "ucpop.y"
{ yyval.node=new Node(yypvt[-2].node, yypvt[-1].nodelist); } break;
case 51:
# line 270 "ucpop.y"
{ yyval.nodelist=yypvt[-1].nodelist; } break;
case 52:
# line 271 "ucpop.y"
{ *(yypvt[-1].nodelist)+= yypvt[-0].node; yyval.nodelist=yypvt[-1].nodelist; } break;
case 53:
# line 272 "ucpop.y"
{ yyval.nodelist=new List<Node>; *(yyval.nodelist)+= (yypvt[-0].node); } break;
case 54:
# line 274 "ucpop.y"
{yyval.node=yypvt[-0].node;} break;
case 55:
# line 275 "ucpop.y"
{(yypvt[-1].node)->Negate(); yyval.node=yypvt[-1].node;} break; 
		}
		goto yystack;  /* stack new state and value */

	}
