#include <stdio.h>
#include <stdlib.h>


/*피보나치 수열의 재귀적 함수*/
int fib(int n) {
	if (n <= 1)
		return n;
	else
		return fib(n - 1) + fib(n - 2);
}

/*피보나치 수열의 반복적 함수*/
int fib2(int n) {
	int i;
	int* f;
	int temp = 0;
	f = (int*)malloc(sizeof(int) * n);

	f[0] = 0;
	if (n > 0) {
		f[1] = 1;
		for (i = 2; i <= n; i++) {
			f[i] = f[i-1] + f[i - 2];
			printf("f[%d] = %d\n", i, f[i]);
		}
	}
	temp = f[n];
	free(f);
	return temp;

}

int main() {

	int result, result2;
	int n;

	printf("피보나치 할 수 입력: ");
	scanf("%d", &n);

	result = fib(n);
	printf("(재귀)결과 : %d\n", result);
	result2 = fib2(n);
	printf("(반복)결과 : %d\n", result2);

}
