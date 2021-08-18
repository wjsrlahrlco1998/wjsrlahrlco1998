#include <stdio.h>
#include <stdlib.h>

//data의 자료형 정의
typedef int element;
//이중연결 노드 구조체 정의
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

//초기화 함수
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

//오른쪽 삽입 함수
void dinsert(DListNode* before, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

//노드 삭제 함수
void ddelete(DListNode* head, DListNode* removed) {
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink - removed->llink;
	free(removed);
}

//노드 출력 함수
void print_dlist(DListNode* phead) {
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

//데이터 역순 출력 함수
void vprint_dlist(DListNode* phead) {
	DListNode* p = phead;
	printf("데이터를 역순으로 출력: ");
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("%d ", p->data);
	}
}

//데이터 탐색 함수
DListNode* search(DListNode* L, element data) {
	DListNode* p = L;
	if (L == NULL) return NULL;
	for (p = L->rlink; p != L; p = p->rlink) {
		if (p->data == data) return p;
	}
	return NULL;
}

//메인함수
int main() {
	DListNode* phead = (DListNode*)malloc(sizeof(DListNode));
	init(phead);

	int num = 0;
	element data = 0;
	printf("데이터의 개수를 입력하시오 : ");
	scanf_s("%d", &num);
	printf("\n");

	for (int i = 0; i < num; i++) {
		printf("노드 #%d의 데이터를 입력하시오 : ", i + 1);
		scanf_s("%d", &data);
		dinsert(phead, data);
	}
	printf("\n");

	print_dlist(phead);
	
	printf("탐색하고 싶은 데이터를 입력하시오 : ");
	scanf_s("%d", &data);
	phead = search(phead, data);
	if (phead != NULL) {
		printf("데이터 %d는 존재합니다.\n", phead->data);
	}
	else {
		printf("데이터 %d는 존재하지 않습니다.\n", data);
	}
}
