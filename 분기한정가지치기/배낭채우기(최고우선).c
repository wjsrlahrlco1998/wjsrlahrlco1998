#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int p[MAX_SIZE] = { 0, 40, 30, 50, 10 };
int w[MAX_SIZE] = { 0, 2, 5, 10, 5 };
int maxprofit;
int W = 16;
int n = 4;

struct node {
	int level;
	int profit;
	int weight;
	float bound;
};

struct priority_queue_of_node {
	struct node data[MAX_SIZE];
	int count;
};

float bound(struct node u);

void initialize(struct priority_queue_of_node* PQ) {
	PQ->count = 0;
}

void swap(struct node* u, struct node* v)
{
	struct node temp = *u;
	*u = *v;
	*v = temp;

}

int empty(struct priority_queue_of_node* PQ)
{
	if (PQ->count <= 0) return 1;
	return 0;
}

void insert(struct priority_queue_of_node* PQ, struct node u)
{
	if (PQ->count >= MAX_SIZE) return;
	int now = PQ->count;
	PQ->data[now] = u;
	printf("[Insert]\nlevel : %d\nprofit : %d\nweight : %d\nbound : %f\n", u.level, u.profit, u.weight, u.bound);
	int parent = (now - 1) / 2;

	while (now > 0 && PQ->data[now].bound > PQ->data[parent].bound) {
		swap(&PQ->data[now], &PQ->data[parent]);
		now = parent;
		parent = (now - 1) / 2;
	}

	PQ->count++;
}

struct node remove_queue(struct priority_queue_of_node* PQ)
{
	if (empty(PQ))
		exit(1);
	struct node u = PQ->data[0];
	printf("[Remove]\nlevel : %d\nprofit : %d\nweight : %d\nbound : %f\n", u.level, u.profit, u.weight, u.bound);
	PQ->count--;
	PQ->data[0] = PQ->data[PQ->count];
	int now = 0, left = 1, right = 2;
	int change = now;
	while (now <= PQ->count) {
		if (left <= PQ->count && PQ->data[now].bound < PQ->data[left].bound) change = left;
		if (right <= PQ->count && PQ->data[now].bound < PQ->data[right].bound) change = right;
		if (change == now) break;

		swap(&PQ->data[now], &PQ->data[change]);
		now = change;
		left = now * 2 + 1;
		right = now * 2 + 2;
	}

	return u;
}

void knapsack3()
{
	struct priority_queue_of_node* PQ = malloc(sizeof(struct priority_queue_of_node));
	struct node u, v;

	initialize(PQ);
	v.level = 0;
	v.profit = 0;
	v.weight = 0;
	maxprofit = 0;
	v.bound = bound(v);
	insert(PQ, v);
	while (!empty(PQ)) {
		v = remove_queue(PQ);
		if (v.bound > (float)maxprofit) {
			u.level = v.level + 1;
			u.weight = v.weight + w[u.level];
			u.profit = v.profit + p[u.level];
			if (u.weight <= W && u.profit > maxprofit)
				maxprofit = u.profit;
			u.bound = bound(u);
			if (u.bound > (float)maxprofit)
				insert(PQ, u);
			u.weight = v.weight;
			u.profit = v.profit;
			if (u.bound > (float)maxprofit)
				insert(PQ, u);
		}
	}

	free(PQ);
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
	knapsack3();
}
