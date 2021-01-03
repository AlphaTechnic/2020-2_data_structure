#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_string_size 30
#define max_pattern_size 10

// 필요한 작은 단위의 함수들 구현
void swap(int i, int j, char* str);
void insertion_sort(int arr[], int size);
int num_in_arr(int* arr, int size, int num);

// 메인 알고리즘
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
    /* 입력받은 pattern에 대한 failure 배열을 만드는 함수 */
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

    for (int i = 0; i < n; i++) {  // 사용의 편의를 위하여 원소를 모두 1씩 증가시킴
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
    /* indices_of_pattern_matching 배열의 원소들을 정렬하기 위한 함수 */
    int i, j, key;

    for (i = 1; i < size; i++) {
        key = arr[i];

        // 현재 정렬된 배열은 i-1까지이고, i-1번째부터 역순으로 조사.
        for (j = i - 1; j >= 0 && arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

void kmp(int* failure, int* indices_of_pattern_matching, int* indices_of_pattern_matching_size, char* str, char* pattern) {
    /* indices_of_pattern_matching 배열을 만드는 것이 목적인 함수이다.
    string에서 pattern에 매칭이되는 시작 index들을 원소로 저장한다.
    ex) 입력 : bbbbabbbc / bbb 에 대해서 {0, 1, 5} 라는 배열을 만듦.*/
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
            // begin 인덱스가 이미 indices_of_pattern_matching 배열의 원소로 들어있지는 않은지 점검
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
    /* 입력된 pattern의 anagram 하나가 생성될 때마다, 이 anagram pattern으로 pmatch를 진행하는 함수이다.
    pmatch의 결과는 indices_of_pattern_matching 정수배열에 누적되면서 기록된다.*/
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
        /* 백트래킹 기법 */
        // swap을 하고,
        swap(i, N - 1, pattern);  
        // 재귀로 들어가며
        make_anagram_and_pmatching(totalN, N - 1, pattern, str, failure, 
                                indices_of_pattern_matching, indices_of_pattern_matching_size); 
        // 재귀가 끝난 뒤에, 재귀로 들어가기 전 상태로 pattern을 복구.
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
    int len_of_str, len_of_pat; // 입력 받은 pattern의 길이를 저장할 변수

    printf("문자열을 입력해 주세요. : ");
    if (scanf("%s", str) == -1) {
        return 0;
    }
    printf("패턴을 입력해 주세요. anagrams까지 포함하여 해당 패턴에 매칭되는 위치를 알려줍니다. : ");
    if (scanf("%s", pattern) == -1) {
        return 0;
    }

    str[max_string_size - 1] = 0; 
    pattern[max_pattern_size - 1] = 0; // str과 pattern이 널문자로 끝나지 않을 수도 있다는 경고 없애기
    
    len_of_str = strlen(str);
    len_of_pat = strlen(pattern);
    if (len_of_str >= 30 || len_of_str < 1 ||
        len_of_pat >= 10 || len_of_pat < 1
        || len_of_str < len_of_pat) { // 예외 처리
        printf("잘못된 입력입니다.");
        exit(1);
    }

    make_anagram_and_pmatching(len_of_pat, len_of_pat, pattern, str, failure,
        indices_of_pattern_matching, &indices_of_pattern_matching_size);

    // indices_of_pattern_matching 배열의 원소들을 정렬한 뒤 출력
    insertion_sort(indices_of_pattern_matching, indices_of_pattern_matching_size); // 삽입 정렬     
    printf("[ ");
    for (int i = 0; i < indices_of_pattern_matching_size; i++) {
        printf("%d ", indices_of_pattern_matching[i]);
    }
    printf("]");

    return 0;
}