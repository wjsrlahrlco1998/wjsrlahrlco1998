#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];
int P[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType* g) {
	int i, j;
	printf("===========================\n");
	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
			if (A[i][j] == INF)
				printf(" * ");
			else printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
	printf("===========================\n");
}

void floyd(GraphType* g) {
	int i, j, k;
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++) {
			A[i][j] = g->weight[i][j];
			P[i][j] = 0;
		}
	//printA(g);
	printf("===========================\n");
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			printf("%3d", P[i][j]);
		}
		printf("\n");
	}
	printf("===========================\n");

	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j]) {
					P[i][j] = k+1;
					A[i][j] = A[i][k] + A[k][j];
				}
		//printA(g);
		printf("===========================\n");
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				printf("%3d", P[i][j]);
			}
			printf("\n");
		}
		printf("===========================\n");
	}
}

void path(int q, int r) {

	if (P[q][r] > 0) {
		path(q, P[q][r]);
		printf("%d->", P[q][r]);
		path(P[q][r], r);
	}

}

int main() {
	GraphType g = { 7,
		{{0, 4, INF, INF, INF, 10, INF},
		{3, 0, INF, 18, INF, INF, INF},
		{INF, 6, 0, INF, INF, INF, INF},
		{INF, 5, 15, 0, 2, 19, 5},
		{INF, INF, 12, 1, 0, INF, INF},
		{INF, INF, INF, INF, INF, 0, 10},
		{INF, INF, INF, 8, INF, INF, 0}},
	};
	floyd(&g);
	/*
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			printf("%3d", P[i][j]);
		}
		printf("\n");
	}
	*/
	printf("%d", P[6][2]);
	path(6, 2);

}
