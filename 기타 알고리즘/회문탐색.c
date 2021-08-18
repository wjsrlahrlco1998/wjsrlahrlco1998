#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//보안성 경고문구 방지
#define _CRT_SECURE_NO_WARNING
//스택의 크기
#define MAX_STACK_SIZE 100
//배열의 크기
#define MAX_SIZE 20
//스택 정의
typedef struct {
	int top;
	int stack[MAX_STACK_SIZE];
} Stack;
//스택검사함수
int is_empty(Stack* s) {
	if (s->top == -1) {
		return 1;
	}
	else return 0;
}
int is_full(Stack* s) {
	if (s->top == MAX_STACK_SIZE - 1) {
		return 1;
	}
	else return 0;
}
//스택 연산 함수
void push(Stack* s, char item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화");
	}
	else
	{
		s->top++;
		s->stack[s->top] = item;
	}
}
char pop(Stack* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백");
		exit(1);
	}
	else {
		char tmp;
		tmp = s->stack[s->top];
		s->top--;
		return tmp;
	}
}
//스택의 top이 가리키는 값 확인함수
char peek(Stack* s) {
	return s->stack[s->top];
}
//스택초기화 함수
void init(Stack* s) {
	s->top = -1;
}

//메인함수
int main() {
	//인덱스 변수 선언 및 초기화
	int i = 0;
	//스택 생성 및 초기화
	Stack a;
	init(&a);
	//문자열 입력 받을 배열 생성
	char s[MAX_SIZE];
	//문자열 입력 받기
	printf("문자열을 입력하시오: ");
	scanf_s("%s", s, sizeof(s));
	//스택에 push
	while (s[i] != (char)NULL) {
		if ('a' <= s[i] && s[i] <= 'z') { //영어의 소문자 외에는 무시
			push(&a, s[i]);
		}
		else if ('A' <= s[i] && s[i] <= 'Z') { //대문자를 소문자로 바꾸기
			push(&a, s[i] - ('A' - 'a'));
		}
		i++;
	}
	//비교
	i = 0;
	while (s[i] != (char)NULL) {
		if ('a' <= s[i] && s[i] <= 'z') {
			char tmp = pop(&a);
			printf("스캔된 스택의 내용 : %c \n 비교할 문자의 내용 : %c \n", tmp, s[i]);
			if (tmp != s[i]) {
				printf("회문이 아닙니다\n");
				exit(1);
			} 
		}
		else if ('A' <= s[i] && s[i] <= 'Z') {
			char tmp = pop(&a);
			printf("스캔된 스택의 내용 : %c \n 비교할 문자의 내용 : %c \n", tmp, s[i]);
			if (tmp != s[i] - ('A' - 'a')) {
				printf("회문이 아닙니다\n");
				exit(1);
			}
		}
		i++;
	}
	printf("회문입니다\n");
	return 0;
}
