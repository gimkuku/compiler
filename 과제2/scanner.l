%{
    /* lex source for Mini C */
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
%}
A	[a-zA-Z_]
D	[0-9]
%%
"const"         return(TCONST);
"else"          return(TELSE);
"if"            return(TIF);
"int"           return(TINT);
"return"        return(TRETURN);
"void"          return(TVOID);
"while"         return(TWHILE);

"+"             return(TADD);
"-"             return(TSUB);
"*"             return(TMUL);
"/"             return(TDIV);
"%"             return(TMOD);

"="             return(TASSIGN);
"+="            return(TADDASSIGN);
"-="            return(TSUBASSIGN);
"*="            return(TMULASSIGN);
"/="            return(TDIVASSIGN);
"%="            return(TMODASSIGN);

"!"             return(TNOT);
"&&"            return(TAND);
"||"            return(TOR);

"=="            return(TEQUAL);
"!="            return(TNOTEQU);
"<"             return(TLESS);
">"             return(TGREAT);
"<="            return(TLESSE);
">="            return(TGREATE);

"++"            return(TINC);
"--"            return(TDEC);

"("             return(TBRASL);
")"             return(TBRASR);
"{"             return(TBRAML);
"}"             return(TBRAMR);
"["             return(TBRALL);
"]"             return(TBRALR);
","             return(TCOMMA);
";"             return(TSEMICOLON);

(" "|"\t")      ;
"\n"            cLine++;

{D}+                    return(TNUMBER);
{D}+"."{D}+             return(TRNUMBER);

{A}({A}|{D})*           {
                            if(yyleng > 12) return(TLONGIDERR);
                            else{
                                SymbolTable();
                                return(TIDENT);
                            }
                        }
{D}({A}|{D})*           return(TSWDIGITERR);                          

"/*"([^*]|\*+[^*/])*\**"*/"     {
                                    int i;
                                    for(i = 0; i < yyleng; i++)
                                        if(yytext[i] == '\n') cLine++;
                                } 
"//".*          ;
.               return(TILLSYMBOLERR);
%%
int yywrap() {
    printf("1871015 김현진\n1971031 이가영");
    return 1;
}