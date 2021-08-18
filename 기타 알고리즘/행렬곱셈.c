#include <stdio.h>

#define INF 999

int A[INF][INF] = {
	{2, 3},
	{4, 1}
};
int B[INF][INF] = {
	{5, 7},
	{6, 8}
};
int C[INF][INF];

void printMatrixC(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d", C[i][j]);
		}
		printf("\n");
	}
}

void matrixmult(int n) {
	int i, j, k;

	for(i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			C[i][j] = 0;
			for (k = 0; k < n; k++)
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
		}

}

int main() {
	int n;
	n = 2;

	matrixmult(n);

	printMatrixC(n);
}
