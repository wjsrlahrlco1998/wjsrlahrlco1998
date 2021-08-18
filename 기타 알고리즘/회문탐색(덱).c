#include <stdio.h>
#include <stdlib.h>
//덱의 사이즈 정의
#define MAX_QUEUE_SIZE 100
//덱의 반환 자료형 정의
typedef char element;
//덱 정의
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;
//오류 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
//초기화 함수
void init(DequeType* q) {
	q->front = q->rear = 0;
}
//공백상태 검출 함수
int is_empty(DequeType* q) {
	return (q->front == q->rear);
}
//포화상태 검출 함수
int is_full(DequeType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
//후 삽입함수
void add_rear(DequeType* q, element item) {
	if (is_full(q)) {
		error("큐가 포화상태 입니다");
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
//전 삽입함수
void add_front(DequeType* q, element item) {
	if (is_full(q)) {
		error("큐가 포화상태 입니다");
	}
	q->data[q->front] = item;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
//전 삭제함수
element delete_front(DequeType* q) {
	if (is_empty(q)) {
		error("큐가 공백상태입니다");
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
//후 삭제함수
element delete_rear(DequeType* q) {
	int prev = q->rear;
	if (is_empty(q)) {
		error("큐가 공백상태입니다");
	}
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

//메인함수
int main() {
	//인덱스 변수 선언
	int i = 0;
	//덱 선언
	DequeType q;
	//덱 초기화
	init(&q);
	//문자열을 입력받을 배열 선언
	char s[MAX_QUEUE_SIZE];
	//문자열 입력 받기
	printf("문자열을 입력하세요 : ");
	scanf_s("%s", &s, sizeof(s));
	//덱에 넣기
	while (s[i] != (char)NULL) {
		if ('a' <= s[i] && s[i] <= 'z') { //영어 소문자 외에는 무시
			add_rear(&q, s[i]);
		}
		else if ('A' <= s[i] && s[i] <= 'Z') { //대문자를 소문자로 바꾸기
			add_rear(&q, s[i] - ('A' - 'a'));
		}
		i++;
	}
	//회문 검사
	while (!is_empty(&q)) {
		char s1, s2;
		if (q.front + 1 != q.rear) {
			s1 = delete_rear(&q);
			s2 = delete_front(&q);
			if (s1 != s2) {
				printf("회문이아닙니다\n");
				exit(1);
			}
		}
		else {
			printf("회문입니다\n");
			exit(1);
		}
	}
	printf("회문입니다\n");
}
