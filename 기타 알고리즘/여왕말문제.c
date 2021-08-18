#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define index int
#define MAX_SIZE 100

int col[MAX_SIZE];
char grid[MAX_SIZE][MAX_SIZE];
int n = 8;
int count = 1;
int count0 = 1;
int promising_x;
int promising_y;



void print_grid()
{
	printf("[%d번째 수행]\n", count0);
	printf("---------------------------------\n");
	for (int i = 1; i <= n; i++)
	{
		//printf("\n==========\n");
		for (int j = 1; j <= n; j++)
		{
			printf("| %c ", grid[i][j]);
			if (j == n)
				printf("|");
		}
		printf("\n---------------------------------\n");
	}
	count0++;

}

int abs1(int value)
{
	if (value >= 0)
		return value;
	else
		return (value * (-1));
}

int promising(int i)
{
	index k;
	int switch_value;

	k = 1;
	switch_value = 1;
	while (k < i && switch_value)
	{
		if (col[i] == col[k] || abs1(col[i] - col[k]) == i - k)
			switch_value = 0;
		k++;
    }
	return switch_value;
}


void queens(index i)
{
	index j;

	if (promising(i)) {
		grid[i][col[i]] = 'X';
		promising_x = i;
		promising_y = col[i];
		//print_grid();
		for (int p = 0; p < i; p++)
			printf("\t");
		printf("[(%d,%d)\n", i, col[i]);
		if (i == n) {
			printf("=========%d번째 해답=========\n", count);
			for (int a = 1; a <= n; a++)
				printf("(%d, %d)\n", a, col[a]);
			count++;
		}
		else 
		{
			for (j = 1; j <= n; j++)
			{
				col[i + 1] = j;
				queens(i + 1);
			}
			for (int p = 0; p < i; p++)
				printf("\t");
			printf("]\n");
			promising_x = i;
			promising_y = col[i];
		}
	}
	grid[i][col[i]] = ' ';
	if (count == 2)
		exit(1);
	else {
		for (int p = 0; p < i; p++)
			printf("\t");
		if (promising_x == i && promising_y == col[i])
			printf("\n");
		else
			printf("[(%d,%d)]\n", i, col[i]);
	}
}

int extimate_n_queens()
{
	index i, j, p;
	int m, mprod, t, numnodes;
	int prom_children[MAX_SIZE];
	int flag;
	int index_value;

	i = 0;
	numnodes = 1;
	m = 1;
	mprod = 1;
	flag = 0;
	index_value = 0;

	while (m != 0 && i != n)
	{
		mprod = mprod * m;
		numnodes = numnodes + mprod * n;
		i++;
		m = 0;
		//prom_children = 공집합
		for (p = 1; p <= n; p++)
			prom_children[p] = 0;

		for (j = 1; j <= n; j++)
		{
			col[i] = j;
			if (promising(i))
			{
				m++;
				//prom_children = prom_children 합집합{ j };
				for(p = 1; p <= n; p++)
					if (prom_children[p] == 0)
					{
						prom_children[p] = j;
						break;
					}
			}
		}
		if (m != 0)
		{
			//j = prom_children에서 무작위로 선택한 인덱스;
			for (p = 1; p <= n; p++)
			{
				if (prom_children[p] != 0)
					index_value++;
			}

			srand((unsigned)time(NULL));
			flag = (rand() % index_value) + 1;


			j = prom_children[flag];

			col[i] = j;
			index_value = 0;
		}
	}

	return numnodes;
}

void main()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			grid[i][j] = ' ';

	int list[20];
	int avg = 0;

	printf("<몬테칼로 추정치 계산>\n");
	for (int i = 0; i < 20; i++)
	{
		list[i] = extimate_n_queens();
		printf("%d : %d\n", i + 1, list[i]);
		avg = avg + list[i];
		Sleep(1000);
	}

	printf("평균값 : %d\n", avg / 20);

	//queens(0);
}
