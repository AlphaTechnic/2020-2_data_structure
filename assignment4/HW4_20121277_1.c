#define MAX_SIZE 300

/////////////////////Singly Linked List ADT//////////////////////
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// head에 삽입
ListNode* insert_first(ListNode* head, element val) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	
	if (p == NULL) {
		printf("동적할당 err!!");
		exit(1);
	}
	p->data = val;
	p->link = head;
	head = p;
	return head;
}

// 노드 pre뒤에 새로운 노드 삽입
ListNode* insert_after_pre(ListNode* head, ListNode* pre, element val) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));

	if (p == NULL) {
		printf("동적할당 err!!");
		exit(1);
	}
	p->data = val;
	p->link = pre->link;
	pre->link = p;
	return head;
}

// head에 있는 노드 삭제
ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

// pre의 link가 가리키는 노드를 삭제
ListNode* delete_after_pre(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

// 마지막 끝에 노드 삽입
ListNode* insert_last(ListNode* head, element val) {
	ListNode* ptr = head;
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	if (new_node == NULL) {
		return NULL;
	}

	new_node->data = val;
	new_node->link = NULL;

	if (head == NULL) { // linked list가 비어있으면,
		head = new_node;
		return head;
	}
	// 그렇지 않으면, link 타고 맨 끝으로 간다.
	while (1) {
		if (ptr->link == NULL) {
			ptr->link = new_node;
			break;
		}
		ptr = ptr->link;
	}
	return head;
}

// 마지막 노드 삭제
ListNode* delete_last(ListNode* head) {
	ListNode* removed = head;
	ListNode* ptr = head;

	if (head == NULL) {
		return NULL;
	}
	while (1) {
		if (ptr->link == NULL) {
			free(ptr);
			break;
		}
		ptr = ptr->link;
	}
	return head;
}

// 연결리스트 인쇄
void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link) {
		printf("%d ", p->data);
	}
	printf("\n");
}

ListNode* rotate(ListNode* head) {
	ListNode* ptr = head;
	ListNode* pre = head;

	if (ptr == NULL || pre == NULL) {
		printf("리스트가 비었습니다!\n");
		exit(1);
	}

	for (ptr = head; ptr->link != NULL; ptr = ptr->link) {
		pre = ptr;
	}
	pre->link = NULL;
	ptr->link = head;
	head = ptr;

	return head;
}
/////////////////////////////////////////////////////////////////

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
			else return arr-start;
		}
	}
	// 숫자를 분리중에 반복문이 중단되었으면 해당 숫자를 arr에 추가한다.
	if (state)*arr++ = num * state;;

	return arr - start;
}

int main() {
	ListNode* head= NULL;
	int size, k;
	int arr[MAX_SIZE];
	char tmp;
	char str[MAX_SIZE];

	printf("singly linked list에 저장될 정수의 크기 : ");
	if (scanf("%d", &size) == -1) {
		return 0;
	}
	
	tmp = getchar();

	printf("singly linked list에 저장될 정수들 : ");
	if (scanf("%[^\n]s", str) == -1) {
		return 0;
	}

	printf("회전시킬 수 : ");
	if (scanf("%d", &k) == -1) {
		return 0;
	}

	str_split_to_int_arr(arr, size, str);
	
	for (int i = 0; i < size; i++) {
		head = insert_last(head, arr[i]);
	}
	//print_list(head);
	
	for (int i = 0; i < k % size; i++) {
		head = rotate(head);
	}
	print_list(head);

	return 0;
}