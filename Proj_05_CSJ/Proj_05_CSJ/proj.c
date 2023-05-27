#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define _CRT_SECURE_NO_WARNINGS

#define PROB 1 // ������ ������ �����ϰ� �ش� ���� ��ȣ�� �����Ͽ� �׽�Ʈ
#if PROB == 1
// 1�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�
// �������� �켱������ ��ȯ�Ѵ�.
typedef char element;
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

typedef int element_int;
typedef struct {
	element_int data[MAX_STACK_SIZE];
	int top;
} StackTypeInt;

// ���� �ʱ�ȭ �Լ�
void init_stackInt(StackTypeInt* s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_emptyInt(StackTypeInt* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_fullInt(StackTypeInt* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void pushInt(StackTypeInt* s, element_int item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item; //s->top++; s->data[s->top];
}
// �����Լ�
element_int popInt(StackTypeInt* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--]; //e = s->data[s->top]; s->top--; return e;
}

// �����Լ�
element_int peekInt(StackTypeInt* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)];
}


int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}


// ���� ǥ�� ���� -> ���� ǥ�� ����
void infix_to_postfix(char exp[] , char* patemp)
{
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;
	char temp[500] = { 0 };
	int j = 0;
	init_stack(&s); // ���� �ʱ�ȭ
	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // ������
			// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch) <=
				prec(peek(&s)))) {
				temp[j] = pop(&s);
				++j;
				//printf("%c", pop(&s));
			}

			push(&s, ch);
			break;
		case '(': // ���� ��ȣ
			push(&s, ch);
			break;
		case ')': // ������ ��ȣ
			top_op = pop(&s);
			// ���� ��ȣ�� ���������� ���
			while (top_op != '(') {
				temp[j] = top_op;
				++j;
				//printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		default: // �ǿ�����
			temp[j] = ch;
			++j;
			//printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s)) // ���ÿ� ����� �����ڵ� ���
	{
		temp[j] = pop(&s);
		++j;
		//printf("%c", pop(&s));
	}
	strcpy_s(patemp, sizeof(temp), temp);
		
}
// ���� ǥ�� ���� ��� �Լ�
int eval(char exp[])
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	int number_count = 0;
	char temp[20] = { 0 };
	StackTypeInt s;
	init_stackInt(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			if (ch != ' ') {
				temp[number_count] = ch;
				++number_count;
			}
			else {
				if (temp[0] != NULL) {
					 value = atoi(temp);
					 pushInt(&s, value);
					 memset(temp, 0, sizeof(temp));
					 number_count = 0;
				}
				
			}
		}
		else { //�������̸� �ǿ����ڸ� ���ÿ��� ����
			if (temp[0] != NULL) {
				value = atoi(temp);
				pushInt(&s, value);
				memset(temp, 0, sizeof(temp));
				number_count = 0;
			}
			op2 = popInt(&s);
			op1 = popInt(&s);
			switch (ch) { //������ �����ϰ� ���ÿ� ����
			case '+': pushInt(&s, op1 + op2); break;
			case '-': pushInt(&s, op1 - op2); break;
			case '*': pushInt(&s, op1 * op2); break;
			case '/': pushInt(&s, op1 / op2); break;
			}
		}
	}
	if (s.top > 0) {
		printf("���Ŀ���");
		return -9999;
	}
	else {
		return popInt(&s);
	}

}
int main(void)
{
	
	char *s = "100 + 11  20  (20 + 10) / 100 + 5 - 3 ";   // ���Ŀ���
	//char* s = "10 + 20 * (20 + 10) / 100 + 5 - 3 ";         // �ùٸ���
	//char *s = "100 + 11 + 20 * (20 + 10) / 100 + 5 - 3 "; // �ùٸ� ��
	char temp[500] = { 0 };
	
	printf("����ǥ�ü��� %s \n", s);
	printf("����ǥ�ü��� ");
	infix_to_postfix(s, temp);
	printf("%s\n", temp);
	int result;
	result = eval(temp);
	if (result != -9999) {
		printf("������� %d\n", result);
	}

	return 0;
}
#elif PROB == 2

// 2�� ������ �ذ��ϱ� ���� ���α׷� �ۼ�


typedef struct { // ��ü!
	short r;
	short c;
} element;
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

#define MAZE_SIZE 6
// ���α׷� 4.3���� ���� �ڵ� �߰� ��
element Prev = { 0,0 };
element here = { 1,0 }, entry = { 1,0 };
int stack_count = 1;
char maze[MAZE_SIZE][MAZE_SIZE] = {
{ '1', '1', '1', '1', '1', '1' },
{ 'e', '0', '1', '0', '0', '1' },
{ '1', '0', '0', '0', '1', '1' },
{ '1', '0', '1', '0', '1', '1' },
{ '1', '0', '1', '0', '0', 'x' },
{ '1', '1', '1', '1', '1', '1' },
};

// ��ġ�� ���ÿ� ����
int push_loc(StackType * s, int r, int c)
{
	if (r < 0 || c < 0) return 0;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		if (Prev.c != 0 || Prev.r != 0) {
			push(s, Prev);
			Prev.c = 0;
			Prev.r = 0;
			++stack_count;
		}
		push(s, tmp);
		++stack_count;
		return 1;
	}
	return 0;
}
// �̷θ� ȭ�鿡 ����Ѵ�. 
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}

}

void print_stack(StackType* s) {
	
	element temp[MAZE_SIZE * MAZE_SIZE];
	int i = stack_count - 1;
	printf("���:\n");
	printf("<row   col>\n");
	while (s->top != -1) {
		temp[i] = pop(s);
		--i;
	}
	for (int j = 0; j < stack_count; ++j) {
		printf("<%d     %d>\n", temp[j].r, temp[j].c);
	}

}


int main(void)
{
	int r, c;
	StackType s;
	init_stack(&s);
	here = entry;
	element tmp;
	tmp.r = here.r;
	tmp.c = here.c;
	push(&s, tmp);
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';

		if (push_loc(&s, r - 1, c)) {
			here.r = r - 1;
			here.c = c;
		}
		else if (push_loc(&s, r + 1, c)) {
			here.r =r + 1;
			here.c = c;
		}
		else if (push_loc(&s, r, c - 1)) {
			here.r = r;
			here.c = c - 1;

		}
		else if (push_loc(&s, r, c + 1)) {
			here.r = r;
			here.c = c + 1;
		}
		else {
			here = pop(&s);
			Prev = here;
			--stack_count;
		}
		

		if (is_empty(&s)) {
			printf("����\n");
			return;
		}
	}
	printf("-------------�̷�--------------");
	maze_print(maze);
	printf("-------------�̷�--------------\n");
	printf("����\n");
	print_stack(&s);
	return 0;
}


#endif