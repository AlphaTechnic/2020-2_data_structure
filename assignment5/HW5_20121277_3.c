#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

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

void inorder(TreeNode* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void postorder(TreeNode* root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

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
			else return arr - start;
		}
	}
	// ���ڸ� �и��߿� �ݺ����� �ߴܵǾ����� �ش� ���ڸ� arr�� �߰��Ѵ�.
	if (state)*arr++ = num * state;;

	return arr - start;
}

void main() {
	TreeNode* node = NULL;
	int for_getchar;
	int size;
	char string[MAX_SIZE];
	int arr[MAX_SIZE];

	printf("Binary Search Tree�� �Է��� ������ ������ �Է��ϼ���. : ");
	if (scanf("%d", &size) == -1) {
		printf("�Է� err!");
		exit(1);
	}
	for_getchar = getchar();

	printf("���ҵ��� ����� �����Ͽ� �Է��ϼ���. : ");
	if (scanf("%[^\n]s", string) == -1) {
		printf("�Է� err!");
		exit(1);
	}

	str_split_to_int_arr(arr, MAX_SIZE, string);

	for (int i = 0; i < size; i++) {
		if (search(node, arr[i]) != NULL) {
			printf("cannot construct BST");
			exit(1);
		}
		node = insert_node(node, arr[i]);
	}
	
	printf("Inorder : "); inorder(node); printf("\n");
	printf("Postorder : "); postorder(node); printf("\n");

	return;
}