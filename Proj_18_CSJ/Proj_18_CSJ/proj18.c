#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
#define SIZE 1000000 // 저장된 데이터의 갯수
#define DATA 586321 // 찾는 키 값

int seqsearch(int list[], int low, int high, int key, int* count)
{
	int i;
	*count = 0;
	for (i = low; i <= high; i++) {
		++(*count);
		if (list[i] == key) {
			return i; // 탐색 성공
		}
	}

	return -1;    	// 탐색 실패
}

int binsearch(int list[], int low, int high, int key, int* count)
{
	int middle;
	*count = 0;
	while (low <= high) { 				// 아직 숫자들이 남아 있으면
		++(*count);
		middle = (low + high) / 2;
		if (key == list[middle]) return middle; 	// 탐색 성공
		else if (key > list[middle]) low = middle + 1; 	// 왼쪽 부분리스트 탐색
		else high = middle - 1; 			// 오른쪽 부분리스트 탐색
	}
	return -1; 					// 탐색 실패
}

int search_interpolation(int list[], int start, int end, int key, int* count)
{
	int low, high, j;

	*count = 0;
	low = start;
	high = end - 1;
	while ((list[high] >= key) && (key > list[low])) {
		++(*count);
		j = ((float)(key - list[low]) / (list[high] - list[low])
			* (high - low)) + low;
		if (key > list[j]) low = j + 1;
		else if (key < list[j]) high = j - 1;
		else low = j;
	}
	if (list[low] == key) return(low);  // 탐색성공
	else return -1;  // 탐색실패
}



int main(void)
{
	int i, s_time, e_time, count, result;
	int* list = (int*)malloc(sizeof(int) * SIZE);
	if (list == NULL) { printf("메모리 할당 오류 \n"); exit(-1); }
	// 오름차순으로 정수 데이터 생성 및 저장
	list[0] = 0;
	for (i = 1; i < SIZE; i++) {
		list[i] = list[i - 1] + (rand() % 3);
	}
	printf("Data 크기 : %d, 검색 데이터 : %d \n", SIZE, DATA);
	printf("----------------------------------------------\n");
	s_time = clock();
	result = seqsearch(list, 0, SIZE - 1, DATA, &count); //순차탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("순차탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
	s_time = clock();
	result = binsearch(list, 0, SIZE - 1, DATA, &count); //이진탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("이진탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
	s_time = clock();
	result = search_interpolation(list, 0, SIZE - 1, DATA, &count);//보간탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("보간탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);
	free(list);
	return 0;
}
#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
// AVL 트리 노드 정의



typedef struct AVLNode
{
	int key;
	struct AVLNode* left;
	struct AVLNode* right;
} AVLNode;
// 테스트를 위한 main 함수

#define MAX_QUEUE_SIZE 100
typedef AVLNode* qdata;
typedef struct { // 큐 타입
	qdata  data[MAX_QUEUE_SIZE];
	int  level[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType* q, qdata item, int num)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	q->level[q->rear] = num;
}

// 삭제 함수
qdata dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
int peek(QueueType* q) {
	return q->level[q->front + 1];
}


AVLNode* rotate_left(AVLNode* parent) {
	AVLNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	// 새로운 루트 반환
	return child;
}

AVLNode* rotate_right(AVLNode* parent) {
	AVLNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	// 새로운 루트를 반환
	return child;
}


int get_height(AVLNode* root) {
	if (root == NULL) {
		return 0;
	}

	int node_left_depth = get_height(root->left);
	int node_right_depth = get_height(root->right);

	return node_left_depth > node_right_depth ? node_left_depth + 1 : node_right_depth + 1;
}
int ChildSub(AVLNode* node)
{
	return get_height(node->left) - get_height(node->right);
}

AVLNode* AVLSet(AVLNode* node)
{
	int depth = ChildSub(node);
	if (depth >= 2)
	{
		depth = ChildSub(node->left);
		if (depth >= 1)
		{
			printf("LL : %d\n", node->key);
			node = rotate_left(node);
		}
		else
		{
			printf("LR : %d\n", node->key);
			node->left = rotate_right(node->left);
			node = rotate_left(node);
		}
	}
	else if (depth <= -2)
	{
		depth = ChildSub(node->right);
		if (depth <= -1)
		{
			printf("RR : %d\n", node->key);
			node = rotate_right(node);
		}
		else
		{
			printf("RL : %d\n", node->key);
			node->right = rotate_left(node->right);
			node = rotate_right(node);
		}

	}

	return node;
}

