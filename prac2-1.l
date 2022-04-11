%{
#include <stdio.h>
#include <stdlib.h>
enum tnumber { TEOF, TIDEN, TNUM, TASSIGN, TADD, TSEMI, TDOT,
TBEGIN, TEND, TERROR};
%}

letter [a-zA-Z_]
digit [0-9]
%%
int	printf("integer ");
"{"	printf("begin\n");
"}"	printf("end\n");
"\n"  printf("\n");
begin	return(TBEGIN);
end	return(TEND);
{letter}({letter}|{digit})*	return(TIDEN);
":="	return(TASSIGN);
"+"	return(TADD);
{digit}+	return(TNUM);
";"	return(TSEMI);
\.	return(TDOT);
[ \t\n]	;
.	return(TERROR);

%%
void main() {
	enum tnumber tn;
	printf("Start of Lex\n");
	while ((tn=yylex()) != TEOF) {
		printf("%s ", yytext);
	}
}
int yywrap() {
	printf("1871015 김현진\n");
	return 1;
}