#include <stdio.h>
#include <stdlib.h>
//최대 우선순위 큐
#define MAX_ELEMENT 100
typedef int element;
typedef struct {
	element que[MAX_ELEMENT];
	int que_size;
} QueType;
//에러 출력함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//우선순위 큐 생성
QueType* create() {
	return (QueType*)malloc(sizeof(QueType));
}

//우선순위 큐 초기화
void init(QueType* q) {
	q->que_size = 0;
}

//우선순위 큐 비어있는지 검사
int is_empty(QueType* q) {
	if (q->que_size == 0) return 1;
	return 0;
}

//우선순위 큐가 가득 찼는지 검사
int is_full(QueType* q) {
	if (q->que_size == MAX_ELEMENT) return 1;
	return 0;
}

//우선순위 큐 삽입 연산
void insert(QueType* q, element item) {
	if (is_full(q)) {
		error("큐가 가득찼습니다");
	}
	q->que[q->que_size] = item;
	(q->que_size)++;
}

//우선순위 큐 삭제 연산
element delete(QueType* q) {
	if (is_empty(q)) {
		error("큐가 비었습니다");
	}
	element max_value;
	int index = 0;
	max_value = q->que[0];
	for (int i = 1; i < (q->que_size); i++) {
		if (max_value < q->que[i]) {
			max_value = q->que[i];
			index = i;
		}
	}
	for (int i = index; i < (q->que_size); i++) {
		q->que[i] = q->que[i + 1];
	}
	(q->que_size)--;
	return max_value;
}

//우선순위가 가장 높은 요소를 반환
element find(QueType* q) {
	if (is_empty(q)) {
		error("큐가 비었습니다");
	}
	element max_value;
	max_value = q->que[0];
	for (int i = 1; i < (q->que_size); i++) {
		if (max_value < q->que[i]) {
			max_value = q->que[i];
		}
	}
	return max_value;
}

int main() {
	QueType* q = create();
	init(q);
	insert(q, 3);
	insert(q, 4);
	insert(q, 5);

	printf("delete: %d\n", delete(q));
	printf("delete: %d\n", delete(q));
	printf("delete: %d\n", delete(q));

	free(q);
	return 0;
}
