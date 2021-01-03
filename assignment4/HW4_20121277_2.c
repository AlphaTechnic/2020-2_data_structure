#define MAX_SIZE 10
///////////////////////Circular Linked List ADT//////////////////////
#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// ����Ʈ�� �׸� ���
void print_list(ListNode* tail) {
	ListNode* p;

	if (tail == NULL) return;
	p = tail->link;
	do {
		printf("%c ", p->data);
		p = p->link;
	} while (p != tail);
	printf("%c\n", p->data); // ������ ��� ���
}

void print_first_node(ListNode* tail) {
	ListNode* p;
	if (tail == NULL) return;
	p = tail->link;
	printf("%c ", p->data);
}

ListNode* insert_first(ListNode* tail, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL) {
		printf("�����Ҵ� err!");
		exit(1);
	}
	node->data = data;
	if (tail == NULL) {
		tail = node;
		node->link = tail;
	}
	else {
		node->link = tail->link;
		tail->link = node;
	}
	return tail;
}

ListNode* insert_last(ListNode* tail, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node == NULL) {
		printf("�����Ҵ� err!");
		exit(1);
	}
	node->data = data;
	if (tail == NULL) {
		tail = node;
		node->link = tail;
	}
	else {
		node->link = tail->link;
		tail->link = node;
		tail = node;
	}
	return tail;
}

// head�� �ִ� ��� ����
ListNode* delete_first(ListNode* tail) {
	ListNode* removed;
	if (tail == NULL) return NULL;
	removed = tail->link;
	tail->link = removed->link;
	free(removed);
	return tail;
}

// pre�� ����Ű�� ����� ���� ��� ����
ListNode* delete_after_pre(ListNode* tail, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;

	if (removed == tail) {
		pre->link = tail->link;
		tail = pre;
		free(removed);
		return tail;
	}
	pre->link = removed->link;
	free(removed);
	return tail;
}

// ������ ��� ����
ListNode* delete_last(ListNode* tail) {
	ListNode* removed = tail;
	ListNode* pre = tail;

	for (pre = tail; pre->link != tail; pre = pre->link);
	tail = delete_after_pre(tail, pre);
	return tail;
}
/////////////////////////////////////////////////////////////////////

int str_split_to_int_arr(int arr[], int max_arr_size, char* str) {
	/*������ ������ str�� �Է¹޾� ���� ���� split�Ͽ� arr�� �����ϴ� �Լ��̴�.*/
	int* start = arr;
	int num = 0;
	// ���� �и� ���¸� ��� (0�̸� ���� �ȵ�, -1�̸� ���� ����, 1�̸� ��� ����)
	int state = 0;

	while (*str == ' ') str++;;  // ���� ���� ����

	for (; *str; str++) {
		if (*str != ' ') {
			if (state == 0) {  // ���� �и��� ������� �ʾҴٸ�,
				if (*str == '-') {
					state = -1;     // ������� ǥ��,
					str++;
				}
				else state = 1;  // ������ ǥ��
			}
			// ���ڸ� ���ڷ� ����
			num = num * 10 + *str - '0';
		}
		else {
			if ((arr - start) < max_arr_size) {
				*arr++ = num * state;

				num = 0;
				state = 0;
				// ���� ���� ����
				while (*(str + 1) == ' ') str++;
			}
			else return arr - start;
		}
	}
	// ���ڸ� �и��߿� �ݺ����� �ߴܵǾ����� �ش� ���ڸ� arr�� �߰��Ѵ�.
	if (state)*arr++ = num * state;;

	return arr - start;
}

int main() {
	ListNode* tail= NULL;
	ListNode* pre;
	char str[MAX_SIZE];
	int arr[2];
	int N, K;

	printf("N�� K�� ����� �����Ͽ� �Է��ϼ���. : ");
	if (scanf("%[^\n]s", str) == -1) {
		return 0;
	}
	str_split_to_int_arr(arr, 2, str);
	N = arr[0];
	K = arr[1];

	for (int i = 0; i < N; i++) {
		tail = insert_last(tail, i + 65);
	}

	int i;
	for (i = 0; i < N; i++) {
		print_first_node(tail);
		tail = delete_first(tail);
		if (i == N-1) break;
		for (int j = 0; j < K-1; j++) {
			tail = tail->link;
		}
	}
	printf("\n");

	return 0;
}