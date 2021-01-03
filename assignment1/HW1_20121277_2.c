#include <stdio.h>
#include <math.h>

void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

int min_num_of_tiles(int w, int h) {
	int i;
	int len_of_square;
	int q, r;
	int w1, h1, w2, h2;
	int count;

	// ��������
	if (w == 0 || h == 0) {
		return 0;
	}
	else {
		// width�� �׻� height���� ū ������ ����� ���� ����
		if (w < h) {
			swap(&w, &h);
		}

		// width�� ���簢�� tile�� �� �� ������ ���� �Լ�
		i = 0;
		while (pow(2, i) <= h) {
			i += 1;
		}
		i -= 1;
		
		// q : width�� �� �� �ִ� Ÿ���� ����
		// r : Ÿ���� �ִ�� ����ְ� ���� width�� ����
		len_of_square = (int)pow(2, i);
		q = w / len_of_square;
		r = w % len_of_square;
		
		w1 = w;
		h1 = h - len_of_square;
		w2 = r;
		h2 = len_of_square;
		count = q + min_num_of_tiles(w1, h1) + min_num_of_tiles(w2, h2);
	
		return count;
	}
}

int main() {
	int ans;
	int w, h;

	printf("����� ���� ���� ũ�⸦ �Է��ϼ���. : ");
	scanf("%d", &w);
	scanf("%d", &h);

	ans = min_num_of_tiles(w, h);

	printf("�� �� �ִ� �ּ� Ÿ���� ���� : ");
	printf("%d", ans);

	return 0;
}