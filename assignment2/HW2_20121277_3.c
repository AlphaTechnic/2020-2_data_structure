#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_string_size 30
#define max_pattern_size 10

// �ʿ��� ���� ������ �Լ��� ����
void swap(int i, int j, char* str);
void insertion_sort(int arr[], int size);
int num_in_arr(int* arr, int size, int num);

// ���� �˰���
void get_failure(int* failure, char* pattern);
void kmp(int* failure, int* indices_of_pattern_matching, 
        int* indices_of_pattern_matching_size, char* str, char* pattern);
void make_anagram_and_pmatching(int totalN, int N, char* pattern, char* str, int* failure,
                            int* indices_of_pattern_matching, int* indices_of_pattern_matching_size);


void swap(int i, int j, char* str) {
    int temp;
    if (i == j) {
        return;
    }
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    return;
}

void get_failure(int* failure, char* pattern) {
    /* �Է¹��� pattern�� ���� failure �迭�� ����� �Լ� */
    int i, n = strlen(pattern);
    failure[0] = -1;
    for (int j = 1; j < n; j++) {
        i = failure[j - 1];
        while ((pattern[j] != pattern[i + 1]) && (i >= 0))
            i = failure[i];
        if (pattern[j] == pattern[i + 1])
            failure[j] = i + 1;
        else  failure[j] = -1;
    }

    for (int i = 0; i < n; i++) {  // ����� ���Ǹ� ���Ͽ� ���Ҹ� ��� 1�� ������Ŵ
        failure[i] += 1;
    }
}

int num_in_arr(int* arr, int size, int num) {
    int check = 1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == num) {
            return check;
        }
    }
    return 0;
}

void insertion_sort(int arr[], int size) {
    /* indices_of_pattern_matching �迭�� ���ҵ��� �����ϱ� ���� �Լ� */
    int i, j, key;

    for (i = 1; i < size; i++) {
        key = arr[i];

        // ���� ���ĵ� �迭�� i-1�����̰�, i-1��°���� �������� ����.
        for (j = i - 1; j >= 0 && arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

void kmp(int* failure, int* indices_of_pattern_matching, int* indices_of_pattern_matching_size, char* str, char* pattern) {
    /* indices_of_pattern_matching �迭�� ����� ���� ������ �Լ��̴�.
    string���� pattern�� ��Ī�̵Ǵ� ���� index���� ���ҷ� �����Ѵ�.
    ex) �Է� : bbbbabbbc / bbb �� ���ؼ� {0, 1, 5} ��� �迭�� ����.*/
    int len_of_string, len_of_pattern;
    int begin, matched;
    int check = 1;

    len_of_string = strlen(str);
    len_of_pattern = strlen(pattern);

    begin = 0;
    matched = 0;
    while (begin <= len_of_string - len_of_pattern) {
        if (matched < len_of_pattern && str[begin + matched] == pattern[matched]) {
            matched += 1;
            // begin �ε����� �̹� indices_of_pattern_matching �迭�� ���ҷ� ��������� ������ ����
            if (matched == len_of_pattern && !num_in_arr(indices_of_pattern_matching, *indices_of_pattern_matching_size, begin)) {
                indices_of_pattern_matching[(*indices_of_pattern_matching_size)++] = begin;
            }
        }
        else {
            if (matched == 0) {
                begin += 1;
            }
            else {
                begin += matched - failure[matched - 1];
                matched = failure[matched - 1];
            }
        }
    }
}

void make_anagram_and_pmatching(int totalN, int N, char* pattern, char* str, int* failure,
    int* indices_of_pattern_matching, int* indices_of_pattern_matching_size) {
    /* �Էµ� pattern�� anagram �ϳ��� ������ ������, �� anagram pattern���� pmatch�� �����ϴ� �Լ��̴�.
    pmatch�� ����� indices_of_pattern_matching �����迭�� �����Ǹ鼭 ��ϵȴ�.*/
    int i;

    if (N == 1) {
        for (i = 0; i < totalN; i++) {
            //add_a_char_to_a_string(anagrams[count], str[i]);
            get_failure(failure, pattern);
            kmp(failure, indices_of_pattern_matching, indices_of_pattern_matching_size, str, pattern);
        }
        return;
    }

    for (i = 0; i < N; i++) {
        /* ��Ʈ��ŷ ��� */
        // swap�� �ϰ�,
        swap(i, N - 1, pattern);  
        // ��ͷ� ����
        make_anagram_and_pmatching(totalN, N - 1, pattern, str, failure, 
                                indices_of_pattern_matching, indices_of_pattern_matching_size); 
        // ��Ͱ� ���� �ڿ�, ��ͷ� ���� �� ���·� pattern�� ����.
        swap(i, N - 1, pattern);  
    }
    return;
}


int main() {
    char str[max_string_size];
    char pattern[max_pattern_size];

    int failure[max_pattern_size];
    int indices_of_pattern_matching[max_string_size];
    int indices_of_pattern_matching_size = 0;
    int len_of_str, len_of_pat; // �Է� ���� pattern�� ���̸� ������ ����

    printf("���ڿ��� �Է��� �ּ���. : ");
    if (scanf("%s", str) == -1) {
        return 0;
    }
    printf("������ �Է��� �ּ���. anagrams���� �����Ͽ� �ش� ���Ͽ� ��Ī�Ǵ� ��ġ�� �˷��ݴϴ�. : ");
    if (scanf("%s", pattern) == -1) {
        return 0;
    }

    str[max_string_size - 1] = 0; 
    pattern[max_pattern_size - 1] = 0; // str�� pattern�� �ι��ڷ� ������ ���� ���� �ִٴ� ��� ���ֱ�
    
    len_of_str = strlen(str);
    len_of_pat = strlen(pattern);
    if (len_of_str >= 30 || len_of_str < 1 ||
        len_of_pat >= 10 || len_of_pat < 1
        || len_of_str < len_of_pat) { // ���� ó��
        printf("�߸��� �Է��Դϴ�.");
        exit(1);
    }

    make_anagram_and_pmatching(len_of_pat, len_of_pat, pattern, str, failure,
        indices_of_pattern_matching, &indices_of_pattern_matching_size);

    // indices_of_pattern_matching �迭�� ���ҵ��� ������ �� ���
    insertion_sort(indices_of_pattern_matching, indices_of_pattern_matching_size); // ���� ����     
    printf("[ ");
    for (int i = 0; i < indices_of_pattern_matching_size; i++) {
        printf("%d ", indices_of_pattern_matching[i]);
    }
    printf("]");

    return 0;
}