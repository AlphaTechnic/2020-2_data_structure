#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ROW 10
#define MAX_COL 10
#define TRUE 1 
#define FALSE 0 
#define EXIT_ROW MAX_ROW-1
#define EXIT_COL MAX_COL-1

///////////////////////////Doubly Linked List ADT//////////////////////////
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	short int row;
	short int col;
	short int dir;
}element;

typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

// 이중 연결 리스트를 초기화
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

int is_empty(DListNode* phead) {
	return phead->llink == phead && phead->rlink == phead;
}

// 이중 연결 리스트의 노드를 출력
void print_dlist_reverse(DListNode* phead) {
	DListNode* p;
	for (p = phead->llink; p != phead; p = p->llink) {
		printf("%2d%5d\n", p->data.row, p->data.col);
	}
}

// 새로운 데이터를 노드 pre의 오른쪽에 삽입
void d_insert(DListNode* pre, element data) {
	DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
	if (newNode == NULL) {
		printf("동적할당 err!");
		exit(1);
	}
	newNode->data = data;
	newNode->llink = pre;
	newNode->rlink = pre->rlink;
	pre->rlink->llink = newNode;
	pre->rlink = newNode;
}

// 노드 removed를 삭제
void d_delete(DListNode* head, DListNode* removed) {
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}
//////////////////////////////////////////////////////////////////////////


// 전역 변수
typedef struct {
	short int vert;
	short int horiz;
}offsets;
offsets move[8] = { {-1, 0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };

int maze[MAX_ROW][MAX_COL];
int mark[MAX_ROW][MAX_COL];

// 함수 선언
void path(DListNode** head);
void push(DListNode* head, element data);
element pop(DListNode* head);


//////////////////////Stack using Doubly linked list ADT/////////////////
void push(DListNode* head, element data) {
	d_insert(head, data);
}

element pop(DListNode* head) {
	element tmp = head->rlink->data;
	d_delete(head, head->rlink);
	return tmp;
}
//////////////////////////////////////////////////////////////////////////


void path(DListNode** head)
{
	int row, col, next_row, next_col, dir, found = FALSE;
	element position, initial;
	FILE* fp1, *fp2;
	if ((fp1 = fopen("maze.txt", "r")) == NULL) {
		printf("파일 읽기 오류! \n");
		exit(1);
	}
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (fscanf(fp1, "%d", &maze[i][j]) == -1) {
				return ;
			};
		}
	}
	fclose(fp1);


	mark[1][1] = 1;

	initial.row = 1;
	initial.col = 1;
	initial.dir = 1;
	push(*head, initial);
	while (!is_empty(*head) && !found) {
		position = pop(*head);
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) {
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;
			if (next_row == EXIT_ROW && next_col == EXIT_COL) {
				found = TRUE;
			}
			else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
				mark[next_row][next_col] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(*head, position);
				row = next_row;
				col = next_col;
				dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		/*
		printf("The path is : \n");
		printf("row col\n");
		print_dlist_reverse(head);
		printf("%2d%5d\n", row, col);
		*/
		DListNode* ptr;
		if ((fp2 = fopen("path.txt", "w")) == NULL) {
			printf("파일 쓰기 오류! \n");
			exit(1);
		}
		for (ptr = (*head)->llink; ptr != (*head); ptr = ptr->llink) {
			fprintf(fp2, "%2d%5d\n", ptr->data.row, ptr->data.col);
		}
		fprintf(fp2, "%2d%5d\n", row, col);
		fclose(fp2);
		printf("path.txt 파일이 생성되었습니다.\n");
	}
	else {
		printf("The maze dose not have a path\n");
	}
}

int main(void) {
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	path(&head);
	return 0;
}
