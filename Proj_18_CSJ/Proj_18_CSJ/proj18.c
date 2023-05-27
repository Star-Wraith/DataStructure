#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 1 // ������ ������ �����ϰ� �ش� ���� ��ȣ�� �����Ͽ� �׽�Ʈ
#if PROB == 1
// 1�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
#define SIZE 1000000 // ����� �������� ����
#define DATA 586321 // ã�� Ű ��

int seqsearch(int list[], int low, int high, int key, int* count)
{
	int i;
	*count = 0;
	for (i = low; i <= high; i++) {
		++(*count);
		if (list[i] == key) {
			return i; // Ž�� ����
		}
	}

	return -1;    	// Ž�� ����
}

int binsearch(int list[], int low, int high, int key, int* count)
{
	int middle;
	*count = 0;
	while (low <= high) { 				// ���� ���ڵ��� ���� ������
		++(*count);
		middle = (low + high) / 2;
		if (key == list[middle]) return middle; 	// Ž�� ����
		else if (key > list[middle]) low = middle + 1; 	// ���� �κи���Ʈ Ž��
		else high = middle - 1; 			// ������ �κи���Ʈ Ž��
	}
	return -1; 					// Ž�� ����
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
	if (list[low] == key) return(low);  // Ž������
	else return -1;  // Ž������
}



int main(void)
{
	int i, s_time, e_time, count, result;
	int* list = (int*)malloc(sizeof(int) * SIZE);
	if (list == NULL) { printf("�޸� �Ҵ� ���� \n"); exit(-1); }
	// ������������ ���� ������ ���� �� ����
	list[0] = 0;
	for (i = 1; i < SIZE; i++) {
		list[i] = list[i - 1] + (rand() % 3);
	}
	printf("Data ũ�� : %d, �˻� ������ : %d \n", SIZE, DATA);
	printf("----------------------------------------------\n");
	s_time = clock();
	result = seqsearch(list, 0, SIZE - 1, DATA, &count); //����Ž�� ȣ�� 
	e_time = clock();
	if (result == -1) printf("�˻� ��� : �˻� ������ ���� \n");
	else printf("�˻���� : %d ��ġ���� ã�� \n", result);
	printf("����Ž�� �ҿ�ð� %d, ��Ƚ�� : %d\n\n", e_time - s_time, count);
	s_time = clock();
	result = binsearch(list, 0, SIZE - 1, DATA, &count); //����Ž�� ȣ�� 
	e_time = clock();
	if (result == -1) printf("�˻� ��� : �˻� ������ ���� \n");
	else printf("�˻���� : %d ��ġ���� ã�� \n", result);
	printf("����Ž�� �ҿ�ð� %d, ��Ƚ�� : %d\n\n", e_time - s_time, count);
	s_time = clock();
	result = search_interpolation(list, 0, SIZE - 1, DATA, &count);//����Ž�� ȣ�� 
	e_time = clock();
	if (result == -1) printf("�˻� ��� : �˻� ������ ���� \n");
	else printf("�˻���� : %d ��ġ���� ã�� \n", result);
	printf("����Ž�� �ҿ�ð� %d, ��Ƚ�� : %d\n\n", e_time - s_time, count);
	free(list);
	return 0;
}
#elif PROB == 2
// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
// AVL Ʈ�� ��� ����



typedef struct AVLNode
{
	int key;
	struct AVLNode* left;
	struct AVLNode* right;
} AVLNode;
// �׽�Ʈ�� ���� main �Լ�

#define MAX_QUEUE_SIZE 100
typedef AVLNode* qdata;
typedef struct { // ť Ÿ��
	qdata  data[MAX_QUEUE_SIZE];
	int  level[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void enqueue(QueueType* q, qdata item, int num)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	q->level[q->rear] = num;
}

// ���� �Լ�
qdata dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
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

	// ���ο� ��Ʈ ��ȯ
	return child;
}

AVLNode* rotate_right(AVLNode* parent) {
	AVLNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	// ���ο� ��Ʈ�� ��ȯ
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

	init_queue(&q);	 // ť �ʱ�ȭ

	if (ptr == NULL) {
		printf("���� Ʈ���Դϴ�.");
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


// �� �κ� rotate �κ� �ϸ� �ɵ� �� ��� ���� �˾ƾ� �� �� ���� 
// LR - child rotate_left���ְ� �� ���� rotate_right	
// RL - child rotate_right���ְ� �� ���� rotate_left
// �� ��� ���� ���ϴ� ���� �ؿ� �����ؾ��ҵ�?


AVLNode* AVL_insert(AVLNode* node, int key)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) {

		return new_node(key);
	}

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (key < node->key) {
		node->left = AVL_insert(node->left, key);
	}
	else if (key > node->key) {
		node->right = AVL_insert(node->right, key);
	}

	node = AVLSet(node);
	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}


AVLNode* min_value_node(AVLNode* node)
{
	AVLNode* current = node;

	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;

	return current;
}


AVLNode* AVL_remove(AVLNode* root, int key)
{
	if (root == NULL) return root;

	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < root->key)
		root->left = AVL_remove(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > root->key)
		root->right = AVL_remove(root->right, key);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
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
		// �� ��° ���
		AVLNode* temp = min_value_node(root->right);

		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->key = temp->key;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->right = AVL_remove(root->right, temp->key);
	}

	root = AVLSet(root);

	return root;
}

int main(void)
{
	AVLNode* root = NULL;
	// 60 50 20 80 90 70 55 10 40 35
	// ���� Ʈ�� ����
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
