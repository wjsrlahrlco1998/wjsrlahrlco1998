#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define INF 99

int W[MAX_SIZE][MAX_SIZE] = {
	{0, 0, 0, 0, 0, 0},
	{0, 0, 6, 6, 10, 8},
	{0, 3, 0, 12, 7, 6},
	{0, 8, 7, 0, 14, 20},
	{0, 5, 13, 9, 0, 8},
	{0, 9, 8, 10, 6, 0}

};

int opttour[MAX_SIZE];

int minlength;
int n = 5;

struct node {
	int level;
	int bound;
	int path[MAX_SIZE]; //array
};

struct priority_queue_of_node {
	struct node data[MAX_SIZE];
	int count;
};

struct priority_queue_of_node PQ;

int PQ_empty();
void swap(struct node* u, struct node* v);
void PQ_init();
struct node PQ_remove();
void PQ_insert(struct node v);
void travel2();
int length(struct node v);
int bound(struct node v);
int hasOutgoing(int i, int n_path[]);
int hasIncoming(int i, int n_path[]);
int constain(int n_path[], int i);
void ordered_set_insert(int n_path[], int i);
void copy_array(int a[], int b[]);
void init_array(int a[]);
int lastOf(int n_path[]);
void print_tour(int a[]);
void print_array(int a[]);

int PQ_empty() {
	if (PQ.count <= 0) return 1;
	return 0;
}

void swap(struct node* u, struct node* v)
{
	struct node temp = *u;
	*u = *v;
	*v = temp;
}

void PQ_init()
{
	PQ.count = 0;
}

struct node PQ_remove()
{
	if (PQ_empty())
	{
		printf("큐가 비었습니다.\n");
		exit(1);
	}
	struct node u = PQ.data[0];
	PQ.count--;
	PQ.data[0] = PQ.data[PQ.count];
	int now = 0;
	int left = 1;
	int right = 2;

	int target = now;

	while (left < PQ.count) {
		if (PQ.data[target].bound > PQ.data[left].bound) target = left;
		if (PQ.data[target].bound > PQ.data[right].bound) target = right;
		if (target == now) break;

		swap(&PQ.data[now], &PQ.data[target]);
		now = target;
		left = now * 2 + 1;
		right = now * 2 + 2;
	}

	printf("[PQ_remove]\n level : %d\nbound : %d\nlength : %d\n\n", u.level, u.bound, length(u));
	print_tour(u.path);
	printf("\n");
	return u;
}

void PQ_insert(struct node v)
{
	if (PQ.count >= MAX_SIZE) return;
	int now = PQ.count;
	PQ.data[now] = v;
	int parent = (now - 1) / 2;

	while (now > 0 && PQ.data[now].bound < PQ.data[parent].bound) {
		swap(&PQ.data[now], &PQ.data[parent]);
		now = parent;
		parent = (now - 1) / 2;
	}

	printf("[PQ_insert]\nlevel : %d\nbound : %d\nlength : %d\n\n", v.level, v.bound, length(v));
	print_tour(v.path);
	printf("\n");
	PQ.count++;
}

void travel2()
{
	struct node u, v;

	PQ_init();

	//path 초기화
	for (int i = 0; i <= n; i++)
		v.path[i] = 0;

	v.level = 0;
	v.path[0] = 1;
	v.bound = bound(v);
	minlength = INF;
	PQ_insert(v);
	while (!PQ_empty()) {
		v = PQ_remove();
		printf("v.bound : %d, minlength : %d\n\n", v.bound, minlength);
		if (v.bound < minlength) {
			u.level = v.level + 1;
			for (int i = 2; i <= n; i++) {
				if (constain(v.path, i)) continue;
				copy_array(u.path, v.path);
				ordered_set_insert(u.path, i);
				
				
				if (u.level == n - 1) {
					//put index of remaining vertices to u.path
					ordered_set_insert(u.path, 1);
					//printf("경로 : ");
					//print_tour(u.path);
					if (length(u) < minlength) {
						minlength = length(u);
						copy_array(opttour, u.path);

					}
				}
				else {
					u.bound = bound(u);
					if (u.bound < minlength)
						PQ_insert(u);
				}
			}
		}
	}
	
}

int length(struct node v) {
	int length = 0;
	for (int i = 1; i <= n; i++)
		if (v.path[i] != 0)
		{
			length += W[i][v.path[i]];
		}
	return length;
}

int bound(struct node v) {
	int min;
	int total = length(v);
	for (int i = 1; i <= n; i++) {
		if (hasOutgoing(i, v.path)) continue;
		min = INF;
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (hasIncoming(j, v.path)) continue;
			if (j == 1 && i == lastOf(v.path)) continue;
			if (min > W[i][j]) min = W[i][j];
		}
		total += min;
	}
	return total;
}

int lastOf(int n_path[])
{
	int index = 1;
	if (n_path[0] == 0)
		return 0;

	while (1)
	{
		if (n_path[index] == 0) break;
		index = n_path[index];
	}

	return index;
}

int hasOutgoing(int i, int n_path[])
{
	int flag[MAX_SIZE];
	init_array(flag);

	for (int j = 1; j <= n; j++)
	{
		if (n_path[j] != 0)
			flag[j] = 1;
	}

	if (flag[i] == 1) return 1;
	else return 0;
}

int hasIncoming(int i, int n_path[])
{
	int flag[MAX_SIZE];
	init_array(flag);

	for (int j = 1; j <= n; j++)
		if (n_path[j] != 0)
			flag[n_path[j]] = 1;

	if (flag[i] == 1) return 1;
	else return 0;
}

int constain(int n_path[], int i)
{
	int flag[MAX_SIZE];
	init_array(flag);

	for (int j = 1; j <= n; j++)
	{
		if (n_path[j] != 0)
		{
			flag[j] = 1;
			flag[n_path[j]] = 1;
		}
	}

	if (flag[i] == 1)
		return 1;
	else
		return 0;
}

void ordered_set_insert(int n_path[], int i)
{
	int index = 0;
	int count = 0;

	while (1)
	{
		if (n_path[index] == 0) {
			n_path[index] = i;
			break;
		}
		index = n_path[index];
		count++;
	}

}

void copy_array(int a[], int b[])
{
	for (int i = 0; i <= n; i++)
	{
		a[i] = b[i];
	}
}

void init_array(int a[])
{
	for (int i = 0; i <= n; i++)
		a[i] = 0;
}

void print_tour(int a[])
{
	int index = 0;
	int flag[MAX_SIZE];
	init_array(flag);

	if (a[index] == 0) return;

	while (1)
	{
		if (a[index] != 0)
			printf("v%d ", a[index]);
		flag[index] = 1;
		index = a[index];
		if (flag[index] == 1) break;
	}
	printf("\n");
	return;
}

void print_array(int a[])
{
	printf("[array]\n");
	for (int i = 0; i <= n; i++)
		printf("[%d] : %d\n", i, a[i]);
	printf("------\n");
}

int main()
{
	int index = 1;

	travel2();
	
	printf("[최적경로]\n");
	print_tour(opttour);
}
