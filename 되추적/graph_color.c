#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_SIZE 100

int vcolor[MAX_SIZE];
int W[MAX_SIZE][MAX_SIZE];
int n;
int m;
int count = 0;
int count_1 = 0;

int promising(int i);

void m_coloring(int i)
{
	int color;

	if (i > 0) {
		printf("%d)정점 %d번 방문.\n", ++count_1, i);
		printf("정점 %d번의 색깔 : %d\n\n", i, vcolor[i]);
	}

	if (promising(i))
		if (i == n)
		{
			++count;
			printf("---%d번째 색칠 방법---\n", count);
			for (int j = 1; j <= n; j++)
				printf("[v%d : %d] ", j, vcolor[j]);
			printf("\n----------------------\n");
		}
		else
			for (color = 1; color <= m; color++)
			{
				vcolor[i + 1] = color;
				m_coloring(i + 1);
			}
}

int promising(int i)
{
	int j;
	int bswitch;

	bswitch = TRUE;
	j = 1;
	while (j < i && bswitch)
	{
		if (W[i][j] && vcolor[i] == vcolor[j]) {
			printf("%d) 인접한 정점 %d와 정점 %d의 색깔이 같으므로 유망하지 않다.\n\n",++count_1, i, j);
			bswitch = FALSE;
		}
		j++;
	}
	return bswitch;
}

void main()
{
	//색깔 종류
	m = 3;

	//노드 갯수
	n = 6;

	//W 초기화
	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
			W[i][j] = FALSE;

	//이음선 잇기
	W[1][2] = TRUE;
	W[2][1] = TRUE;
	W[1][4] = TRUE;
	W[4][1] = TRUE;
	W[2][3] = TRUE;
	W[3][2] = TRUE;
	W[2][5] = TRUE;
	W[5][2] = TRUE;
	W[3][6] = TRUE;
	W[6][3] = TRUE;
	W[4][5] = TRUE;
	W[5][4] = TRUE;
	W[5][6] = TRUE;
	W[6][5] = TRUE;

	m_coloring(0);
}
