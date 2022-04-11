%{
    /* lex source for Mini C */
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
%}
letter	[a-zA-Z_]
digit	[0-9]
%%
"const"	return(TCONST);
"else" return (TELSE);
"if" return(TIF);
"int" return(TINT);
"return" return(TRETURN);
"void" return(TVOID);
"while" return(TWHILE);
"==" return(TEQUAL);
"!=" return(TNOTEQU);
"<=" return(TLESSE);
">=" return(TGREATE);
"&&" return(TAND);
"||" return(TOR);
"++" return(TINC);
"--" return(TDEC);
"+=" return(TADDASSIGN);
"-=" return(TSUBASSIGN);
"*=" return(TMULASSIGN);
"/=" return(TDIVASSIGN);
"%=" return(TMODASSIGN);
[A-Za=z_][A-Za-z0-9_]* return (TIDENT);
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?    return(TNUMBER);
"/*"([^*]|\*+[^*/])*\**"*/" ;
"//".* ;
[ \t\n] ;
. return (yytext[0]);
%%
void main(){
	enum tokentypes tn;
	printf("Start of Lex\n");
	while ((tn=yylex()) != TEOF){
		switch(tn){
			case TCONST : printf("Const\n"); break;
			case TELSE : printf("Else\n"); break;
			case TIF : printf("If\n"); break;
			case TINT : printf("Int\n"); break;
			case TRETURN : printf("Return\n"); break;
			case TVOID : printf("Void : %d\n"); break;
			case TWHILE : printf("While\n"); break;
			case TEQUAL : printf("Equal\n"); break;
            case TNOTEQU : printf("Not Equal\n"); break;
			case TLESSE : printf("Less Equal\n"); break;
			case TGREATE : printf("Great Equal\n"); break;
			case TAND : printf("And\n"); break;
			case TOR : printf("Or\n"); break;
			case TINC : printf("Increase\n"); break;
			case TDEC : printf("Decrease\n"); break;
			case TADDASSIGN : printf("Add Assign\n"); break;
			case TSUBASSIGN : printf("Subscribe Assign\n"); break;
            case TMULASSIGN : printf("Multify Assign\n"); break;
			case TDIVASSIGN : printf("Divide Assign\n"); break;
			case TMODASSIGN : printf("Mod Assign\n"); break;
			case TIDENT : printf("Identifier : %s\n",yytext); break;
			case TNUMBER : printf("Number : %s\n",yytext); break;
            default : printf("%s", yytext); break;
		}
	}
}

int yywrap() {
    printf("1871015 김현진\n");
    return 1;
}