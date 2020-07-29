#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  
#define OVERFLOW -2
#define UNDERFLOW -3

#define MAXSTRLEN 255
typedef int Status;
typedef int ElemType;

#define MAX_ARRAY_DIM	8

typedef struct{
	ElemType	*base;	//数组元素基址，由InitArray分配
	int dim;			
	int *bounds;		//数组维界基址，由InitArray分配，就是每一维最多有多少
	int *constants;		//数组影响函数常量基址，由InitArray分配
}Array;

Status InitArray(Array *A, int dim,...);
Status DestroyArray(Array *A);
Status Locate(Array A, va_list ap, int *off);
Status Value_ary(Array A,ElemType *e,...);

int main(){
	Array test;
	InitArray(&test,3,2,3,4);
	printf("%d\n",test.constants[3]);
	return 0;
}

Status InitArray(Array *A, int dim,...){
	int elemtotal,i;
	va_list ap;
	
	//维度不合法，返回ERROR
	if(dim<1||dim>MAX_ARRAY_DIM)	return ERROR;
	
	//维度合法，
	A->dim = dim;									//设置数组维度
	A->bounds = (int *)malloc(dim*sizeof(int));		//设置A->bounds
	if(!A->bounds)	exit(OVERFLOW);
	elemtotal = 1;
	va_start(ap,dim);								//应该是将dim后边的参数用ap存起来
	for(i=0;i<dim;i++){
		A->bounds[i] = va_arg(ap,int);
		if(A->bounds[i]<0)	return UNDERFLOW;
		elemtotal *= A->bounds[i];					//ary[2][4][6]，则elemtotal=2*4*6;
	}
	va_end(ap);
	
	//设置A->base
	A->base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if(!A->base)	exit(OVERFLOW);
	//设置A->constants
	A->constants = (int *)malloc(dim * sizeof(int));
	if(!A->constants)	exit(OVERFLOW);
	A->constants[dim-1] = 1;
	for(i=dim-2;i>=0;--i)
		A->constants[i] = A->bounds[i+1] * A->constants[i+1];
	return OK;
}

Status DestroyArray(Array *A){
	if(!A->base)	return ERROR;
	free(A->base);	A->base = NULL;
	if(!A->bounds)	return ERROR;
	free(A->bounds);	A->bounds = NULL;
	if(!A->constants)	return ERROR;
	free(A->constants);	A->constants = NULL;
	return OK;
}

Status Locate(Array A, va_list ap, int *off){
	int i,ind;
	*off = 0;
	for(i=0;i<A.dim;++i){
		ind = va_arg(ap,int);
		if(ind<0||ind>=A.bounds[i])	return OVERFLOW;
		off+=A.constants[i] * ind;
	}
	return OK;
}

Status Value_ary(Array A,ElemType *e,...){
	int *off=0;
	va_list ap;
	int result;
	va_start(ap,*e);
	if((result = Locate(A,ap,off))<=0)	return result;
	*e = *(A.base + *off);
	return OK;
}

Status Assign(Array *A,ElemType e,...){
	int *off=0;
	va_list ap;
	int result;
	va_start(ap,e);
	if((result=Locate(*A,ap,off))<=0)	return result;
	*(A->base+*off) = e;
	return OK;
}

