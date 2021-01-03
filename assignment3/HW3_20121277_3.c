#include <string.h>

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

	for (int i = start; i < size; i++) { // stack�� result�� ��´�.
		// ������ �Է����� ������ ��Ȳ�� ����Ͽ�, �ε�ȣ ������ state ������ �����Ѵ�.
		while (get_size(st) && k > 0 && (state)*peek(st) > (state) * (str[i] - '0')) {
			pop(st);
			k--;
		}
		push(st, str[i] - '0');
	}

	flag = 1;
	end = get_size(st) - k; // k�� 0�� �ƴѰ�� stack�� ��� ���� �� ������ k���� ������ ��.
	if (state == -1) {
		printf("-");
	}

	for (int i = 0; i < end; i++) { // print
		check = 0;              // for���� ���Կ��θ� check�ϴ� ����. for���� �������� ������ ��°��� 0�̴�.
		if (st->data[i] != 0) { // ����� 0200�̶�� �� ���� 0�� ������� �ʰ� 200���� ����ϱ� ����.
			flag = 0;
		}
		if (!flag) {
			printf("%d", st->data[i]);
		}
	}

	if (flag || check) { // for���� ���� ���ϰų�(end = 0�� case) stack�� 0�� ��� ���(00 ���� case)
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

	printf("������ �Է��ϼ��� : ");
	if (scanf("%s", str) == -1) {
		return 0;
	}
	str[MAX_STACK_SIZE - 1] = 0;
	size = strlen(str);
	printf("������ ������ ������ �Է��ϼ���. : ");
	if (scanf("%d", &k) == -1) {
		return 0;
	}

	if (str[0] == '-') {
		check = 1;
	}
	if (k > size - check || k < 0) {
		printf("\nerr: ������ ������ ������ �߸� �ԷµǾ����ϴ�.\n");
		exit(1);
	}

	print_result(str, &st, k);

	return 0;
}
