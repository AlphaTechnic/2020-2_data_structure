#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 1000
#define true 1
#define false 0

int visited[MAX_VERTICES];
FILE* fp_input;
FILE* fp_output_DFS;
FILE* fp_output_BFS;

//// Graph 자료구조
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int E_num;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

//// Queue 자료구조
typedef int element;
typedef struct QueueNode {
	element data;
	struct QueueNode* link;
}QueueNode;
typedef struct LinkedQueueType {
	QueueNode* front, * rear;
}LinkedQueueType;

//// Queue
void init_Q(LinkedQueueType* q);
int is_empty(LinkedQueueType* q);
void enqueue(LinkedQueueType* q, element data);
element dequeue(LinkedQueueType* q);

//// Graph
void graph_init(GraphType* g);
void insert_vertex(GraphType* g, int v);
void insert_edge(GraphType* g, int start, int end);

//// dfs, bfs
void dfs(GraphType* g, int v);
void bfs(GraphType* g, int v);

/////////////////////////////// Queue ///////////////////////////////////
void init_Q(LinkedQueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(LinkedQueueType* q) {
	return (q->front == NULL);
}

void enqueue(LinkedQueueType* q, element data) {
	QueueNode* tmp = (QueueNode*)malloc(sizeof(QueueNode));
	if (tmp == NULL) {
		printf("alloc err!\n");
		return;
	}

	tmp->data = data;
	tmp->link = NULL;
	if (is_empty(q)) {
		q->front = q->rear = tmp;
	}
	else {
		q->rear->link = tmp;
		q->rear = tmp;
	}
}

element dequeue(LinkedQueueType* q) {
	QueueNode* tmp = q->front;
	element data;
	if (tmp == NULL) {
		printf("alloc err!\n");
		return 0;
	}

	if (is_empty(q)) {
		printf("stack is empty!\n");
		return 0;
	}
	else {
		data = tmp->data;
		q->front = q->front->link;
		if (q->front == NULL) {
			q->rear = NULL;
		}
		free(tmp);
		return data;
	}
}
///////////////////////////////////////////////////////////////////////


////////////////////////////// Graph ///////////////////////////////////
// 그래프 초기화
void graph_init(GraphType* g) {
	int v;
	g->E_num = 0;
	for (v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if ((g->E_num) + 1 > MAX_VERTICES) {
		printf("그래프 : 정점 개수 초과\n");
		return;
	}
	g->E_num++;
}

// 간선 삽입 연산, e를 s의 인접리스트에 삽입한다.(s->e 연결)
void insert_edge(GraphType* g, int start, int end) {
	GraphNode* new_node = (GraphNode*)malloc(sizeof(GraphNode));

	if (new_node == NULL) {
		printf("alloc err!\n");
		return;
	}

	if (start >= g->E_num || end >= g->E_num) {
		printf("그래프 : 정점 번호 오류\n");
		return;
	}
	new_node->vertex = end;
	new_node->link = NULL;
	GraphNode* ptr = g->adj_list[start];
	if (ptr == NULL) {
		g->adj_list[start] = new_node;
	}
	else {
		for (; ptr->link; ptr = ptr->link);
		ptr->link = new_node;
	}
}

// 출력(for test)
void print_adj_list(GraphType* g) {
	for (int i = 0; i < g->E_num; i++) {
		GraphNode* ptr = g->adj_list[i];
		printf("정점 %d의 인접리스트 ", i);
		while (ptr != NULL) {
			printf("-> %d", ptr->vertex);
			ptr = ptr->link;
		}
		printf("\n");
	}
}
//////////////////////////////////////////////////////////////////

//////////////////////////// dfs, bfs ///////////////////////////////
void dfs(GraphType* g, int v) {
	GraphNode* w;

	visited[v] = true;
	fprintf(fp_output_DFS, "%d ", v);
	for (w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex]) {
			dfs(g, w->vertex);
		}
	}
}

void bfs(GraphType* g, int v) {
	GraphNode* w;
	LinkedQueueType q;
	init_Q(&q);
	
	visited[v] = true;
	fprintf(fp_output_BFS, "%d ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = g->adj_list[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				visited[w->vertex] = true;
				fprintf(fp_output_BFS, "%d ", w->vertex);
				enqueue(&q, w->vertex);
			}
		}
	}
}
/////////////////////////////////////////////////////////////////

void main() {
	int V_num;
	int tmp;
	
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	if ((fp_input = fopen("input.txt", "r")) == NULL) {
		printf("file open err!\n");
		return;
	}
	if ((fp_output_DFS = fopen("output_DFS.txt", "w")) == NULL) {
		printf("file open err!\n");
		return;
	}
	if ((fp_output_BFS = fopen("output_BFS.txt", "w")) == NULL) {
		printf("file open err!\n");
		return;
	}

	if (fscanf(fp_input, "%d", &V_num) == -1) { // size 읽음
		printf("scanf err!");
		return ;
	}

	for (int i = 0; i < V_num; i++) {
		insert_vertex(g, i);
	}

	for (int i = 0; i < V_num; i++) {
		for (int j = 0; j < V_num; j++) {
			if (fscanf(fp_input, "%d", &tmp) == -1) { // 숫자 읽음
				printf("scanf err!");
				return ;
			}
			if (tmp != 0) {
				insert_edge(g, i, j);
			}
		}
	}
	
	for (int i = 0; i < V_num; i++) {
		if (!visited[i]) {
			dfs(g, i);
			fprintf(fp_output_DFS, "\n");
		}
	}

	for (int i = 0; i < V_num; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < V_num; i++) {
		if (!visited[i]) {
			bfs(g, i);
			fprintf(fp_output_BFS, "\n");
		}
	}
	printf("output_DFS.txt, output_BFS.txt 파일 생성이 완료되었습니다.\n");

	free(g);
	fclose(fp_input); fclose(fp_output_DFS); fclose(fp_output_BFS);
}