#include <stdio.h>

#define INF 999
#define MAX_SIZE 100

/*가중치 그래프*/
int W[MAX_SIZE][MAX_SIZE] = {
		{0, 32, INF, 17, INF, INF, INF, INF, INF, INF},
		{32, 0, INF, INF, 45, INF, INF, INF, INF, INF},
		{INF, INF, 0, 18, INF, INF, 5, INF, INF, INF},
		{17, INF, 18, 0, 10, INF, INF, 3, INF, INF},
		{INF, 45, INF, 10, 0, 28, INF, INF, 25, INF},
		{INF, INF, INF, INF, 28, 0, INF, INF, INF, 6},
		{INF, INF, 5, INF, INF, INF, 0, 59, INF, INF},
		{INF, INF, INF, 3, INF, INF, 59, 0, 4, INF},
		{INF, INF, INF, INF, 25, INF, INF, 4, 0, 12},
		{INF, INF, INF, INF, INF, 6, INF, INF, 12, 0}
};
/*이음선의 집합 F*/
int F[MAX_SIZE][MAX_SIZE];

/*distance 출력*/
void print_distance(int n,  int D[]) {
	printf("----------Distance----------\n");
	for (int i = 2; i <= n; i++)
		printf("%5d", D[i]);
	printf("\n");
	printf("----------------------------\n");
}

/*F출력*/
void print_F(int n) {
	printf("----------F----------\n");
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (F[i][j] == 1)
				printf("이음선(%d, %d)\n", i, j);

	printf("---------------------\n");
}

/*nearest 출력*/
void print_nearest(int n, int N[]) {
	printf("----------Nearest----------\n");
	for (int i = 2; i <= n; i++)
		printf("%3d", N[i]);
	printf("\n");
	printf("---------------------------\n");
}
void prim(int n) {
	int i, j, vnear;
	int min;
	int e;
	int nearest[MAX_SIZE];
	int distance[MAX_SIZE];

	/*이음선 집합 F 초기화*/
	for (i = 0; i <= n; i++)
		for (j = 0; j <= n; j++) {
			if (i == j)
				F[i][j] = 0;
			else
				F[i][j] = INF;
		}

	for (i = 2; i <= n; i++) {
		nearest[i] = 1;
		distance[i] = W[0][i-1];
	}
	
	for (j = 1; j <= n - 1; j++) {
		min = INF;
		for(i = 2; i <= n; i++)
			if (distance[i] >= 0  && distance[i] < min) {
				min = distance[i];
				vnear = i;
			}
		/*
		e = evnear가 인덱스인 마디를 Y에 추가한다
		add to F
		*/
		F[vnear][nearest[vnear]] = 1;

		distance[vnear] = -1;
		print_distance(n, distance);
		print_nearest(n, nearest);
		for(i = 2; i <= n; i++)
			if (W[i-1][vnear-1] < distance[i]) {
				distance[i] = W[i-1][vnear-1];
				nearest[i] = vnear;
			}
	}

	/*Disatance 출력*/
	print_distance(n, distance);

	/*F출력*/
	print_F(n);

	/*Nearest 출력*/
	print_nearest(n, nearest);

}

void main() {
	int n;
	n = 10;
	prim(n);

}
