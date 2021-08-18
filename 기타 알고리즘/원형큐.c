#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
typedef int element; //큐가 반환하는 값의 자료형
/*큐의 구조체 정의*/
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;
//오류함수 정의
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
//초기화 함수 정의
void init(QueueType* q) {
	q->front = q->rear = 0;
}
//공백상태 검출 함수 정의
int is_empty(QueueType* q) {
	return (q->front == q->rear);
}
//포화상태 검출 함수 정의
int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
//삼입 함수
void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		error("포화상태입니다");
	} 
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
//삭제 함수
element dequeue(QueueType* q) {
	if (is_empty(q)) {
		error("큐가 공백상태입니다");
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
//rear 값만 반환하는 함수
element peek(QueueType* q) {
	if (is_empty(q)) {
		error("큐가 공백상태입니다");
	}
	return q->data[q->rear];
}
//큐의 요소의 갯수를 반환
int get_count(QueueType* q) {
	int count = q->rear - q->front;
	if (count >= 0) {
		return count;
	}
	else {
		return -count;
	}
}
//큐를 이용한 피보나치 수열
int fibonacci(QueueType* q, int n) {
	int sum = 0;
	if (n == 1) {
		return 0;
	}
	else if (n == 2) {
		return 1;
	}
	else if (n >= 3) {
			int tmp = dequeue(q);
			sum = tmp + peek(q);
			enqueue(q, sum);
		
		return sum;
	}
	return -1;
}

//메인함수
int main() {
	//큐 선언
	QueueType q;
	//큐 초기화
	init(&q);
	//초기값 0과 1을 할당
	enqueue(&q, 0);
	enqueue(&q, 1);
	//피보나치 반복값 입력
	int num;
	printf("출력할 피보나치의 항의 수를 입력하시오 : ");
	scanf_s("%d", &num);
	for (int i = 0; i < num; i++) {
		printf("%d항 : %d\n", i + 1, fibonacci(&q, i + 1));
	}
	
}
