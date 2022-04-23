#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glob.h"

void printError(){
    printf("%-18s", "ERROR!!");
    printf("%-18s", "");
    printf("%s ", yytext);
}

/* printtoolongError  
    : identifier가 12자 이상인 경우*/
void printtoolongError(){
    printError();
    printf("indentifier is too long");
}

/* printillidError
   : identifier가 숫자로 시작하는 경우 */
void printillidError(){
    printError();
    printf("start with digit");
}

/* printillspError
   : 잘못된 구분자인 경우 */
void printillspError(){
    printError();
    printf("illegal seperator");
}

/* printoverflowError
   : overflow인경우 */
void printoverflowError(){
    printf("%-18s", "***error***");
    printf("%-18s", "");
    printf("OVERFLOW %s", yytext);
}