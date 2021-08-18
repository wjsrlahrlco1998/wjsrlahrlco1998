#include <stdio.h>
#include <malloc.h>

#define INF 999

void merge(int h, int m, const int U[], const int V[], int S[]) {
	int i, j, k;

	i = 1; j = 1; k = 1;
	while (i <= h && j <= m) {
		if (U[i] < V[j]) {
			S[k] = U[i];
			i++;
		}
		else {
			S[k] = V[j];
			j++;
		}
		k++;
	}
	if (i > h) {
		/*copy V[j]...V[m] to S[k]...S[h+m]*/
		for (int p = j; p <= m; p++)
			if (k <= h + m) {
				S[k] = V[p];
				k++;
			}
	}
	else {
		/*copy U[i]...U[h] to S[k]...S[h+m]*/
		for(int p = i; p <= h; p++)
			if (k <= h + m) {
				S[k] = U[p];
				k++;
			}
	}
}

void mergesort(int n, int S[]) {
	if (n > 1) {
		const int h = n / 2;
		const int m = n - h;
		int* U = (int*)malloc(sizeof(int) * h);
		int* V = (int*)malloc(sizeof(int) * m);
		//copy S[1]...S[h] to U[1]...U[h]
		for (int i = 1; i <= h; i++)
			U[i] = S[i];
		//copy S[h+1]...S[n] to V[1]...V[m]
		for (int i = 1; i <= m; i++)
			V[i] = S[h + i];
		mergesort(h, U);
		mergesort(m, V);
		merge(h, m, U, V, S);
	}
}

void printArray(int n, int S[]) {
	for (int i = 1; i <= n; i++) {
		printf("%3d", S[i]);
	}
	printf("\n");
}

int main() {
	int n;
	int S[INF] = { 0, 27, 10, 12, 20, 25, 13, 15, 22 };
	n = 8;
	mergesort(n, S);

	printf("정렬된 배열 S : ");
	printArray(n, S);
}
