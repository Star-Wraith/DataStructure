#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 1 // ������ ������ �����ϰ� �ش� ���� ��ȣ�� �����Ͽ� �׽�Ʈ
#if PROB == 1
// 1�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�


typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
} element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;
typedef struct {
	StackNode* top;
} LinkedStack;

// �ʱ�ȭ �Լ�
void init(LinkedStack* s) {
	s->top = NULL;
}

// ���� ���� ���� �Լ�
int is_empty(LinkedStack* s)
{
	return (s->top == NULL);
}
// ��ȭ ���� ���� �Լ�
int is_full(LinkedStack* s)
{
	return 0;
}

// ���� �Լ�
void push(LinkedStack* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}


void print_stack(LinkedStack* s)
{

	printf("============ ���� ���� ============\n");
	if (is_empty(s)) {

		printf("<NULL> <-- TOP \n");
		printf("==================================\n");
		return;
	}

	for (StackNode* p = s->top; p != NULL; p = p->link) {
		
		if (p == s->top) {
			printf("<%d,%d,%d> <-- TOP\n", p->data.x, p->data.y, p->data.z);
		}
		else {
			printf("<%d,%d,%d>\n", p->data.x, p->data.y, p->data.z);
		}


	}
	printf("==================================\n");

}

// ���� �Լ�
element pop(LinkedStack* s)
{
	if (is_empty(s)) {
		printf("������ �������\n");
		element data = { -5555,-5555,-5555 };
		return data;
	}
	else {
		StackNode* temp = s->top;
		element data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}
int main(void)
{
	element item = { 0,0,0 };
	LinkedStack s;
	init(&s);
	print_stack(&s);
	item.x = 1; item.y = 1; item.z = 1;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 2; item.y = 2; item.z = 2;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 3; item.y = 3; item.z = 3;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 4; item.y = 4; item.z = 4;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);

	return 0;
}
#elif PROB == 2
// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
}element;
typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;
typedef struct {
	QueueNode* front, * rear;
} LinkedlistQueue;


void init(LinkedlistQueue* q) {
	q->front = NULL;
	q->rear  = NULL;
}
int is_empty(LinkedlistQueue* q) {
	if (q->front == NULL && q->rear == NULL) {
		return 1;
	}
	else
	{
		return 0;
	}
	
}

// ���� �Լ�
void enqueue(LinkedlistQueue* q, element data)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = data; // ������ ����
	temp->link = NULL; // ��ũ �ʵ带 NULL
	if (is_empty(q)) { // ť�� �����̸�
		q->front = temp;
		q->rear = temp;
	}
	else { // ť�� ������ �ƴϸ�
		q->rear->link = temp; // ������ �߿�
		q->rear = temp;
	}
}

// ���� �Լ�
element dequeue(LinkedlistQueue* q)
{
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q)) { // �������
		printf("ť�� �������\n");
		element data = { -5555,-5555,-5555 };
		return data;
	}
	else {
		data = temp->data; // �����͸� ������.
		q->front = q->front->link; // front�� �������
		if (q->front == NULL) // ���� ����
			q->rear = NULL;
		free(temp); // �����޸� ����
		return data; // ������ ��ȯ
	}
}

void print_queue(LinkedlistQueue* s)
{

	printf("============ ť ���� ============\n");
	if (is_empty(s)) {

		printf("<NULL> <-- Front, Rear \n");
		printf("==================================\n");
		return;
	}

	for (QueueNode* p = s->front; p != s->rear->link; p = p->link) {

		if (p == s->front && p == s->rear) {
			printf("<%d,%d,%d> <-- Front, Rear\n", p->data.x, p->data.y, p->data.z);
		}
		else {
			if (p == s->front) {
				printf("<%d,%d,%d> <-- Front\n", p->data.x, p->data.y, p->data.z);
			}
			else if (p == s->rear) {
				printf("<%d,%d,%d> <-- Rear\n", p->data.x, p->data.y, p->data.z);
			}
			else {
				printf("<%d,%d,%d>\n", p->data.x, p->data.y, p->data.z);
			}

		}



	}
	printf("==================================\n");

}

int main(void)
{
	element item = { 0,0,0 };
	LinkedlistQueue queue;
	init(&queue); // ť �ʱ�ȭ
	print_queue(&queue);
	printf("enqueue item \n");
	item.x = 1, item.y = 1, item.z = 1;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 2, item.y = 2, item.z = 2;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 3, item.y = 3, item.z = 3;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 4, item.y = 4, item.z = 4;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 5, item.y = 5, item.z = 5;
	enqueue(&queue, item); print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue�� data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	return 0;
}
#endif

