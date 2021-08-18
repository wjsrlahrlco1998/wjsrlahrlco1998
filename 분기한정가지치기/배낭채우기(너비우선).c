#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int p[MAX_SIZE] = { 0, 20, 30, 35, 12, 3 };
int w[MAX_SIZE] = { 0, 2, 5, 7, 3, 1 };
int maxprofit;
int W = 10;
int n = 5;

float bound(struct node u);

struct node {
	int level;
	int profit;
	int weight;
};

struct queue_of_node{
	int head;
	int tail;
	struct node data[MAX_SIZE];
};

void initialize(struct queue_of_node* q) {
	q->head = 0;
	q->tail = 0;
}

int empty(struct queue_of_node* q) {
	if (q->head == q->tail)
		return 1;
	return 0;
}

void enqueue(struct queue_of_node* q, struct node u)
{
	q->data[q->head++] = u;
	printf("[enqueue]\nlevel : %d\nprofit : %d\nweight : %d\n\n", u.level, u.profit, u.weight);
	q->head = q->head % MAX_SIZE;
}

struct node dequeue(struct queue_of_node* q)
{
	struct node data;

	if (empty(q))
	{
		printf("큐가 비었습니다.\n");
		exit(1);
	}

	data = q->data[q->tail++];
	printf("[dequeue]\nlevel : %d\nprofit : %d\nweight : %d\n\n", data.level, data.profit, data.weight);
	q->tail = q->tail % MAX_SIZE;

	return data;
}

void knapsack2()
{
	struct queue_of_node* Q = malloc(sizeof(struct queue_of_node));
	struct node u, v;

	initialize(Q);
	v.level = 0;
	v.profit = 0;
	v.weight = 0;

	maxprofit = 0;
	enqueue(Q, v);
	while (!empty(Q)) {
		v = dequeue(Q);
		u.level = v.level + 1;
		u.weight = v.weight + w[u.level];
		u.profit = v.profit + p[u.level];
		if (u.weight <= W && u.profit > maxprofit)
			maxprofit = u.profit;
		if (bound(u) > (float)maxprofit)
			enqueue(Q, u);
		u.weight = v.weight;
		u.profit = v.profit;
		if (bound(u) > (float)maxprofit)
			enqueue(Q, u);
	}

	printf("\nMaxprofit : %d\n", maxprofit);

}

float bound(struct node u)
{
	int j, k;
	int totweight;
	float result;

	if (u.weight >= W)
		return 0;
	else {
		result = (float)u.profit;
		j = u.level + 1;
		totweight = u.weight;
		while (j <= n && totweight + w[j] <= W) {
			totweight = totweight + w[j];
			result = result + p[j];
			j++;
		}
		k = j;
		if (k <= n)
			result = result + (W - totweight) * p[k] / w[k];
		return result;
	}
}

int main()
{
	knapsack2();
}
