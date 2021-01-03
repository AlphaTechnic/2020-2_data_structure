#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node* treePointer;
typedef struct node {
    int key;
    struct node* parent;
    struct node* leftChild;
    struct node* rightChild;
} node;

// 연결 리스트로 queue를 표현
typedef struct queue {
    struct queue* next;
    treePointer element;
} queue;


treePointer create_a_node(int x, treePointer parent);
queue* create_a_queue(node* element);
void free_queue(queue** q);
int search_key(treePointer* root, int x);
void insert_a_node_into_Q(treePointer n, queue** last);
void insertion(treePointer* root, int x);
void deletion(treePointer* root);
void print_heap(treePointer* root);
int str_split_to_int_arr(int arr[], int max_arr_size, char* str);


// node 하나를 생성
treePointer create_a_node(int x, treePointer parent) {
    treePointer nd = (treePointer)malloc(sizeof(node));
    if (nd == NULL) {
        printf("동적할당 err!");
        exit(1);
    }
    nd->key = x;
    nd->leftChild = NULL;
    nd->rightChild = NULL;
    nd->parent = parent;
    return nd;
}

// queue 원소(treePointer와 링크) 하나를 생성
queue* create_a_queue(node* element) {
    queue* q = (queue*)malloc(sizeof(queue));
    if (q == NULL) {
        printf("동적할당 err!");
        exit(1);
    }
    q->next = NULL;
    q->element = element;
    return q;
}

// free queue
void free_queue(queue** q) {
    queue* current_q = *q;
    while (current_q != NULL) {
        *q = current_q->next;
        free(current_q);
        current_q = *q;
    }
}

int search_key(treePointer* root, int x) {
    if (*root != NULL) {
        queue* q = create_a_queue(*root);
        queue* current_q = q;
        queue* last_q = q;
        treePointer current_node;
        while (current_q != NULL) {
            current_node = current_q->element;
            insert_a_node_into_Q(current_node, &last_q);
            // printf("%d ", current_node->key);
            if (current_node->key == x) {
                return 1;
            }
            current_q = current_q->next;
        }
        free_queue(&q);
    }
    return 0;
}

// 큐에 insert
void insert_a_node_into_Q(treePointer n, queue** last) {
    if (n->leftChild != NULL) {
        (*last)->next = create_a_queue(n->leftChild);
        (*last) = (*last)->next;
    }
    if (n->rightChild != NULL) {
        (*last)->next = create_a_queue(n->rightChild);
        (*last) = (*last)->next;
    }
}

// 힙에 insert
void insertion(treePointer* root, int x) {
    if (*root == NULL) { // 힙이 비어있다면,
        *root = create_a_node(x, NULL);
    }
    else { // 힙이 비어있지 않다면, node가 들어갈 적절한 위치를 탐색한 뒤 넣는다.
        queue* q = create_a_queue(*root);
        queue* current_q = q;
        queue* last_q = q;
        treePointer current_node;

        if (search_key(root, x)) {
            printf("Exist Number\n");
            return;
        }

        while (current_q != NULL) {
            // Q에서 노드하나 꺼냄.
            current_node = current_q->element;

            if (current_node->leftChild == NULL) {
                current_node->leftChild = create_a_node(x, current_node);
                current_node = current_node->leftChild;
            }
            else if (current_node->rightChild == NULL) {
                current_node->rightChild = create_a_node(x, current_node);
                current_node = current_node->rightChild;
            }
            else {
                insert_a_node_into_Q(current_node, &last_q);
                current_q = current_q->next;
                continue;
            }

            // heap tree를 heapify한다.
            while (current_node->parent != NULL && current_node->parent->key < current_node->key) {
                // swap the value
                int temp = current_node->parent->key;
                current_node->parent->key = current_node->key;
                current_node->key = temp;
                current_node = current_node->parent;
            }
            break;
        }
        free_queue(&q);
    }
    printf("Insert %d\n", x);
    return;
}

