#pragma once

typedef struct st_info
{
	int id;			// 학번
	char name[10];  // 이름
	int score;		// 성적

	struct st_info* link ;

} ST_INFO;


int Insert(ST_INFO** phead, int pid, char* pszName, int pscore);


void PrintList(ST_INFO* phead);

void PrintNode(ST_INFO* phead);

ST_INFO* SearchById(ST_INFO* phead, int pid);

ST_INFO* SearchByName(ST_INFO* phead, char *pname);

ST_INFO* DeleteNodeById(ST_INFO* phead, int pid);

ST_INFO* DeleteList(ST_INFO* phead);