%{
/* $Log: ucpop.l,v $
 * Revision 1.1  1993/07/04  05:09:48  ctkwok
 * Initial revision
 * */
/* UCPOP Lexical Driver
 * Is included by the parser,  ucpop.y
 */
/* 
 * Would prefer using FLEX scan generator
 */
char buffer[80];
char varbuffer[10];
#include <ctype.h>

int LineNumber;

void stolower(char* str)
{
   int size=strlen(str);
   for(int i=0;i<size;i++)
     str[i]=tolower(str[i]);
}

/* rule is case insensitive(LISP),  convert all to lower case
 * input() is defined by LEX
 */
#ifndef FLEX_SCANNER
#ifdef input
#undef input
/* redefine input to return lower case letters only */
#define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?:tolower(yytchar))
#endif
#endif


/* FLEX scanner uses YY_INPUT
#ifdef FLEX_SCANNER
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	result = (buf[0] = tolower(getchar())) == EOF ? YY_NULL : 1;	
#endif

%}

ws		[ \t]
forall		{ws}*:?forall
exists		{ws}*:?exists
when		{ws}*:?when
and		{ws}*:?and
or		{ws}*:?or
not		{ws}*:?not
parameters	{ws}*:?parameters
precondition	{ws}*:?precondition
effect		{ws}*:?effect
problem		[ \t]*problem[ \t]*
domain		{ws}*:?domain
init		{ws}*:?init
goals		{ws}*:?goals
define 		[ \t]*define[ \t]*
alphanum	[a-zA-Z0-9\-]
operator	[ \t]*operator[ \t]*

%%
\n		{LineNumber++;}
[ \t]*		;
\(		{return (LP);}
\)		{return (RP);}
;.*$		;
\?{alphanum}+	{
 		 strcpy(varbuffer, &(yytext[1])); 
		 stolower(varbuffer);
		 yylval.ident= varbuffer;
		 return (VARIABLE);}

{alphanum}+	{
		 strcpy(buffer, yytext); 
	 	 stolower(buffer);
		 DBG(_TEMPL_, cerr << "'" << buffer <<  "'"); 	
		 yylval.ident=buffer; 
		 return (CONSTANT);}

\({define}	{return (DEFINE); /* is a definition only if '(define' */ }
\({and}		{return (AND);}
\({or}		{return (OR);}
\({when}	{return (WHEN);}
\({exists}	{return (EXISTS);}
\({forall}	{return (FORALL);}
\({not}		{return (NOT);}
\({operator}	{return (OPERATOR);}
\({problem}	{return (PROBLEM);}
{parameters}	{return (PARAMETERS);}
{precondition}	{return (PRECONDITION);}
{effect}	{return (EFFECT);}
{init}		{return (INITS);}
{goals}		{return (GOALS);}
%{
 /* These rules can match to the constant case above or here */
%}
:?eq		{yylval.ident="eq"; return (CONSTANT);}/* special predicates */
:?neq		{yylval.ident="neq"; return (CONSTANT);}
%%
