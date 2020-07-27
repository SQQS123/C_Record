#include <stdio.h>
#include <stdlib.h>
 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  
#define OVERFLOW -2
#define LIST_INIT_SIZE 100		//˳����ʼ����ռ䣬�û�ָ��
#define LISTINCREMENT 10		//˳���洢�ռ�����������û�ָ��

#define MAXSIZE		1000		//��̬���Ե��������󳤶�

typedef int Status;		//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬��
typedef int ElemType;   //˳���洢Ԫ�����ͣ� ���ǵ�����ֲ�ԣ� ���ı�洢���ͣ� ֻ���޸���һ�����ȽϷ���

//���Ա�ľ�̬������洢�ṹ
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

//���뼯��A�ͼ���B��space=(A-B)U(B-A)
void difference(SLinkList space,int *S){

}

int main(){
	SLinkList test;
	InitSpace_SL(test);
	return 0;
}