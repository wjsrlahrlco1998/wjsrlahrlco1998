#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100
typedef int element;

typedef struct {
	element item[MAX_LIST_SIZE];
	int size;
} ArrayListType;

//초기화 함수
void init(ArrayListType* L) {
	L->size = 0;
}

//공백 검사 함수
int is_empty(ArrayListType* L) {
	return L->size == 0;
}

//포화 검사 함수
int is_full(ArrayListType* L) {
	return L->size == MAX_LIST_SIZE;
}

//요소 추가 함수(정렬)
void insert_sort(ArrayListType* L, element item) {
	int i = 0;
	if (is_full(L)) return;
	for (i = 0; i < L->size; i++) {
		if (L->item[i] > item) {
			for (int j = L->size; j > i; j--) {
				L->item[j] = L->item[j - 1];
			}
			break;
		}
	}
	L->item[i] = item;
	L->size++;
}

//정렬된 리스트에서 요소 제거
void delete_item(ArrayListType* L, element item) {
	int i;
	if (is_empty(L)) return;
	for (i = 0; i < L->size; i++) {
		if (L->item[i] == item) {
			for (int j = i; j < L->size; j++) {
				L->item[j] = L->item[j + 1];
			}
		}
	}
	L->size--;
}

//리스트 모든 요소 제거
void clear(ArrayListType* L) {
	L->size = 0;
}

//리스트 길이 반환 함수
int get_length(ArrayListType* L) {
	return L->size;
}

//리스트 내 item 검사 함수
int is_in_list(ArrayListType* L, element item) {
	for (int i = 0; i < L->size; i++) {
		if (L->item[i] == item) return L->item[i] == item;
	}
	return -1;
}

//리스트 출력 함수
void display(ArrayListType* L) {
	for (int i = 0; i < L->size; i++)
		printf("%d번 요소 : %d \n", i + 1, L->item[i]);
}

//메인함수
int main() {
	ArrayListType L;
	init(&L);
	insert_sort(&L, 5);
	insert_sort(&L, 3);
	insert_sort(&L, 9);
	insert_sort(&L, 1);

	delete_item(&L, 3);

	display(&L);
}
