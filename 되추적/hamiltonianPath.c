#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define MAX_SIZE 100

int vindex[MAX_SIZE];
int W[MAX_SIZE][MAX_SIZE];

int n;
int judg = 0;
int count = 0;

int promising(int i);

void hamiltonian(int i)
{
	int j;

	if (i > 0)
	{
		printf("\n%d. 정점 %d 방문.\n", ++count, i);
		printf("선택 경로 : %d\n", vindex[i]);
	}

	if (promising(i))
		if (i == n - 1)
		{
			judg = 1;
			printf("---해밀튼 경로---\n");
			for (j = 0; j <= n - 1; j++)
			{
				printf("vindex[%d] : %d\n", j, vindex[j]);
			}
			printf("-----------------\n");
		}
		else
		{
			for (j = 2; j <= n; j++)
			{
				vindex[i + 1] = j;
				hamiltonian(i + 1);
			}
		}
}

int promising(int i)
{
	int j;
	int bswitch;

	if (i == n - 1 && !W[vindex[n - 1]][vindex[0]]) {
		printf("첫번째 정점과 마지막 정점이 인접하지 않아 유망하지 않음.\n");
		bswitch = FALSE;
	}
	else if (i > 0 && !W[vindex[i - 1]][vindex[i]]) {
		printf("%d번째 정점과 %d번째 정점이 인접하지 않아 유망하지 않음\n", i-1, i);
		bswitch = FALSE;
	}
	else
	{
		bswitch = TRUE;
		j = 1;
		while (j < i && bswitch)
		{
			if (vindex[i] == vindex[j]) {
				printf("%d번째 정점은 이미 선택된 정점이라 유망하지 않음\n", j);
				bswitch = FALSE;
			}
			j++;
		}
	}
	return bswitch;
}

void main()
{
	//노드의 개수
	n = 12;
	
	//W 초기화
	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
			W[i][j] = FALSE;
	
	W[1][2] = TRUE;
	W[2][1] = TRUE;
	W[1][5] = TRUE;
	W[5][1] = TRUE;
	W[2][3] = TRUE;
	W[3][2] = TRUE;
	W[2][7] = TRUE;
	W[7][2] = TRUE;
	W[2][8] = TRUE;
	W[8][2] = TRUE;
	W[3][4] = TRUE;
	W[4][3] = TRUE;
	W[3][8] = TRUE;
	W[8][3] = TRUE;
	W[4][9] = TRUE;
	W[9][4] = TRUE;
	W[5][6] = TRUE;
	W[6][5] = TRUE;
	W[5][10] = TRUE;
	W[10][5] = TRUE;
	W[6][7] = TRUE;
	W[7][6] = TRUE;
	W[6][11] = TRUE;
	W[11][6] = TRUE;
	W[7][8] = TRUE;
	W[8][7] = TRUE;
	W[8][9] = TRUE;
	W[9][8] = TRUE;
	W[9][12] = TRUE;
	W[12][9] = TRUE;
	W[10][11] = TRUE;
	W[11][10] = TRUE;
	W[11][12] = TRUE;
	W[12][11] = TRUE;
	

	/*
	W[1][2] = TRUE;
	W[2][1] = TRUE;
	W[1][7] = TRUE;
	W[7][1] = TRUE;
	W[1][8] = TRUE;
	W[8][1] = TRUE;
	W[1][3] = TRUE;
	W[3][1] = TRUE;
	W[2][3] = TRUE;
	W[3][2] = TRUE;
	W[2][7] = TRUE;
	W[7][2] = TRUE;
	W[2][8] = TRUE;
	W[8][2] = TRUE;
	W[3][4] = TRUE;
	W[4][3] = TRUE;
	W[3][6] = TRUE;
	W[6][3] = TRUE;
	W[4][5] = TRUE;
	W[5][4] = TRUE;
	W[5][6] = TRUE;
	W[6][5] = TRUE;
	W[6][7] = TRUE;
	W[7][6] = TRUE;
	W[7][8] = TRUE;
	W[8][7] = TRUE;
	*/

	vindex[0] = 1;
	hamiltonian(0);
	if (judg == 0)
	{
		printf("해밀튼 경로가 존재하지 않습니다.\n");
	}

}
