#include <stdio.h>
#define max_str_length 100

void add_a_char_to_a_string(char* str, char c) {
	char* p = str;
	while (*p != '\0') { // ���ڿ� �� Ž��
		p++;
	}
	*p = c;
	*(p + 1) = '\0';
}

void eliminate_duplication(char* str, char* new_string) {
	/* string�� �պ��� ��ȸ�ϸ鼭 char�� tmp�� ���,
	'tmp�� ����ִ� char'�� �ٸ� ������ char�� �����ٸ�,
	char�� ������ new_string�� �����Ѵ�.*/
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

	printf("���ڿ��� �Է��ϼ���. �ߺ��� �����ϰڽ��ϴ�. : ");
	if (scanf("%s", str) == -1) {
		return 0;
	}

	eliminate_duplication(str, new_string);
	printf("%s", new_string);

	return 0;
}