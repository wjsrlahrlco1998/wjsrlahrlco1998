#include <stdio.h>

int location;

/*배열에서 key값 찾고 location 반환*/
void seqsearch(int n, int S[], int key) {

	location = 1;
	while (location <= n && S[location] != key) {
		location++;
		if (location > n)
			location = 0;
	}
}

/*배열의 수 더하기*/
int sum(int n, const int S[]) {
	int i, result;
	result = 0;

	for (i = 0; i < n; i++)
		result = result + S[i];
	return result;
}

/*배열 정렬 함수*/
void exchange(int n, int S[]) {
	int i, j;
	int temp;
	for (i = 0; i < n-1; i++) {
		for (j = i + 1; j < n; j++)
			if (S[j] < S[i])
			{
				temp = S[i];
				S[i] = S[j];
				S[j] = temp;
			}
	}
}

/*배열 출력*/
void printArray(int n, int S[]) {
	for (int i = 0; i < n; i++)
		printf("%d ", S[i]);
	printf("\n");
}

int main() {
	
	int S[6] = { 6, 2, 1, 5, 7, 9 };
	int n = 6;
	
	int key;
	printf("찾을 수 : ");
	scanf("%d", &key);

	seqsearch(n, S, key);

	printf("key의 위치는? %d\n", location+1);

	int result = sum(n, S);
	printf("배열의 합 : %d\n", result);

	exchange(n, S);
	printArray(n, S);

}