void deletion(treePointer* root) {
    int tmp;
    if (*root != NULL) {
        tmp = (*root)->key;
        queue* q = create_a_queue(*root);
        queue* current_q = q;
        queue* last_q = q;
        queue* previous_q = (queue*)malloc(sizeof(queue));
        treePointer current_node;

        if (previous_q == NULL) {
            printf("동적할당 err!");
            exit(1);
        }

        // 마지막 노드를 찾는다.
        while (current_q != NULL) {
            current_node = current_q->element;

            insert_a_node_into_Q(current_node, &last_q);

            previous_q = current_q;
            current_q = current_q->next;
        }
        current_node = previous_q->element;
        free_queue(&q);

        // 가장 끝 노드를 free 하고, 이 노드 정보를 root로 옮긴다.
        if (current_node->parent == NULL) {
            free(current_node);
            *root = NULL;
        }
        else {
            (*root)->key = current_node->key;
            current_node = current_node->parent;
            if (current_node->rightChild != NULL) {
                free(current_node->rightChild);
                current_node->rightChild = NULL;
            }
            else {
                free(current_node->leftChild);
                current_node->leftChild = NULL;
            }
            
            // 끝 노드를 무작정 root에 옮겼으니, heapify를 진행한다.
            int cur_key, l_key, r_key;
            current_node = *root;
            while (1) {
                if (current_node->leftChild == NULL) {
                    // (current->right == NULL) 가 true임을 함의한다.
                    break;
                }
                else if (current_node->rightChild == NULL) {
                    cur_key = current_node->key;
                    l_key = current_node->leftChild->key;
                    if (cur_key < l_key) {
                        current_node->key = l_key;
                        current_node->leftChild->key = cur_key;
                        current_node = current_node->leftChild;
                    }
                    else {
                        break;
                    }
                }
                else {
                    cur_key = current_node->key;
                    l_key = current_node->leftChild->key;
                    r_key = current_node->rightChild->key;
                    //cur_key와 l_key, r_key를 비교
                    if (cur_key >= l_key && cur_key >= r_key) { // cur_key가 가장 크다면, 
                        break;
                    }
                    else if (l_key > cur_key && l_key >= r_key) { // l_key가 가장 크다면,
                        current_node->leftChild->key = cur_key;
                        current_node->key = l_key;
                        current_node = current_node->leftChild;
                    }
                    else { // r_key가 가장 크다면,
                        current_node->rightChild->key = cur_key;
                        current_node->key = r_key;
                        current_node = current_node->rightChild;
                    }
                }
            }
        }
        printf("Delete %d\n", tmp);
    }
    else {
        printf("The heap is empty\n");
        return;
    }
}

void print_heap(treePointer* root) {
    if (*root != NULL) {
        queue* q = create_a_queue(*root);
        queue* current_q = q;
        queue* last_q = q;
        treePointer test;
        while (current_q != NULL) {
            test = current_q->element;
            insert_a_node_into_Q(test, &last_q);
            printf("%d ", test->key);
            current_q = current_q->next;
        }
        free_queue(&q);
        printf("\n");
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

int main() {
    treePointer root = NULL;
    int for_getchar;
    char command;
    int num;
    char str[10];
    int arr[10];

    while (1) {
        printf("명령을 입력하세요. (삽입 : i [삽입을 원하는 정수], 삭제 : d, 종료 q) ");
        if (scanf("%[^\n]s", str) == -1) {
            return 0;
        }

        str_split_to_int_arr(arr, 2, str);
        command = (char)(arr[0] + '0');
        num = arr[1];

        switch (command) {
        case 'i':
            insertion(&root, num);
            break;
        case 'd':
            deletion(&root);
            break;
        case 'q':
            exit(1);
            break;
        default:
            printf("잘못된 명령을 입력하였습니다. (i - insert, d - delete, q - 종료)\n\n");
        }
        //print_heap(&root);
        for_getchar = getchar();
    }
    return 0;
}