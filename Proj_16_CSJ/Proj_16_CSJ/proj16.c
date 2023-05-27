#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 3 // ������ ������ �����ϰ� �ش� ���� ��ȣ�� �����Ͽ� �׽�Ʈ

#if PROB == 1
// 1�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 10000 /* ���Ѵ� (������ ���� ���) */
typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int distance[MAX_VERTICES];/* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES]; /* �湮�� ���� ǥ�� */
int path[MAX_VERTICES];/* ���� ��� */

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status(GraphType* g) { // 
	static int step_number = 0;
	printf("STEP %d:", ++step_number);
	printf("distance: ");
	for (int i = 0; i < g->n; ++i) {
		if (g->weight[0][i] > distance[i]) {
			g->weight[0][i] = distance[i];
			g->weight[i][0] = distance[i];
		}
		if (g->weight[0][i] == INF) {
			printf(" * ");
		}
		else {
			printf("%2d ", g->weight[0][i]);
		}
	}
	putchar('\n');
	printf("\t found:\t ");
	for (int i = 0; i < g->n; ++i) {
		printf("%2d ", found[i]);
	}
	putchar('\n');
	putchar('\n');
	
	if (step_number == g->n) {
		printf("Index  : ");
		for (int i = 0; i < g->n; ++i) {
			printf("%2d ", i);
		}
		
		printf("\nPath[i]: ");
		for (int i = 0; i < g->n; ++i) {
			printf("%2d ", path[i]);
		}
		putchar('\n');
	}


}

//
void shortest_path(GraphType* g, int start)
{
	
	int i, u, w;
	for (i = 0; i < g->n; ++i) /* �ʱ�ȭ */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;
	for (i = 0; i < g->n; ++i) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; ++w)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					path[w] = u;
				}
					
	}
	
}

typedef struct Stack {
	int size;
	int stack[MAX_VERTICES];
}Stack;

void init(Stack* s) {
	s->size = -1;
}


int IsFull(Stack* s) {
	
	if (s->size >= MAX_VERTICES)
		return 1;
	
	return 0;
}

int IsEmpty(Stack* s) {

	if (s->size == -1)
		return 1;

	return 0;
}

void Push(Stack* s, int path) {

	if (IsFull(s)) {
		printf("������ ����á���ϴ�.");
		return;
	}
	
	s->stack[++s->size] = path;
}

int Pop(Stack* s) {

	if (IsEmpty(s)) {
		printf("������ ����á���ϴ�.");
		return;
	}

	return s->stack[s->size--];
}

void print_path(GraphType* g, int start, int end) {
	
	Stack s;
	init(&s);
	int destination = end;
	int temppop = 0;
	while (destination != start) {
		
		Push(&s, destination);
		destination = path[destination];
	}

	while (!IsEmpty(&s)) {
		
		temppop = Pop(&s);
		if (start == 0 && distance[temppop] == INF) {
			printf(" ��� ����\n");
			break;
		}
		printf("<%d->%d> ", start,temppop);
		start = temppop;
	}
}



// ���ͽ�Ʈ�� �˰��� - ���ӿ����� ���� ����.

int main(void)
{

	int end;
	// test data 1
	
	//GraphType g = { 7,
	//{{ 0, 7, INF, INF, 3, 10, INF },
	//{ 7, 0, 4, 10, 2, 6, INF },
	//{ INF, 4, 0, 2, INF, INF, INF },
	//{ INF, 10, 2, 0, 11, 9, 4 },
	//{ 3, 2, INF, 11, 0, INF, 5 },
	//{ 10, 6, INF, 9, INF, 0, INF },
	//{ INF, INF, INF, 4, 5, INF, 0 } }
	//};
	
	// ���⼺ �׷������� ���� ����
	// test data 2
	
	//GraphType g = {6,
	//{{ 0, 50, 45, 10, INF, INF},
	//{ INF, 0, 10, 15, INF, INF},
	//{ INF, INF, 0, INF, 30, INF},
	//{ 20, INF, INF, 0, 15, INF},
	//{ INF, 20, 35, INF, 0, INF},
	//{ INF, INF, INF, INF, 3, 0}}
	//};
	
	// test data 3
///*
	GraphType g = { 7,
	{{ 0, 7, INF, 5,INF, INF, INF},
	{ 7, 0, 8, 9, 7, INF, INF},
	{ INF, 8, 0, INF, 5, INF, INF},
	{ 5, 9, INF, 0, 15, 6, INF },
	{ INF, 7, 5, 15, 0, 8, 9},
	{ INF, INF, INF, 6, 8, 0, 11 },
	{ INF, INF, INF, INF, 9, 11, 0 }
	 }
	};
	//*/
	shortest_path(&g, 0);
	end = 3;
	printf("\n���� %d���� ���� %d������ ��� : ", 0, end);
	print_path(&g, 0, end); // ���� 0���� ���� end���� ���� �ִܰ�� ���
	printf("\n");
	return 0;
}

#elif PROB == 2
// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* ���Ѵ� (������ ���� ���) */
typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int A[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType* g) {
	static int k = -1;
	
	if (k > -1) {
		printf("k=%d\n", k);
	}
	printf("\t");
	for (int i = 0; i < g->n; ++i) {
		printf("%2d\t", i);
	}
	printf("\n===========================================================\n");
	

	for (int i = 0; i < g->n; ++i) {
		printf("%d :\t", i);
		for (int j = 0; j < g->n; ++j) {
			if (g->weight[i][j] > A[i][j]) {
				g->weight[i][j] = A[i][j];
			}
			if (g->weight[i][j] == INF) {
				printf(" *\t");
			}
			else {
				printf("%2d\t", g->weight[i][j]);
			}

		}
		putchar('\n');
	}
	printf("===========================================================\n\n");
	++k;
}

