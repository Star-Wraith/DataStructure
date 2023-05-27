#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 3 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 10000 /* 무한대 (연결이 없는 경우) */
typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES]; /* 방문한 정점 표시 */
int path[MAX_VERTICES];/* 경유 노드 */

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
	for (i = 0; i < g->n; ++i) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
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
		printf("스택이 가득찼습니다.");
		return;
	}
	
	s->stack[++s->size] = path;
}

int Pop(Stack* s) {

	if (IsEmpty(s)) {
		printf("스택이 가득찼습니다.");
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
			printf(" 경로 없음\n");
			break;
		}
		printf("<%d->%d> ", start,temppop);
		start = temppop;
	}
}



// 다익스트라 알고리즘 - 게임에서도 많이 쓴다.

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
	
	// 방향성 그래프에도 적용 가능
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
	printf("\n정점 %d에서 정점 %d까지의 경로 : ", 0, end);
	print_path(&g, 0, end); // 정점 0에서 정점 end으로 가는 최단경로 출력
	printf("\n");
	return 0;
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */
typedef struct GraphType {
	int n; // 정점의 개수
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
	printf("\n정점 %d에서 정점 %d까지의 경로 : ", start, end);
	printf("%d->", start);
	print_path(start, end); // 정점 start에서 정점 end으로 가는 최단경로 출력
	printf("%d", end);
	printf("\n");
	return 0;
}


#elif PROB == 3
// 3번 문제를 해결하기 위한 프로그램 작성
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;
typedef struct GraphType {
	int n; // 정점의 개수
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
		printf("스택이 가득찼습니다.");
		return;
	}

	s->stack[++s->size] = path;
}

int pop(StackType* s) {

	if (is_empty(s)) {
		printf("스택이 가득찼습니다.");
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

	// 모든 정점의 진입 차수를 계산
	int* in_degree = (int*)malloc(g->n * sizeof(int));
	for (i = 0; i < g->n; i++)			// 초기화
		in_degree[i] = 0;
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];//정점 i에서 나오는 간선들
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}
	// 진입 차수가 0인 정점을 스택에 삽입
	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}
	// 위상 순서를 생성 
	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("정점 %d ->", w);		//정점 출력
		node = g->adj_list[w];	//각 정점의 진입 차수를 변경
		while (node != NULL) {
			int u = node->vertex;
			in_degree[u]--;			//진입 차수를 감소
			if (in_degree[u] == 0) push(&s, u);
			node = node->link;   // 다음 정점
		}
	}
	free(in_degree);
	printf("\n");
	return (i == g->n);	// 반환값이 1이면 성공, 0이면 실패
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
	//위상 정렬 
	topo_sort(&g);
	// 동적 메모리 반환 코드 생략
	delete_graph(&g);
	return 0;
}

#endif