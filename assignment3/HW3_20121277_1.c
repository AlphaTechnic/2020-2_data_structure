#include <string.h>
#define MAX_STRING_SIZE 21
#define ARR_SIZE 4

//==================stack ADT ����===================//
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 50

typedef char element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s) {
	s->top = -1;
}

// ���� ���� �Լ�
int is_empty(StackType* s) {
	return(s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

// ���� �Լ�
void push(StackType* s, element item) {
	if (is_full(s)) {
		printf("������ ��ȭ���� �Դϴ�.");
		return;
	}
	else {
		s->data[++(s->top)] = item;
	}
}

// ���� �Լ�
element pop(StackType* s) {
	if (is_empty(s)) {
		printf("������ ����ֽ��ϴ�.");
		exit(1);
	}
	else {
		return s->data[(s->top)--];
	}
}

// top���� ��ȸ �Լ�
element peek(StackType* s) {
	if (is_empty(s)) {
		printf("������ ����ֽ��ϴ�.");
		exit(1);
	}
	else {
		return s->data[s->top];
	}
}

int get_size(StackType* s) {
	return (s->top) + 1;
}
/////////////////////////////////////////////////////////


// ���� �迭�� ����
char opening[ARR_SIZE] = {'(', '[', '{'};
char closing[ARR_SIZE] = {')', ']', '}'};

int check_parentheses(char *str){
	StackType s;
	init_stack(&s);
	
	char ch, open_ch;
	int n = strlen(str);
	
	for (int i = 0; i < n; i++) {
		ch = str[i];

		switch (ch) {
		case '(': case '[': case '{':
			push(&s, ch);
			break;
		case ')': case ']': case '}':
			if (is_empty(&s)) {
				return 0;
			}
			else {
				open_ch = pop(&s);
				if ((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') || (open_ch == '{' && ch != '}')) {
					return 0;
				}
			}
			break;
		default:
			printf("err : ��ȣ�� �ƴ� ���ڰ� �ԷµǾ����ϴ�.");
			exit(1);
		}
	}	
	if (!is_empty(&s)) {
		return 0;
	}
	return 1;
}

int main() {
	char str[MAX_STRING_SIZE];
	printf("�Է��� ���ڿ��� ��ȣ �˻縦 �����մϴ� : ");
	if (scanf("%s", str) == -1) {
		return 0;
	}

	if (check_parentheses(str)) {
		printf("true");
	}
	else {
		printf("false");
	}

	return 0;
}