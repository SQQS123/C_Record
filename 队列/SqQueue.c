#include <stdio.h>
#include <stdlib.h>
 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  
#define OVERFLOW -2
#define STACK_INIT_SIZE 100	
#define STACKINCREMENT 10	

#define MAXSIZE		1000
#define MAXQSIZE		100

typedef int Status;
typedef int QElemType;

//循环队列——顺序存储结构
typedef struct{
	QElemType	*base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue *Q);
int QueueLength(SqQueue Q);
Status EnQueue(SqQueue *Q,QElemType e);
Status DeQueue(SqQueue *Q, QElemType *e);

int main(){
	SqQueue test;
	InitQueue(&test);
}

Status InitQueue(SqQueue *Q){
	//构造一个空队列
	Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if(!Q->base)	exit(OVERFLOW);
	Q->front = Q->rear = 0;
	return OK;
}

int QueueLength(SqQueue Q){
	return (Q.rear - Q.front+MAXQSIZE)%MAXQSIZE;
}

Status EnQueue(SqQueue *Q,QElemType e){
	if((Q->rear+1) % MAXQSIZE ==Q->front)	return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear+1) % MAXQSIZE;
	return OK;
}

Status DeQueue(SqQueue *Q,QElemType *e){
	if(Q->front == Q->rear)	return ERROR;
	e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

