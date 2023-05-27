#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

#define PROB 2 // ������ ������ �����ϰ� �ش� ���� ��ȣ�� �����Ͽ� �׽�Ʈ
#if PROB == 1
// 1�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000
struct Edge { // ������ ��Ÿ���� ����ü
	int start, end, weight;
};
typedef struct GraphType {
	int en; // ������ ����
	int vn; // ������ ����
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;
int parent[MAX_VERTICES];
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}
// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// ��Ʈ 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// ��� a�� ��Ʈ�� ã�´�. 
	int root2 = set_find(b);	// ��� b�� ��Ʈ�� ã�´�. 
	if (root1 != root2) 	// ���Ѵ�. 
		parent[root1] = root2;
}
// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	g->vn = 0;
	g->en = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void set_nodes(GraphType* g, int n)
{
	g->vn = n;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->en].start = start;
	g->edges[g->en].end = end;
	g->edges[g->en].weight = w;
	g->en++;
}
// qsort()�� ���Ǵ� �Լ�
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}
// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(GraphType* g)
{
	int edge_accepted = 0;	                 // ������� ���õ� ������ ��	
	int uset, vset;			// ���� u�� ���� v�� ���� ��ȣ
	struct Edge e;

	set_init(g->vn);				// ���� �ʱ�ȭ
	qsort(g->edges, g->en, sizeof(struct Edge), compare);

	printf("ũ�罺Į �ּ� ���� Ʈ�� �˰��� \n");
	int i = 0;
	while (edge_accepted < (g->vn - 1))	// ������ �� < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// ���� u�� ���� ��ȣ 
		vset = set_find(e.end);		                 // ���� v�� ���� ��ȣ
		if (uset != vset) {			// ���� ���� ������ �ٸ���
			printf("���� (%d,%d) %d ����\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// �ΰ��� ������ ��ģ��.
		}
		i++;
	}
}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);
	// test data 1 
	/*set_nodes(g, 7);
	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);*/
	
	// test data 2
	set_nodes(g, 8);
	insert_edge(g, 0, 1, 10);
	insert_edge(g, 0, 3, 6);
	insert_edge(g, 0, 7, 1);
	insert_edge(g, 1, 2, 4);
	insert_edge(g, 1, 5, 2);
	insert_edge(g, 2, 3, 11);
	insert_edge(g, 2, 5, 7);
	insert_edge(g, 3, 7, 3);
	insert_edge(g, 4, 5, 5);
	insert_edge(g, 4, 7, 8);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 6, 7, 12);
	
	kruskal(g);
	free(g);
	return 0;
}
#elif PROB == 2
// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L
typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// �ּ� dist[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)                  // ���õ��� ���� ó�� ��� i ����
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++) // ���õ��� ���� ��� �� dist�� ���� ���� ��弱���Ͽ� v�� �Ҵ�
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	return (v);
}

//
void prim(GraphType* g, int s)
{
	int i, u, v;

	for (u = 0; u < g->n; u++)
		distance[u] = INF;
	distance[s] = 0;
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		if (distance[u] == INF) return; //���� �ȵ�
		printf("���� %d �߰�, distance : %d\n", u, distance[u]);
		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) {
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];
				}
					
			}

		}
	}
}


int main(void)
{
	int i;
	//test data1
	//GraphType g = { 7,
	//{{ 0, 29, INF, INF, INF, 10, INF },
	//{ 29, 0, 16, INF, INF, INF, 15 },
	//{ INF, 16, 0, 12, INF, INF, INF },
	//{ INF, INF, 12, 0, 22, INF, 18 },
	//{ INF, INF, INF, 22, 0, 27, 25 },
	//{ 10, INF, INF, INF, 27, 0, INF },
	//{ INF, 15, INF, 18, 25, INF, 0 } }
	//};
	//test data2
	
	GraphType g = { 8,
	{ { 0, 10, INF, 6, INF, INF, INF, 1 },
	{ 10, 0, 4, INF, INF, 2, INF, INF },
	{ INF, 4, 0, 11, INF, 7, INF, INF },
	{ 6, INF, 11, 0, INF, INF, INF, 3 },
	{ INF, INF, INF, INF, 0, 5, INF, 8},
	{ INF, 2, 7, INF, 5, 0, 9, INF },
	{ INF, INF, INF, INF, INF, 9, 0, 12 },
	{ 1, INF, INF, 3, 8, INF, 12, 0 }
	}
	};
	
	prim(&g, 0);
	//�߰��� � ������ �����ؾ� �ұ ǥ���������� ���ڴ�. 
	return 0;
}

#endif