#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arr.h"
#include "list.h"

#define MAX_NUM 100 // 인덱스
#define SEED 200


int main()
{
	srand(1);

	////////////////////////////////////////////////
	//시간 재는 변수
	time_t startarr, endarr; // 배열 시간
	time_t startlist, endlist; // 리스트 시간
	//////////////////////////////////////////////

	// 배열 할당//////////////////////////////////////////
	int* nData = (int*)malloc(sizeof(int)* MAX_NUM);
	ReleaseArray(nData, MAX_NUM);
	//배열 시간 측정
	int* num = (int*)malloc(sizeof(int) * MAX_NUM);
	for (int i = 0; i < MAX_NUM; ++i)
	{
		num[i] = rand() % SEED;
	}

	time(&startarr); // 시작
	for (int i = 0; i < MAX_NUM; ++i)
	{ 
		//num[i] = rand() % SEED;
		RandomAfterSort(nData, MAX_NUM, num[i]);
	}
	time(&endarr);   // 끝

	
	/////////////////////////////////////////////////////
	//리스트

	MyList* head = NULL;

	time(&startlist); // 시작
	for (int i = 0; i < MAX_NUM; ++i)
	{
		//num = rand() % SEED;
		InsertList(&head, num[i]);
	}
	time(&endlist);   // 끝

	

	printf("\nData size: %d", MAX_NUM);
	printf("\nrand 함수의 seed값: %d\n", SEED);
	printf("배열을 이용한 경우 소요시간: %d\n", (int)(endarr - startarr));
	PrintArray(nData, MAX_NUM); 
	printf("리스트를 이용한 경우 소요시간: %d\n", (int)(endlist - startlist));
	PrintList(head);

	free(nData);
	DeleteList(head);
	free(num);
	return 0;
}