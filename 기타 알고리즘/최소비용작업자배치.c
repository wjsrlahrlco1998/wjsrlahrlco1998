#include <stdio.h>

#define MAX_SIZE 100
#define INF 999

//i째 작업자를 j에 배치하는 비용
int C[MAX_SIZE][MAX_SIZE];
int flag_worker[MAX_SIZE];
int flag_work[MAX_SIZE];


int min_placement(int n) {
	int i, j;
	int min = INF;
	int value = 0;
	int flag_i;
	int flag_j;
	int count = 0;

	for (i = 1; i <= n; i++) {
		flag_worker[i] = 0;
		flag_work[i] = 0;
	}

	while (1) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (min > C[i][j] && flag_worker[i] != 1 && flag_work[j] != 1) {
					min = C[i][j];
					flag_i = i;
					flag_j = j;
				}

		value += min;
		min = INF;
		flag_worker[flag_i] = 1;
		flag_work[flag_j] = 1;

		for (i = 1; i <= n; i++) {
			if (flag_worker[i] == 1)
				count++;
		}

		if (count == 3)
			break;
		else
			count = 0;
	}

	return value;
}

void main() {

	int n; //작업자와 작업의 수
	
	n = 3;

	C[1][1] = 20;
	C[1][2] = 10;
	C[1][3] = 30;
	C[2][1] = 10;
	C[2][2] = 40;
	C[2][3] = 15;
	C[3][1] = 30;
	C[3][2] = 35;
	C[3][3] = 35;

	int result = min_placement(3);
	printf("최소비용배치 : %d\n", result);
}
