#include <stdio.h>
#include <math.h>

#define MAX_SIZE 100
#define MIN(A, B) ((A) > (B) ? (B) : (A))
#define MAX_VALUE 99999

int M[MAX_SIZE][MAX_SIZE];
int P[MAX_SIZE][MAX_SIZE];

int minmult(int n, int d[]) {
	int i, j, k, diagonal;
	int min = 99999;
	int minidx = 0;
	int temp = 0;

	int size = n;
	
	//M[][]을 초기화
	for (i = 1; i < n; i++) {
		M[i][i] = 0;
	}

	//P[][]를 초기화
	for (i = 1; i < n; i++)
		for (j = 1; j < n; j++) {
			P[i][j] = 0;
		}
	
	//최소 곱셈 횟수 계산
	for(diagonal = 1; diagonal <  size; diagonal++)
		for (i = 1; i <= size - diagonal; i++) {
			j = i + diagonal;
			if (j == i)
				M[i][j] = 0;
			M[i][j] = MAX_VALUE;
			for (k = i; k <= j - 1; k++) {
				printf("------------------ \nM[%d][%d] = %d\n", i, j, M[i][j]);
				M[i][j] = MIN(M[i][j], M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j]);
				P[i][j] = k;
				printf("M[%d][%d] + M[%d][%d] + d[%d] * d[%d] * d[%d] = %d\n", i, k, k + 1, j, i - 1, k, j, M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j]);
				printf("P[%d][%d] = %d\n", i, j, k);
			}
		}
	return M[1][size];
}

void order(int i, int j) {
	int k;
	if (i == j)
		printf("A%d", i);
	else {
		k = P[i][j];
		printf("(");
		order(i, k);
		order(k + 1, j);
		printf(")");
	}
}

int main() {

	//d의 값 입력
	int d[5] = { 10, 5, 4, 20, 3};
	int result = 0;
	int size = 4;
	result = minmult(4, d);
	printf("result : %d \n", result);

	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++) {
			printf("%5d ", M[i][j]);
		}
		printf("\n");
	}

	printf("===P의 값=============\n");
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++) {
			printf("%2d", P[i][j]);
		}
		printf("\n");
	}

	printf("최적의 순서 : ");
	order(1, 4);
}	
