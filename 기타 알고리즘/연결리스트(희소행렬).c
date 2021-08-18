#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//Data의 자료형 정의
typedef struct element {
	int row;
	int col;
	int value;
} element;
//노드의 구조체 정의
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

//오류처리 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//노드의 맨앞에 삽입 함수
ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}


//노드의 맨뒤에 삽입 함수
void insert_last(ListNode** head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (*head == NULL) {
		p->link = NULL;
		p->data = value;
		*head = p;
		return;
	}
	p->link = NULL;
	ListNode* q = *head;
	p->link = NULL;
	p->data = value;
	while (q->link != NULL)
		q = q->link;
	q->link = p;
}

//맨 앞의 노드 삭제 함수
ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

//노드 전체 출력 함수
void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("행 : %d, 열 : %d, 값 : %d\n", p->data.col, p->data.row, p->data.value);
	printf("NULL \n");
}


//노드 크기 구하는 함수
int size(ListNode* list) {
	ListNode* p;
	int count = 0;
	for (p = list; p != NULL; p = p->link)
		count++;
	return count;
}


//메인함수
int main() {
	ListNode* head1 = NULL;
	ListNode* head2 = NULL;
	int num = 0;
	element data;
	printf("희소행렬 중 0이 아닌 항의 개수 : ");
	scanf_s("%d", &num);
	for (int i = 0; i < num; i++) {
		printf("0이 아닌 항의 행과 열과 값 : ");
		scanf_s("%d %d %d", &data.col, &data.row, &data.value);
		head1 = insert_first(head1, data);
	}

	print_list(head1);
	free(head1);
}
