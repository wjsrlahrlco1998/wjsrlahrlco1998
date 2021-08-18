#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6
#define MAX_STACK_SIZE 100
//미로설계(전역변수)
char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1', '1', '1', '1', '1', '1'},
	{'e', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '1'},
	{'1', '0', '1', '0', '1', '1'},
	{'1', '0', '1', '0', '0', 'x'},
	{'1', '1', '1', '1', '1', '1'},
};
//위치를 나타내는 구조체
typedef struct {
	int row;
	int cal;
} element;
//스택의 구조체
typedef struct {
	int top;
	element Stack[MAX_STACK_SIZE];
} Stack;
// 스택 상태 함수
int is_empty(Stack* s)
{
	if (s->top == -1)
		return 1;
	else
		return 0;
}
int is_full(Stack* s)
{
	if (s->top == MAX_STACK_SIZE - 1)
		return 1;
	else
		return 0;
}
// 스택 연산 함수
void init(Stack* s) {
	s->top = -1;
}
void push(Stack* s, element item)
{
	if (is_full(s))
	{
		fprintf(stderr, "스택 공백");
	}
	else {
		s->top++;
		s->Stack[s->top].row = item.row;
		s->Stack[s->top].cal = item.cal;
	}
}
element pop(Stack* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백");
	}
	else
	{
		element tmp;
		tmp.row = s->Stack[s->top].row;
		tmp.cal = s->Stack[s->top].cal;
		s->top--;
		return tmp;
	}
}
//미로 출력 함수
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int row = 0; row < MAZE_SIZE; row++) {
		for (int cal = 0; cal < MAZE_SIZE; cal++) {
			printf("%c", maze[row][cal]);
		}
		printf("\n");
	}
}
//미로 이동판별 함수
void push_loc(Stack* s, int row, int cal) {
	if (row < 0 || cal < 0) return;
	if (maze[row][cal] != '1' && maze[row][cal] != '.')
	{
		element tmp;
		tmp.row = row;
		tmp.cal = cal;
		push(s, tmp);
	}
}
//main 함수
int main() {
	//인덱스 변수 설정 및 초기화
	int i = 0;
	//가로, 세로 변수 설정
	int row, cal;
	//스택생성 및 초기화
	Stack s;
	init(&s);
	//미로초기위치 설정(1,0)
	element here = { 1, 0 };
	//미로경로 저장 배열 생성
	element road[MAX_STACK_SIZE];
	//미로이동
	while (maze[here.row][here.cal] != 'x') {
		row = here.row;
		cal = here.cal;
		maze[row][cal] = '.'; //지나온 경로 표시
		road[i].row = row; // 지나간 경로 저장
		road[i].cal = cal; // ''
		maze_print(maze); //미로상태 출력
		push_loc(&s, row - 1, cal);
		push_loc(&s, row + 1, cal);
		push_loc(&s, row, cal - 1);
		push_loc(&s, row, cal + 1);

		if (is_empty(&s)) {
			printf("실패\n");
			return;
		}
		else
		{
			here = pop(&s); // 이동이 성공하면 현재위치에 저장
		}
		i++;
	}
	printf("\n 성공 \n");
	
	for (int q = 0; q < i; q++) {
		printf("경로: %d %d \n", road[q].row, road[q].cal);
	}
}
