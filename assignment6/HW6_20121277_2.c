#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
#define inf 10000 
#define MAX_VERTICES 100

typedef struct Edge {
	int start, end, weight;
}Edge;
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int V_num; // vertex�� ����
	int E_num; // edge�� ����
	struct GraphNode* adj_list[MAX_VERTICES]; // vertex�� ���� ����
	struct Edge edges[MAX_VERTICES * MAX_VERTICES]; // edge�� ���� ����
}GraphType;

int visited[MAX_VERTICES];
GraphType* MST;

FILE* fp_input;
FILE* fp_output;


//////////////////// Union Find //////////////////////
int parent[MAX_VERTICES];

void set_init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
}

// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr) {
	if (parent[curr] == -1) return curr;
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2) {
		parent[root1] = root2;
	}
}
////////////////////////////////////////////////////

//////////////////// Kruskal ///////////////////////
// �׷��� �ʱ�ȭ
void graph_init(GraphType* g) {
	g->V_num = 0;
	g->E_num = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
	for (int e = 0; e < MAX_VERTICES * MAX_VERTICES; e++) {
		g->edges[e].start = 0;
		g->edges[e].end = 0;
		g->edges[e].weight = inf;
	}
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v) {
	if ((g->V_num) + 1 > MAX_VERTICES) {
		printf("�׷��� ���� ���� �ʰ�!\n");
		return;
	}
	g->V_num++;
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w) {
	GraphNode* new_node;
	if (start >= g->V_num || end >= g->V_num) {
		printf("�׷��� ���� ��ȣ ����!\n");
		return;
	}
	new_node = (GraphNode*)malloc(sizeof(GraphNode));
	if (new_node == NULL) {
		printf("alloc err!\n");
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

	g->edges[g->E_num].start = start;
	g->edges[g->E_num].end = end;
	g->edges[g->E_num].weight = w;
	g->E_num++;
}

// ���� ����
void insertion_sort(Edge arr[], int size) {
	int i, j;
	Edge key;

	for (i = 1; i < size; i++) {
		key = arr[i]; 
		for (j = i - 1; j >= 0 && arr[j].weight > key.weight; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}

// kruskal MST ���α׷�
int kruskal(GraphType* g) {
	int edge_accepted = 0; // ������� ���õ� ������ ��
	int uset, vset;     // ���� u�� ���� v�� ���� ��ȣ
	struct Edge e;

	set_init(g->V_num); // ���� �ʱ�ȭ
	insertion_sort(g->edges, g->E_num); // ����

	printf("Kruskal MST algorithm\n");

	int i = 0;
	int sum = 0;
	while (edge_accepted < (g->V_num - 1)) {
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) { // ���� ���� ������ �ٸ���
			//printf("edge (%d, %d) %d ����\n", e.start, e.end, e.weight); // for test
			insert_edge(MST, e.start, e.end, e.weight);
			insert_edge(MST, e.end, e.start, e.weight);
			sum += e.weight;
			edge_accepted++;
			set_union(uset, vset); // �� ���� ������ ��ģ��.
		}
		i++;
	}
	return sum;
}

//////////////////////////// dfs /////////////////////////////
void dfs(GraphType* g, int v) {
	GraphNode* w;

	visited[v] = true;
	fprintf(fp_output, "%d ", v);
	for (w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex]) {
			dfs(g, w->vertex);
		}
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

	if (fscanf(fp_input, "%d", &V_num) == -1) { // size ����
		printf("scanf err!");
		return;
	}
	
	graph_init(g);
	for (int i = 0; i < V_num; i++) {
		insert_vertex(g, i);
	}

	for (int i = 0; i < V_num; i++) {
		for (int j = 0; j < V_num; j++) {
			if (fscanf(fp_input, "%d", &tmp) == -1) { // ���� ����
				printf("scanf err!");
				return;
			}
			if (tmp != -1) {
				insert_edge(g, i, j, tmp);
			}
		}
	}

	graph_init(MST);
	for (int i = 0; i < V_num; i++) {
		insert_vertex(MST, i);
	}

	cost = kruskal(g);
	dfs(MST, 0);

	fprintf(fp_output, "\n%d", cost);
	free(g); free(MST);
	fclose(fp_input); fclose(fp_output);

	printf("output.txt ������ �����Ǿ����ϴ�\n");
	return;
}