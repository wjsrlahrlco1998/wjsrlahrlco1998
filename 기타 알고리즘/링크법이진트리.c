#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//트리의 구조체 정의
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

//트리 선언
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 3, &n1, NULL };
TreeNode n3 = { 11, NULL, NULL };
TreeNode n4 = { 12, NULL, NULL };
TreeNode n5 = { 13, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

/*반복적인 중위 순회를 위한 스택 정의*/
#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void push(TreeNode* p) {
	if (top < SIZE - 1)
		stack[++top] = p;
}

TreeNode* pop() {
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

void inorder_iter(TreeNode* root) {
	while (1) {
		for (; root; root = root->left)
			push(root);
		root = pop();
		if (!root) break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}
/*------------------------------------*/

/*레벨 순회를 위한 원형 큐 정의*/
#define MAX_QUEUE_SIZE 100
typedef TreeNode* element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태 입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태 입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode* ptr) {
	QueueType q;

	init_queue(&q);

	if (ptr == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf(" [%d] ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}
/*----------------------------------*/

//중위 순회
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}

//전위 순회
void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("[%d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

//후위 순회
void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data);
	}
}


//트리 높이 구하는 함수
int get_height(TreeNode* t) {
	int height = 0;
	if (t != NULL)
		height = 1 + max(get_height(t->left), get_height(t->right));
	return height;
}

//균형트리 검사 함수
void isBalanced(TreeNode* t) {
	if (t == NULL) {
		printf("트리가 NULL입니다.\n");
		return;
	}
	int left_height = get_height(t->left);
	int right_height = get_height(t->right);

	if (left_height >= right_height) {
		if (left_height - right_height <= 1) {
			printf("균형 트리 입니다\n");
			return;
		}
		else {
			printf("균형 트리가 아닙니다\n");
			return;
		}
	}
	else {
		if (right_height - left_height <= 1) {
			printf("균형 트리 입니다\n");
			return;
		}
		else {
			printf("균형 트리가 아닙니다\n");
			return;
		}
	}
	


}

//주어진 값보다 작으면 그 노드를 출력하는 함수
void print_less_value(TreeNode* t, int value) {
	if (t != NULL) {
		print_less_value(t->left, value);
		if (t->data < value) {
			printf("%d보다 작은 노드: %d\n", value, t->data);
		}
		print_less_value(t->right, value);
	}
}

//노드의 최대값을 탐색하는 함수
int search_max(TreeNode* t) {
	if (t == NULL) {
		return -1000;
	}
	int max_value = t->data;
	max_value = max(max_value, search_max(t->left));
	max_value = max(max_value, search_max(t->right));
	return max_value;
}

//노드의 최소값을 탐색하는 함수
int search_min(TreeNode* t) {
	if (t == NULL) {
		return 1000;
	}
	int min_value = t->data;
	min_value = min(min_value, search_min(t->left));
	min_value = min(min_value, search_min(t->right));
	return min_value;
}

//모든 노드 값의 합
int cal_dir_size(TreeNode* root) {
	int left_size, right_size;
	if (root == NULL) return 0;

	left_size = cal_dir_size(root->left);
	right_size = cal_dir_size(root->right);
	return (root->data + left_size + right_size);
}


//메인함수
int main() {
	printf("최소값=%d\n", search_min(&n6));
	printf("최대값=%d\n", search_max(&n6));

	printf("레벨 순회=");
	level_order(root);
	printf("\n");

	printf("중위 순회=");
	inorder(root);
	printf("\n");

	printf("중위 순회(스택)=");
	inorder_iter(root);
	printf("\n");

	printf("전위 순회=");
	preorder(root);
	printf("\n");

	printf("후위 순회=");
	postorder(root);
	printf("\n");

	printf("모든 노드의 합 : %d\n", cal_dir_size(root));

}
