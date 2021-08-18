#include <stdio.h>

typedef struct
{
	int weight;
	int v1;
	int v2;
}edge;

typedef struct
{
	int parent;
	int depth;
}universe;

#define VERTEX_NUM 5
#define EDGE_NUM 7
#define TRUE 1
#define FALSE 0


void input(int vertex1, int vertex2, int w);
void kruskal(int n, int m, edge* E, edge* F);
void initial(universe* U, int n);
void makeset(universe* U, int i);
int find(universe* U, int i);
void merge(universe* U, int p, int q);
int equal(int p, int q);
int check(int* array);

edge set_of_edges[EDGE_NUM];
int index = -1;
int f_index = -1;

int main()
{
	edge result[EDGE_NUM];

	input(1, 2, 1);
	input(1, 3, 3);
	input(2, 3, 3);
	input(2, 4, 6);
	input(3, 4, 4);
	input(3, 5, 2);
	input(4, 5, 5);

	kruskal(VERTEX_NUM, EDGE_NUM, set_of_edges, result);

	for (int i = 0; i <= f_index; i++)
	{
		printf("%d - %d , weight: %d\n", result[i].v1, result[i].v2, result[i].weight);
	}
}

void input(int vertex1, int vertex2, int w)
{
	set_of_edges[++index].v1 = vertex1;
	set_of_edges[index].v2 = vertex2;
	set_of_edges[index].weight = w;
}

void kruskal(int n, int m, edge* E, edge* F)
{
	universe U[VERTEX_NUM + 1];
	int add[VERTEX_NUM + 1] = { 0, };

	//sort
	for (int i = 0; i < m - 1; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if (E[i].weight > E[j].weight)
			{
				edge temp = E[i];
				E[i] = E[j];
				E[j] = temp;
			}
		}
	}
	//init array U
	for (int i = 1; i <= VERTEX_NUM; i++)
	{
		U[i].parent = 0;
		U[i].depth = 0;
	}

	//init array F
	for (int i = 0; i < m; i++)
	{
		F[i].v1 = 0;
		F[i].v2 = 0;
		F[i].weight = 0;
	}

	//initial
	initial(U, VERTEX_NUM);


	int index = 0;
	while (1)
	{
		int i, j, p, q;
		edge e = E[index];

		i = E[index].v1;
		j = E[index].v2;

		p = find(U, i);
		q = find(U, j);

		if (!equal(p, q))
		{
			merge(U, p, q);
			F[++f_index] = E[index];

		}

		index++;

		int cnt = 0;
		for (int i = 1; i <= EDGE_NUM; i++)
		{
			if (U[i].parent == i)
				cnt++;
		}

		if (cnt == 1)
			break;
	}

}

void initial(universe* U, int n)
{
	for (int i = 1; i <= n; i++)
		makeset(U, i);
}

void makeset(universe* U, int i)
{
	U[i].parent = i;
	U[i].depth = 0;
}

int find(universe* U, int i)
{
	int j;
	j = i;

	while (U[j].parent != j)
	{
		j = U[j].parent;
	}
	return j;
}

void merge(universe* U, int p, int q)
{
	if (U[p].depth == U[q].depth)
	{
		U[p].depth += 1;
		U[q].parent = p;
	}
	else if (U[p].depth < U[q].depth)
		U[p].parent = q;
	else
		U[q].parent = p;
}

int equal(int p, int q)
{
	if (p == q)
		return TRUE;
	else
		return FALSE;
}

int check(int* array)
{
	int finish = TRUE;
	for (int i = 1; i <= VERTEX_NUM; i++)
	{
		if (array[i] == FALSE)
			finish = FALSE;
	}

	return finish;
}
