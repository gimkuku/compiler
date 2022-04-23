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
"\n" cLine++;
[A-Za=z_][A-Za-z0-9_]* {
                            if(yyleng > 12) return(TLONGIDERR);
                            else{
                                SymbolTable();
                                return(TIDENT);
                            }
                        }
[0-9][A-Za-z0-9_]*           return(TSWDIGITERR);  
"/*"([^*]|\*+[^*/])*\**"*/"     {
                                    int i;
                                    for(i = 0; i < yyleng; i++)
                                        if(yytext[i] == '\n') cLine++;
                                }   
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?    return(TNUMBER);
"//".* ;
[ \t\n] ;
. return (TILLSYMBOLERR);
%%
int yywrap() {
    printf("1871015 김현진\n1971031 이가영");
    return 1;
}