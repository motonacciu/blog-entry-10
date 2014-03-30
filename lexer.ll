%{
#include "parser.h"
#include <string>

extern "C" int yylex();
extern void yyerror(const char*);

%}

%option noyywrap
%option case-insensitive

%%
	/* operators */
add						{ return OP_ADD; }
sub						{ return OP_SUB; }
bra						{ return OP_BRA; }

,						{ return COMMA; }
:						{ return COLON; }

#[0-9]+					{ yylval.integer = atoi(yytext+1); return IMMEDIATE; }

[a-zA-Z_][a-zA-Z0-9]*	{ yylval.string = new std::string(yytext, yyleng); return IDENTIFIER; }

[ \t]					;					
\n						{ return NEWLINE; }

.						{ yyerror("Unknown character"); }

%%
