#pragma once




typedef struct myList
{
	int nData;

	struct myList* pNext;
} MyList;

// ����Ʈ�� �߰�,�����ϴ� �Լ�
int InsertList(MyList** phead, int ran);

// ����Ʈ�� ��ü����ϴ� �Լ�
void PrintList(MyList* phead);

// ����Ʈ�� ��ü �����ϴ� �Լ�
void DeleteList(MyList* phead);