void level_order(AVLNode* ptr)
{



	QueueType q;
	int num = 0;
	int peek_num = 0;

	init_queue(&q);	 // 큐 초기화

	if (ptr == NULL) {
		printf("공백 트리입니다.");
		return;
	}
	enqueue(&q, ptr, 1);
	printf("Level Print");
	while (!is_empty(&q)) {
		peek_num = peek(&q);
		if (peek_num != num) {
			putchar('\n');
			printf("Level%d ", peek_num);
		}
		num = peek_num;
		ptr = dequeue(&q);
		printf("[%d] ", ptr->key);
		if (ptr->left)
			enqueue(&q, ptr->left, num + 1);
		if (ptr->right)
			enqueue(&q, ptr->right, num + 1);
	}
	putchar('\n');
	putchar('\n');

}


AVLNode* new_node(int item)
{
	AVLNode* temp = (AVLNode*)malloc(sizeof(AVLNode));
	temp->key = item;
	temp->left = temp->right = NULL;

	return temp;
}


// 이 부분 rotate 부분 하면 될듯 각 노드 높이 알아야 할 것 같고 
// LR - child rotate_left해주고 그 다음 rotate_right	
// RL - child rotate_right해주고 그 다음 rotate_left
// 각 노드 높이 구하는 것은 밑에 수정해야할듯?


AVLNode* AVL_insert(AVLNode* node, int key)
{
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) {

		return new_node(key);
	}

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (key < node->key) {
		node->left = AVL_insert(node->left, key);
	}
	else if (key > node->key) {
		node->right = AVL_insert(node->right, key);
	}

	node = AVLSet(node);
	// 변경된 루트 포인터를 반환한다. 
	return node;
}


AVLNode* min_value_node(AVLNode* node)
{
	AVLNode* current = node;

	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;

	return current;
}


AVLNode* AVL_remove(AVLNode* root, int key)
{
	if (root == NULL) return root;

	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < root->key)
		root->left = AVL_remove(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > root->key)
		root->right = AVL_remove(root->right, key);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		// 첫 번째나 두 번째 경우
		if (root->left == NULL) {
			AVLNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			AVLNode* temp = root->left;
			free(root);
			return temp;
		}
		// 세 번째 경우
		AVLNode* temp = min_value_node(root->right);

		// 중외 순회시 후계 노드를 복사한다. 
		root->key = temp->key;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = AVL_remove(root->right, temp->key);
	}

	root = AVLSet(root);

	return root;
}

int main(void)
{
	AVLNode* root = NULL;
	// 60 50 20 80 90 70 55 10 40 35
	// 예제 트리 구축
	printf("Insert %d\n", 60); root = AVL_insert(root, 60);
	printf("Insert %d\n", 50); root = AVL_insert(root, 50);
	printf("Insert %d\n", 20); root = AVL_insert(root, 20);
	level_order(root);
	printf("Insert %d\n", 80); root = AVL_insert(root, 80);
	level_order(root);
	printf("Insert %d\n", 90); root = AVL_insert(root, 90);
	level_order(root);
	printf("Insert %d\n", 70); root = AVL_insert(root, 70);
	level_order(root);
	printf("Insert %d\n", 55); root = AVL_insert(root, 55);
	level_order(root);
	printf("Insert %d\n", 10); root = AVL_insert(root, 10);
	level_order(root);
	printf("Insert %d\n", 40); root = AVL_insert(root, 40);
	level_order(root);
	printf("Insert %d\n", 35); root = AVL_insert(root, 35);
	level_order(root);
	printf("Remove %d\n", 50); root = AVL_remove(root, 50);
	level_order(root);
	printf("Remove %d\n", 55); root = AVL_remove(root, 55);
	level_order(root);
	return 0;
}
#endif
