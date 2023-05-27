#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arr.h"
#include "list.h"

#define MAX_NUM 100 // �ε���
#define SEED 200


int main()
{
	srand(1);

	////////////////////////////////////////////////
	//�ð� ��� ����
	time_t startarr, endarr; // �迭 �ð�
	time_t startlist, endlist; // ����Ʈ �ð�
	//////////////////////////////////////////////

	// �迭 �Ҵ�//////////////////////////////////////////
	int* nData = (int*)malloc(sizeof(int)* MAX_NUM);
	ReleaseArray(nData, MAX_NUM);
	//�迭 �ð� ����
	int* num = (int*)malloc(sizeof(int) * MAX_NUM);
	for (int i = 0; i < MAX_NUM; ++i)
	{
		num[i] = rand() % SEED;
	}

	time(&startarr); // ����
	for (int i = 0; i < MAX_NUM; ++i)
	{ 
		//num[i] = rand() % SEED;
		RandomAfterSort(nData, MAX_NUM, num[i]);
	}
	time(&endarr);   // ��

	
	/////////////////////////////////////////////////////
	//����Ʈ

	MyList* head = NULL;

	time(&startlist); // ����
	for (int i = 0; i < MAX_NUM; ++i)
	{
		//num = rand() % SEED;
		InsertList(&head, num[i]);
	}
	time(&endlist);   // ��

	

	printf("\nData size: %d", MAX_NUM);
	printf("\nrand �Լ��� seed��: %d\n", SEED);
	printf("�迭�� �̿��� ��� �ҿ�ð�: %d\n", (int)(endarr - startarr));
	PrintArray(nData, MAX_NUM); 
	printf("����Ʈ�� �̿��� ��� �ҿ�ð�: %d\n", (int)(endlist - startlist));
	PrintList(head);

	free(nData);
	DeleteList(head);
	free(num);
	return 0;
}