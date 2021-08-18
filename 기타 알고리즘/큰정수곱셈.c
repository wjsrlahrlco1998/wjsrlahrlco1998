#include <stdio.h>
#include <math.h>

#define MAX(A, B) ((A) > (B)) ? (A) : (B)

/*임계점 정하기*/
int threshold = 5;

int countNumber(int num) {
	int count = 0;
	while (num != 0) {
		num = num / 10;
		count++;
	}

	return count;
}

unsigned long long prod(int u, int v) {
	int x, y, w, z;
	int n, m;

	/*n=maximum(u의 숫자 개수, v의 숫자 개수*/
	n = MAX(countNumber(u), countNumber(v));
	if (u == 0 || v == 0)
		return 0;
	else if (n <= threshold)
		return u * v;
	else {
		m = n / 2;
		/* x = u devide 10^m*/
		x = u / (int)pow(10, m);
		/* y = u rem 10^m*/
		y = u % (int)pow(10, m);
		/* w = v divide 10^m*/
		w = v / (int)pow(10, m);
		/* z = v rem 10^m*/
		z = v % (int)pow(10, m);
		int temp = 2 * m;
		return prod(x, w) * (int)pow(10, temp) + (prod(x, z)+(prod(w, y))) * (int)pow(10, m) + prod(y, z);
	}
}

unsigned long long prod2(int u, int v) {
	int x, y, w, z;
	unsigned long long r, p, q;
	int n, m;

	n = MAX(countNumber(u), countNumber(v));
	if (u == 0 || v == 0)
		return 0;
	else if (n <= threshold)
		return u * v;
	else {
		m = n / 2;
		x = u / (int)pow(10, m);
		y = u % (int)pow(10, m);
		w = v / (int)pow(10, m);
		z = v % (int)pow(10, m);
		r = prod2(x + y, w + z);
		p = prod2(x, w);
		q = prod2(y, z);
		int temp = 2 * m;
		return p * (int)pow(10, temp) + (r - p - q) * (int)pow(10, m) + q;
	}
}

int main() {
	int large_a, large_b;
	unsigned long long result = 0;

	large_a = 567832;
	large_b = 9423;
	
	result = prod(large_a, large_b);
	printf("(prod1)곱셈의 결과 : %lld\n", result);
	result = prod2(large_a, large_b);
	printf("(prod2)곱셈의 결과 : %lld\n", result);
	
}
