#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 3 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1

#define MAX_QUEUE_SIZE 1000000
// 1번 문제를 해결하기 위한 프로그램 작성

// ===== 원형큐 코드 시작 ======

int g_check_size = 0;
int print_count = 0;

typedef  struct ele {
	int virus;
	int time;
} element;
typedef struct { // 큐 타입
	element* data;
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
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형큐 출력 함수
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
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
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 스택의 data를 virus, time값 두개를 받게 하고 - clear
// (2*N, T+1), (N/3, T+1) 재귀함수 만들기
// 
void VirusMultiplication(QueueType* q, int* _check_virus, int problem) {
	/*if (print_count != 0) {
		return;
	}
	element virus_status = dequeue(q);

	for (int i = 0; i <= g_check_size; ++i) {
		if (_check_virus[i] == virus_status.virus) {
			virus_status.virus = 0;
			break;
		}
	}
	if (virus_status.virus != 0) {
		for (int i = 0; i <= g_check_size; ++i) {
			if (_check_virus[i] == 0) {
				_check_virus[i] = virus_status.virus;
				++g_check_size;
				break;
			}
		}
	}
	else {
		VirusMultiplication(q, _check_virus, problem);
	}

	if (problem == virus_status.virus) {
		if (print_count == 0) {

			printf("%d 마리가 되는데 필요한 소요 시간 %d ", virus_status.virus, virus_status.time);
			++print_count;
		}
		return;
	}
	
	element item = { virus_status.virus / 3 , virus_status.time + 1 };
	enqueue(q, item);
	item.virus = 2 * virus_status.virus;
	item.time = virus_status.time + 1;
	enqueue(q, item);
	VirusMultiplication(q, _check_virus, problem);*/

	while (print_count == 0) {

		element virus_status = dequeue(q);

		for (int i = 0; i <= g_check_size; ++i) {
			if (_check_virus[i] == virus_status.virus) {
				virus_status.virus = 0;
				break;
			}
		}
		if (virus_status.virus != 0) {
			for (int i = 0; i <= g_check_size; ++i) {
				if (_check_virus[i] == 0) {
					_check_virus[i] = virus_status.virus;
					++g_check_size;
					break;
				}
			}
		}
		else {
			
			VirusMultiplication(q, _check_virus, problem);
		}

		if (problem == virus_status.virus) {
			if (print_count == 0) {

				printf("%d 마리가 되는데 필요한 소요 시간 %d ", virus_status.virus, virus_status.time);
				++print_count;
			}
			return;
		}

		element item = { virus_status.virus / 3 , virus_status.time + 1 };
		enqueue(q, item);
		item.virus = 2 * virus_status.virus;
		item.time = virus_status.time + 1;
		enqueue(q, item);
	}
}
int main(void)
{
	QueueType q;
	q.data = (element*)malloc(sizeof(element) * MAX_QUEUE_SIZE);
	init_queue(&q);
	int* check = (int*)malloc(sizeof(int) * MAX_QUEUE_SIZE);
	memset(check, 0, sizeof(int) * MAX_QUEUE_SIZE);
	element start_vir = { 1,0 };
	enqueue(&q, start_vir);
	int problem = 0;
	printf("현재 바이러스 수 입력 : ");
	scanf_s("%d", &problem);
	VirusMultiplication(&q, check, problem);

	free(q.data);
	free(check);
	return 0;
}
#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
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
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형큐 출력 함수
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
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
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void AscendingOrder(QueueType* _queue, int num) {

	for (int i = 1; i <= num; ++i) {
		enqueue(_queue, i);
	}
}

void SurviveGame(QueueType* _queue, int num, int k, int* box) {
	printf("선택된 사람의 번호: ");
	while (num != 1) {
		if (num >= k) {
			for (int i = 0; i < k; ++i) {
				if (i != k - 1) {
					box[i] = dequeue(_queue);
				}
				else {
					printf("%d ", dequeue(_queue));
				}

			}
			for (int i = 0; i < k - 1; ++i) {
				if (box[i] != 0) {
					enqueue(_queue, box[i]);
				}
			}
		}
		else {
			int k_copy = k;
			while (k_copy > num) {
				for (int i = 0; i < num; ++i) {

					box[i] = dequeue(_queue);
					
				}
				for (int i = 0; i < num; ++i) {
					if (box[i] != 0) {
						enqueue(_queue, box[i]);
					}
					--k_copy;
				}
			}
			for (int i = 0; i < k_copy; ++i) {
				if (i != k_copy - 1) {
					box[i] = dequeue(_queue);
				}
				else {
					printf("%d ", dequeue(_queue));
				}

			}
			for (int i = 0; i < k_copy - 1; ++i) {
				if (box[i] != 0) {
					enqueue(_queue, box[i]);
				}
			}

		}

		memset(box, 0, sizeof(int) * MAX_QUEUE_SIZE);
		--num;
	}
	if (num == 1) {
		int survivor = dequeue(_queue);
		printf("%d \n", survivor);
		printf("최종 살아남은 사람은 %d 위치에 줄은 선 사람이다. ", survivor);
	}
}

int main(void)
{
	QueueType queue;
	int human_num = 0;
	int k_num = 0;
	int store_box[MAX_QUEUE_SIZE] = { 0 };
	init_queue(&queue);
	
	printf("게임에 참여하는 사람의 수 n과 선택하는 k값 입력 :");
	scanf_s("%d%d", &human_num, &k_num);
	AscendingOrder(&queue, human_num);
	SurviveGame(&queue, human_num, k_num, store_box);
	


	return 0;
}
#elif PROB == 3
// 3번 문제를 해결하기 위한 프로그램 작성
// 2번 문제를 해결하기 위한 프로그램 작성
// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 공백 상태 검출 함수
void init_queue_Q(QueueType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty_Q(QueueType* q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full_Q(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형큐 출력 함수
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty_Q(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
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
	if (is_full_Q(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty_Q(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

#define MAX_STACK_SIZE 100


typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item; //s->top++; s->data[s->top];
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--]; //e = s->data[s->top]; s->top--; return e;
}

// 삭제함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)];
}





void AscendingOrderRQ(QueueType* _queue, int num) {

	for (int i = 1; i <= num; ++i) {
		enqueue(_queue, i);
	}
}

// 처음에 스택에 숫자가 있는지 확인 숫자가 있으면 그 숫자랑 비교
// 같으면 끝 작으면 패스 크면 fail
// 그 다음 큐에서 계속 같을때까지 가져오기
void CompareStart(QueueType* rq, QueueType* lq, int num, StackType* s , int* mission) {
	int i = 0;
	if (num == 1) {
		printf("생성 가능 여부 : 가능");
		return;
	}
	while (i < num) {
		if (s->top != -1) {
			if (mission[i] == peek(s)) {
				enqueue(lq, pop(s));
				++i;
			}
			else if (mission[i] > peek(s)) {
				int temp = dequeue(rq);
				if (mission[i] == temp) {
					enqueue(lq, temp);
					++i;
				}
				else if (mission[i] > temp) {
					push(s, temp);
				}
			}
			else {
				printf("생성 가능 여부 : 불가능");
				return;
			}
			
		}
		else {
			int temp = dequeue(rq);
			if (mission[i] == temp) {
				enqueue(lq, temp);
				++i;
			}
			else if (mission[i] > temp) {
				push(s, temp);
			}
			else {
				printf("생성 가능 여부 : 불가능");
				return;
			}
		}
		 
	}
	// i == num
	printf("생성 가능 여부 : 가능");
}

// 피곤에 멍해져서 노가다로 했습니다.
void Nogada(int num, int* arr_data) {
	if (num == 1) {
		scanf_s("%d", &(arr_data[0]));
	}
	if (num == 2) {
		scanf_s("%d %d", &(arr_data[0]), &(arr_data[1]));
	}
	if (num == 3) {
		scanf_s("%d %d %d", &(arr_data[0]), &(arr_data[1]), &(arr_data[2]));
	}
	if (num == 4) {
		scanf_s("%d %d %d %d", &(arr_data[0]), &(arr_data[1]), &(arr_data[2]), &(arr_data[3]));
	}
	if (num == 5) {
		scanf_s("%d %d %d %d %d", &(arr_data[0]), &(arr_data[1]), &(arr_data[2]), &(arr_data[3]), &(arr_data[4]));
	}
	if (num == 6) {
		scanf_s("%d %d %d %d %d %d", &(arr_data[0]), &(arr_data[1]), &(arr_data[2]), &(arr_data[3]), &(arr_data[4]), &(arr_data[5]));
	}
	if (num == 7) {
		scanf_s("%d %d %d %d %d %d %d", &(arr_data[0]), &(arr_data[1]), &(arr_data[2]), &(arr_data[3]), &(arr_data[4]), &(arr_data[5]), &(arr_data[6]));
	}
	if (num == 8) {
		scanf_s("%d %d %d %d %d %d %d %d", &(arr_data[0]), &(arr_data[1]), &(arr_data[2]), &(arr_data[3]), &(arr_data[4]), &(arr_data[5]), &(arr_data[6]), &(arr_data[7]));
	}
	if (num == 9) {
		scanf_s("%d %d %d %d %d %d %d %d %d", &(arr_data[0]), &(arr_data[1]), &(arr_data[2]), &(arr_data[3]), &(arr_data[4]), &(arr_data[5]), &(arr_data[6]), &(arr_data[7]), &(arr_data[8]));
	}
	if (num == 10) {
		scanf_s("%d %d %d %d %d %d %d %d %d %d", &(arr_data[0]), &(arr_data[1]), &(arr_data[2]), &(arr_data[3]), &(arr_data[4]), &(arr_data[5]), &(arr_data[6]), &(arr_data[7]), &(arr_data[8]), &(arr_data[9]));
	}
}
int main() {
	
	QueueType RQ;
	QueueType LQ;	
	init_queue_Q(&RQ);
	init_queue_Q(&LQ);
	StackType s;
	init_stack(&s);


	int n = 2;  // 몇개인지 정하는 변수 1 ~ 10



	int testNumberSquence[MAX_QUEUE_SIZE] = {0};

	printf("%d개의 테스트 수열\n", n);
	Nogada(n, testNumberSquence);

	AscendingOrderRQ(&RQ, n);
	CompareStart(&RQ, &LQ, n, &s, testNumberSquence);
}
#endif