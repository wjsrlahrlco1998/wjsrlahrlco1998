#include <stdio.h>

#define MAX_SIZE 100

int deadline[MAX_SIZE] = { 3, 1, 1, 3, 1, 3, 2};
int profit[MAX_SIZE] = { 40, 35, 30, 25, 20, 15, 10 };
int n = 7;

struct node {
	int deadline;
	int profit;
	int number;
};

struct node array[MAX_SIZE] = { {3, 40, 1}, {1, 35, 2}, {1, 30, 3}, {3, 25, 4}, {1, 20, 5}, {3, 15, 6}, {2, 10, 7} };

int J[MAX_SIZE]; // 최적의 작업순서

int promising(struct node task)
{
	int count = 1;
	int temp = task.deadline;

	if (J[0] == 0)
		return 1;
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (J[i] != 0) {
				if (temp < deadline[J[i]-1])
					temp = deadline[J[i]-1];
				count++;
			}

		}

		if (temp < count)
			return 0;
		else
			return 1;
	}
}

void schedule()
{
	struct node temp;
	int count = 0;
	int count_J = 0;

	for (int i = 0; i < n; i++)
	{
		J[i] = 0;
	}

	// 작업의 이익이 큰 것부터 차례대로 정렬
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			if (array[i].profit > array[j].profit)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}

	while (count < n) {
		//다음 작업 선택
		temp = array[count++];
		if (promising(temp)) {
			J[count_J++] = temp.number;
			printf("유망 : %d\n", temp.number);
		}
		if (count >= n)
			break;
	}
}

int main()
{
	schedule();
	printf("작업의 순서\n");
	for (int i = 0; i < n; i++)
	{
		if (J[i] != 0)
			printf("작업[%d]\n", J[i]);
	}

}
