#include <stdio.h>
#include <stdlib.h>

#define TRUE 1

typedef void element;
typedef struct QueueNode {
	element(*data)();
	int order;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front, * rear;
} LinkedQueueType;

//큐 초기화 함수
void init(LinkedQueueType* q) {
	q->front = q->rear = 0;
}

//공백 상태 검출 함수
int is_empty(LinkedQueueType* q) {
	return (q->front == NULL);
}

//포화 상태 검출 함수
int is_full(LinkedQueueType* q) {
	return 0;
}

//삽입 함수 (큐의 마지막에 함수 포인터를 추가)
void enqueue(LinkedQueueType* q, element(*data)(), int order) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	QueueNode* p;
	QueueNode* t = q->front;
	
	int count = 0;

	temp->data = data;
	temp->order = order;
	temp->link = NULL;

	if (is_empty(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else {
		if (temp->order >= q->rear->order) { //우선순위가 낮거나 같을 경우
			q->rear->link = temp;
			q->rear = temp;
		}
		else {
			for (p = q->front; p != NULL; p = p->link) {
				for (int i = 0; i < count - 1; i++)
					t = t->link;
				if (temp->order < p->order) { //우선순위가 더 높을 경우
					if (p == q->front) { //큐의 첫번째요소와 바꾸는 경우
						temp->link = p;
						q->front = temp;
					}
					else { //큐의 첫번째 요소가 아닌 요소랑 바꾸는 경우
						temp->link = p;
						t->link = temp;
					}
				}
				count++;
			}
		}
	}

}

//삭제 함수 (큐로부터 첫번째 포인터를 읽음)
int dequeue(LinkedQueueType* q) {
	QueueNode* temp = q->front;
	element(*data)();
	if (is_empty(q)) {
		fprintf(stderr, "스택 공백 \n");
		return NULL;
	}
	else {
		data = temp->data;
		q->front = q->front->link;
		if (q->front == NULL)
			q->rear = NULL;
		free(temp);
		return data;
	}
}

//출력 함수
void print_queue(LinkedQueueType* q) {
	QueueNode* p;
	for (p = q->front; p != NULL; p = p->link)
		printf("%d->", (int)p->data);
	printf("NULL\n");
}

//DeviceA 동작 함수
void deviceA() {
	printf("DeviceA의 동작\n"); //장치A에게 필요한 일을 처리
}
//DeviceB 동작 함수
void deviceB() {
	printf("DeviceB의 동작\n"); //장치B에게 필요한 일을 처리
}
//DeviceC 동작 함수
void deviceC() {
	printf("DeviceC의 동작\n"); //장치C에게 필요한 일을 처리
}
//DeviceD 동작 함수
void deviceD() {
	printf("DeviceD의 동작\n"); //장치D에게 필요한 일을 처리
}
//disable
void disable() {
	printf("인터럽트 금지 시작-----\n");
}
//enable
void enable() {
	printf("인터럽트 금지 해제-----\n");
}

//메인함수
int main() {
	LinkedQueueType queue;
	init(&queue);
	void(*fp)();

	enqueue(&queue, deviceA, 2); print_queue(&queue);
	enqueue(&queue, deviceB, 1); print_queue(&queue);
	enqueue(&queue, deviceC, 4); print_queue(&queue);
	enqueue(&queue, deviceD, 3); print_queue(&queue);

	while (TRUE) {
		while (!is_empty(&queue)) { //함수 포인터들의 큐가 비어 있다면 기다린다
			disable();
			fp = dequeue(&queue); //큐에 있는 첫번째 함수를 호출한다
			fp();
			enable();
		}
	}

}
