#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

int error_index1 = 0;
int error_index2 = 0;	// �������� ��ġ �ε����� �˷��ֱ� ����


typedef struct element_structure {
	char stack_data[MAX_STACK_SIZE];
	int  ch_index[MAX_STACK_SIZE];
}element;
typedef struct {
	element data;
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
void push(StackType* s, char item, int index)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else {
		++(s->top);
		s->data.stack_data[(s->top)] = item;
		s->data.ch_index[s->top] = index;
	}
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else
	{
		element temp;
		temp.ch_index[0] = s->data.ch_index[s->top];
		temp.stack_data[0] = s->data.stack_data[s->top];
		--(s->top);
		return temp;
	}
}

int check_matching(const char* in)
{
	StackType s;
	char ch;
	element temp;
	int i, n = strlen(in); // n= ���ڿ��� ����
	init_stack(&s); // ������ �ʱ�ȭ
	for (i = 0; i < n; i++) {
		ch = in[i]; // ch = ���� ����
		switch (ch) {
		case '(': case '[': case '{':
			push(&s, ch, i);
			break;
		case ')': case ']': case '}':
			if (is_empty(&s)) {
				error_index2 = i;
				return 3;
			}
			else {
				temp = pop(&s);
				if ((temp.stack_data[0] == '(' && ch != ')') ||
					(temp.stack_data[0] == '[' && ch != ']') ||
					(temp.stack_data[0] == '{' && ch != '}')) {
					error_index1 = temp.ch_index[0];
					error_index2 = i;
					return 2;
				}
				break;
			}
		}
	}
	if (!is_empty(&s)) {
		temp = pop(&s);
		error_index1 = temp.ch_index[0];
		return 4; // ���ÿ� ���������� ����
	}
		
	return 1;
}


int main(void)
{
	char* p = "A(x) = 24.5 * (x + func(x, y)) * (r * r * 3.14)( / [7 % 10 *sqrt(25)]];";
	//char* p = "A(x) = [[()((]];";
	int result = check_matching(p);
	if (result == 1)
		printf("%s ��ȣ�˻缺��\n", p);
	else if (result == 2) {
		printf("%s ��ȣ�˻���� %d,%d ��ġ\n", p, error_index1, error_index2);
	}
	else if (result == 3) {
		printf("%s ��ȣ�˻���� %d ��ġ\n", p,error_index2);
	}
	else if (result == 4) {
		printf("%s ��ȣ�˻���� %d ��ġ\n", p, error_index1);
	}
		
	return 0;
}