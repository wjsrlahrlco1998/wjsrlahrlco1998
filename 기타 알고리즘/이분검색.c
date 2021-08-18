#include <stdio.h>
#define INF 999

int location;
int key;
int S2[INF] = { 0, 1, 4, 5, 6, 10, 17 };

/*이분검색의 반복적 방법*/
void binsearch(int n, const int S[], int x) {
	int low, high, mid;

	low = 1;
	high = n;
	location = 0;
	while (low <= high && location == 0) {
		mid = (low + high) / 2;
		if (x == S[mid])
			location = mid;
		else if (x < S[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
}

/*이분검색의 재귀적 방법*/
int locations(int low, int high) {
	int mid;

	if (low > high)
		return 0;
	else {
		mid = (low + high) / 2;
		if (key == S2[mid])
			return mid;
		else if (key < S2[mid])
			return locations(low, mid - 1);
		else
			locations(mid + 1, high);

	}
}

int main() {

	int S[INF] = { 0, 1, 4, 5, 6, 10, 17 };
	int n = 6;

	int x = 0;
	printf("이분검색할 수 : ");
	scanf("%d", &x);
	key = x;

	binsearch(n, S, x);

	printf("(반복)위치 : %d\n", location);

	int temp = locations(0, n);
	printf("(재귀)위치 : %d\n", temp);

}
