#include <stdio.h>

#define INF 999

int S[INF] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int count = 0;

int partition(int low, int high) {
	int i, j;
	int pivotitem;
	int temp;
	int pivotpoint;

	pivotitem = S[low];
	j = low;
	for(i = low + 1; i <= high; i++)
		if (S[i] < pivotitem) {
			j++;
			/*exchange S[i] and S[j]*/
			temp = S[j];
			S[j] = S[i];
			S[i] = temp;
		}
	pivotpoint = j;
	/*exchange S[low] and S[pivotpoint]*/
	temp = S[pivotpoint];
	S[pivotpoint] = S[low];
	S[low] = temp;

	return pivotpoint;
}

void quicksort(int low, int high) {
	int pivotpoint;
	printf("실행횟수 : %d \n", ++count);
	if (high > low) {
		pivotpoint = partition(low, high);
		quicksort(low, pivotpoint - 1);
		quicksort(pivotpoint + 1, high);
	}
}

void printArray(int n) {
	for (int i = 1; i <= n; i++)
		printf("%3d", S[i]);
	printf("\n");
}

int main() {

	int n;
	n = 10;

	quicksort(0, n);
	printf("정렬된 배열 S : ");
	printArray(n);
}
