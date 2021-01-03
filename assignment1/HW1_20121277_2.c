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

	// 종료조건
	if (w == 0 || h == 0) {
		return 0;
	}
	else {
		// width를 항상 height보다 큰 값으로 만들기 위한 과정
		if (w < h) {
			swap(&w, &h);
		}

		// width에 정사각형 tile이 몇 개 들어가는지 세는 함수
		i = 0;
		while (pow(2, i) <= h) {
			i += 1;
		}
		i -= 1;
		
		// q : width에 들어갈 수 있는 타일의 개수
		// r : 타일을 최대로 집어넣고 남은 width의 길이
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

	printf("욕실의 가로 세로 크기를 입력하세요. : ");
	scanf("%d", &w);
	scanf("%d", &h);

	ans = min_num_of_tiles(w, h);

	printf("들어갈 수 있는 최소 타일의 개수 : ");
	printf("%d", ans);

	return 0;
}