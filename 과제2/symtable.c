/*
역할 분담
50% 이가영(1971031) : 에러 처리 및 구현, 출력 코드 
50% 김현진(1871015) : 구조체 설계, 최종 코드 에러 수정
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "./testdata.txt"
 
#define STsize 1000  //size of string table
#define HTsize 1000	//size of hash table
 
#define FALSE 0
#define TRUE 1
 
#define isLetter(x) (((x)>='a'&&(x)<='z')||((x)>='A'&&(x)<='Z') || (x)=='_')
#define isDigit(x) ((x)>='0'&&(x)<='9')
 
typedef struct HTentry *HTpointer;
typedef struct HTentry {
  int index;  //index of identifier in ST
  HTpointer next;  //pointer to next identifier
}HTentry;
 
enum errorTypes { noerror, illsp, illid, overst, toolong };
typedef enum errorTypes ERRORtypes;
 
char seperators[] = " .,;:?!\t\n";

 
HTpointer HT[HTsize];
char ST[STsize];

int nextid = 0;  //the current identifier
int nextfree = 0;  //the next available index of ST
int hashcode;  //hash code of identifier
int sameid;  //first index of identifier

int found;  //for the previous occurrence of an identifie

ERRORtypes error;

FILE *fp;   //to be a pointer to FILE 
char input;
 
 
//Initialize - open input file

void initialize() {
	fp = fopen(FILE_NAME, "r");
	input = fgetc(fp);
}
 
// 작성자 : 함께 작성
//isSeperator - distinguish the seperator
int isSeperator(char c)
{
	int i;
	int sep_len;
 
	sep_len = strlen(seperators);
	for (i = 0; i < sep_len; i++) {
		if (c == seperators[i])
			return 1;
	}
	return 0;
}
 
//printHeading - print the heading
// 작성자 : 이가영(1971031)
void PrintHeading(){
	printf("\n\n");
	printf("--------------------------\n");
	printf("Index in ST     identifier\n");
	printf("--------------------------\n");
	printf("\n");
}
 
/* PrintHStable - Prints the hash table.write out the hashcode and the list of identifiers
associated with each hashcode,but only for non-empty lists.
Print out the number of characters used up in ST.
*/
// 작성자 : 이가영(1971031)
void PrintHStable() {
	int i, j;
	HTpointer ptr;
 
	printf("\n\n[[ HASH TABLE ]]\n");
 
	for (i = 0; i<HTsize; i++) {
		if (HT[i] != NULL) {     //단, HT의 값이 non-empty list인 경우
			printf("Hash code %5d: ", i);
			for (ptr = HT[i]; ptr != NULL; ptr = ptr->next) {
				j = ptr->index;
				while (ST[j] != '\0' && j<STsize) {
					printf("%c", ST[j++]);
				}
				printf("\t");
			}
			printf("\n");
 
		}
	}
}
 
 
/* PrintError - Print out error messages
overst : overflow in ST
print the hashtable and abort by calling the function "abort()".
illid : illegal identifier
illsp :illegal seperator
long : long identifier
*/
// 작성자 : 이가영(1971031)
void PrintError(ERRORtypes error) {
  printf("...Error... ");
  for (int i = nextid; i<nextfree; i++) {
		printf("%c", ST[i]);
	}
	switch (error) {
	case overst:
		printf("OVERFLOW");
		PrintHStable(); //
		exit(0); //
		break;
 
	case illsp:
    while (input != EOF && (isLetter(input) || isDigit(input))){
      printf("%c", input);
      input = fgetc(fp);
    }
    printf("%c\tillegal seperator \n",input);
    break;
 
	case illid:
		while (input != EOF && (isLetter(input) || isDigit(input))){
			printf("%c", input);
			input = fgetc(fp);
		}
		printf("\tstart with digit\n");
		break;

	case toolong: //indentifier이 12자 이상일 경우 출력
		while (input != EOF && (isLetter(input) || isDigit(input))){
			printf("%c", input);
			input = fgetc(fp);
		}
		printf("\tindentifier is too long\n");
    break;
  }
}
 
//SkipSeperators -skip over strings of spaces,tabs,newlines, . , ; : ? ! 
//if illegal seperators,print out error message.
// 작성자 : 함께
void SkipSeperators() 
{
	while (input != EOF && !(isLetter(input) || isDigit(input))){
		if (!isSeperator(input)) {
			error = illsp;
      PrintError(error);
		}
		input = fgetc(fp);
	}
}
 
