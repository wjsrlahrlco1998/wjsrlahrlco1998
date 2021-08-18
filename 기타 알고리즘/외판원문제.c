#include <stdio.h>
#include <math.h>

#define INF 999

#define TRUE 1
#define FALSE 0

int n;
int W[INF][INF];

int minlength;
int P[INF][INF];
int D[INF][INF];

void print_matrix(int n, int m[][INF]) {
	int i, j;

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++)
			printf("%4d", m[i][j]);
		printf("\n");
	}
}

void print_matrix_powered(int n, int m[][INF]) {
	int i, j;

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n*3; j++)
			printf("%4d", m[i][j]);
		printf("\n");
	}

}


int contains(int A, int k) {
	int i, count = 0;

	for (i = 0; i < n; i++)
		if ((A & (1 << i)) != 0) count++;

	return (count == k) ? TRUE : FALSE;
}

int isIn(int i, int A) {
	return ((A & (1 << (i - 2))) != 0) ? TRUE : FALSE;
}

int diff(int A, int j) {
	int t = 1 << (j - 2);
	return (A & (~t));
}

int minimum(int A, int i, int* minj) {
	int j, m, min;

	min = INF;
	for (j = 1; j < (int)pow(2, (n-1)); j++) {
		if (!isIn(j, A)) continue;
		m = W[i][j] + D[j][diff(A, j)];
		if (min > m) {
			min = m;
			*minj = j;
		}
	}

	return min;
}

void travel() {
	int i, j, k, A, size;

	size = (int)pow(2, (n - 1));
	printf("n = %d\nsize = %d\n\n", n, size);

	for (i = 2; i <= n; i++)
		D[i][0] = W[i][1];

	printf("---------D배열 초기값----------\n");
	print_matrix_powered(n, D);
	printf("-------------------------------\n");

	for (k = 1; k <= n - 2; k++) {
		for (A = 0; A < size; A++) {
			//printf("A=%d:\n", A);
			if (!contains(A, k)) continue;
			for (i = 2; i <= n; i++) {
				if (isIn(i, A)) continue;
				D[i][A] = minimum(A, i, &j);
				P[i][A] = j;
			}
		}
		printf("K=%d\n", k);
		printf("A=%d 일 때, table of D\n", A);
		print_matrix_powered(n, D);
	}
	A = size - 1;
	D[1][A] = minimum(A, 1, &j);
	P[1][A] = j;
	minlength = D[1][A];
}

void tour(int v, int A) {
	int next = P[v][A];
	printf("v%d ->", v);
	if (A == 0) // an empty set
		return;
	tour(next, diff(A, next));
}

int main() {
	int i, j, size, v;
	int adjMat[5][5] = {
		{0, 8, 13, 18, 20},
		{3, 0, 7, 8, 10},
		{4, 11, 0, 10, 7},
		{6, 6, 7, 0, 11},
		{10, 6, 2, 1, 0},
	};
	n = 5;
	size = (int)pow(2, (n - 1));

	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			W[i][j] = adjMat[i - 1][j - 1];

	for (i = 1; i <= n; i++)
		for (j = 1; j <= size; j++)
			D[i][j] = 0;

	printf("Table of W:\n");
	print_matrix(n, W);
	printf("\n");

	travel();

	printf("\nThe table of D:\n");
	print_matrix_powered(n, D);

	printf("\nThe table of P:\n");
	print_matrix_powered(n, P);

	printf("\n The optimal tour is: ");
	v = 1;
	tour(v, size - 1);
	printf("v%d ", v);
	printf("\n");
}
