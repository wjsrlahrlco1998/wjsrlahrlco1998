#include <stdio.h>

#define keytype int
#define MAX_SIZE 100
#define MAX_VALUE 10000
#define MIN(A, B) ((A) > (B) ? (B) : (A))

struct nodetype{
	keytype key;
	struct nodetype* left;
	struct nodetype* right;

} nodetype;

typedef struct nodetype* node_pointer;

void search(node_pointer tree, keytype keyin, node_pointer p) {
	int found;

	p = tree;
	found = -1;
	while (found != -1) {
		if (p->key == keyin)
			found = 1;
		else if (keyin < p->key)
			p = p->left;
		else
			p = p->right;
	}
}

//배열 
float A[MAX_SIZE][MAX_SIZE];
int R[MAX_SIZE][MAX_SIZE];
float minavg = 0;

void optsearchtree(int n, const float p[]) {

	int i, j, k, diagonal;
	float sum = 0;
	for (i = 1; i <= n; i++) {
		A[i][i - 1] = 0;
		A[i + 1][i] = 0;
		A[i][i] = p[i-1];
		R[i][i] = i;
		R[i][i - 1] = 0;
		R[i + 1][i] = 0;
	}
	A[n + 1][n] = 0;
	R[n + 1][n] = 0;
	for(diagonal=1; diagonal <= n-1; diagonal++)
		for (i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
			A[i][j] = MAX_VALUE;


			for (k = i; k <= j; k++) {
				if (A[i][j] > A[i][k - 1] + A[k + 1][j])
					R[i][j] = k;
				A[i][j] = MIN(A[i][j], A[i][k - 1] + A[k + 1][j]);
				
			}
			//p의 합
			for (int m = i - 1; m < j; m++)
				sum += p[m];
			A[i][j] += sum;
			sum = 0;
		}
	
	minavg = A[1][n];
}

void printA(int n) {
	printf("--------------A--------\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%2.5f ", A[i][j]);
		}
		printf("\n");
	}
	printf("-------------------------\n");
}

void printR(int n) {
	printf("--------------R--------\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%3d ", R[i][j]);
		}
		printf("\n");
	}
	printf("-------------------------\n");
}

int main() {
	float p[4] = { 0.375, 0.375, 0.125, 0.125};
	optsearchtree(4, p);

	printA(4);
	printR(4);
	printf("A[1][%d] = %f\n", 4, minavg);

}