/*ReadIO - Read identifier from the input file the string table ST directly into
ST(append it to the previous identifier).
An identifier is a string of letters and digits, starting with a letter.
If first letter is digit, print out error message.
*/
// 작성자 : 함께
void ReadID() {
	//초기 위치 설정(ST에 저장하는 시작위치) 
	nextid = nextfree;
	//indentifierd이 숫자로 시작하는 경우 오류 출력
	if (isDigit(input)) { 
		error = illid;
		PrintError(error);
	}

	else{
		while(input!=EOF && (isLetter(input) || isDigit(input))){
			if(nextfree==STsize){ //overflow 에러 출력
				error=overst;
				PrintError(error);
			}
			ST[nextfree]=input;
			nextfree++;
			input=fgetc(fp);
			//indentifier이 12자 초과일경우 toolong error 출력
      //12자 이내 : no error
			if((nextfree - nextid) > 12){
				error=toolong;
				PrintError(toolong);
	}
		}
	}
}
 
 
// ComputeHS - Compute the hash code of identifier by summing the ordinal values of its 
//              characters and then taking the sum modulo the size of HT.
// 작성자 : 김현진(1871015)
void ComputeHS(int nid, int nfree)
{
	int askiisum = 0; //identifier의 아스키코드 총 합 변수 선언
	for (int i = nid; i<nfree - 1; i++) {
		askiisum += (int)ST[i];

	}
	hashcode = askiisum % HTsize +1 ;
	//인덱스 nid부터 nfree 까지에 해당하는 ST의 값을 읽어와서 더해준 후, HT의 크기로 나누고, +1 한 값이 hashcode

}
 
/* LookupHS -For each identifier,Look it up in the hashtable for previous occurrence
of the identifier.If find a match, set the found flag as true.
Otherwise flase.
If find a match, save the starting index of ST in same id.
*/
// 작성자 : 김현진(1871015)
void LookupHS(int nid, int hscode) {
	
	int i, j;
	HTpointer ptr;
	found = FALSE; //중복 체크하는 불린값

	if (HT[hscode] != NULL) {
		ptr = HT[hscode];
		while (ptr != NULL && found == FALSE) {
			found = TRUE;
			j = ptr->index;
			i = nid;
			sameid = i;
			while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {
				if (ST[i] != ST[j]) {
					found = FALSE;
				}
				else {
					i++;
					j++;
				}
			}
			ptr = ptr->next;
		}
	}
}
 
 
/* ADDHT- Add a new identifier to the hash table.
If list head ht[hashcode] is null, simply add a list element with
starting index of the identifier in ST.
IF list head is not a null , it adds a new identifier to the head of the chain
*/
// 작성자 : 김현진(1871015)
void ADDHT(int hscode) {
	HTpointer point;
 
	point = (HTpointer)malloc(sizeof(point));
	point->index = nextid;
	point->next = HT[hscode];
	HT[hscode] = point;
	//HT에 추가되지 않은 identifier인 경우
    //index는 ST의 index, next는 null 인 새로운 HTEntry를 생성
    //기존 HT에 추가
}
 
 
/*
Read the identifier from the file directly into ST.
Compute its hashcode.
Look up the idetifier in hashtable HT[hashcode]
If matched, delete the identifier from ST and print ST-index of the matching identifier.
If not matched , add a new element to the list,pointing to new identifier.
Print the identifier,its index in ST, and whether it was entered or present.
Print out the hashtable,and number of characters used up in ST
*/
// 작성자 : 함께
int SymbolTable()
{
	int i;
	PrintHeading();
	initialize();
 
	while (input != EOF) {
		//EOF: end of file
		error = noerror;
		SkipSeperators();
		ReadID();

    if(error == noerror) {
      if (nextfree == STsize)
      {
        // print error message 
				error = overst;
				PrintError(error);
      }
      ST[nextfree] = '\0';
			nextfree++;
 
			ComputeHS(nextid, nextfree);
			LookupHS(nextid, hashcode);

			if (!found) {
				// print message
				printf("%6d\t", nextid);
				for (i = nextid; i<nextfree; i++) {
					printf("%c", ST[i]);
				}
				printf("\t(entered)\n");
				ADDHT(hashcode);
			} 
			else {
				//print message
				printf("same_id");
				for (i = nextid; i<nextfree - 1; i++) {
					printf("%c", ST[i]);
				}
				printf("\t(already existed)\n");
				nextfree = nextid;
			}
		}
	}
	PrintHStable();
}