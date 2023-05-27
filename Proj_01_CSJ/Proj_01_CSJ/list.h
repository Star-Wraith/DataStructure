#pragma once




typedef struct myList
{
	int nData;

	struct myList* pNext;
} MyList;

// 리스트를 추가,삽입하는 함수
int InsertList(MyList** phead, int ran);

// 리스트를 전체출력하는 함수
void PrintList(MyList* phead);

// 리스트를 전체 삭제하는 함수
void DeleteList(MyList* phead);
