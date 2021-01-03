#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
}TreeNode;

// ��ȯ���� Ž�� �Լ�
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

// ���ο� ��带 �����ϴ� �Լ�
TreeNode* new_node(int item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL) {
		printf("���� �Ҵ� err!");
		exit(1);
	}
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
	if (root == NULL) return new_node(key);

	// �׷��� ������, ��ȯ������ Ʈ���� ��������.
	if (key < root->data) {
		root->left = insert_node(root->left, key);
	}
	else if (key > root->data) {
		root->right = insert_node(root->right, key);
	}

	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
	return root;
}

int sum_nodes_having_0_or_1_child(TreeNode* root)
{
	int temp = 0;
	if (root == NULL)
		return 0;
	//���� ��尡 ������ 0�� ��ȯ�Ѵ�
	else
	{
		if ((root->left != NULL && root->right == NULL)
			|| (root->left == NULL && root->right != NULL)
			|| (root->left == NULL && root->right == NULL))
			temp += root->data;
		//���� ����� �ڽ��� 1. �����ʸ� �ְų� 2. ���ʸ� �ְų� 3. ������ temp�� ���� �״´�.
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
		printf("���� �б� err!");
		exit(1);
	}

	if (fscanf(fp, "%d", &size) == -1) {
		printf("���� �Է� err!");
		exit(1);
	}

	for (int i = 0; i < size; i++) {
		if (fscanf(fp, "%d", &data) == -1) {
			printf("���� �Է� err!");
			exit(1);
		}
		if (search(node, data) != NULL) {
			printf("������ ���Ұ� �̹� ���� Ž�� Ʈ���� �ֽ��ϴ�.");
			exit(1);
		}
		node = insert_node(node, data);
	}

	printf("�ڽ� ����� ������ �ϳ� or 0���� ��� data�� : %d\n", sum_nodes_having_0_or_1_child(node));
	fclose(fp);

	return;
}