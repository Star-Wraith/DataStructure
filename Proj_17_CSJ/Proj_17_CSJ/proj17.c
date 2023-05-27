#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define SIZE 100000 // 데이터크기를 변경하며 테스트

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) 			// 최솟값 탐색
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], temp);
	}
}

// 삽입정렬
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j]; 		// 레코드의 오른쪽 이동
		list[j + 1] = key;
	}
}

void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) 	// 앞뒤의 레코드를 비교한 후 교체
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}

// gap 만큼 떨어진 요소들을 삽입 정렬
// 정렬의 범위는 first에서 last
inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
//
void shell_sort(int list[], int n)   // n = size
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)		// 부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

int* sorted = NULL; // 추가 공간이 필요
// i는 정렬된 왼쪽리스트에 대한 인덱스
// j는 정렬된 오른쪽리스트에 대한 인덱스
// k는 정렬될 리스트에 대한 인덱스

void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	if (i > mid) 	// 남아 있는 레코드의 일괄 복사
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else 	// 남아 있는 레코드의 일괄 복사
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	// 배열 sorted[]의 리스트를 배열 list[]로 복사
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;              // 리스트의 균등분할
		merge_sort(list, left, mid);     // 부분리스트 정렬
		merge_sort(list, mid + 1, right);//부분리스트 정렬
		merge(list, left, mid, right);    // 합병
	}
}


int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

typedef int element;
typedef struct { // 큐 타입
	element data[SIZE];
	int front, rear;
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
	return ((q->rear + 1) % SIZE == q->front);
}

// 원형큐 출력 함수
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % SIZE;
	return q->data[q->front];
}

#define BUCKETS 10
#define DIGITS 4
void radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init_queue(&queues[b]);	// 큐들의 초기화

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++)				// 데이터들을 자리수에 따라 큐에 입력
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0; b < BUCKETS; b++)			// 버켓에서 꺼내어 list로 합친다.
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;				// 그 다음 자리수로 간다.
	}
}

typedef struct {
	int key;
} element_heap;

typedef struct {
	element_heap heap[SIZE];
	int heap_size;
} HeapType;

// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}


HeapType heap;		// 정적 메모리 할당 사용
//HeapType* heap = create();	// 동적 메모리 할당 사용 

// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}


void insert_max_heap(HeapType* h, element_heap item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}

// 삭제 함수
element_heap delete_max_heap(HeapType* h) {
	int parent, child;
	element_heap item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 큰 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child; //인덱스변경
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 우선 순위 큐인 히프를 이용한 정렬
void heap_sort(element_heap a[], int n)
{
	int i;
	HeapType* h;

	h = create();
	init(h);
	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		a[i] = delete_max_heap(h);
	}
	free(h);
}



int main(void)
{
	int i, s_time, e_time;
	int* data = (int*)malloc(sizeof(int) * SIZE); // 각 정렬을 동일한 데이터로 테스트하기 위한 원데이터
		int* list = (int*)malloc(sizeof(int) * SIZE); // 원데이터 -> 정렬된 데이터
	sorted = (int*)malloc(sizeof(int) * SIZE); //병합정렬을 위한 추가 메모리로 글로벌 변수로 선언
		if (data == NULL || list == NULL || sorted == NULL) {
			printf("데이터 저장을 위한 메모리 할당 오류\n"); exit(-1);
		}
	printf("정렬 기법 비교 \n");
	printf("Data 크기 : %d \n\n", SIZE);
	srand(100);
	for (i = 0; i < SIZE; i++) // 난수 생성 및 출력 
		data[i] = rand(); // 난수 발생
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	selection_sort(list, SIZE); // 선택정렬 호출 
	e_time = clock();
	printf("선택정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	insertion_sort(list, SIZE);
	e_time = clock();
	printf("삽입정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	bubble_sort(list, SIZE);
	e_time = clock();
	printf("버블정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	shell_sort(list, SIZE);
	e_time = clock();
	printf("셸정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	merge_sort(list, 0, SIZE - 1);
	e_time = clock();
	printf("병합정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	quick_sort(list, 0, SIZE - 1);
	e_time = clock();
	printf("퀵정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	heap_sort(list, SIZE);
	e_time = clock();
	printf("힙정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	radix_sort(list, SIZE); // 기수정렬 호출 
	e_time = clock();
	printf("기수정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	free(data); free(list); free(sorted);
	return 0;
}
