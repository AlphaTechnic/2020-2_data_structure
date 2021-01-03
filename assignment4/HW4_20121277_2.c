#define MAX_SIZE 10
///////////////////////Circular Linked List ADT//////////////////////
#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// 리스트의 항목 출력
void print_list(ListNode* tail) {
	ListNode* p;

	if (tail == NULL) return;
	p = tail->link;
	do {
		printf("%c ", p->data);
		p = p->link;
	} while (p != tail);
	printf("%c\n", p->data); // 마지막 노드 출력
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
		printf("동적할당 err!");
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
		printf("동적할당 err!");
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

// head에 있는 노드 삭제
ListNode* delete_first(ListNode* tail) {
	ListNode* removed;
	if (tail == NULL) return NULL;
	removed = tail->link;
	tail->link = removed->link;
	free(removed);
	return tail;
}

// pre가 가리키는 노드의 다음 노드 삭제
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

// 마지막 노드 삭제
ListNode* delete_last(ListNode* tail) {
	ListNode* removed = tail;
	ListNode* pre = tail;

	for (pre = tail; pre->link != tail; pre = pre->link);
	tail = delete_after_pre(tail, pre);
	return tail;
}
/////////////////////////////////////////////////////////////////////

int str_split_to_int_arr(int arr[], int max_arr_size, char* str) {
	/*공백을 포함한 str을 입력받아 공백 기준 split하여 arr에 저장하는 함수이다.*/
	int* start = arr;
	int num = 0;
	// 숫자 분리 상태를 기억 (0이면 진행 안됨, -1이면 음수 진행, 1이면 양수 진행)
	int state = 0;

	while (*str == ' ') str++;;  // 앞쪽 공백 제거

	for (; *str; str++) {
		if (*str != ' ') {
			if (state == 0) {  // 숫자 분리가 진행되지 않았다면,
				if (*str == '-') {
					state = -1;     // 음수라는 표시,
					str++;
				}
				else state = 1;  // 양수라는 표시
			}
			// 문자를 숫자로 변경
			num = num * 10 + *str - '0';
		}
		else {
			if ((arr - start) < max_arr_size) {
				*arr++ = num * state;

				num = 0;
				state = 0;
				// 공백 문자 제거
				while (*(str + 1) == ' ') str++;
			}
			else return arr - start;
		}
	}
	// 숫자를 분리중에 반복문이 중단되었으면 해당 숫자를 arr에 추가한다.
	if (state)*arr++ = num * state;;

	return arr - start;
}

int main() {
	ListNode* tail= NULL;
	ListNode* pre;
	char str[MAX_SIZE];
	int arr[2];
	int N, K;

	printf("N과 K를 띄어쓰기로 구분하여 입력하세요. : ");
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