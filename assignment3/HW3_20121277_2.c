#include <string.h>   
//======================���� deque ADT ����=================================
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 300

/*���� deque�� �����Ѵ�.*/
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}DequeType;

// ���� ��� �Լ�
void error(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// �ʱ�ȭ
void init_deque(DequeType* q) {
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(DequeType* q) {
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// �� ����
void add_front(DequeType* q, element item) {
	if (is_full(q)) {
		error("ť�� ��ȭ�����Դϴ�.");
	}
	q->data[q->front] = item;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

// �� ���� ��ȸ
element get_front(DequeType* q) {
	if (is_empty(q)) {
		error("ť�� ��������Դϴ�.");
	}
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

// �� ���� ����
element delete_front(DequeType* q) {
	if (is_empty(q)) {
		error("ť�� ��������Դϴ�.");
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// �� ����
void add_rear(DequeType* q, element item) {
	if (is_full(q)) {
		error("ť�� ��ȭ�����Դϴ�.");
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// �� ��ȸ
element get_rear(DequeType* q) {
	if (is_empty(q)) {
		error("ť�� ������� �Դϴ�.");
	}
	return q->data[q->rear];
}

// �� ����
element delete_rear(DequeType* q) {
	int pre = q->rear;
	if (is_empty(q)) {
		error("ť�� ���� �����Դϴ�.");
	}
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[pre];
}

// ȸ�� �Լ�(���� ���Ҹ� �� �ڷ� ������ �Լ�)
void rotate(DequeType* q) {
	element item = delete_front(q);
	add_rear(q, item);
}

// deque�� ����� ������ ������ �˷��ִ� �Լ�
int get_size(DequeType* q) {
	return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
//=====================================================================


#define MAX_STR_SIZE 300  // ���ڿ� �ִ� ũ��(���� ����)

int str_split_to_Deque(DequeType* dq, int max_arr_size, char* str) {
	/*������ ������ str�� �Է¹޾� ���� ���� split�Ͽ� ����Deque�� �����ϴ� �Լ��̴�.*/
	int* start = dq->data;
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
			if ((dq->data - start) < max_arr_size) {
				add_rear(dq, num * state);

				num = 0;
				state = 0;
				// ���� ���� ����
				while (*(str + 1) == ' ') str++;
			}
			else return get_size(dq);
		}
	}
	// ���ڸ� �и��߿� �ݺ����� �ߴܵǾ����� �ش� ���ڸ� deque�� �߰��Ѵ�.
	if (state) add_rear(dq, num * state);

	return get_size(dq);
}



int main() {
	char str[MAX_STR_SIZE];
	int size;
	int max_val;
	int printed_num;

	DequeType wait_to_print;
	init_deque(&wait_to_print);
	DequeType printed;
	init_deque(&printed);

	printf("�μ��� ��ϵ��� �߿䵵�� �Է��ϼ��� : ");
	if (scanf_s("%[^\n]s", str, MAX_STR_SIZE) == -1) {
		return 0;
	}// �Է��� ���ڿ��� �޴´�.
	size = str_split_to_Deque(&wait_to_print, MAX_QUEUE_SIZE, str); // ���ڿ� �Է��� ���� �迭 wait_to_print�� ����

	printf("\n�μ� :\n");
	while (!is_empty(&wait_to_print)) {
		while (1) {
			max_val = get_front(&wait_to_print);
			for (int i = wait_to_print.front + 2; i <= wait_to_print.rear; i++) {
				if (wait_to_print.data[i] > max_val) {
					max_val = wait_to_print.data[i];
				}
			}
			if (max_val == get_front(&wait_to_print)) {
				break;
			}
			else {
				rotate(&wait_to_print);
			}
		}
		printed_num = delete_front(&wait_to_print);
		add_rear(&printed, printed_num);

		for (int i = printed.front + 1; i <= printed.rear; i++) {
			printf("%d ", printed.data[i]);
		}
		printf("/ ");
		for (int i = wait_to_print.front + 1; i <= wait_to_print.rear; i++) {
			printf("%d ", wait_to_print.data[i]);
		}
		printf("\n");
	}

	return 0;
}
