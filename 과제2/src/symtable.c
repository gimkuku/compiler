/*
역할 분담
50% 이가영(1971031) : 에러 처리 및 구현, 출력 코드 
50% 김현진(1871015) : 구조체 설계, 최종 코드 에러 수정
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glob.h"


HTpointer HT[HTsize];
char ST[STsize];

int hashcode; //hash code of identifier
int sameid;  //first index of identifier
int stindex;
int overflow = 0;
int found; //for the previous occurrence of an identifie
int nextid = 0;
int nextfree = 0;



// 작성자 : 함께
void ReadID() {
   // 한 글자씩 ST에 저장
   for(int i = 0; i < yyleng; i++){
      // 오버플로우 체크
      if (nextfree >= STsize) {
         overflow = 1;
         return;
      }

      ST[nextfree] = yytext[i];
   }

   // identifier 마지막에 널문자 추가
   if (nextfree >= STsize)
      overflow = 1;
   else
      ST[nextfree] = '\0';
}

/* deleteID
   :ST에 받아두었던 id 삭제 */
void deleteID() {
   nextfree = nextid;
}

/* insertID
   :ST에 받아두었던 id 저장 확정 */
void insertID() {
   stindex = nextid;
   nextid = nextfree;
}
 
// 작성자 : 김현진(1871015)
int ComputeHS(int nid, int nfree)
{
	int askiisum = 0; //identifier의 아스키코드 총 합 변수 선언
	for (int i = nid; i<nfree - 1; i++) {
		askiisum += (int)ST[i];
	}
	/* 인덱스 nid부터 nfree 까지에 해당하는 ST의 값을 읽어와서 더해준 후, 
	HT의 크기로 나누고, +1 한 값이 hashcode	*/
	hashcode = askiisum % HTsize +1 ;
	return hashcode;
}
 

// 작성자 : 김현진(1871015)
int LookupHS(int nid, int hscode) {
	
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
					return -1;
				}
				else {
					i++;
					j++;
				}
			}
			ptr = ptr->next;
		}
		return ptr -> index;

	}

}
 
 
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
 
 
// 작성자 : 함께
void SymbolTable()
{
	int i;
	int ptr_idx;
	ReadID();

	if (overflow) {
		return ;
	}

	nextfree++;
	hashcode = ComputeHS(nextid, nextfree);
	ptr_idx = LookupHS(nextid, hashcode);

	if (!found) {
		ADDHT(hashcode);
		insertID();
	} 
	else {
		stindex = ptr_idx;
		deleteID();
	}
}