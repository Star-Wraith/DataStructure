#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 3 // ������ ������ �����ϰ� �ش� ���� ��ȣ�� �����Ͽ� �׽�Ʈ
#if PROB == 1

#define MAX_QUEUE_SIZE 1000000
// 1�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�

// ===== ����ť �ڵ� ���� ======

int g_check_size = 0;
int print_count = 0;

typedef  struct ele {
	int virus;
	int time;
} element;
typedef struct { // ť Ÿ��
	element* data;
	int front, rear;
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
// ����ť ��� �Լ�
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
// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ������ data�� virus, time�� �ΰ��� �ް� �ϰ� - clear
// (2*N, T+1), (N/3, T+1) ����Լ� �����
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

			printf("%d ������ �Ǵµ� �ʿ��� �ҿ� �ð� %d ", virus_status.virus, virus_status.time);
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

				printf("%d ������ �Ǵµ� �ʿ��� �ҿ� �ð� %d ", virus_status.virus, virus_status.time);
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
	printf("���� ���̷��� �� �Է� : ");
	scanf_s("%d", &problem);
	VirusMultiplication(&q, check, problem);

	free(q.data);
	free(check);
	return 0;
}
#elif PROB == 2
// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
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
// ����ť ��� �Լ�
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
// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void AscendingOrder(QueueType* _queue, int num) {

	for (int i = 1; i <= num; ++i) {
		enqueue(_queue, i);
	}
}

void SurviveGame(QueueType* _queue, int num, int k, int* box) {
	printf("���õ� ����� ��ȣ: ");
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
		printf("���� ��Ƴ��� ����� %d ��ġ�� ���� �� ����̴�. ", survivor);
	}
}

int main(void)
{
	QueueType queue;
	int human_num = 0;
	int k_num = 0;
	int store_box[MAX_QUEUE_SIZE] = { 0 };
	init_queue(&queue);
	
	printf("���ӿ� �����ϴ� ����� �� n�� �����ϴ� k�� �Է� :");
	scanf_s("%d%d", &human_num, &k_num);
	AscendingOrder(&queue, human_num);
	SurviveGame(&queue, human_num, k_num, store_box);
	


	return 0;
}
#elif PROB == 3
// 3�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 100
typedef int element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// ���� ���� ���� �Լ�
void init_queue_Q(QueueType* q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty_Q(QueueType* q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full_Q(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ����ť ��� �Լ�
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
// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full_Q(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty_Q(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

#define MAX_STACK_SIZE 100


typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item; //s->top++; s->data[s->top];
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--]; //e = s->data[s->top]; s->top--; return e;
}

// �����Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)];
}





void AscendingOrderRQ(QueueType* _queue, int num) {

	for (int i = 1; i <= num; ++i) {
		enqueue(_queue, i);
	}
}

// ó���� ���ÿ� ���ڰ� �ִ��� Ȯ�� ���ڰ� ������ �� ���ڶ� ��
// ������ �� ������ �н� ũ�� fail
// �� ���� ť���� ��� ���������� ��������
void CompareStart(QueueType* rq, QueueType* lq, int num, StackType* s , int* mission) {
	int i = 0;
	if (num == 1) {
		printf("���� ���� ���� : ����");
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
				printf("���� ���� ���� : �Ұ���");
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
				printf("���� ���� ���� : �Ұ���");
				return;
			}
		}
		 
	}
	// i == num
	printf("���� ���� ���� : ����");
}

// �ǰ￡ �������� �밡�ٷ� �߽��ϴ�.
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


	int n = 2;  // ����� ���ϴ� ���� 1 ~ 10



	int testNumberSquence[MAX_QUEUE_SIZE] = {0};

	printf("%d���� �׽�Ʈ ����\n", n);
	Nogada(n, testNumberSquence);

	AscendingOrderRQ(&RQ, n);
	CompareStart(&RQ, &LQ, n, &s, testNumberSquence);
}
#endif