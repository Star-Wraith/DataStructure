#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트

#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5
typedef struct ele {
	const char* date;
	int data_time;
}ele;

typedef struct ment {
	int grade;
	ele class[MAX_QUEUE_SIZE];
} ment;

typedef struct element {
	const char* sub_name;
	const char* pro_name;
	ment class_information;
	
}element;
typedef struct { // 데큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형데큐 출력 함수
void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			putchar('\n');
			printf("교과목 명: %s, 담당교수 : %s, 수업시간 : ", q->data[i].sub_name,q->data[i].pro_name);
			int j = 0;
			while (q->data[i].class_information.class[j].date != NULL) {
				printf(" %s요일 %d교시,", q->data[i].class_information.class[j].date, q->data[i].class_information.class[j].data_time);
				++j;
			}
			
			if (i == q->rear)
				break;
		} while (i != q->front);
		putchar('\n');
	}
	else {
		printf("\n데큐가 비었음\n");
	}
	printf("\n");
}
// 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 삭제 함수
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}
int main(void)
{
	DequeType queue;
	element data1 = { "자료구조","오황석",{4, {"화", 1, "화", 2, "수", 1, "수", 2}} };
	element data2 = { "컴퓨터구조","김경철",{4, {"월", 3, "월", 4, "목", 6, "목", 7}} };
	element data3 = { "선형대수","이용희",{3, {"월", 8, "월", 9, "금", 3}} };
	init_deque(&queue);
	deque_print(&queue);
	add_front(&queue, data1);
	deque_print(&queue);
	add_rear(&queue, data2);
	deque_print(&queue);
	add_front(&queue, data3);
	deque_print(&queue);
	delete_rear(&queue);
	deque_print(&queue);
	delete_front(&queue);
	deque_print(&queue);
	delete_front(&queue);
	deque_print(&queue);
	delete_rear(&queue);
	deque_print(&queue);
	return 0;
}


#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
# include <stdio.h>
# include <stdlib.h>
// 프로그램 5.2에서 다음과 같은 부분을 복사한다. 
// ================ 원형큐 코드 시작 =================


#define MAX_QUEUE_SIZE 50
#define WORK_TIME 10000




typedef struct { // 요소 타입
	int id;
	int arrival_time;
	int service_time;
} element; // 교체!







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
// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}


// 원형큐 출력 함수
//void queue_print(QueueType* q)
//{
//	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
//	if (!is_empty(q)) {
//		int i = q->front;
//		do {
//			i = (i + 1) % (MAX_QUEUE_SIZE);
//			printf("%d | ", q->data[i]);
//			if (i == q->rear)
//				break;
//		} while (i != q->front);
//	}
//	printf("\n");
//}

// ================ 원형큐 코드 종료 =================

typedef struct menu {
	int menu_count;
	int wait_time;
}Menu;

int main(void)
{


	int total_wait = 0;
	int total_customers = 0;

	int service_time = 0;
	int service_customer;

	int service_time2 = 0;
	int service_customer2;

	int cancel_count = 0;

	int random_menu = 0;

	Menu menu0 = { 0 };
	Menu menu1 = { 0 };
	Menu menu2 = { 0 };
	Menu menu3 = { 0 };
	Menu menu4 = { 0 };

	int counter_menu1 = 0;
	int counter_menu2 = 0;

	int counter_sleep1 = 0;
	int counter_sleep2 = 0;

	QueueType queue;
	init_queue(&queue);
	srand(time(NULL));
	for (int clock = 0; clock < WORK_TIME; clock++) {
		if (clock % 7 == 0 && clock != 0) {
			element customer;
			customer.id = total_customers++;
			customer.arrival_time = clock;

			random_menu = rand() % 5;
			if (random_menu == 0) {
				random_menu = 5;
			}
			else if (random_menu == 1) {
				random_menu = 10;
			}
			else if (random_menu == 2) {
				random_menu = 15;
			}
			else if (random_menu == 3) {
				random_menu = 20;
			}
			else if (random_menu == 4) {
				random_menu = 25;
			}
			customer.service_time = random_menu;
			if (is_full(&queue)) {
				++cancel_count;
			}
			else {
				enqueue(&queue, customer);
			}
		}
		if (service_time > 0) {

			if (service_time == 1) {

			}
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				counter_menu1 = service_time;
				if (counter_menu1 == 5) {
					++menu0.menu_count;
					menu0.wait_time += clock - customer.arrival_time;
				}
				if (counter_menu1 == 10) {
					++menu1.menu_count;
					menu1.wait_time += clock - customer.arrival_time;
				}
				if (counter_menu1 == 15) {
					++menu2.menu_count;
					menu2.wait_time += clock - customer.arrival_time;
				}
				if (counter_menu1 == 20) {
					++menu3.menu_count;
					menu3.wait_time += clock - customer.arrival_time;
				}
				if (counter_menu1 == 25) {
					++menu4.menu_count;
					menu4.wait_time += clock - customer.arrival_time;
				}
			}
			else {
				++counter_sleep1;
			}
		}

		if (service_time2 > 0) {
			service_time2--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer2 = customer.id;
				service_time2 = customer.service_time;
				counter_menu2 = service_time2;
				if (counter_menu2 == 5) {
					++menu0.menu_count;
					menu0.wait_time += clock - customer.arrival_time;
				}
				if (counter_menu2 == 10) {
					++menu1.menu_count;
					menu1.wait_time += clock - customer.arrival_time;
				}
				if (counter_menu2 == 15) {
					++menu2.menu_count;
					menu2.wait_time += clock - customer.arrival_time;
				}
				if (counter_menu2 == 20) {
					++menu3.menu_count;
					menu3.wait_time += clock - customer.arrival_time;
				}
				if (counter_menu2 == 25) {
					++menu4.menu_count;
					menu4.wait_time += clock - customer.arrival_time;
				};
			}
			else {
				++counter_sleep2;
			}
		}
	}
	printf("==================Results================\n");
	printf("큐의 갯수: %d\n" , MAX_QUEUE_SIZE);
	printf("Menu 0 %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f \n", menu0.menu_count,menu0.wait_time, (float)(menu0.wait_time)/ (float)(menu0.menu_count));
	printf("Menu 1 %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f \n", menu1.menu_count,menu1.wait_time, (float)(menu1.wait_time)/ (float)(menu1.menu_count));
	printf("Menu 2 %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f \n", menu2.menu_count,menu2.wait_time, (float)(menu2.wait_time)/ (float)(menu2.menu_count));
	printf("Menu 3 %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f \n", menu3.menu_count,menu3.wait_time, (float)(menu3.wait_time)/ (float)(menu3.menu_count));
	printf("Menu 4 %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f \n", menu4.menu_count,menu4.wait_time, (float)(menu4.wait_time)/ (float)(menu4.menu_count));
	printf("취소된 주문 %d개\n", cancel_count);
	printf("서버1과 서버2의 휴식 시간: %d, %d \n", counter_sleep1, counter_sleep2);
	printf("=========================================\n");
	return 0;
}





#endif