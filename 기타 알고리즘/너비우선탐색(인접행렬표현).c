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
typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];
int count = 0;

//그래프 초기화
void graph_init(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

//정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

//간선 삽입 연산
void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

//깊이 우선 탐색 함수
void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = TRUE;
	printf("정점 %d -> ", v);
	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
}

//깊이 우선 탐색 함수
void dfs_mat_bridge(GraphType* g, int v) {
	int w;
	visited[v] = count;
	printf("정점 %d -> ", v);
	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat_bridge(g, w);
}

//너비 우선 탐색 함수
void bfs_mat(GraphType* g, int v) {
	int w;
	QueueType q;

	queue_init(&q);
	visited[v] = TRUE;
	printf("%d 방문 -> ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w=0; w<g->n; w++)
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE;
				printf("%d 방문 -> ", w);
				enqueue(&q, w);
			}
	}
}

// 진출 차수 계산 함수
int out_degree(GraphType* g, int v) {
	int sum = 0;

	for (int i = 0; i < g->n; i++)
		sum += g->adj_mat[v][i];
	return sum;
}

//진입 차수 계산 함수
int in_degree(GraphType* g, int v) {
	int sum = 0;

	for (int i = 0; i < g->n; i++)
		sum += g->adj_mat[i][v];
	return sum;
}

//간선의 개수 계산 함수
int cal_edge(GraphType* g) {
	int sum = 0;

	for (int i = 0; i < g->n; i++)
		for (int j = 0; j < g->n; j++)
			sum += g->adj_mat[i][j];

	return sum;
}

//브릿지(끊어진 간선)을 찾는 함수
void find_bridge(GraphType* g) {
	int i;
	int u, v;
	int temp = 0;
	for (i = 0; i < g->n; i++) {
		if (!visited[i]) {
			count++;
			dfs_mat_bridge(g, i);
		}
	}
	printf("\n");

	for (i = 0; i < g->n; i++) {
		printf("visited[%d] : %d \n", i, visited[i]);
	}

	for (i = 0; i < g->n; i++) {
		if (visited[i] == 2) {
			temp = i;
			break;
		}
			
	}

	u = temp - 1;
	v = temp;

	printf("Bridge is (%d, %d) \n", u, v);

}

//파일 읽는 함수
void read_graph_mat(GraphType* g, char* name) {
	char buffer[20];
	char n_char;
	int n;
	int i = 0;
	FILE* fp = fopen(name, "r");
	fgets(buffer, 20, fp);
	n_char = buffer[0];
	n = n_char - '0';
	for (int i = 0; i < n; i++)
		insert_vertex(g, i);
	while (feof(fp) == 0) {
		fgets(buffer, 20, fp);
		printf("%s", buffer);
		
			for (int j = 0; j < ((g->n) * 2); j += 2) {
				n_char = buffer[j];
				n = n_char - '0';
				if (j == 0) g->adj_mat[i][j] = n;
				else g->adj_mat[i][j / 2] = n;

			}
			i++;
	}

	

	fclose(fp);
}

//파일 작성 함수
void write_graph_mat(GraphType* g, char* name) {
	FILE* fp = fopen(name, "w");
	fclose(fp);
	char n_char;

	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			n_char = g->adj_mat[i][j] + '0';
			fp = fopen(name, "a");
			fputc(n_char, fp);
			fputs(" ", fp);
			fclose(fp);
		}
		fp = fopen(name, "a");
		fputs("\n", fp);
		fclose(fp);
	}
}

//인접행렬 출력 함수
void print_adj_mat(GraphType* g)
{
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}

//메인함수
int main() {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	
	for (int i = 0; i < 5; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 1);
	
	insert_edge(g, 0, 2);
	
	insert_edge(g, 1, 2);
	
	insert_edge(g, 3, 4);
	
	
	print_adj_mat(g);

	


	printf("%d의 진출차수 : %d \n", 0, out_degree(g, 0));
	printf("%d의 진입차수 : %d \n", 1, in_degree(g, 1));
	printf("Graph g의 간선의 개수 : %d \n", cal_edge(g));
	

	
	free(g);
	return 0;
}
