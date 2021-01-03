#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_string_size 30
#define max_pattern_size 30

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
	
	for (int i=0; i < n; i++) { // ����� ���Ǹ� ���Ͽ� ���Ҹ� ��� 1�� ������Ŵ
		failure[i] ++;
	}
}

void kmp(int* failure, int* indices_of_pattern_matching, int* indices_of_pattern_matching_size, char* str, char* pattern) {
	/* indices_of_pattern_matching �迭�� ����� ���� ������ �Լ��̴�.
	string���� pattern�� ��Ī�̵Ǵ� ���� index���� ���ҷ� �����Ѵ�.
	ex) �Է� : bbbbabbbc / bbb �� ���ؼ� {0, 1, 5} ��� �迭�� ����.*/
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
	/* pos_of_surviving_chars �迭�� �����ϴ� ���� ������ �Լ��̴�.
	pattern�� matching�� �Ǿ� ������ char�� index ��ġ�� 0���� ��ŷ�ϰ�,
	��Ƴ��� char(surviving char�� �ǹ�. �������� �ʰ� ��Ƴ��� char)�� index ��ġ�� 1�� ��ŷ�Ѵ�.
	ex) �Է� : bbbbabbbc / bbb �� ���� {0,0,0,0,1,0,0,0,1}�̶�� �迭�� ����.*/
	int matching_ind;
	int len_of_string = strlen(str);
	int len_of_pattern = strlen(pattern);

	for (int i = 0; i < len_of_string; i++) { // �⺻������ ��� 1�� ��ŷ�صд�.
		pos_of_surviving_chars[i] = 1;
	}

	for (int i = 0;i < *indices_of_pattern_matching_size; i++) { // ������ char�� index ��ġ�� 0���� ��ŷ�Ѵ�.
		matching_ind = indices_of_pattern_matching[i];
		for (int j = matching_ind;j<matching_ind + len_of_pattern; j++) {
			pos_of_surviving_chars[j] = 0;
		}
	}
}

void add_a_char_to_a_string(char* str, char c) {
	char* p = str;
	while (*p != '\0') { // ���ڿ� �� Ž��
		p++;
	}
	*p = c;
	*(p + 1) = '\0';
}

void create_a_new_string(char* new_str, char* str, int* pos_of_surviving_chars) {
	/* string���� pattern�� ��Ī�Ǵ� �κ��� ������, new_string�� �����Ѵ�. */
	int size_of_string = strlen(str);

	for (int i = 0; i < size_of_string; i++) {
		if (pos_of_surviving_chars[i] == 1) { // ��Ƴ��� char���� new_string�� �����Ѵ�.
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

	printf("���ڿ��� �Է��ϼ���. : ");
	if (scanf("%s", str) == -1) {
		return 0;
	}
	printf("������ �Է��ϼ���. �� ���ڿ����� �ش� ������ ������ ����� ����մϴ�. : ");
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

	get_failure(failure, pattern); // failure �迭 ����
	kmp(failure, indices_of_pattern_matching, &indices_of_pattern_matching_size, str, pattern); // indices_of_pattern_matching �迭 ����
	gen_pos_of_surviving_chars(indices_of_pattern_matching, &indices_of_pattern_matching_size, pos_of_surviving_chars, str, pattern);
	//  pos_of_surviving_chars �迭 ����. 
	create_a_new_string(new_str, str, pos_of_surviving_chars); // new_string ����

	printf("%s", new_str);
		
	return 0;
}


