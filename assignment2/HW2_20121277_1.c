#include <stdio.h>
#define max_str_length 100

void add_a_char_to_a_string(char* str, char c) {
	char* p = str;
	while (*p != '\0') { // 문자열 끝 탐색
		p++;
	}
	*p = c;
	*(p + 1) = '\0';
}

void eliminate_duplication(char* str, char* new_string) {
	/* string을 앞부터 순회하면서 char를 tmp에 담고,
	'tmp에 담겨있는 char'와 다른 내용의 char를 만난다면,
	char를 꺼내어 new_string에 대입한다.*/
	char tmp;
	for (int i = 0; str[i] != 0; i++) {
		if (i == 0) {
			tmp = str[i];
			add_a_char_to_a_string(new_string, str[i]);
		}
		else if (str[i - 1] != str[i]) {
			tmp = str[i];
			add_a_char_to_a_string(new_string, str[i]);
		}
	}
}

int main() {
	char str[max_str_length];
	char new_string[max_str_length] = { 0, };

	printf("문자열을 입력하세요. 중복을 제거하겠습니다. : ");
	if (scanf("%s", str) == -1) {
		return 0;
	}

	eliminate_duplication(str, new_string);
	printf("%s", new_string);

	return 0;
}