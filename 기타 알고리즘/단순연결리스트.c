#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//Data의 자료형 정의
typedef int element;
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

// 노드의 중간에 삽입하는 함수
ListNode* insert(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
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

//중간 노드 삭제 함수(pre가 가리키는 다음 노드 삭제)
ListNode* delete(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

//노드 전체 출력 함수
void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

//노드 생성 함수
ListNode* create(element data) {
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->data = data;
	new_node->link = NULL;
	return new_node;
}

//노드 크기 구하는 함수
int size(ListNode* list) {
	ListNode* p;
	int count = 0;
	for (p = list; p != NULL; p = p->link)
		count++;
	return count;
}

//특정 값을 갖는 노드의 개수를 구하는 함수
int size_value(ListNode* list, element value) {
	ListNode* p;
	int count = 0;
	for (p = list; p != NULL; p = p->link) {
		if (p->data == value)
			count++;
	}
	return count;
}

//홀수번째 노드 삭제 함수
void delete_odd(ListNode** head) {
	*head = (*head)->link;
	ListNode* p = NULL;
	ListNode* removed = *head;
	while (removed->link != NULL) {
		p = removed;
		removed = removed->link;
		p->link = removed->link;
		if (removed->link != NULL)
			removed = removed->link;
		else
			break;
	}
	return;
}

//두개의 리스트를 합치는 함수
ListNode* concat_list(ListNode* head1, ListNode* head2) {
	if (head1 == NULL && head2 == NULL) return NULL;
	ListNode* p;
	p = head1;
	while (p->link != NULL)
		p = p->link;
	p->link = head2;
	return head1;
}

//두개의 리스트를 오름차순으로 합치는 함수
ListNode* merge(ListNode* head1, ListNode* head2) {
	if (head1 == NULL && head2 == NULL) return NULL;
	ListNode* p = head1;
	ListNode* q = head2;
	ListNode* new_node = NULL;
	while (p != NULL && q != NULL) {
		if (p->data < q->data) {
			insert_last(&new_node, p->data);
			p = p->link;
		}
		else {
			insert_last(&new_node, q->data);
			q = q->link;
		}
	}
	while (p != NULL) {
		insert_last(&new_node, p->data);
		p = p->link;
	}
	while (q != NULL) {
		insert_last(&new_node, q->data);
		q = q->link;
	}
	return new_node;
}

//노드값 탐색 함수
ListNode* search_list(ListNode* head, element x)
{
	ListNode* p = head;
	while (p != NULL) {
		if (p->data == x) return p;
		p = p->link;
	}
	return NULL;
}

//두개의 리스트를 하나로 합치는 함수
/*
ListNode* concat_list(ListNode* head1, ListNode* head2) {
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		ListNode* p;
		p = head1;
		while (p->link != NULL) {
			p = p->link;
		}
		p->link = head2;
		return head1;
	}
}
*/

//리스트를 역순으로 만드는 함수
ListNode* reverse(ListNode* head) {
	ListNode* p, * q, * r;

	p = head;
	q = NULL;
	while (p != NULL) {
		r = q;

		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

//리스트 분리 함수
void split(ListNode** A, ListNode** B, ListNode* C) {
	ListNode* p = C;
	int count = 1;
	while (p != NULL) {
		if (count) {
			insert_last(A, p->data);
			p = p->link;
			count = 0;
		}
		else {
			insert_last(B, p->data);
			p = p->link;
			count = 1;
		}
	}
	return;
}

//메인함수
int main() {
	ListNode* head1 = NULL;
	ListNode* head2 = NULL;
	ListNode* head3 = NULL;
	int num = 0;
	element data = 0;
	printf("1번 노드의 개수 : ");
	scanf_s("%d", &num);
	for (int i = 0; i < num; i++) {
		printf("노드 #%d 데이터 : ", i + 1);
		scanf_s("%d", &data);
		head1 = insert_first(head1, data);
	}
	
	/*
	printf("2번 노드의 개수 : ");
	scanf_s("%d", &num);
	for (int i = 0; i < num; i++) {
		printf("노드 #%d 데이터 : ", i + 1);
		scanf_s("%d", &data);
		head2 = insert_first(head2, data);
	}
	*/
	



	//노드 분리하기
	split(&head2, &head3, head1);
	printf("C 리스트 : ");
	print_list(head1);
	printf("A 리스트 : ");
	print_list(head2);
	printf("B 리스트 : ");
	print_list(head3);
	

	free(head1);
}
