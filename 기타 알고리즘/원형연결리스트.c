#include <stdio.h>
#include <stdlib.h>

//data 자료형 정의
typedef int element;

//노드 구조체 정의
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

//앞 삽입함수 정의
ListNode* insert_first(ListNode* head, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
	}
	return head;
}

//뒷 삽입함수 정의
ListNode* insert_last(ListNode* head, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
		head = node;
	}
	return head;
}

//리스트 출력 함수
void print_list(ListNode* head) {
	ListNode* p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);
	printf("%d->", p->data);
}

//탐색함수
ListNode* search(ListNode* head, element value) {
	ListNode* p;
	if (head == NULL) {
		printf("값이 존재하지 않습니다\n");
		return NULL;
	}
	for (p = head->link; p != head; p = p->link) {
		if (p->data == value) {
			printf("값이 존재합니다\n");
			return p;
		}
	}
	printf("값이 존재하지 않습니다\n");
	return NULL;
}

//리스트 데이터 갯수 반환 함수
int get_size(ListNode* head) {
	ListNode* p = head;
	int count = 0;
	if (head == NULL) return count;
	for (p = head->link; p != head; p = p->link) {
		count++;
	}
	return count + 1;
}

//리스트 삭제 함수(처음 노드 삭제)
ListNode* delete_first(ListNode* head) {
	ListNode* p;
	if (head == NULL) return NULL;
	if (head == head->link) { 
		p = head;
		head = NULL;
	}
	else {
		p = head->link;
		head->link = p->link;
	}
	free(p);
	return head;
}

//리스트 삭제 함수(마지막 노드 삭제)
ListNode* delete_last(ListNode* head) {
	ListNode* p, * q;
	if (head == NULL) return NULL;
	if (head == head->link) {
		p = head;
		head = NULL;
	}
	else {
		q = head->link;
		while (head != q->link)
			q = q->link;
		p = head;
		q->link = p->link;
		head = q;
	}
	free(p);
	return head;
}


//메인함수
int main() {
	ListNode* head = NULL;
	head = insert_last(head, 10);
	head = insert_last(head, 20);
	head = insert_last(head, 30);

	//int value = 0;
	//printf("검색할 값을 입력하시오: ");
	//scanf_s("%d", &value);

	//head = search(head, value);
	//delete_first(head);
	head = delete_last(head);
	print_list(head);
	

}
