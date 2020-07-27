#include <stdio.h>
#include <stdlib.h>
 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  
#define OVERFLOW -2
#define LIST_INIT_SIZE 100		//顺序表初始分配空间，用户指配
#define LISTINCREMENT 10		//顺序表存储空间分配增量，用户指配

#define MAXSIZE		1000		//静态线性单链表的最大长度

typedef int Status;		//Status是函数的类型，其值是函数结果状态码
typedef int ElemType;   //顺序表存储元素类型， 考虑到可移植性， 若改变存储类型， 只需修改这一处，比较方便

//线性表的静态单链表存储结构
typedef struct{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];

int LocateElem_SL(SLinkList S, ElemType e){
	int i = S[0].cur;
	while(i && S[i].data!=e)	i=S[i].cur;
	return i;
}

void InitSpace_SL(SLinkList space){
	int i;
	for(i=0;i<MAXSIZE-1;++i)
		space[i].cur = i+1;
	space[MAXSIZE-1].cur=0;
}

int Malloc_SL(SLinkList space){
	int i;
	i = space[0].cur;
	if(space[0].cur)
		space[0].cur = space[i].cur;
	return i;
}

void Free_SL(SLinkList space,int k){
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

//输入集合A和集合B，space=(A-B)U(B-A)
void difference(SLinkList space,int *S){

}

int main(){
	SLinkList test;
	InitSpace_SL(test);
	return 0;
}