#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L //무한대 표현

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 최소 distance[v] 값을 갖는 정점을 반환
int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i<n; i++) 
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	return (v);
}

//prim Algorithm
void prim(GraphType* g, int s) {
	int i, u, v;

	for (u = 0; u < g->n; u++)
		distance[u] = INF;
	distance[s] = 0;
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		/*1번위치*/
		for (int j = 0; j < g->n; j++) {
			printf("1번위치 distance[%d] 값 : %d, selected[%d] 값 : %d\n", j, distance[j], j, selected[j]);
		}
		if (distance[u] == INF) return;
		printf("정점 %d 추가\n", u);
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF)
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];
					/*2번위치*/
					for (int j = 0; j < g->n; j++) {
						printf("2번위치 distance[%d] 값 : %d, selected[%d] 값 : %d\n", j, distance[j], j, selected[j]);
					}
				}
	}
}

int main(void)
{
	GraphType g = { 10,
		{{0, 32, INF, 17, INF, INF, INF, INF, INF, INF},
		{32, 0, INF, INF, 45, INF, INF, INF, INF, INF},
		{INF, INF, 0, 18, INF, INF, 5, INF, INF, INF},
		{17, INF, 18, 0, 10, INF, INF, 3, INF, INF},
		{INF, 45, INF, 10, 0, 28, INF, INF, 25, INF},
		{INF, INF, INF, INF, 28, 0, INF, INF, INF, 6},
		{INF, INF, 5, INF, INF, INF, 0, 59, INF, INF},
		{INF, INF, INF, 3, INF, INF, 59, 0, 4, INF},
		{INF, INF, INF, INF, 25, INF, INF, 4, 0, 12},
		{INF, INF, INF, INF, INF, 6, INF, INF, 12, 0}}
	};

	prim(&g, 0);
	return 0;
}
