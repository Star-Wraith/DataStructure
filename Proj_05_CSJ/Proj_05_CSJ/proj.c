#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define _CRT_SECURE_NO_WARNINGS

#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
// 연산자의 우선순위를 반환한다.
typedef char element;
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

typedef int element_int;
typedef struct {
	element_int data[MAX_STACK_SIZE];
	int top;
} StackTypeInt;

// 스택 초기화 함수
void init_stackInt(StackTypeInt* s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_emptyInt(StackTypeInt* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_fullInt(StackTypeInt* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void pushInt(StackTypeInt* s, element_int item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item; //s->top++; s->data[s->top];
}
// 삭제함수
element_int popInt(StackTypeInt* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--]; //e = s->data[s->top]; s->top--; return e;
}

// 삭제함수
element_int peekInt(StackTypeInt* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
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


// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char exp[] , char* patemp)
{
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;
	char temp[500] = { 0 };
	int j = 0;
	init_stack(&s); // 스택 초기화
	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // 연산자
			// 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (prec(ch) <=
				prec(peek(&s)))) {
				temp[j] = pop(&s);
				++j;
				//printf("%c", pop(&s));
			}

			push(&s, ch);
			break;
		case '(': // 왼쪽 괄호
			push(&s, ch);
			break;
		case ')': // 오른쪽 괄호
			top_op = pop(&s);
			// 왼쪽 괄호를 만날때까지 출력
			while (top_op != '(') {
				temp[j] = top_op;
				++j;
				//printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		default: // 피연산자
			temp[j] = ch;
			++j;
			//printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s)) // 스택에 저장된 연산자들 출력
	{
		temp[j] = pop(&s);
		++j;
		//printf("%c", pop(&s));
	}
	strcpy_s(patemp, sizeof(temp), temp);
		
}
// 후위 표기 수식 계산 함수
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
		else { //연산자이면 피연산자를 스택에서 제거
			if (temp[0] != NULL) {
				value = atoi(temp);
				pushInt(&s, value);
				memset(temp, 0, sizeof(temp));
				number_count = 0;
			}
			op2 = popInt(&s);
			op1 = popInt(&s);
			switch (ch) { //연산을 수행하고 스택에 저장
			case '+': pushInt(&s, op1 + op2); break;
			case '-': pushInt(&s, op1 - op2); break;
			case '*': pushInt(&s, op1 * op2); break;
			case '/': pushInt(&s, op1 / op2); break;
			}
		}
	}
	if (s.top > 0) {
		printf("수식오류");
		return -9999;
	}
	else {
		return popInt(&s);
	}

}
int main(void)
{
	
	char *s = "100 + 11  20  (20 + 10) / 100 + 5 - 3 ";   // 수식오류
	//char* s = "10 + 20 * (20 + 10) / 100 + 5 - 3 ";         // 올바른값
	//char *s = "100 + 11 + 20 * (20 + 10) / 100 + 5 - 3 "; // 올바른 값
	char temp[500] = { 0 };
	
	printf("중위표시수식 %s \n", s);
	printf("후위표시수식 ");
	infix_to_postfix(s, temp);
	printf("%s\n", temp);
	int result;
	result = eval(temp);
	if (result != -9999) {
		printf("결과값은 %d\n", result);
	}

	return 0;
}
#elif PROB == 2

// 2번 문제를 해결하기 위한 프로그램 작성


typedef struct { // 교체!
	short r;
	short c;
} element;
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

#define MAZE_SIZE 6
// 프로그램 4.3에서 스택 코드 추가 끝
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

// 위치를 스택에 삽입
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
// 미로를 화면에 출력한다. 
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
	printf("경로:\n");
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
			printf("실패\n");
			return;
		}
	}
	printf("-------------미로--------------");
	maze_print(maze);
	printf("-------------미로--------------\n");
	printf("성공\n");
	print_stack(&s);
	return 0;
}


#endif