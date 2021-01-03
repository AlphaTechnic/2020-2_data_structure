#include <string.h>

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
///////////////////////////////////////////////////


void print_result(char* str, StackType* st, int k) {
	int size = strlen(str);
	int flag;
	int end;
	int state = 1;
	int start = 0;
	int check = 1;

	if (str[0] == '-') {
		state = -1;
		start = 1;
	}

	for (int i = start; i < size; i++) { // stack에 result를 담는다.
		// 음수가 입력으로 들어오는 상황을 고려하여, 부등호 방향을 state 변수로 조정한다.
		while (get_size(st) && k > 0 && (state)*peek(st) > (state) * (str[i] - '0')) {
			pop(st);
			k--;
		}
		push(st, str[i] - '0');
	}

	flag = 1;
	end = get_size(st) - k; // k가 0이 아닌경우 stack에 담긴 원소 중 뒤쪽의 k개를 지워야 함.
	if (state == -1) {
		printf("-");
	}

	for (int i = 0; i < end; i++) { // print
		check = 0;              // for문에 진입여부를 check하는 변수. for문에 진입하지 않으면 출력값은 0이다.
		if (st->data[i] != 0) { // 출력이 0200이라면 맨 앞의 0을 출력하지 않고 200으로 출력하기 위함.
			flag = 0;
		}
		if (!flag) {
			printf("%d", st->data[i]);
		}
	}

	if (flag || check) { // for문에 진입 못하거나(end = 0인 case) stack에 0만 담긴 경우(00 같은 case)
		printf("0");
	}
	return;
}


int main() {
	char str[MAX_STACK_SIZE];
	int k;
	int size;
	int check = 0;

	StackType st;
	init_stack(&st);

	printf("정수를 입력하세요 : ");
	if (scanf("%s", str) == -1) {
		return 0;
	}
	str[MAX_STACK_SIZE - 1] = 0;
	size = strlen(str);
	printf("제거할 숫자의 갯수를 입력하세요. : ");
	if (scanf("%d", &k) == -1) {
		return 0;
	}

	if (str[0] == '-') {
		check = 1;
	}
	if (k > size - check || k < 0) {
		printf("\nerr: 제거할 숫자의 갯수가 잘못 입력되었습니다.\n");
		exit(1);
	}

	print_result(str, &st, k);

	return 0;
}
