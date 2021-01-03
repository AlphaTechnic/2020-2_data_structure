#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define true 1
#define false 0
#define MAX_VERTICES 100
#define inf 100000


typedef struct GraphNode {
	int vertex;
	int weight;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int V_num; // vertex의 개수
	int E_num; // edge의 개수
	struct GraphNode* adj_list[MAX_VERTICES]; // vertex에 대한 정보
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int visited[MAX_VERTICES];
GraphType* MST;

FILE* fp_input;
FILE* fp_output;

int distance[MAX_VERTICES]; // 집합 S에 있는 정점만을 거쳐서 다른 정점으로 가는 최단거리
int found[MAX_VERTICES]; // 방문한 정점 표시

// 그래프 초기화
void graph_init(GraphType* g) {
	g->V_num = 0;
	g->E_num = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if ((g->V_num) + 1 > MAX_VERTICES) {
		printf("그래프 정점 개수 초과!\n");
		return;
	}
	g->V_num++;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w) {
	GraphNode* new_node;
	if (start >= g->V_num || end >= g->V_num) {
		printf("그래프 정점 번호 오류!\n");
		return;
	}
	new_node = (GraphNode*)malloc(sizeof(GraphNode));
	if (new_node == NULL) {
		printf("alloc err!\n");
		return;
	}

	new_node->vertex = end;
	new_node->link = NULL;
	new_node->weight = w;
	GraphNode* ptr = g->adj_list[start];
	if (ptr == NULL) {
		g->adj_list[start] = new_node;
	}
	else {
		for (; ptr->link; ptr = ptr->link);
		ptr->link = new_node;
	}
}

int get_weight(GraphType* g, int start, int end) {
	GraphNode* ptr = (GraphNode*)malloc(sizeof(GraphNode));

	ptr = g->adj_list[start];
	while (ptr != NULL) {
		if (ptr->vertex == end) {
			return ptr->weight;
		}
		ptr = ptr->link;
	}
	return inf;
}

int choose(int distance[], int n, int found[]) {
	int min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (int i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void print_status(GraphType* g) {
	static int step = 1;
	fprintf(fp_output, "STEP %d :\n", step++);
	fprintf(fp_output, "distance: ");
	for (int i = 0; i < g->V_num; i++) {
		if (distance[i] == inf) fprintf(fp_output, " * ");
		else fprintf(fp_output, "%2d ", distance[i]);
	}
	fprintf(fp_output, "\nfound   : ");
	for (int i = 0; i < g->V_num; i++) fprintf(fp_output, "%2d ", found[i]);
	fprintf(fp_output, "\n\n");
}


void shortest_path(GraphType* g, int start) {
	int u, w;
	for (int i = 0; i < g->V_num; i++) {
		distance[i] = get_weight(g, start, i);
		found[i] = false;
	}
	found[start] = true; // 시작 정점 방문 표시
	distance[start] = 0;

	////
	fprintf(fp_output, "Iteration   Vertex selected    Distance\n");
	fprintf(fp_output, " initial               ..            ");
	for (int i = 0; i < g->V_num; i++) { 
		if (distance[i] == inf) fprintf(fp_output, " * ");
		else fprintf(fp_output, "%3d ", distance[i]);
	}
	fprintf(fp_output, "\n");
	////

	for (int i = 0; i < g->V_num - 1; i++) {
		//print_status(g);
		u = choose(distance, g->V_num, found);
		found[u] = true;

		/////
		fprintf(fp_output, "    %d   ", i + 1); 
		fprintf(fp_output, "              %d            ", u); 
		/////

		for (w = 0; w < g->V_num; w++) {
			if (!found[w]) {
				if (distance[u] + get_weight(g, u, w) < distance[w])
					distance[w] = distance[u] + get_weight(g, u, w);
			}
		}

		////
		for (int i = 0; i < g->V_num; i++) { 
			if (distance[i] == inf) fprintf(fp_output, " * ");
			else fprintf(fp_output, "%3d ", distance[i]);
		}
		fprintf(fp_output, "\n");
		////
	}
}

void main() {
	int V_num;
	int tmp;
	int cost;

	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	MST = (GraphType*)malloc(sizeof(GraphType));

	if ((fp_input = fopen("input.txt", "r")) == NULL) {
		printf("file open err!");
		return;
	}
	if ((fp_output = fopen("output.txt", "w")) == NULL) {
		printf("file open err!\n");
		return;
	}

	if (fscanf(fp_input, "%d", &V_num) == -1) { // size 읽음
		printf("scanf err!");
		return;
	}

	graph_init(g);
	for (int i = 0; i < V_num; i++) {
		insert_vertex(g, i);
	}

	for (int i = 0; i < V_num; i++) {
		for (int j = 0; j < V_num; j++) {
			if (fscanf(fp_input, "%d", &tmp) == -1) { // 숫자 읽음
				printf("scanf err!");
				return;
			}
			if (i == j) {
				insert_edge(g, i, j, 0);
			}
			else if (tmp == -1) {
				insert_edge(g, i, j, inf);
			}
			else {
				insert_edge(g, i, j, tmp);
			}
		}
	}

	shortest_path(g, 0);
	printf("output.txt 파일 생성이 완료되었습니다\n");
}