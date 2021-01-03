#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_string_size 30
#define max_pattern_size 30

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
	
	for (int i=0; i < n; i++) { // 사용의 편의를 위하여 원소를 모두 1씩 증가시킴
		failure[i] ++;
	}
}

void kmp(int* failure, int* indices_of_pattern_matching, int* indices_of_pattern_matching_size, char* str, char* pattern) {
	/* indices_of_pattern_matching 배열을 만드는 것이 목적인 함수이다.
	string에서 pattern에 매칭이되는 시작 index들을 원소로 저장한다.
	ex) 입력 : bbbbabbbc / bbb 에 대해서 {0, 1, 5} 라는 배열을 만듦.*/
	int len_of_string = strlen(str), len_of_pattern = strlen(pattern);
	int begin, matched;
	
	begin = 0;
	matched = 0;
	while (begin <= len_of_string - len_of_pattern) {
		if (matched < len_of_pattern && str[begin + matched] == pattern[matched]) {
			matched += 1;
			if (matched == len_of_pattern) {
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

void gen_pos_of_surviving_chars(int* indices_of_pattern_matching, int* indices_of_pattern_matching_size, int* pos_of_surviving_chars, char* str, char* pattern) {
	/* pos_of_surviving_chars 배열을 생성하는 것이 목적인 함수이다.
	pattern에 matching이 되어 지워질 char의 index 위치를 0으로 마킹하고,
	살아남은 char(surviving char를 의미. 지워지지 않고 살아남은 char)의 index 위치를 1로 마킹한다.
	ex) 입력 : bbbbabbbc / bbb 에 대해 {0,0,0,0,1,0,0,0,1}이라는 배열을 만듦.*/
	int matching_ind;
	int len_of_string = strlen(str);
	int len_of_pattern = strlen(pattern);

	for (int i = 0; i < len_of_string; i++) { // 기본적으로 모두 1로 마킹해둔다.
		pos_of_surviving_chars[i] = 1;
	}

	for (int i = 0;i < *indices_of_pattern_matching_size; i++) { // 지워질 char의 index 위치를 0으로 마킹한다.
		matching_ind = indices_of_pattern_matching[i];
		for (int j = matching_ind;j<matching_ind + len_of_pattern; j++) {
			pos_of_surviving_chars[j] = 0;
		}
	}
}

void add_a_char_to_a_string(char* str, char c) {
	char* p = str;
	while (*p != '\0') { // 문자열 끝 탐색
		p++;
	}
	*p = c;
	*(p + 1) = '\0';
}

void create_a_new_string(char* new_str, char* str, int* pos_of_surviving_chars) {
	/* string에서 pattern에 매칭되는 부분을 삭제한, new_string을 생성한다. */
	int size_of_string = strlen(str);

	for (int i = 0; i < size_of_string; i++) {
		if (pos_of_surviving_chars[i] == 1) { // 살아남은 char만을 new_string에 대입한다.
			add_a_char_to_a_string(new_str, str[i]);
		}
	}
}


int main() {
	char str[max_string_size];
	char pattern[max_pattern_size];
	char new_str[max_string_size] = {0,};

	int failure[max_pattern_size];
	int indices_of_pattern_matching[max_string_size];
	int indices_of_pattern_matching_size = 0;
	int pos_of_surviving_chars[max_pattern_size];
	
	int len_of_str;
	int len_of_pat;

	printf("문자열을 입력하세요. : ");
	if (scanf("%s", str) == -1) {
		return 0;
	}
	printf("패턴을 입력하세요. 위 문자열에서 해당 패턴을 삭제한 결과를 출력합니다. : ");
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

	get_failure(failure, pattern); // failure 배열 생성
	kmp(failure, indices_of_pattern_matching, &indices_of_pattern_matching_size, str, pattern); // indices_of_pattern_matching 배열 생성
	gen_pos_of_surviving_chars(indices_of_pattern_matching, &indices_of_pattern_matching_size, pos_of_surviving_chars, str, pattern);
	//  pos_of_surviving_chars 배열 생성. 
	create_a_new_string(new_str, str, pos_of_surviving_chars); // new_string 생성

	printf("%s", new_str);
		
	return 0;
}


