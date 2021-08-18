#include <stdio.h>
#include <stdlib.h>

//키의 자료형 정의
typedef int element;
//트리의 구조체 정의
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
} TreeNode;

//순환 탐색 함수
TreeNode* search(TreeNode* node, element key) {
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

//반복적 탐색 함수
TreeNode* search_2(TreeNode* node, element key) {
	while (node != NULL) {
		if (key == node->key) return node;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

//노드 생성 함수
TreeNode* new_node(element item) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

//노드 삽입 함수
TreeNode* insert_node(TreeNode* node, element key) {
	// 트리가 공백이면 새로운 노드 반환
	if (node == NULL) return new_node(key);

	// 순환적으로 트리 탐색
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);

	// 변경된 루트 포인터 반환
	return node;
}

//노드의 최솟값 찾는 함수
TreeNode* min_value_node(TreeNode* node) {
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

//노드 삭제 함수
TreeNode* delete_node(TreeNode* root, element key) {
	if (root == NULL) return root;

	//key < root->key이면 왼쪽 서브 트리
	if (key < root->key)
		root->left = delete_node(root->left, key);
	//key > root->key이면 오른쪽 서브 트리
	if (key > root->key)
		root->right = delete_node(root->right, key);
	else {
		// key == root->key인 경우 root 삭제
		// 첫번째 or 두번째 경우
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// 세번째 경우, 오른쪽 서브트리에서 후계노드 찾기
		TreeNode* temp = min_value_node(root->right);

		// 중위 순회시 후계 노드 복사
		root->key = temp->key;
		// 중위 순회시 후계 노드 삭제
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

//중위 순회
void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left);
		printf("[%d] ", root->key);
		inorder(root->right);
	}
}

//내림차순 정렬 함수
void inorder_up(TreeNode* root) {

	if (root) {
		inorder_up(root->right);
		printf("[%d] ", root->key);
		inorder_up(root->left);
	}
}

//노드의 개수 구하는 함수
int get_node_count(TreeNode* node) {
	int count = 0;

	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);

	return count;
}

//단말노드 개수 구하기
int get_leaf_count(TreeNode* node) {
	int count = 0;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
	}
	return count;
}

//높이 구하기
int get_height(TreeNode* node) {
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

//메인함수
int main() {
	TreeNode* root = NULL;

	root = insert_node(root, 11);
	root = insert_node(root, 3);
	root = insert_node(root, 4);
	root = insert_node(root, 1);
	root = insert_node(root, 56);
	root = insert_node(root, 5);
	root = insert_node(root, 6);
	root = insert_node(root, 2);
	root = insert_node(root, 98);
	root = insert_node(root, 32);
	root = insert_node(root, 23);

	printf("중위 순회: ");
	inorder(root);
	printf("\n");
	
	printf("오름차순 정렬: ");
	inorder(root);
	printf("\n");
	printf("내림차순 정렬: ");
	inorder_up(root);
	printf("\n");

	printf("노드의 개수: %d\n", get_node_count(root));
	printf("단말노드의 개수: %d\n", get_leaf_count(root));
	printf("트리의 높이: %d\n", get_height(root));
	
}
