#include <stdio.h>

#define INF 999

int C[INF][INF];

void strassen(int n, int A[][4], int B[][4]) {

	if(n <= threshold) // n이 임계점 보다 작을 시에 표준 알고리즘으로 계산
		for(int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				C[i][j] = 0;
				for (int k = 0; k < n; k++)
					C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
	else {
		/*A를 A11 A12 A21 A22로 분할*/
		/*B를 B11 B12 B21 B22로 분할*/
		/*쉬트라센의 방법으로 C=A*B를 계산*/
	}

}

int main() {

	int n;
	int A[4][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 1, 2, 3},
		{4, 5, 6, 7}
	};
	int B[4][4] = {
		{8, 9, 1, 2},
		{3, 4, 5, 6},
		{7, 8, 9, 1},
		{2, 3, 4, 5}
	};

	strassen(n, A, B);
}
