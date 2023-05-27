#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <memory.h>



#define _CRT_SECURE_NO_WARNINGS
#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
#define MAX_LIST_SIZE 100 // 리스트의 최대크기
typedef int element; // 항목의 정의
typedef struct {
	element array[MAX_LIST_SIZE]; // 배열 정의
	int size; // 현재 리스트에 저장된 항목들의 개수
} SortedList;

int is_empty(SortedList* L);
int is_full(SortedList* L);
void init(SortedList* L);
element get_entry(SortedList* L, int pos);
void add(SortedList* L, element item);
int is_in_list(SortedList* L, element item);
element delete(SortedList* L, element item);
void clear(SortedList* L);
int get_length(SortedList* L);
void display(SortedList* L);

// 리스트가 비어 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_empty(SortedList* L)
{
	return L->size == 0;
}

int is_full(SortedList* L)
{
	return L->size == MAX_LIST_SIZE;
}

// 리스트 초기화 함수
void init(SortedList* L)
{
	memset(L->array, 0, sizeof(int) * MAX_LIST_SIZE);
	L->size=0;
}

element get_entry(SortedList* L, int pos)
{
	if (pos < 0 || pos >= L->size)
	{
		return -1;
	}
	return L->array[pos];
}


void add(SortedList* L, element item)
{
	int value = item;
	int temp = 0;
	if (!is_full(L)) {
		++L->size;
		for (int i = 0; i < L->size; ++i) {
			if (value < L->array[i]) {
				temp = L->array[i];
				L->array[i] = value;
				value = temp;
			}
			else if (L->array[i] == 0) {
				L->array[i] = value;
			}
		}
	}
}
int is_in_list(SortedList* L, element item) {
	for (int i = 0; i < L->size; ++i) {
		if (L->array[i] == item) {
			return i;
		}
	}
	return -1;
}
element delete(SortedList* L, element item)
{
	int result = is_in_list(L, item);

	if (result != -1) {
		for (int i = result; i < (L->size - 1); ++i) {
			L->array[i] = L->array[i + 1];
		}
			
		L->size--;

		return result;
	}

	return -1;
	
}
void clear(SortedList* L) {
	init(L);
}

// 
int get_length(SortedList* L) {

	return L->size;
}


// 리스트 출력
void display(SortedList* L)
{
	
	for (int i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n");
}


// 1번 문제를 해결하기 위한 프로그램 작성
int main(void) {
	SortedList list;
	//필요한 초기화 코드 추가
	init(&list);
	int item = 0;
	char ch = 0;

	srand(100); // 동일한 패턴을 찾기 위해 seed 값 100 부여함
	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = _getch();
		if (ch == 'q') break;
	}
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",
		is_empty(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
	display(&list);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("리스트 길이 %d \n", get_length(&list));

	//종료하기 전에 수행해야 할 코드 추가

		return 0;
}


#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
#define MAX_LIST_SIZE 100
typedef int element;
typedef struct SortedList { // 노드 타입을 구조체로 정의한다.
	element data;
	struct SortedList* link;
} SortedList;

int list_count = 0;

void init(SortedList* _pNode);
void add(SortedList* _pNode, int _item);
int delete(SortedList* _pNode, int _item);
void clear(SortedList* _pNode);
int is_in_list(SortedList* _pNode, int _item);
int get_length(SortedList* _pNode);
int is_empty(SortedList* _pNode);
int is_full(SortedList* _pNode);
void display(SortedList* _pNode);

void init(SortedList* _pNode) {
	_pNode->data = 0;
	_pNode->link = NULL;
}

void add(SortedList* _pNode, int _item) {
	SortedList* pNewNode = (SortedList*)malloc(sizeof(SortedList));
	pNewNode->data = _item;
	pNewNode->link = NULL;
	if (list_count < MAX_LIST_SIZE) {
		if (_pNode->link == NULL) {
			_pNode->link = pNewNode;
			++list_count;
			return;
		}


		SortedList* pTmp = _pNode->link;
		while (pTmp != NULL) {
			if (pTmp->link == NULL) {
				pTmp->link = pNewNode;
				++list_count;
				return;
			}
			if (pNewNode->data < pTmp->link->data) {
				pNewNode->link = pTmp->link;
				pTmp->link = pNewNode;
				++list_count;
				return;
			}

			pTmp = pTmp->link;
		}
	}

}

int delete(SortedList* _pNode, int _item) {
	
	int pos = is_in_list(_pNode, _item);
	int i = 1;

	if (pos != -1) {
		SortedList* pTmp = _pNode->link;
		SortedList* pDelete = NULL;

		while (pTmp != NULL) {
			if (i == pos) {
				pDelete = pTmp->link;
				pTmp->link = pDelete->link;
				free(pDelete);
				--list_count;
				return pos;
			}
			++i;
			pTmp = pTmp->link;
		}
	}
	
	return -1;
}

void clear(SortedList* _pNode) {
	SortedList* pTmp = _pNode->link;
	SortedList* pDelete = NULL;
	while (pTmp != NULL) {
		pDelete = pTmp;
		pTmp = pTmp->link;
		free(pDelete);
	}
	init(_pNode);
	list_count = 0;
}

int is_in_list(SortedList* _pNode, int _item) {
	SortedList* pTmp = _pNode->link;
	int i = 0;
	while (pTmp != NULL) {
		if (pTmp->data == _item) {
			return i;
		}
		++i;
		pTmp = pTmp->link;
	}
	

	return -1;
}

element get_entry(SortedList* _pNode, int pos)
{

	int i = 0;
	SortedList* pTmp = _pNode->link;

	while (pTmp != NULL) {
		if (i == pos) {
			return pTmp->data;
		}
		pTmp = pTmp->link;
		++i;
	}


}


int get_length(SortedList* _pNode) {
	return list_count;
}

int is_empty(SortedList* _pNode) {
	if (list_count == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
int is_full(SortedList* _pNode) {
	if (list_count == MAX_LIST_SIZE) {
		return 1;
	}
	else {
		return 0;
	}
}

void display(SortedList* _pNode)
{
	SortedList* pTmp = _pNode->link;
	while (pTmp != NULL) {
		printf("%d->", pTmp->data);
		pTmp = pTmp->link;
	}
	printf("\n");
}

int main(void) {
	SortedList list;
	//필요한 초기화 코드 추가
	init(&list);
	int item = 0;
	char ch = 0;

	srand(100); // 동일한 패턴을 찾기 위해 seed 값 100 부여함
	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = _getch();
		if (ch == 'q') break;
	}
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",
		is_empty(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
	display(&list);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("리스트 길이 %d \n", get_length(&list));

	//종료하기 전에 수행해야 할 코드 추가
	
	return 0;
}
#endif