typedef union {
  char *ident;
  int  keyword;
} YYSTYPE;
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


extern YYSTYPE yylval;
