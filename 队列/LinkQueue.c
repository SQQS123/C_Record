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

typedef int Status;
typedef int QElemType;

//单链队列
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue *Q);
Status DestroyQueue(LinkQueue *Q);
Status EnQueue(LinkQueue *Q,QElemType e);
Status DeQueue(LinkQueue *Q, QElemType *e);

int main(){
	QElemType *e;
	LinkQueue test;
	e = (QElemType*)malloc(sizeof(QElemType));
	InitQueue(&test);
	EnQueue(&test,5);
	EnQueue(&test,6);
	DeQueue(&test,e);
	printf("%d\n",test.front->next->data);

	return 0;
}

Status InitQueue(LinkQueue *Q){
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front)	exit(OVERFLOW);
	Q->front->next = NULL;
	return 0;
}

Status DestroyQueue(LinkQueue *Q){
	while(Q->front){
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}

//入队有问题
Status EnQueue(LinkQueue *Q,QElemType e){
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)	exit(OVERFLOW);
	p->data = e;	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e){
	QueuePtr p;
	if(Q->front == Q->rear)	return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p)	Q->rear = Q->front;
	free(p);
	return OK;
}