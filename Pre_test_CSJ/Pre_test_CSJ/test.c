#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"


int main(void)
{
	ST_INFO* head = NULL;
	ST_INFO* result = NULL;
	// 연결리스트의 마지막 노드로 삽입
	PrintList(head);
	Insert(&head, 1, "김길동", 83);
	PrintList(head);
	Insert(&head, 2, "나길동", 70);
	PrintList(head);
	Insert(&head, 3, "다길동", 80);
	Insert(&head, 4, "라길동", 55);
	Insert(&head, 5, "마길동", 76);
	Insert(&head, 6, "홍길동", 90);
	PrintList(head);
	// id와 name 필드를 이용한 검색
	result = SearchById(head, 3);
	PrintNode(result);
	result = SearchById(head, 10);
	PrintNode(result);
	result = SearchByName(head, "홍길동");
	PrintNode(result);
	// id를 이용하여 해당되는 노드 검색하여 삭제
	head = DeleteNodeById(head, 4);
	PrintList(head);
	head = DeleteNodeById(head, 1);
	PrintList(head);
	// 전체 연결리스트 삭제
	head = DeleteList(head);
	PrintList(head);
	return 0;
}