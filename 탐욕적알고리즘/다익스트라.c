#include <stdio.h>

#define MAX_SIZE 100
#define INF 999

int W[MAX_SIZE][MAX_SIZE] = {
	{0, 7, 4, 6, 1},
	{INF, 0, INF, INF, INF},
	{INF, 2, 0, 5, INF},
	{INF, 3, INF, 0, INF},
	{INF, INF, INF, 1, 0}
};

/*이음선의 집합 F*/
int F[MAX_SIZE][MAX_SIZE];

void dijkstra(int n)
{
	int e;
	int i, vnear;
	int min;
	int touch[MAX_SIZE];
	int length[MAX_SIZE];

	// F초기화
	for (i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (i == j)
				F[i][j] = 0;
			else
				F[i][j] = INF;
		}
			

	for (i = 2; i <= n; i++)
	{
		touch[i] = 1;
		length[i] = W[0][i-1];
	}

	for (int j = 0; j < n; j++)
	{
		min = INF;
		for (i = 2; i <= n; i++) {
			if (length[i] >= 0 && length[i] < min) {
				min = length[i];
				vnear = i;
			}
		}

			// e = touch[vnear]와 vnear을 잇는 이음선
			// e를 F에 추가
			F[touch[vnear]][vnear] = length[vnear];


			for (i = 2; i <= n; i++) {
				if (length[vnear] + W[vnear-1][i-1] < length[i]) {
					length[i] = length[vnear] + W[vnear-1][i-1];
					touch[i] = vnear;
				}
			}
			length[vnear] = -1;
		
	}

}

void print_F(int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (F[i][j] != INF && F[i][j] != 0)
				printf("이음선(%d, %d)\n", i, j);
		}
	}
}

int main()
{
	int n = 5;
	dijkstra(5);
	print_F(5);
}
