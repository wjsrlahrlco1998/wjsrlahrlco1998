#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10

typedef int element;

//큐타입 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

//오류 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//큐 초기화 함수
void queue_init(QueueType* q) {
	q->front = q->rear = 0;
}

//큐 공백 상태 검출 함수
int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

//큐 포화 상태 검출 함수
int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

//큐 삽입 함수
void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태 입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

//큐 삭제 함수
element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백 상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

/*----------------여기서부터 그래프 정의-------------------*/
#define MAX_VERTICES 50
typedef struct GraphNode {
	int vertex;
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
void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
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

//너비 우선 탐색
void bfs_list(GraphType* g, int v) {
	GraphNode* w0;
	QueueType q;

	queue_init(&q);
	visited[v] = TRUE;
	printf("%d 방문 -> ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w0 = g->adj_list[v]; w0; w0 = w0->link) {
			if (!visited[w0->vertex]) {
				visited[w0->vertex] = TRUE;
				printf("%d 방문 -> ", w0->vertex);
				enqueue(&q, w0->vertex);
			}
		}
	}
}

//깊이 우선 탐색
void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE;
	printf("정점 %d -> ", v);
	for (w = g->adj_list[v]; w; w = w->link)
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
}

//진출 차수 계산 함수
int out_degree(GraphType* g, int v) {
	int sum = 0;
	GraphNode* w = g->adj_list[v];
	while (w != NULL) {
		sum++;
		w = w->link;
	}

	return sum;
}

//진입 차수 계산 함수
int in_degree(GraphType* g, int v) {
	int sum = 0;
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		if (p != v) {
			while (p != NULL) {
				int target = p->vertex;
				if (target == v) sum++;
				p = p->link;
			}
		}
	}

	return sum;
}

//그래프 간선 개수 계산 함수
int cal_edge(GraphType* g) {
	int sum = 0;
	for (int i = 0; i < g->n; i++) {
		GraphNode* p = g->adj_list[i];
		while (p != NULL) {
			sum++;
			p = p->link;
		}
	}

	return sum;
}

//메인함수
int main() {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 4; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 1);
	insert_edge(g, 1, 0);
	insert_edge(g, 0, 2);
	insert_edge(g, 2, 0);
	insert_edge(g, 0, 3);
	insert_edge(g, 3, 0);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 3, 2);

	printf("%d의 진출 차수 : %d\n", 0, out_degree(g, 0));
	printf("%d의 진입 차수 : %d\n", 0, in_degree(g, 3));
	printf("그래프 g의 간선의 개수 : %d \n", cal_edge(g));

	//printf("%d의 너비 우선 탐색 결과 \n", 0);
	//bfs_list(g, 0);
	//printf("\n");
	printf("%d의 깊이 우선 탐색 결과 \n", 0);
	dfs_list(g, 0);
	printf("\n");

	print_adj_list(g);
	free(g);
	return 0;
}
