#include "arr.h"
#include <stdio.h>
#include <stdlib.h>


void ReleaseArray(int* pnData, int nMax)
{
	for (int i = 0; i < nMax; ++i)
	{
		pnData[i] = 0;
		// printf("%d\t", pnData[i]);
	}
}

void PrintArray(const int* pnData, int nMax)
{
	printf("\n========================array°á°ú!======================\n");
	for (int i = 0; i < nMax; ++i)
	{
		printf("%d\t", pnData[i]);
	}
	putchar('\n');
}



void RandomAfterSort(int* pnData, int nMax, int ran)
{
	int SelectData = ran;
	for (int i = 0; i < nMax; ++i)
	{
		if (pnData[i] == 0)
		{
			pnData[i] = SelectData;
			return;
		}
		else if (pnData[i] >= SelectData)
		{
			int temp = SelectData;
			SelectData = pnData[i];
			pnData[i] = temp;
		}
	}

}
