%{
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


%}

%union {
  char *ident;
  int  keyword;
  Node *node;
  List<Node>* nodelist;
  Sym sym;
}



%token <keyword> DEFINE OPERATOR DOMAIN PROBLEM
%token <keyword> PARAMETERS PRECONDITION EFFECT
%token <keyword> LP RP
%token <keyword> FORALL EXISTS NOT AND OR WHEN
%token <ident> CONSTANT VARIABLE
%token <keyword> INITS GOALS

%type <ident> argument
%type <node> term
%type <node> GD
%type <nodelist> GDPlus
%type <nodelist> preconds
%type <node> ueffect
%type <nodelist> ueffects
%type <node> peffect
%type <nodelist> peffects
%type <node> ceffect
%type <sym> typedvar
%type <nodelist> effects
%type <node> effect
%type <nodelist> effectspec
%type <node> initials
%type <node> goals

/* define (operator constant) 
	[:parameters(parameters*)] 
	[:precondition GD]
	:effect effect)
*/

%% /* rules */

ucpopInput: operators problems
	;
problem: DEFINE PROBLEM CONSTANT {strcpy(namebuf1, $3);} RP initials goals RP 
{
//	cerr << "Problem: " << ($6)->GetList() << ($7)->GetList() << endl;
	planner.AddProblem(*new Problem(namebuf1, *($6), *($7)));
}
	;	
problems: problems problem
	| problem
	;
initials: INITS effect {$$=$2;}
	;
goals:    GOALS GD {$$=$2;}
	;
operator: DEFINE OPERATOR CONSTANT {stepName=parser.symtab.AddOp($3); 
				    /* have to do this,  otherwise name will be corrupted */}
	RP params preconds effectspec RP 
{ 
//  cerr << "HERE::::::::"; parser.PrintNodes(*($7)); cerr << endl;
  tmpNode=new Node(stepbuf, stepName);
  /* have to make a new list and pass it,  because the list is mangled later.*/
  parser.CreateOperator(*tmpNode, 
			typedVarList + *($7), 
			*($8), 
			scope, 
			numParams);
//  parser.PrintNodes(typedVarList + *($7));
  /* reset all global variables */
  typedVarList.FreeUp();
  stepbuf.Reset(); 
  buf.Reset();
  numParams=0;
  scope=0;
}
	;
operators: operators operator
	| operator
	;

/* [:parameters(parameters*)] */
params	: /* empty */
	| PARAMETERS LP parameters RP
	;

/* left recursive */
parameters : /* empty */
	| parameters parameter { numParams++; scope++; }
	;
/* typed-var ::= (constant variable) */
typedvar : LP CONSTANT VARIABLE RP 
	{ 
	  $$=parser.symtab.FindVar($3);
	  typedVar = new Node(parser.symtab.FindPred($2), $$);
	}
	;	
/* parameter ::= constant | typedvar */
parameter : VARIABLE {tmp=parser.symtab.AddVar($1); stepbuf+=tmp;}
	| typedvar {stepbuf+=$1; typedVarList += typedVar; }
	;
/* rule used by forall's */
typedvarplus : typedvarplus typedvar { univVarList += $2; 
				       univTypeVarList += typedVar; 
				     }
        | typedvarplus VARIABLE { univVarList += parser.symtab.FindVar($2); 
				  cerr << "*" << parser.symtab.FindVar($2) << "*";
				}
	| typedvar { univVarList += $1; univTypeVarList += typedVar; }
        | VARIABLE { univVarList += parser.symtab.FindVar($1); 
/*		     cerr << "*" << parser.symtab.FindVar($1) << "*"; */
		   }
   	;
effectspec: EFFECT effect {$$=new List<Node>; *($$)+= *($2);}
	;
/* [:precondition GD] */
preconds: /* empty */ { $$=NULL; }
	| PRECONDITION GD { $$=new List<Node>; 
			    *($$)+= *($2); }
	;

argument: CONSTANT { tmp=parser.symtab.FindConst($1); buf+=tmp; }
	| VARIABLE { tmp=parser.symtab.LookupVar($1); buf+=tmp; }
	;

/* argument* */
arguments: /* empty */ 
	| arguments argument
	;
/* term ::= (constant argument*) */
term	: LP CONSTANT {strcpy(namebuf2, $2);} arguments RP  
   	  { 
	    tmpNode=new Node(buf, parser.symtab.FindPred(namebuf2));
            buf.Reset(); 
	    $$=tmpNode;
	  }	  
    	;

GDPlus	: GDPlus GD {*($1)+= *($2); $$=$1;}
	| GD {$$=new List<Node>; *($$)+= *($1);}
	;

GD	: term {$$=$1;}
      	| AND GDPlus RP {$$=new Node(*($2), And);}
	| OR GDPlus RP {$$=new Node(*($2), Or);}
	| NOT GD RP {$$=new Node(*($2), Not);}
	| FORALL LP typedvarplus RP GD RP {	  
	  List<Node> tmp;
	  tmp += $5;
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
	  $$=new Node(tmp, univTypeVarList, Universal);
	  univVarList.FreeUp();
	  univTypeVarList.FreeUp();
	}
	| EXISTS LP typedvarplus RP GD RP {cerr << "Not yet implemented\n";}
	;

effect  : peffect {$$=$1;}
	| ceffect {$$=$1;}
	| AND effects RP {$$=new Node(*($2), And);}
   	| FORALL LP typedvarplus RP ueffects RP {
	  $$=new Node(univVarList, univTypeVarList + *($5), scope, numParams);
	  univVarList.FreeUp();
	  univTypeVarList.FreeUp();
	}
	;
ueffect : ceffect { $$=$1; }
	| peffect { $$=$1; }
	;
ueffects: ueffect { $$=new List<Node>; *($$)+= $1;}
	| AND ueffects ueffect RP { *($$)+=new Node(*($2), And); }
	;
effects : effect { $$=new List<Node>; *($$)+= *($1); }
   	| effects effect { *($1) += *($2); $$=$1; }
	;
ceffect : WHEN GD peffects RP { $$=new Node($2, $3); }
	;
peffects : AND peffects RP { $$=$2; }
	| peffects peffect { *($1)+= $2; $$=$1; }
	| peffect { $$=new List<Node>; *($$)+= ($1); }
	;
peffect : term {$$=$1;}
	| NOT term RP {($2)->Negate(); $$=$2;}
	;
%%
#include "lex.yy.cc"




