

#define _CRT_SECURE_NO_WARNINGS



#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000
typedef int element;
typedef struct {
	element heap[SIZE+1];
	int heap_size;
} HeapType;

// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}

// 삭제 함수
element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++;
		if (temp >= h->heap[child]) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
void heap_sort(element a[], element b[], int n)
{
	int i;
	HeapType* h;

	h = create();
	init(h);
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		b[i] = delete_max_heap(h);
	}
	free(h);
}

void selection_sort(element a[], element b[], int n) {
	for (int i = 0; i < n - 1; ++i) {
		element temp = a[i];
		int pos = 0;
		for (int j = i + 1; j < n; ++j) {
			if (temp > a[j]) {
				temp = a[j];
				pos = j;
			}

		}
		a[pos] = a[i];
		a[i] = temp;
		b[i] = temp;
		
	}
}

int main(void)
{
	element* list, * sorted_list; //원데이터와 정렬된 데이터 각각 저장용
	int i, s_time, e_time;
	srand(100);
	list = (element*)malloc(sizeof(element) * SIZE);
	sorted_list = (element*)malloc(sizeof(element) * SIZE);
	for (i = 0; i < SIZE; i++) list[i] = rand();
	printf("정수형 데이터 %d개 정렬 \n", SIZE);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", list[i]);
		printf("\n\n");
	}
	s_time = clock();
	heap_sort(list, sorted_list, SIZE);
	e_time = clock();
	printf("Heap Sort 걸린 시간 : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i]);
		printf("\n\n");
	}
	s_time = clock();
	selection_sort(list, sorted_list, SIZE);
	e_time = clock();
	printf("Selection Sort 걸린 시간 : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i]);
		printf("\n");
	}
	return 0;
}
#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct TreeNode {
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;
typedef TreeNode* element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 생성 함수
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

// 초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item->weight < h->heap[i / 2]->weight)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}

// 삭제 함수
element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child]->weight) > h->heap[child + 1]->weight)
			child++;
		if (temp->weight < h->heap[child]->weight) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node =
		(TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

// 이진 트리 제거 함수
void destroy_tree(TreeNode* root) {
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int is_leaf(TreeNode* root) {
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top)
{
	// 1을 저장하고 순환호출한다. 
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}

	// 0을 저장하고 순환호출한다. 
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	// 단말노드이면 코드를 출력한다. 
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}


// 허프만 코드 생성 함수
TreeNode* make_huffman_tree(int freq[], char ch_list[], int n)
{
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;

	e = NULL;
	
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	for (i = 0; i < n; i++) { // 모든 문자에 대한 min heap 생성
		node = make_tree(NULL, NULL);
		/*e->ch = node->ch = ch_list[i];
		e->weight = node->weight = freq[i];*/

		node->ch = ch_list[i];
		node->weight = freq[i];
		e = node;
		insert_min_heap(heap, e);
	}
	for (i = 1; i < n; i++) { //최소노드 두개 노드 삭제 후 합친 1개 노드 추가(n-1번 반복)
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// 두개의 노드를 합친다.
		x = make_tree(e1, e2); //왼쪽 작은값, 오른쪽 두번째 작은 값
		//e->weight = x->weight = e1->weight + e2->weight;
		x->weight = e1->weight + e2->weight;
		e = x;
		printf("%d+%d->%d \n", e1->weight, e2->weight, e->weight);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // 최종 트리
	print_codes(e, codes, top);
	free(heap);
	return e;
	
}
void huffman_decode(TreeNode* root, char* pszhufman)
{
	int i = 0;

	int j = 0;
	char rdata[20];
	char r2data[10][4];
	int k = 0;

	TreeNode* temp = root;
	printf("Decode  ");
	while (pszhufman[i] != '\0') {
		printf("%c", pszhufman[i]);
		if (pszhufman[i] == '0') {

			if (temp->right != NULL) {
				temp = temp->right;
				++i;
				r2data[j][k] = '0';
				++k;

			}
			else {
				rdata[j] = temp->ch;
				r2data[j][k] = '\0';
				++j;
				temp = root;

				k = 0;
			}

		}
		else if (pszhufman[i] == '1') {
			if (temp->left != NULL) {
				temp = temp->left;
				++i;
				r2data[j][k] = '1';
				++k;

			}
			else {
				rdata[j] = temp->ch;
				r2data[j][k] = '\0';
				++j;
				temp = root;

				k = 0;
			}
		}
	}
	if (temp != root) {
		rdata[j] = temp->ch;
		r2data[j][k] = '\0';
		++j;
	}
	putchar('\n');

	int t = 0;
	for (int i = 0; i < j; ++i) {
		while (r2data[i][t] != '\0') {
			printf("%c", r2data[i][t]);
			++t;
		}
		printf(" ==> %c \n",rdata[i]);
		t = 0;
		
	}
}



int main(void)
{
	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4, 6, 8, 12, 15 };
	TreeNode* head;
	head = make_huffman_tree(freq, ch_list, 5);
	huffman_decode(head, "1110101010000101");
	destroy_tree(head);
	return 0;
}

#endif