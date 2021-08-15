#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_SIZE 100


int maxprofit;
int numbest;
int bestset[MAX_SIZE];
int include[MAX_SIZE];
int p[MAX_SIZE];
int w[MAX_SIZE];
int W = 9;
int n = 5;

int promising(int i, int weight, int profit);

void knapsack(int i, int profit, int weight)
{
	if (i > 0) {
		if (include[i] == TRUE) {
			printf("마디(%d,%d) 방문\n", i, 1);
			printf("weight : %d\n", weight);
			printf("profit : %d\n", profit);
		}
		else {
			printf("마디(%d,%d) 방문\n", i, 2);
			printf("weight : %d\n", weight);
			printf("profit : %d\n", profit);
		}
	}

	if (weight <= W && profit > maxprofit)
	{
		maxprofit = profit;
		numbest = i;
		printf("maxprofit가 %d로 교체됨.\n", maxprofit);
		//bestset = include;
		for (int j = 1; j <= n; j++)
			bestset[j] = include[j];
	}

	if (promising(i, weight, profit))
	{
		include[i + 1] = TRUE;
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = FALSE;
		knapsack(i + 1, profit, weight);
	}
}

int promising(int i, int weight, int profit)
{
	int j, k;
	int totweight;
	float bound;

	if (weight >= W) {
		printf("weight >= W이므로 유망하지 않음\n");
		return FALSE;
	}
	else {
		j = i + 1;
		bound = profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= W)
		{
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		}
		k = j;
		if (k <= n)
			bound = bound + (W - totweight) * p[k] / w[k];
		printf("totweight : %d\n", totweight);
		printf("bound : %f\n", bound);

		if (!(bound > maxprofit))
			printf("bound > maxprofit이므로 유망하지 않음.\n");

		return bound > maxprofit;
	}
}

void main()
{
	p[1]= 20;
	p[2] = 30;
	p[3] = 35;
	p[4] = 12;
	p[5] = 3;

	w[1] = 2;
	w[2] = 5;
	w[3] = 7;
	w[4] = 3;
	w[5] = 1;

	numbest = 0;
	maxprofit = 0;
	knapsack(0, 0, 0);

	printf("maxprofit = %d\n", maxprofit);
	for (int j = 1; j <= numbest; j++)
		printf("bestset[%d] : %d\n", j, bestset[j]);
}
