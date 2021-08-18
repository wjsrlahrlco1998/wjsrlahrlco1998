#include <stdio.h>
#include <math.h>

#define MAX_SIZE 100
#define MAX(A, B) ((A) > (B) ? (A) : (B))

int P[MAX_SIZE][MAX_SIZE];
int weight[MAX_SIZE]; //무게
int p[MAX_SIZE]; //가치

int fillBag(int n, int W) {

	int w, i;

	for (w = 0; w <= W; w++)
		P[0][w] = 0;
	for (i = 0; i <= n; i++)
		P[i][0];

	for (i = 1; i <= n; i++)
		for (w = 1; w <= W; w++)
			if (w < weight[i])
				P[i][w] = P[i - 1][w];
			else
				P[i][w] = MAX(P[i - 1][w], P[i - 1][w - weight[i]] + p[i]);

	return P[n][W];
}

void main() {

	int n; //물건의 개수
	int w; //제한무게


	n = 3;
	w = 30;
	
	weight[1] = 5;
	weight[2] = 10;
	weight[3] = 20;

	p[1] = 50;
	p[2] = 60;
	p[3] = 140;
	
	int result = fillBag(n, w);
	printf("최대 이익 : %d\n", result);


}
