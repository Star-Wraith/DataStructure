#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "linkedlist.h"



//리스트를 추가하여 맨뒤로 보내는 함수
int Insert(ST_INFO** phead, int pid, char* pszName, int pscore)
{
	
	ST_INFO* pNewNode = (ST_INFO*)malloc(sizeof(ST_INFO));

	
	
	pNewNode->id = pid;
	pNewNode->score = pscore;
	pNewNode->link = NULL;

	strcpy_s(pNewNode->name, sizeof(pNewNode->name),pszName);
	ST_INFO* pTmp = *phead;
	printf("\ninsert\n");
	if (*phead == NULL)
	{
		*phead = pNewNode;
		return 0;
	}
	else if (pTmp->link == NULL)
	{
		pTmp->link = pNewNode;
		return 0;
	}
	else
	{
		while (pTmp->link!= NULL)
		{
			pTmp = pTmp->link;
		}
		
		pTmp->link = pNewNode;
		return 0;
	}

	return -1;
}
//리스트를 전체출력하는 함수
void PrintList(ST_INFO* phead)
{
	printf("\nPrintList\n");
	ST_INFO* pTmp = phead;
	
	if (pTmp == NULL)
	{
		printf("Head->NuLL");
	
	}
	else
	{
		while (pTmp != NULL)
		{
			printf("<%d, %s, %d>",
				pTmp->id,
				pTmp->name,
				pTmp->score);
			
			pTmp = pTmp->link;
		}
	}


}
//리스트에 있는 노드하나의 정보를 출력하는 함수
void PrintNode(ST_INFO* phead)
{
	printf("\nPrintNode\n");
	if (phead == NULL)
	{
		printf("이 리스트는 NULL이다.");
	}
	else
	{
		printf("<%d, %s, %d>",
			phead->id,
			phead->name,
			phead->score);
	}

}
//id에 맞는 노드를 찾는 함수
ST_INFO* SearchById(ST_INFO* phead, int pid)
{
	ST_INFO* pTmp = phead;
	printf("\nSearchById\n");
	while (pTmp != NULL)
	{
		if (pTmp->id == pid)
		{
			return pTmp;
		}

		pTmp = pTmp->link;
	}
	return NULL;
}
//NAME에 맞는 노드를 찾는 함수
ST_INFO* SearchByName(ST_INFO* phead, char *pname)
{
	ST_INFO* pTmp = phead;

	printf("\nSearchByName\n");
	while (pTmp != NULL)
	{
		if (strcmp(pTmp->name, pname) == 0)
		{
			return pTmp;
		}

		pTmp = pTmp->link;
	}
	return NULL;
}
//id에 맞는 노드를 삭제하는 함수
ST_INFO* DeleteNodeById(ST_INFO* phead, int pid)
{
	ST_INFO* pTmp = phead;
	ST_INFO* pPrevNode = phead;



	printf("\nDeleteNodeById\n");

	if (pTmp->id == pid)
	{
		phead = phead->link;
		printf("%d", phead->id);
		free(pTmp);
		return phead;
	}
	else
	{
		pTmp = pTmp->link;
		while (pTmp != NULL)
		{
			if (pTmp->id == pid)
			{
				pPrevNode->link = pTmp->link;

				free(pTmp);
				return phead;
			}
			pTmp = pTmp->link;
			pPrevNode = pPrevNode->link;
		}
	}

	return NULL;
}
//리스트를 전체삭제하는 함수
ST_INFO* DeleteList(ST_INFO* phead)
{
	ST_INFO* pTmp = phead;
	ST_INFO* pDelete = NULL;

	printf("\nDeleteList\n");
	if (pTmp->link == NULL)
	{
		free(pTmp);
	}
	else
	{
		while (pTmp->link != NULL)
		{

			pDelete = pTmp;
			pTmp = pTmp->link;
			free(pDelete);
		}
	}

	return NULL;
}
