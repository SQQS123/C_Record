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
typedef int SElemType;

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack *S);
Status DestroyStack(SqStack *S);
Status ClearStack(SqStack *S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
Status GetTop(SqStack S,SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
Status StackTraverse(SqStack S, Status (*visit)());

void conversion();
void LineEdit();

int main(){
	SElemType e=5;
	SElemType *r;
	SqStack *S;			//如果将S设置为静态变量，就可以传入函数之后再初始化
	r = (SElemType*)malloc(sizeof(SElemType));	//指针需要初始化
	//S = (SqStack *)malloc(sizeof(SqStack));

	InitStack(S);		
	//conversion();
	return 0;
}

Status InitStack(SqStack *S){
	//S = (SqStack *)malloc(sizeof(SqStack));
	S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S->base)	exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType *e){
	if(S.top == S.base)	return ERROR;
	*e = *(S.top-1);
	return OK;
}

Status Push(SqStack *S, SElemType e){
	if(S->top - S->base >= S->stacksize){
		S->base = (SElemType *)realloc(S->base,(S->stacksize + STACKINCREMENT) *sizeof(SElemType));
		if(!S->base)	exit(OVERFLOW);
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	return OK;
}

Status Pop(SqStack *S, SElemType *e){
	if(S->top== S->base)	return ERROR;
	*e = * --S->top;
	return OK;
}

Status StackEmpty(SqStack S){
	if (S.base == S.top)	return TRUE;
	return FALSE;
}

Status ClearStack(SqStack *S){
	SElemType *e;
	e = (SElemType *)malloc(sizeof(SElemType));
	if(S->top > S->base){
		while(S->top != S->base)
			Pop(S, e);
	}
	if(S->top == S->base) return OK;
	return ERROR;
}

Status DestoryStack(SqStack *S){
	if(S->base){
		S->base = NULL;
		S->top = NULL;
		S->stacksize = 0;
		return OK;
	}
	return ERROR;
}

//进制转换
void conversion(){
	SqStack *S;
	SElemType *e;
	int N;
	S = (SqStack *)malloc(sizeof(SqStack));
	e = (SElemType *)malloc(sizeof(SElemType));
	InitStack(S);
	scanf("%d",&N);
	while(N){
		Push(S,N%8);
		N/=8;
	}
	while(!StackEmpty(*S)){
		Pop(S,e);
		printf("%d",*e);
	}
	printf("\n");
}

void LineEdit(){
	SqStack S;
	char c;
	InitStack(&S);
}