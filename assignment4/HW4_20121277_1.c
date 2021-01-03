#define MAX_SIZE 300

/////////////////////Singly Linked List ADT//////////////////////
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

// head�� ����
ListNode* insert_first(ListNode* head, element val) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	
	if (p == NULL) {
		printf("�����Ҵ� err!!");
		exit(1);
	}
	p->data = val;
	p->link = head;
	head = p;
	return head;
}

// ��� pre�ڿ� ���ο� ��� ����
ListNode* insert_after_pre(ListNode* head, ListNode* pre, element val) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));

	if (p == NULL) {
		printf("�����Ҵ� err!!");
		exit(1);
	}
	p->data = val;
	p->link = pre->link;
	pre->link = p;
	return head;
}

// head�� �ִ� ��� ����
ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

// pre�� link�� ����Ű�� ��带 ����
ListNode* delete_after_pre(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

// ������ ���� ��� ����
ListNode* insert_last(ListNode* head, element val) {
	ListNode* ptr = head;
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	if (new_node == NULL) {
		return NULL;
	}

	new_node->data = val;
	new_node->link = NULL;

	if (head == NULL) { // linked list�� ���������,
		head = new_node;
		return head;
	}
	// �׷��� ������, link Ÿ�� �� ������ ����.
	while (1) {
		if (ptr->link == NULL) {
			ptr->link = new_node;
			break;
		}
		ptr = ptr->link;
	}
	return head;
}

// ������ ��� ����
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

// ���Ḯ��Ʈ �μ�
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
		printf("����Ʈ�� ������ϴ�!\n");
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
			else return arr-start;
		}
	}
	// ���ڸ� �и��߿� �ݺ����� �ߴܵǾ����� �ش� ���ڸ� arr�� �߰��Ѵ�.
	if (state)*arr++ = num * state;;

	return arr - start;
}

int main() {
	ListNode* head= NULL;
	int size, k;
	int arr[MAX_SIZE];
	char tmp;
	char str[MAX_SIZE];

	printf("singly linked list�� ����� ������ ũ�� : ");
	if (scanf("%d", &size) == -1) {
		return 0;
	}
	
	tmp = getchar();

	printf("singly linked list�� ����� ������ : ");
	if (scanf("%[^\n]s", str) == -1) {
		return 0;
	}

	printf("ȸ����ų �� : ");
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