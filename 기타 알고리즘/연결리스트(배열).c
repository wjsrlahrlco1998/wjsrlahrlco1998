#include <stdio.h>
#include<stdlib.h>

#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
	element array[MAX_LIST_SIZE];
	int size;
} ArrayListType;

//오류 처리 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//리스트 초기화 함수
void init(ArrayListType* L) {
	L->size = 0;
}

//리스트 공백 검사 함수
int is_empty(ArrayListType* L) {
	return L->size == 0;
}

//리스트 포화 검사 함수
int is_full(ArrayListType* L) {
	return L->size == MAX_LIST_SIZE;
}

//리스트 요소 추출 함수
element get_entry(ArrayListType* L, int pos) {
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];
}

//리스트 출력 함수
void print_list(ArrayListType* L) {
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n");
}

//리스트 삽입 함수(리스트 끝에 삽입)
void insert_last(ArrayListType* L, element item) {
	if (L->size >= MAX_LIST_SIZE) {
		error("리스트 오버플로우");
	}
	L->array[L->size++] = item;
}

//리스트 삽입 함수(삽입 위치 지정)
void insert(ArrayListType* L, int pos, element item) {
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size++;
	}
}

//리스트 삭제 함수(삭제 위치 지정)
element delete(ArrayListType* L, int pos) {
	element item;

	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	item = L->array[pos];
	for (int i = pos; i < (L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;
	return item;
}

//메인함수
int main() {
	ArrayListType list;

	init(&list);
	insert(&list, 0, 10); print_list(&list);
	insert(&list, 0, 20); print_list(&list);
	insert(&list, 0, 30); print_list(&list);
	insert_last(&list, 40); print_list(&list);
	delete(&list, 0); print_list(&list);
	return 0;
}
