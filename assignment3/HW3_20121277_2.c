#include <string.h>   
//======================원형 deque ADT 구현=================================
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 300

/*원형 deque을 구현한다.*/
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}DequeType;

// 오류 출력 함수
void error(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 초기화
void init_deque(DequeType* q) {
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(DequeType* q) {
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(DequeType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 앞 삽입
void add_front(DequeType* q, element item) {
	if (is_full(q)) {
		error("큐가 포화상태입니다.");
	}
	q->data[q->front] = item;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

// 앞 원소 조회
element get_front(DequeType* q) {
	if (is_empty(q)) {
		error("큐가 공백상태입니다.");
	}
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

// 앞 원소 삭제
element delete_front(DequeType* q) {
	if (is_empty(q)) {
		error("큐가 공백상태입니다.");
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 뒤 삽입
void add_rear(DequeType* q, element item) {
	if (is_full(q)) {
		error("큐가 포화상태입니다.");
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 뒤 조회
element get_rear(DequeType* q) {
	if (is_empty(q)) {
		error("큐가 공백상태 입니다.");
	}
	return q->data[q->rear];
}

// 뒤 삭제
element delete_rear(DequeType* q) {
	int pre = q->rear;
	if (is_empty(q)) {
		error("큐가 공백 상태입니다.");
	}
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[pre];
}

// 회전 함수(앞의 원소를 맨 뒤로 보내는 함수)
void rotate(DequeType* q) {
	element item = delete_front(q);
	add_rear(q, item);
}

// deque에 저장된 원소의 갯수를 알려주는 함수
int get_size(DequeType* q) {
	return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
//=====================================================================


#define MAX_STR_SIZE 300  // 문자열 최대 크기(공백 포함)

int str_split_to_Deque(DequeType* dq, int max_arr_size, char* str) {
	/*공백을 포함한 str을 입력받아 공백 기준 split하여 원형Deque에 저장하는 함수이다.*/
	int* start = dq->data;
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
			if ((dq->data - start) < max_arr_size) {
				add_rear(dq, num * state);

				num = 0;
				state = 0;
				// 공백 문자 제거
				while (*(str + 1) == ' ') str++;
			}
			else return get_size(dq);
		}
	}
	// 숫자를 분리중에 반복문이 중단되었으면 해당 숫자를 deque에 추가한다.
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

	printf("인쇄할 목록들의 중요도를 입력하세요 : ");
	if (scanf_s("%[^\n]s", str, MAX_STR_SIZE) == -1) {
		return 0;
	}// 입력을 문자열로 받는다.
	size = str_split_to_Deque(&wait_to_print, MAX_QUEUE_SIZE, str); // 문자열 입력을 정수 배열 wait_to_print에 저장

	printf("\n인쇄 :\n");
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
