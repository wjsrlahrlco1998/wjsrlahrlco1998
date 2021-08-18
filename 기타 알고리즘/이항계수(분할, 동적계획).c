#include <stdio.h>
#include <malloc.h>



int* B;

/*분할정복으로 이항계수 구하기*/
int bin(int n, int k) {
	if (k == 0 || n == k)
		return 1;
	else
		return bin(n - 1, k - 1) + bin(n - 1, k);
}


/*동적계획법으로 이항계수 구하기*/
int bin3(int n, int k) {
	int i, j;
	B = (int*)malloc(sizeof(int) * k);

	for (i = 1; i <= n; i++) {
		for (j = i; j >= 0; j--)
			if (j == 0 || j == i) B[j] = 1;
			else B[j] = B[j - 1] + B[j];
	}
	return B[k];
}

int main() {
	int n, k;
	n = 6;
	k = 3;

	printf("분할정복으로 계산한 이항계수 값 : %3d\n", bin(n, k));
	printf("동적계획법으로 계산한 이항계수 값 : %3d\n", bin3(n, k));

	free(B);
}
