#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_SIZE 100

int include[MAX_SIZE];
int n;
int w[MAX_SIZE];
int W;
int count = 1;

void print_bag()
{
	printf("==========BAG%d===========\n", count);
	printf("=========================\n");
	for (int i = 1; i <= n; i++)
		if (include[i] == 1) 
		{
			printf("| X ");
		}
		else
		{
			printf("|   ");
		}
	printf("|   ");
	printf("\n=========================\n");
	count++;
}

void sum_of_subsets(int i, int weight, int total)
{
	print_bag();
	if (promising(i, weight, total))
		if (weight == W) {
			printf("!!weight == W인 부분집합 발견!!\n");
			for (int p = 1; p <= i; p++) 
			{
				if(include[p] == 1)
					printf("w[%d] 를 포함\n", p);
			}
		}
		else
		{
			include[i + 1] = 1; // w[i+1]을 포함한다.
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
			include[i + 1] = 0; // w[i+1]을 포함하지 않는다.
			sum_of_subsets(i + 1, weight, total - w[i + 1]);
		}

}

int promising(int i, int weight, int total)
{
	return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

int extimate_sum_of_subsets(int i, int weight, int total)
{
	int m, mprod, t, numnodes;
	int prom_children[MAX_SIZE]; // 유망한 자식 마디의 집합
	int index = 0;
	int j, q;
	int flag = 0;
	int select = 0;

	int uncontent_total = 0;
	int uncontent_weight = 0;

	int content_total = 0;
	int content_weight = 0;

	int uncontent_flag = 0;
	int content_flag = 0;

	numnodes = 1;
	m = 1; //유망한 마디의 갯수
	mprod = 1; //각 수준에서 만들어진 m0 * m1 ... * m을 표현
	t = 2; //t = 수준 i에서 어떤 마디의 자식마디의 총 개수

	while (m != 0 && W != weight)
	{
		printf("weight : %d\n", weight);
		//mprod = v의 자식마디의 개수;
		mprod = mprod * m;
		numnodes = numnodes + mprod * t;
		
		m = 0; //m = v의 유망한 자식마디의 개수;
		i++;
		/*j를 포함할 때, 유망한 자식 갯수 구하기*/
		for (q = 0; q <= 1; q++) {
			if (q == 0)
			{
				uncontent_weight = weight;
				uncontent_total = total - w[i];
				if (promising(i, uncontent_weight, uncontent_total))
				{
					m++;
					uncontent_flag = 1;
				}
			}
			else
			{
				content_weight = weight + w[i];
				content_total = total - w[i];
				if (promising(i, content_weight, content_total))
				{
					m++;
					content_flag = 1;
				}

			}
		}
		if (m != 0)
		{
			//v = v의 무작위로 선택한 자식마디의 개수;
			if (uncontent_flag == 0 && content_flag == 0)
			{
				//back
				--i;
				if (j == 0)
				{
					j = 1;
					uncontent_total = total + w[i];
					include[i] = j;
				}
				else
				{
					j = 0;
					content_weight = weight - w[i];
					content_total = total + w[i];
					include[i] = j;
				}
			}
			else if (uncontent_flag == 1 && content_flag == 0)
			{
				j = 0;
				include[i] = j;
			}
			else if (uncontent_flag == 0 && content_flag == 1)
			{
				j = 1;
				include[i] = j;
			}
			else if (uncontent_flag == 1 && content_flag == 1)
			{
				srand((unsigned)time(NULL));
				j = (rand() % 2);
				include[i] = j;
			}

			

			if (include[i] == 0)
			{
				total = uncontent_total;
			}
			else if(include[i] == 1)
			{
				weight = content_weight;
				total = content_total;
			}
			
			uncontent_weight = 0;
			uncontent_total = 0;

			content_weight = 0;
			content_total = 0;

			content_flag = 0;
			uncontent_flag = 0;

			
			
		}
	}
	printf("FINAL weight : %d\n", weight);
	return numnodes;
}

void main()
{
	int total = 0;

	w[1] = 2;
	w[2] = 10;
	w[3] = 13;
	w[4] = 17;
	w[5] = 22;
	w[6] = 42;

	n = 6;

	for (int i = 0; i < n; i++)
		total = total + w[i+1];

	W = 52; // 수용가능 무게

	//최초호출
	//sum_of_subsets(0, 0, total);

	int list[20];
	int avg = 0;

	printf("<몬테칼로 추정치 계산>\n");
	for (int i = 0; i < 20; i++)
	{
		list[i] = extimate_sum_of_subsets(0, 0, total);
		printf("%d : %d\n", i + 1, list[i]);
		avg = avg + list[i];
		Sleep(1000);
	}

	printf("평균값 : %d\n", avg / 20);
}
