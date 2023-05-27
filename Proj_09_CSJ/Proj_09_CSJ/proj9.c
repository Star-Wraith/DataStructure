#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_PLAY_LIST_NAME 100
#define MAX_SONG_NAME 100


typedef struct DSongNode {
	char sName[MAX_SONG_NAME];
	struct DSongNode* llink;
	struct DSongNode* rlink;
} DSongNode;

typedef struct DPlaylistNode { // 이중연결 노드 타입
	char pName[MAX_PLAY_LIST_NAME];
	struct DPlaylistNode* llink;
	struct DPlaylistNode* rlink;
	struct DSongNode*	  slink;
} DPlaylistNode;

// 이중 연결 리스트를 초기화
void init(DPlaylistNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
	phead->slink = NULL;
}

// 이중 연결 리스트의 노드를 출력
void print_dlist(DPlaylistNode* phead)
{
	DPlaylistNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%s| |-> ", p->pName);
	}
	printf("\n");
}
// 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
void dinsert(DPlaylistNode* before, const char* _playlist_name)
{
	DPlaylistNode* newnode = (DPlaylistNode*)malloc(sizeof(DPlaylistNode));
	strcpy_s(newnode->pName, sizeof(newnode->pName), _playlist_name);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// 노드 removed를 삭제한다.
void ddelete(DPlaylistNode* head, DPlaylistNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

void print_playlist_menu()
{
	printf("\n\n---- Playlist Menu ---- \n");
	printf(" a : print all playlist \n");
	printf(" c : print current playlist\n");
	printf(" n : new playlist \n");
	printf(" d : delete playlist \n");
	printf(" > : next playlist \n");
	printf(" < : previous playlist \n");
	printf(" s : song menu \n");
	printf(" q : quit \n");
	return;
}

void print_song_menu()
{
	printf("\n\n---- Song Menu ---- \n");
	printf(" a : print all songs \n");
	printf(" c : print current song\n");
	printf(" n : add new song in playlist \n");
	printf(" d : delete current song \n");
	printf(" > : next song \n");
	printf(" < : previous song \n");
	printf(" b : quit \n");
	return;
}

void print_aPlaylist(DPlaylistNode* _head, DPlaylistNode* _currentPlaylist) {

	DPlaylistNode* pTmp = _head;
	printf("Playlist : ");
	if (pTmp == NULL) {
		printf("(null)\n");
		return;
	}
	else if(pTmp->rlink == NULL){
		printf(" <-[*%s*]-> ", pTmp->pName);
		return;
	}
	else {
		pTmp = _head->rlink;
	}
	while (pTmp != _head) {

		if (pTmp == _currentPlaylist) {
			printf(" <-[*%s*]-> ", pTmp->pName);
		}
		else {
			printf(" <-[%s]-> ", pTmp->pName);
		}

		pTmp = pTmp->rlink;
	}
	if (pTmp == _head) {
		if (pTmp == _currentPlaylist) {
			printf(" <-[*%s*]-> ", pTmp->pName);
		}
		else {
			printf(" <-[%s]-> ", pTmp->pName);
		}

	}


}

void insert_nPlaylist(DPlaylistNode** _phead, char* _buf, DPlaylistNode** _pcurrentPlaylist) {

	DPlaylistNode* pNewNode = (DPlaylistNode*)malloc(sizeof(DPlaylistNode));
	strcpy_s(pNewNode->pName, sizeof(pNewNode->pName), _buf);
	pNewNode->rlink = NULL;
	pNewNode->llink = NULL;
	pNewNode->slink = NULL;

	if (*_phead == NULL) {
		*_phead = pNewNode;

	}
	else if ((*_phead)->rlink == NULL) {
		pNewNode->rlink = (*_phead);
		pNewNode->llink = (*_phead);
		(*_phead)->rlink = pNewNode;
		(*_phead)->llink = pNewNode;
		(*_phead) = pNewNode;
	}
	else{
		pNewNode->rlink = (*_phead)->rlink;
		pNewNode->llink = (*_phead);
		pNewNode->rlink->llink = pNewNode;
		(*_phead)->rlink = pNewNode;

		(*_phead) = pNewNode;
		
	}
	*_pcurrentPlaylist = *_phead;
}

void delete_SongWithList(DPlaylistNode* _currentPlaylist) {
	DSongNode* pTmp = _currentPlaylist->slink;
	DSongNode* pDelete = NULL;
	if (pTmp != NULL) {
		pDelete = pTmp;

		pTmp = pTmp->rlink;
		free(pDelete);
	}
}

void delete_cPlaylist(DPlaylistNode** _phead, DPlaylistNode** _currentPlaylist) {
	if (*_currentPlaylist == NULL) {
		printf("playlist가 없습니다.");
		return;
	}
	DPlaylistNode* pDelete = *_currentPlaylist;

	int head_same_current = 0;

	if ((*_phead) == *_currentPlaylist) {
		
		head_same_current = 1;

	}

	if ((*_currentPlaylist)->rlink != NULL) {
		if ((*_currentPlaylist)->rlink->rlink == *_currentPlaylist) {
			(*_currentPlaylist)->llink->rlink = NULL;
			(*_currentPlaylist)->rlink->llink = NULL;
		}
		else {
			(*_currentPlaylist)->llink->rlink = (*_currentPlaylist)->rlink;
			(*_currentPlaylist)->rlink->llink = (*_currentPlaylist)->llink;
		}


		if (head_same_current == 1) {
			(*_currentPlaylist) = (*_currentPlaylist)->rlink;
			(*_phead) = (*_currentPlaylist);
		}
		else {
			(*_currentPlaylist) = (*_currentPlaylist)->rlink;
		}
		

	}
	else {
		(*_currentPlaylist) = NULL;

		(*_phead) = NULL;

	}
	if (pDelete->slink != NULL) {
		delete_SongWithList(pDelete);
	}
	free(pDelete);
}

// 2는 앞쪽으로 1은 뒤쪽으로 이동
void change_cPlaylist(DPlaylistNode** _currentPlaylist, int _dir) {

	if (_dir == 2) {
		if ((*_currentPlaylist)->llink != NULL) {
			(*_currentPlaylist) = (*_currentPlaylist)->llink;
		}
		else {
			printf("\n 이동 할 수 없어요.. 플레이 리스트가 부족해요 \n");
		}
	}
	else if (_dir == 1) {
		if ((*_currentPlaylist)->rlink != NULL) {
			(*_currentPlaylist) = (*_currentPlaylist)->rlink;
		}
		else {
			printf("\n 이동 할 수 없어요.. 플레이 리스트가 부족해요 \n");
		}
	}
	
}

void print_aSong(DPlaylistNode* _currentPlaylist, DSongNode* _currentSong) {
	DSongNode* pTmp = _currentPlaylist->slink;
	printf("Songlist : ");
	if (pTmp == NULL) {
		printf("(null)\n");
		return;
	}
	else if (pTmp->rlink == NULL) {
		printf(" <-[*%s*]-> ", pTmp->sName);
		return;
	}
	while (pTmp != _currentPlaylist->slink->llink) {

		if (pTmp == _currentSong) {
			printf(" <-[*%s*]-> ", pTmp->sName);
		}
		else {
			printf(" <-[%s]-> ", pTmp->sName);
		}

		pTmp = pTmp->rlink;
	}
	if (pTmp == _currentPlaylist->slink->llink) {
		if (pTmp == _currentSong) {
			printf(" <-[*%s*]-> ", pTmp->sName);
		}
		else {
			printf(" <-[%s]-> ", pTmp->sName);
		}

	}
}

void insert_nSongList(DPlaylistNode* _currentPlaylist, char* _buf, DSongNode** _currentSong) {
	DSongNode* pNewNode = (DSongNode*)malloc(sizeof(DSongNode));
	strcpy_s(pNewNode->sName, sizeof(pNewNode->sName), _buf);
	pNewNode->rlink = NULL;
	pNewNode->llink = NULL;

	if (_currentPlaylist->slink == NULL) {
		_currentPlaylist->slink = pNewNode;
		*_currentSong = pNewNode;

	}
	else if (_currentPlaylist->slink->rlink == NULL) {
		pNewNode->rlink = _currentPlaylist->slink;
		pNewNode->llink = _currentPlaylist->slink;
		_currentPlaylist->slink->rlink = pNewNode;
		_currentPlaylist->slink->llink = pNewNode;
		*_currentSong = pNewNode;
	}
	else {
		pNewNode->rlink = (*_currentSong)->rlink;
		pNewNode->llink = (*_currentSong);
		pNewNode->rlink->llink = pNewNode;
		(*_currentSong)->rlink = pNewNode;

		(*_currentSong) = pNewNode;

	}
}



void delete_cSong(DPlaylistNode* _currentPlaylist, DSongNode** _currentSong) {
	if (_currentPlaylist->slink == NULL) {
		printf("Song이 없습니다.");
		return;
	}
	DSongNode* pDelete = *_currentSong;

	int head_same_current = 0;

	if (_currentPlaylist->slink == *_currentSong) {

		head_same_current = 1;
	}

	if ((*_currentSong)->rlink != NULL) {
		if ((*_currentSong)->rlink->rlink == (*_currentSong)) {
			(*_currentSong)->llink->rlink = NULL;
			(*_currentSong)->rlink->llink = NULL;
		}
		else {
			(*_currentSong)->llink->rlink = (*_currentSong)->rlink;
			(*_currentSong)->rlink->llink = (*_currentSong)->llink;
		}


		if (head_same_current == 1) {
			(*_currentSong) = (*_currentSong)->rlink;
			_currentPlaylist->slink = (*_currentSong);
		}
		else {
			(*_currentSong) = (*_currentSong)->rlink;
		}


	}
	else {
		(*_currentSong) = NULL;

		_currentPlaylist->slink = NULL;

	}
	free(pDelete);
}

void change_cSong(DSongNode** _currentSong, int _dir) {
	if (_dir == 2) {
		if ((*_currentSong)->llink != NULL) {
			(*_currentSong) = (*_currentSong)->llink;
		}
		else {
			printf("\n 이동 할 수 없어요.. 플레이 리스트가 부족해요 \n");
		}
	}
	else if (_dir == 1) {
		if ((*_currentSong)->rlink != NULL) {
			(*_currentSong) = (*_currentSong)->rlink;
		}
		else {
			printf("\n 이동 할 수 없어요.. 플레이 리스트가 부족해요 \n");
		}
	}
}

int main(void)
{
	DPlaylistNode* head = NULL;
	char buf[MAX_PLAY_LIST_NAME] = {0};
	DPlaylistNode* currentPlaylist = NULL;
	DSongNode* currentSong = NULL;
	char menu, sub_menu;
	do {
		//printf("메뉴 선택");
		print_playlist_menu();
		printf("Select Menu : ");
		scanf_s(" %c", &menu, 1);
		printf("--------------------------\n");
		printf("Selected playlist menu : %c \n", menu);
		switch (menu) {
		case 'a':
			print_aPlaylist(head, currentPlaylist);
			break;
		case 'c':
			printf("Current playlist : %s\n", currentPlaylist->pName);
			break;
		case 'n':
			printf("Playlist name : ");
			scanf_s("%s", buf, MAX_PLAY_LIST_NAME);
			insert_nPlaylist(&head, buf, &currentPlaylist);
			print_aPlaylist(head, currentPlaylist);
			break;
		case 'd':
			delete_cPlaylist(&head, &currentPlaylist);
			print_aPlaylist(head, currentPlaylist);
			break;
		case '<':
			change_cPlaylist(&currentPlaylist, 2);
			print_aPlaylist(head, currentPlaylist);
			break;
		case '>':
			change_cPlaylist(&currentPlaylist, 1);
			print_aPlaylist(head, currentPlaylist);
			break;
		case 's':
			currentSong = currentPlaylist->slink;
			do {
				printf("Cur PL : %s, Cur Song : %s \n", currentPlaylist->pName,
					currentSong->sName);
				print_song_menu();
				printf("Select Menu : ");
				scanf_s(" %c", &sub_menu, 1);
				printf("Selected song menu : %c \n", sub_menu);
				switch (sub_menu) {
				case 'a':
					print_aSong(currentPlaylist, currentSong);
					break;
				case 'c':
					printf("current song : %s\n", currentSong->sName);
					break;
				case 'n':
					printf("Song name : ");
					scanf_s("%s", buf, MAX_PLAY_LIST_NAME);
					insert_nSongList(currentPlaylist, buf,
						&currentSong);
					print_aSong(currentPlaylist, currentSong);
					break;
				case 'd':
					delete_cSong(currentPlaylist, &currentSong);
					print_aSong(currentPlaylist, currentSong);
					break;
				case '<':
					change_cSong(&currentSong, 2);
					print_aSong(currentPlaylist, currentSong);
					break;
				case '>':
					change_cSong(&currentSong, 1);
					print_aSong(currentPlaylist, currentSong);
					break;
				}
			} while (sub_menu != 'b');
			break;
		}
	} while (menu != 'q');
	return 0;
}