#include <stdio.h>
#include <malloc.h>

#define INF 999

int S[INF] = { 0, 27, 10, 12, 20, 25, 13, 15, 22 };

void merge2(int low, int mid, int high) {
	int i, j, k;
	int U[INF];
	i = low; j = mid + 1; k = low;
	while (i <= mid && j <= high) {
		if (S[i] < S[j]) {
			U[k] = S[i];
			i++;
		}
		else
		{
			U[k] = S[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		/*move S[j]...S[high] to U[k]...U[high]*/
		for (int p = j; p <= high; p++)
			if (k <= high) {
				U[k] = S[p];
				k++;
			}
	}
	else {
		/*move S[i]...S[mid] to U[k]...U[high]*/
		for(int p = i; p <= mid; p++)
			if (k <= high) {
				U[k] = S[p];
				k++;
			}
	}
	/*move U[low]...U[high] to S[low]...S[high]*/
	for (int p = low; p <= high; p++)
		S[p] = U[p];
}

void mergesort2(int low, int high) {
	int mid;

	if (low < high) {
		mid = (low + high) / 2;
		mergesort2(low, mid);
		mergesort2(mid + 1, high);
		merge2(low, mid, high);
	}
}

void printArray(int n) {
	for (int i = 1; i <= n; i++)
		printf("%3d", S[i]);
	printf("\n");
}

int main() {
	int n;
	n = 8;

	mergesort2(1, n);
	printf("정렬된 배열 S : ");
	printArray(n);

}
