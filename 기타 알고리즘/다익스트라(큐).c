#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000
#define MAX_QUEUE_SIZE 100

typedef struct {
	int front;
	int rear;
	int data[MAX_QUEUE_SIZE];
} QueueType;
QueueType q;

void init_queue(QueueType* q) {
	q->rear = -1;
	q->front = -1;
}

int is_full(QueueType* q) {
	if (q->rear == MAX_QUEUE_SIZE - 1)
		return 1;
	else
		return 0;
}

int is_empty(QueueType* q) {
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

void enqueue(QueueType* q, int item) {
	if (is_full(q)) {
		fprintf(stderr, "큐가 포화상태 입니다");
		return;
	}
	q->data[++(q->rear)] = item;
}

int dequeue(QueueType* q) {
	if (is_empty(q)) {
		fprintf(stderr, "큐가 공백상태입니다");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}

typedef struct GraphType {
	int n; //정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int path[MAX_VERTICES];

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0; i<n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status(GraphType* g) {
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF) {
			printf(" * ");
		}
		else {
			enqueue(&q, i);
			printf("0");
			for (int i = 0; is_empty(&q) != 1; i++) {
				printf("->%d", dequeue(&q));
			}
			printf(" (%2d) ", distance[i]);
			
		}
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
	printf(" path: \n");
}


void shortest_path(GraphType* g, int start) {
	int i, u, w;
	init_queue(&q);
	for (i = 0; i < g->n; i++) { /*초기화*/
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; /*시작 정점 방문 표시*/
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					printf("w: %d, u: %d \n", w, u);
					enqueue(&q, u);
					enqueue(&q, w);

				}
	}
}

int main() {
	GraphType g = { 6,
		{{0, 50, 45, 10, INF, INF},
		{INF, 0, 10, 15, INF, INF},
		{INF, INF, 0, INF, 30, INF},
		{20, INF, INF, 0, 15, INF},
		{INF, 20, 35, INF, 0, INF},
		{INF, INF, INF, INF, 3, 0}},
	};
	shortest_path(&g, 0);
	return 0;
}
