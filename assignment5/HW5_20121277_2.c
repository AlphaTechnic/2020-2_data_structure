#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
}TreeNode;

// 순환적인 탐색 함수
TreeNode* search(TreeNode* node, int key) {
	if (node == NULL) return NULL;

	if (key == node->data) return node;
	else if (key < node->data) {
		return search(node->left, key);
	}
	else {
		return search(node->right, key);
	}
}

// 새로운 노드를 생성하는 함수
TreeNode* new_node(int item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL) {
		printf("동적 할당 err!");
		exit(1);
	}
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
	// 트리가 공백이면 새로운 노드를 반환한다.
	if (root == NULL) return new_node(key);

	// 그렇지 않으면, 순환적으로 트리를 내려간다.
	if (key < root->data) {
		root->left = insert_node(root->left, key);
	}
	else if (key > root->data) {
		root->right = insert_node(root->right, key);
	}

	// 변경된 루트 포인터를 반환한다.
	return root;
}

int sum_nodes_having_0_or_1_child(TreeNode* root)
{
	int temp = 0;
	if (root == NULL)
		return 0;
	//만약 노드가 없으면 0을 반환한다
	else
	{
		if ((root->left != NULL && root->right == NULL)
			|| (root->left == NULL && root->right != NULL)
			|| (root->left == NULL && root->right == NULL))
			temp += root->data;
		//만약 노드의 자식이 1. 오른쪽만 있거나 2. 왼쪽만 있거나 3. 없으면 temp에 값을 쌓는다.
	}
	return temp + sum_nodes_having_0_or_1_child(root->left) + sum_nodes_having_0_or_1_child(root->right);
}

void main() {
	TreeNode* node = NULL;
	FILE* fp;
	int size;
	int data;

	fp = fopen("input.txt", "rt");
	if (fp == NULL) {
		printf("파일 읽기 err!");
		exit(1);
	}

	if (fscanf(fp, "%d", &size) == -1) {
		printf("파일 입력 err!");
		exit(1);
	}

	for (int i = 0; i < size; i++) {
		if (fscanf(fp, "%d", &data) == -1) {
			printf("파일 입력 err!");
			exit(1);
		}
		if (search(node, data) != NULL) {
			printf("동일한 원소가 이미 이진 탐색 트리에 있습니다.");
			exit(1);
		}
		node = insert_node(node, data);
	}

	printf("자식 노드의 개수가 하나 or 0개인 노드 data합 : %d\n", sum_nodes_having_0_or_1_child(node));
	fclose(fp);

	return;
}