void floyd(GraphType* g)
{

	int i, j, k;
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
			A[i][j] = g->weight[i][j];
	printA(g);

	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j]) {
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = k;
				}
					
		printA(g);
	}
}


void print_path(int start, int end) {

	if (path[start][end] != 0) {
		print_path(start, path[start][end]);
		printf("%d->", path[start][end]);
		print_path(path[start][end], end);
	}
}

int main(void)
{
	int start, end;
	
	// test data 1
	/*GraphType g = { 7,
	{{ 0, 7, INF, INF, 3, 10, INF },
	{ 7, 0, 4, 10, 2, 6, INF },
	{ INF, 4, 0, 2, INF, INF, INF },
	{ INF, 10, 2, 0, 11, 9, 4 },
	{ 3, 2, INF, 11, 0, INF, 5 },
	{ 10, 6, INF, 9, INF, 0, INF },
	{ INF, INF, INF, 4, 5, INF, 0 } }
	};*/
	// test data 2
	GraphType g = { 7,
	{{ 0, 7, INF, 5,INF, INF, INF},
	{ 7, 0, 8, 9, 7, INF, INF},
	{ INF, 8, 0, INF, 5, INF, INF},
	{ 5, 9, INF, 0, 15, 6, INF },
	{ INF, 7, 5, 15, 0, 8, 9},
	{ INF, INF, INF, 6, 8, 0, 11 },
	{ INF, INF, INF, INF, 9, 11, 0 } }
	};
	floyd(&g);
	start = 6; end = 1;
	printf("\n���� %d���� ���� %d������ ��� : ", start, end);
	printf("%d->", start);
	print_path(start, end); // ���� start���� ���� end���� ���� �ִܰ�� ���
	printf("%d", end);
	printf("\n");
	return 0;
}


#elif PROB == 3
// 3�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;
typedef struct GraphType {
	int n; // ������ ����
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;




typedef struct StackType {
	int size;
	int stack[MAX_VERTICES];
}StackType;

void init(StackType* s) {
	s->size = -1;
}


int is_full(StackType* s) {

	if (s->size >= MAX_VERTICES)
		return 1;

	return 0;
}

int is_empty(StackType* s) {

	if (s->size == -1)
		return 1;

	return 0;
}

void push(StackType* s, int path) {

	if (is_full(s)) {
		printf("������ ����á���ϴ�.");
		return;
	}

	s->stack[++s->size] = path;
}

int pop(StackType* s) {

	if (is_empty(s)) {
		printf("������ ����á���ϴ�.");
		return -1;
	}

	return s->stack[s->size--];
}

void graph_init(GraphType* g) {
	g->n = 0;

	for (int i = 0; i < MAX_VERTICES; ++i) {
		g->adj_list[i] = NULL;
	}
}


void set_vertex(GraphType* g, int vertex) {
	g->n = vertex;
}

void insert_edge(GraphType* g, int start, int end) {

	GraphNode* pNewNode = (GraphNode*)malloc(sizeof(GraphNode));

	pNewNode->vertex = end;
	pNewNode->link = g->adj_list[start];
	g->adj_list[start] = pNewNode;

}

int topo_sort(GraphType* g)
{
	int i;
	StackType s;
	GraphNode* node;

	// ��� ������ ���� ������ ���
	int* in_degree = (int*)malloc(g->n * sizeof(int));
	for (i = 0; i < g->n; i++)			// �ʱ�ȭ
		in_degree[i] = 0;
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];//���� i���� ������ ������
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	// ���� ������ 0�� ������ ���ÿ� ����
	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}
	// ���� ������ ���� 
	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("���� %d ->", w);		//���� ���
		node = g->adj_list[w];	//�� ������ ���� ������ ����
		while (node != NULL) {
			int u = node->vertex;
			in_degree[u]--;			//���� ������ ����
			if (in_degree[u] == 0) push(&s, u);
			node = node->link;   // ���� ����
		}
	}
	free(in_degree);
	printf("\n");
	return (i == g->n);	// ��ȯ���� 1�̸� ����, 0�̸� ����
}


void delete_graph(GraphType* g) {

	for (int i = 0; i < g->n; ++i) {
		free(g->adj_list[i]);
	}
}

int main(void)
{
	GraphType g;
	graph_init(&g);
	// test data 1
	
	/*set_vertex(&g, 6);
	insert_edge(&g, 0, 2);
	insert_edge(&g, 0, 3);
	insert_edge(&g, 1, 3);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 2, 5);
	insert_edge(&g, 3, 5);
	insert_edge(&g, 4, 5);*/
	
	// test data 2
	set_vertex(&g, 8);
	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 1, 3);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 7);
	insert_edge(&g, 3, 6);
	insert_edge(&g, 4, 5);
	insert_edge(&g, 4, 6);
	insert_edge(&g, 5, 7);
	insert_edge(&g, 6, 7);
	//���� ���� 
	topo_sort(&g);
	// ���� �޸� ��ȯ �ڵ� ����
	delete_graph(&g);
	return 0;
}

#endif