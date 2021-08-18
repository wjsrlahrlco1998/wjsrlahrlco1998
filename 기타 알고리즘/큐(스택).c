#include <stdio.h>
#include <stdlib.h>
//스택의 크기 정의
#define MAX_STACK_SIZE 100
//스택의 반환 자료형 정의
typedef int element;
//#스택 정의
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} STACK;
//스택초기화 함수
void init(STACK* s) {
	s->top = -1;
}
//에러 알림
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
//공백 검출 함수
int is_empty(STACK* s) {
	return (s->top == -1);
}
//포화 검출 함수
int is_full(STACK* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
//스택에 입력하는 함수
void push(STACK* s, element item) {
	if (is_full(s)) {
		error("스택 포화 에러");
	}
	s->data[++(s->top)] = item;
}
//스택 삭제 함수
element pop(STACK* s) {
	if (is_empty(s)) {
		error("스택 공백 에러");
	}
	return s->data[(s->top)--];
}
//큐 삭제 함수 구현
element dequeue(STACK* s1, STACK* s2) {
	if (is_empty(s2)) {
		while (!is_empty(s1)) {
			push(s2, pop(s1));
		}
	}
	return pop(s2);
}

//메인 함수
int main() {
	STACK s_in, s_out; // s_in은 입력을 받는 스택, s_out은 출력하는 스택
	//두 스택 초기화
	init(&s_in);
	init(&s_out);
	//s_in에 값을 push
	push(&s_in, 4);
	push(&s_in, 2);
	push(&s_in, 3);
	printf("큐한 값 4 2 3\n");
	//s_out의 출력 값
	printf("1번째 dequeue : %d\n", dequeue(&s_in, &s_out));
	printf("2번째 dequeue : %d\n", dequeue(&s_in, &s_out));
	printf("3번째 dequeue : %d\n", dequeue(&s_in, &s_out));
}
