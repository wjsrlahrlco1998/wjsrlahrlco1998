#include <stdio.h>
#include <stdlib.h>

//다항식 리스트 정의
typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode* link;
} ListNode;

//연결리스트 헤더
typedef struct ListType {
	int size;
	ListNode* head;
	ListNode* tail;
} ListType;

//오류 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//리스트 헤더 생성 함수
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

void insert_last(ListType* plist, int coef, int expon) {
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) error("메모리 할당 에러");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

//리스트 더하기 함수
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3) {
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;

	int sum;

	while (a && b) {
		if (a->expon == b->expon) {
			sum = a->coef + b->coef;
			if (sum != 0) insert_last(plist3, sum, a->expon);
			a = a->link;
			b = b->link;
		}
		else if (a->expon > b->expon) {
			insert_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else {
			insert_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}

	for (; a != NULL; a = a->link)
		insert_last(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		insert_last(plist3, b->coef, b->expon);
}

//다항식 출력 함수
void poly_print(ListType* plist)
{
	ListNode* p = plist->head;

	printf("polynomial = ");
	for (; p; p = p->link) {
		printf("%d^%d + ", p->coef, p->expon);
	}
	printf("\n");
}

//메인함수
int main() {
	ListType* list1;
	ListType* list2;
	ListType* list3;

	list1 = create();
	list2 = create();
	list3 = create();

	//1번 다항식 생성
	insert_last(list1, 3, 6);
	insert_last(list1, 7, 3);
	insert_last(list1, -2, 2);
	insert_last(list1, -9, 0);

	//2번 다항식 생성
	insert_last(list2, -2, 6);
	insert_last(list2, -4, 4);
	insert_last(list2, 6, 2);
	insert_last(list2, 6, 1);
	insert_last(list2, 1, 0);

	poly_print(list1);
	poly_print(list2);

	//1번 + 2번 다항식 = 3번 다항식
	poly_add(list1, list2, list3);
	poly_print(list3);

	free(list1);
	free(list2);
	free(list3);
}
