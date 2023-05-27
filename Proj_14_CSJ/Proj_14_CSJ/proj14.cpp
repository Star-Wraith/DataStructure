#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 1 // ������ ������ �����ϰ� �ش� ���� ��ȣ�� �����Ͽ� �׽�Ʈ
#if PROB == 1
// 1�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
#define MAX_VERTICES 50
#define TRUE 1
typedef struct GraphType {
	int n; // ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

#define MAX_QUEUE_SIZE 100
typedef int qdata;
typedef struct { // ť Ÿ��
	qdata  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(const char* message)
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
void enqueue(QueueType* q, qdata item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
qdata dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// �׷��� �ʱ�ȭ
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

// ���� ���� ����
void set_vertex(GraphType* g, int v)
{
	g->n = v;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// ���� ��ķ� ǥ���� �׷����� ���� ���� �켱 Ž��
void dfs_mat(GraphType* g, int v, int* visited)
{
	int w;
	visited[v] = TRUE; // ���� v�� �湮 ǥ��
	printf("[%d] -> ", v); // �湮�� ���� ���
	for (w = 0; w < g->n; w++) // ���� ���� Ž��
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w, visited); //���� w���� DFS ���� ����
}

void bfs_mat(GraphType* g, int v, int* visited)
{
	int w;
	QueueType q;
	init_queue(&q); // ť �ʱ�ȭ
	visited[v] = TRUE; // ���� v �湮 ǥ��
	printf("[%d] -> ", v);
	enqueue(&q, v); // ���� ������ ť�� ����
	while (!is_empty(&q)) {
		v = dequeue(&q); // ť�� ���� ����
		for (w = 0; w < g->n; w++) // ���� ���� Ž��
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE; // �湮 ǥ��
				printf("[%d] -> ", w);
				enqueue(&q, w); // �湮�� ������ ť�� ����
			}
	}
}

void printf_graph_matrix(GraphType* g) {
	printf("�׷��� ��� ���\n");
	for (int k = 0; k < g->n; ++k) {
		
		if (k == 0) {
			printf("  : %2d", k);
		}
		else {
			printf("%3d", k);
		}

	}
	putchar('\n');
	for (int k = 0; k < g->n; ++k) {

		printf("===");
	}
	printf("===");
	putchar('\n');


	for (int i = 0; i < g->n; ++i) {
		for (int j = 0; j < g->n; ++j) {
			
			if (j == 0) {
				printf("%2d : %d  ", i, g->adj_mat[i][j]);
			}
			else {
				printf("%d  ", g->adj_mat[i][j]);
			}
		}
		putchar('\n');
	}
	putchar('\n');
}


int main(void)
{
	GraphType* g;
	int i;
	int visited[MAX_VERTICES];
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	//�׷��� �ʱ�ȭ �� ���� �߰�
	set_vertex(g, 11);
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	//print matrix of graph
	printf_graph_matrix(g);
	//���� �켱 Ž��
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("���� �켱 Ž��\n");
	dfs_mat(g, 0, visited);
	printf("\n\n");
	//�ʺ� �켱 Ž��
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("�ʺ� �켱 Ž��\n");
	bfs_mat(g, 0, visited);
	printf("\n");
	free(g);
	return 0;
}
#elif PROB == 2
// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
#define MAX_VERTICES 50
#define TRUE 1
typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;
typedef struct GraphType {
	int n; // ������ ����
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

#define MAX_QUEUE_SIZE 100
typedef int qdata;
typedef struct { // ť Ÿ��
	qdata  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(const char* message)
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
void enqueue(QueueType* q, qdata item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
qdata dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// �׷��� �ʱ�ȭ
void init(GraphType* g)
{
	int c;
	g->n = 0;
	for (c = 0; c < MAX_VERTICES; c++)
		g->adj_list[c] = NULL;
}

// ���� ���� ����
void set_vertex(GraphType* g, int v)
{
	g->n = v;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	GraphNode* pNewNode = (GraphNode*)malloc(sizeof(GraphNode));
	pNewNode->link = NULL;
	pNewNode->vertex = end;

	if (g->adj_list[start] == NULL) {
		g->adj_list[start] = pNewNode;
	}
	else {
		GraphNode* pTmp = g->adj_list[start];

		while (pTmp->link != NULL) {
			pTmp = pTmp->link;
		}
		pTmp->link = pNewNode;
	}

}

// ���� ����Ʈ�� ǥ���� �׷����� ���� ���� �켱 Ž��
void dfs_list(GraphType* g, int v, int* visited)
{
	GraphNode* w;
	visited[v] = TRUE; // ���� v�� �湮 ǥ��
	printf("[%d] -> ", v); // �湮�� ���� ���
	for (w = g->adj_list[v]; w; w = w->link)// ���� ���� Ž��
		if (!visited[w->vertex])
			dfs_list(g, w->vertex, visited); //���� w���� DFS ���� ����
}


void bfs_list(GraphType* g, int v, int* visited)
{
	GraphNode* w;
	QueueType q;
	init_queue(&q); // ť �ʱ� ȭ
	visited[v] = TRUE; // ���� v �湮 ǥ��
	printf("[%d] -> ", v);
	enqueue(&q, v); // ���������� ť�� ����
	while (!is_empty(&q)) {
		v = dequeue(&q); // ť�� ����� ���� ����
		for (w = g->adj_list[v]; w; w = w->link) //���� ���� Ž��
			if (!visited[w->vertex]) { // �̹湮 ���� Ž��
				visited[w->vertex] = TRUE; // �湮 ǥ��
				printf("[%d] -> ", w->vertex);
				enqueue(&q, w->vertex); //������ ť�� ����
			}
	}
}

void print_adj_list(GraphType* g) {
	printf("�׷��� ��������Ʈ\n");
	for (int i = 0; i < g->n; ++i) {
		GraphNode* pTmp = g->adj_list[i];
		printf("%4d:  ", i);
		while (pTmp != NULL) {
			printf("%d -> ", pTmp->vertex);
			pTmp = pTmp->link;
		}
		printf("NULL\n");
	}
	putchar('\n');
}

int main(void)
{
	GraphType* g;
	int i;
	int visited[MAX_VERTICES];
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	//�׷��� �ʱ�ȭ �� ���� �߰�
	set_vertex(g, 11);
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	// �׷��� ���
	print_adj_list(g);
	// ���� �켱 Ž��
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("���� �켱 Ž��\n");
	dfs_list(g, 0, visited);
	printf("\n\n");
	// �ʺ� �켱 Ž��
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("�ʺ� �켱 Ž��\n");
	bfs_list(g, 0, visited);
	printf("\n");
	free(g);
	return 0;
}

#endif