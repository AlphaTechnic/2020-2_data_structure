#include <string.h>
#define MAX_STRING_SIZE 21
#define ARR_SIZE 4

//==================stack ADT 구현===================//
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 50

typedef char element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

// 스택 초기화 함수
void init_stack(StackType* s) {
	s->top = -1;
}

// 공백 검출 함수
int is_empty(StackType* s) {
	return(s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

// 삽입 함수
void push(StackType* s, element item) {
	if (is_full(s)) {
		printf("스택이 포화상태 입니다.");
		return;
	}
	else {
		s->data[++(s->top)] = item;
	}
}

// 삭제 함수
element pop(StackType* s) {
	if (is_empty(s)) {
		printf("스택이 비어있습니다.");
		exit(1);
	}
	else {
		return s->data[(s->top)--];
	}
}

// top원소 조회 함수
element peek(StackType* s) {
	if (is_empty(s)) {
		printf("스택이 비어있습니다.");
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


// 전역 배열로 선언
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
			printf("err : 괄호가 아닌 문자가 입력되었습니다.");
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
	printf("입력한 문자열의 괄호 검사를 진행합니다 : ");
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