#include <stdio.h>
#include <malloc.h>
#include "list.h"

int InsertList(MyList** phead, int ran)
{

	MyList* pNewNode = (MyList*)malloc(sizeof(MyList));
	pNewNode->pNext = NULL;
	MyList* pTmp = *phead;

	int SelectListData = ran;

	if (pTmp == NULL)
	{
		*phead = pNewNode;
		pNewNode->nData = SelectListData;
	}
	else
	{
		while (pTmp != NULL)
		{
			if (pTmp->nData >= SelectListData)
			{
				int temp = 0;
				temp = pTmp->nData;
				pTmp->nData = SelectListData;
				SelectListData = temp;
			}
			if (pTmp->pNext == NULL)
			{
				pTmp->pNext = pNewNode;
				pNewNode->nData = SelectListData;
				return 1;
			}
			pTmp = pTmp->pNext;
		}

	}


	return 1;
}

void PrintList(MyList* phead)
{
	MyList* pTmp = phead;
	printf("\n========================List결과!======================\n");
	if (pTmp == NULL)
	{
		printf("pTmp는 NULL입니다.\n");
	}
	else
	{
		while (pTmp != NULL)
		{
			printf("%d\t", pTmp->nData);
			pTmp = pTmp->pNext;
		}
	}
	putchar('\n');
}

void DeleteList(MyList* phead)
{
	MyList* pTmp = phead;
	MyList* pDelete = NULL;

	if (pTmp == NULL)
	{
		printf("head는 NULL입니다.");
	}
	else
	{
		while (pTmp != NULL)
		{
			pDelete = pTmp;
			pTmp = pTmp->pNext;
			free(pDelete);
		}
	}
}
