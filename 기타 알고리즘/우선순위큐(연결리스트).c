#include <stdio.h>
#include <stdlib.h>
//최대 우선순위 큐
typedef int element;
typedef struct ListNode{
	element data;
	struct ListNode* left;
	struct ListNode* right;
} ListNode;
//에러 출력함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
//우선순위 큐 생성
ListNode* create() {
	return (ListNode*)malloc(sizeof(ListNode));
}

//우선순위 큐 초기화
void init(ListNode* head) {
	head->left = head;
	head->right = head;
}

//우선순위 큐 비어있는지 검사
int is_empty(ListNode* head) {
	if (head->right == NULL && head->left) return 1;
	return 0;
}


//우선순위 큐 삽입 연산(삽입과 동시에 새로운 노드 생성) - first 삽입
void insert(ListNode* head, element item) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	init(p);
	p->data = item;
	p->left = head;
	p->right = head->right;
	head->right->left = p;
	head->right = p;
}

//우선순위 큐 삭제 연산
element delete(ListNode* head) {
	ListNode* remove = (ListNode*)malloc(sizeof(ListNode));
	if (is_empty(head)) {
		error("우선순위 큐가 비었습니다");
	}
	element max_value;
	remove = head;
	max_value = remove->data;
	for (ListNode* p = head->right; p != head; p = p->right) {
		if (max_value < p->data) {
			max_value = p->data;
			remove = p;
		}
	}
	remove->left->right = remove->right;
	remove->right->left = remove->left;
	free(remove);

	return max_value;

}

//우선순위가 가장 높은 요소를 반환
element find(ListNode* head) {
	if (is_empty(head)) {
		error("우선순위 큐가 비었습니다");
	}
	element max_value = -1;
	for (ListNode* p = head; p != NULL; p = p->right) {
		if (max_value < p->data) {
			max_value = p->data;
		}
	}

	return max_value;
}

int main() {
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	init(head);
	insert(head, 3);
	insert(head, 5);
	insert(head, 7);
	insert(head, 2);
	insert(head, 1);

	printf("delete: %d\n", delete(head));
	printf("delete: %d\n", delete(head));
	printf("delete: %d\n", delete(head));
	printf("delete: %d\n", delete(head));
	printf("delete: %d\n", delete(head));

	return 0;
}
