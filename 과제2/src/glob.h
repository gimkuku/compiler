#ifndef GLOB_H_
#define GLOB_H_

#define STsize 1000    
#define HTsize 100     

#define TRUE 1
#define FALSE 0 

typedef struct HTentry* HTpointer;
typedef struct HTentry {
   int index;         
   HTpointer next;    
} HTentry;

HTpointer HT[HTsize];
char ST[STsize];


void SymbolTable();           
void printtoolongError();   
void printillidError();     
void printillspError();     
void printoverflowError();
void printtoken();

extern yylex();
extern yyleng;
extern char *yytext;
extern int cLine;      
extern int stindex;       
extern int overflow;      

#endif