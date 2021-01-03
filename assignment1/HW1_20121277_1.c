#include <stdio.h>
#include <stdlib.h>

int nCr_iterative(int n, int r, int** memo) {
	// 이차원 배열에 파스칼의 삼각형 맨 위의 초깃값 1C0, 1C1을 memo[1][0] memo[1][1]에 저장하고, 
	// 이를 활용해서 원하는 combination값 까지 추적하는 함수이다.
	int i, j;
	memo[1][0] = 1;
	memo[1][1] = 1;

	for (i = 2; i <= n; i++) {
		for (j = 0; j <= r; j++) {
			if (i == j || j == 0) {
				memo[i][j] = 1;
			}
			else {
				memo[i][j] = memo[i - 1][j - 1] + memo[i - 1][j];
			}
		}
	}
	return memo[n][r];
}

int nCr_recursive(int n, int r, int** memo) {
	// 함수 call의 중복을 막기 위해 memo[n][r]에 nCr 함숫값을 기록
	memo[1][0] = 1;
	memo[1][1] = 1;

	if (r == 0 || n == r) {
		memo[n][r] = 1;
		return memo[n][r];
	}
	else {
		// memo에 기록된 바 있으면, 그 값을 가져온다.
		if (memo[n][r] != -1) {
			return memo[n][r];
		}
		// memo에 함숫값 기록이 없다면, 재귀를 통해 함숫값을 구한다.
		else {
			return nCr_recursive(n - 1, r - 1, memo) + nCr_recursive(n - 1, r, memo);
		}
	}
	return memo[n][r];
}


int main() {
	int** memo;
	int n, r;
	int i,j;
	int interative_ans, recursive_ans;

	printf("nCr의 n과 r을 입력해주세요. ex) 12 3\n");
	scanf("%d", &n);
	scanf("%d", &r);
	
	// (n+1) by (r+1) 행렬을 생성
	memo = (int**)malloc((n+1) * sizeof(int*));
	for (i = 0; i <= n; i++) {
		memo[i] = (int*)malloc((r + 1) * sizeof(int));
	}

	// (n+1) by (r+1) 행렬을 초기화
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= r; j++) {
			memo[i][j] = -1;
		}
	}
	interative_ans = nCr_iterative(n, r, memo);

	// (n+1) by (r+1) 행렬을 초기화
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= r; j++) {
			memo[i][j] = -1;
		}
	}
	recursive_ans = nCr_recursive(n, r, memo);

	printf("interative answer : %d\n", interative_ans);
	printf("recursive answer : %d", recursive_ans);

	return 0;
}