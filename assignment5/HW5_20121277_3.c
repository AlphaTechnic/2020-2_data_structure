#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

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
	/*공백을 포함한 str을 입력받아 공백 기준 split하여 arr에 저장하는 함수이다.*/
	int* start = arr;
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
			if ((arr - start) < max_arr_size) {
				*arr++ = num * state;

				num = 0;
				state = 0;
				// 공백 문자 제거
				while (*(str + 1) == ' ') str++;
			}
			else return arr - start;
		}
	}
	// 숫자를 분리중에 반복문이 중단되었으면 해당 숫자를 arr에 추가한다.
	if (state)*arr++ = num * state;;

	return arr - start;
}

void main() {
	TreeNode* node = NULL;
	int for_getchar;
	int size;
	char string[MAX_SIZE];
	int arr[MAX_SIZE];

	printf("Binary Search Tree에 입력할 원소의 개수를 입력하세요. : ");
	if (scanf("%d", &size) == -1) {
		printf("입력 err!");
		exit(1);
	}
	for_getchar = getchar();

	printf("원소들을 띄어쓰기로 구분하여 입력하세요. : ");
	if (scanf("%[^\n]s", string) == -1) {
		printf("입력 err!");
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