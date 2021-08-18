#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0
#define INF 1000000

int distance[MAX_VERTICES];
int found[MAX_VERTICES];


typedef struct GraphNode {
	int vertex;
	int weight;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];

//그래프 초기화 
void init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;

}

//정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

//간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType* g, int u, int v, int weight) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->weight = weight;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

//그래프 출력 함수
void print_adj_list(GraphType* g) {
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		printf("정점 %d의 인접 리스트", i);
		while (p != NULL) {
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}

//choose
int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

//distance 출력함수
void print_status(GraphType* g) {
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf("found : ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
	

}

//Dijkstra 함수
void shortest_path(GraphType* g, int start) {
	int i, u, w;
	int correct[6];
	GraphType* t = (GraphType*)malloc(sizeof(GraphType));
	init(t);
	t->n = 6;
	GraphNode* p = g->adj_list[start];
	for (i = 0; i < g->n; i++) {
		distance[i] = p->weight;
		found[i] = FALSE;
		correct[i] = FALSE;
		p = p->link;
	}
	found[start] = TRUE;
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		GraphNode* p = g->adj_list[u];
		for(w=0; w < g->n; w++, p = p->link)
			if (!found[w]) {
				if (distance[u] + p->weight < distance[w]) {
					distance[w] = distance[u] + p->weight;
					printf("수정후 경로 : %d -> %d -> %d \n", start, u, w);
					correct[w] = TRUE;
					insert_edge(t, w, u, w);
				}
				else {
					if (distance[w] != INF && correct[w] != FALSE) {
						printf("수정후 경로 : %d -> %d -> %d \n", start, t->adj_list[w]->vertex, t->adj_list[w]->weight);
					}
					else if(distance[w] != INF) {
						printf("수정후 경로 : %d -> %d \n", start, w);
					}
				}
			}
			else {
				if (distance[w] != INF && correct[w] != FALSE) {
					printf("수정후 경로 : %d -> %d -> %d \n", start, t->adj_list[w]->vertex, t->adj_list[w]->weight);
				}
				else if(distance[w] != INF) {
					printf("수정후 경로 : %d -> %d \n", start, w);
				}
			}
				
	}
}


int main() {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 6; i++) {
		insert_vertex(g, i);
	}

	
	

	insert_edge(g, 0, 5, INF);
	insert_edge(g, 0, 4, INF);
	insert_edge(g, 0, 3, 10);
	insert_edge(g, 0, 2, 45);
	insert_edge(g, 0, 1, 50);
	insert_edge(g, 0, 0, 0);
	insert_edge(g, 1, 5, INF);
	insert_edge(g, 1, 4, INF);
	insert_edge(g, 1, 3, 15);
	insert_edge(g, 1, 2, 10);
	insert_edge(g, 1, 1, 0);
	insert_edge(g, 1, 0, INF);
	insert_edge(g, 2, 5, INF);
	insert_edge(g, 2, 4, 30);
	insert_edge(g, 2, 3, INF);
	insert_edge(g, 2, 2, 0);
	insert_edge(g, 2, 1, INF);
	insert_edge(g, 2, 0, INF);
	insert_edge(g, 3, 5, INF);
	insert_edge(g, 3, 4, 15);
	insert_edge(g, 3, 3, 0);
	insert_edge(g, 3, 2, INF);
	insert_edge(g, 3, 1, INF);
	insert_edge(g, 3, 0, 20);
	insert_edge(g, 4, 5, INF);
	insert_edge(g, 4, 4, 0);
	insert_edge(g, 4, 3, INF);
	insert_edge(g, 4, 2, 34);
	insert_edge(g, 4, 1, 20);
	insert_edge(g, 4, 0, INF);
	insert_edge(g, 5, 5, 0);
	insert_edge(g, 5, 4, 3);
	insert_edge(g, 5, 3, INF);
	insert_edge(g, 5, 2, INF);
	insert_edge(g, 5, 1, INF);
	insert_edge(g, 5, 0, INF);

	
	shortest_path(g, 0);

	free(g);

}
