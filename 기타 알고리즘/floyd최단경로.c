#include <stdio.h>

#define INF 999
#define MIN(A, B) ((A) > (B) ? (B) : (A))

int P[INF][INF];

void printArray(int n, int D[][5]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%5d", D[i][j]);
		}
		printf("\n");
	}
}

void floyd(int n, const int W[][5], int D[][5]) {
	int i, j, k;
	/*D = W*/
	printf("---------table of W----------\n");
	printArray(n, W);
	for (int p = 0; p < n; p++)
		for (int q = 0; q < n; q++)
			D[p][q] = W[p][q];
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				D[i][j] = MIN(D[i][j], D[i][k] + D[k][j]);
}

/*경로까지 포함하는 플로이드 함수*/
void floyd2(int n, const int W[][5], int D[][5]) {
	int i, j, k;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			P[i][j] = 0;
	for (int p = 0; p < n; p++)
		for (int q = 0; q < n; q++)
			D[p][q] = W[p][q];
	for(k = 0; k < n; k++)
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i+1][j+1] = k+1;
					D[i][j] = D[i][k] + D[k][j];
				}

}

/*최단경로 출력*/
void path(int q, int r) {
	if (P[q][r] != 0) {
		path(q, P[q][r]);
		printf("v%d->", P[q][r]);
		path(P[q][r], r);
	}
}

void printP(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%3d", P[i][j]);
		}
		printf("\n");
	}
}


int main() {
	int n;
	n = 5;

	int W[5][5] = {
		{0, 1, INF, 1, 5},
		{9, 0, 3, 2, INF},
		{INF, INF, 0, 4, INF},
		{INF, INF, 2, 0, 3},
		{3, INF, INF, INF, 0}
	};
	int D[5][5];

	floyd2(n, W, D);
	printf("---------table of D----------\n");
	printArray(n, D);
	printf("---------table of P----------\n");
	printP(n);
	printf("---------pass of D-----------\n");
	printf("v%d->", 5);
	path(5, 3);
	printf("v%d\n", 3);
}
