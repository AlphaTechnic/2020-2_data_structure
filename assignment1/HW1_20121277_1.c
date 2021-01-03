#include <stdio.h>
#include <stdlib.h>

int nCr_iterative(int n, int r, int** memo) {
	// ������ �迭�� �Ľ�Į�� �ﰢ�� �� ���� �ʱ갪 1C0, 1C1�� memo[1][0] memo[1][1]�� �����ϰ�, 
	// �̸� Ȱ���ؼ� ���ϴ� combination�� ���� �����ϴ� �Լ��̴�.
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
	// �Լ� call�� �ߺ��� ���� ���� memo[n][r]�� nCr �Լ����� ���
	memo[1][0] = 1;
	memo[1][1] = 1;

	if (r == 0 || n == r) {
		memo[n][r] = 1;
		return memo[n][r];
	}
	else {
		// memo�� ��ϵ� �� ������, �� ���� �����´�.
		if (memo[n][r] != -1) {
			return memo[n][r];
		}
		// memo�� �Լ��� ����� ���ٸ�, ��͸� ���� �Լ����� ���Ѵ�.
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

	printf("nCr�� n�� r�� �Է����ּ���. ex) 12 3\n");
	scanf("%d", &n);
	scanf("%d", &r);
	
	// (n+1) by (r+1) ����� ����
	memo = (int**)malloc((n+1) * sizeof(int*));
	for (i = 0; i <= n; i++) {
		memo[i] = (int*)malloc((r + 1) * sizeof(int));
	}

	// (n+1) by (r+1) ����� �ʱ�ȭ
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= r; j++) {
			memo[i][j] = -1;
		}
	}
	interative_ans = nCr_iterative(n, r, memo);

	// (n+1) by (r+1) ����� �ʱ�ȭ
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