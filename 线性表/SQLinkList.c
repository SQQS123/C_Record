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


typedef int Status;		//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬��
typedef int ElemType;   //˳���洢Ԫ�����ͣ� ���ǵ�����ֲ�ԣ� ���ı�洢���ͣ� ֻ���޸���һ�����ȽϷ���

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;


//��C��û�д����ã����Ƕ���ָ����ʵ��
void CreateList_L(LinkList *L, int n){
	int i;
	LinkList p;
	//p=(LinkList)malloc(sizeof(LNode));
	*L=(LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	for(i=n;i>0;--i){
		p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		p->next = (*L)->next;(*L)->next=p;
	}
}

Status GetELem_L(LinkList L, int i, ElemType *e){
	LinkList p;
	int j = 1;
	p = L->next;
	while(p && j<i){
		p = p->next;++j;
	}
	if(!p||j>i)	return ERROR;
	*e = p->data;
	return OK;
}

//�ڵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e���α�p29����
Status ListInsert_L(LinkList L, int i, ElemType e){
	int j = 0;
	LinkList p,s;
	p = (LinkList)malloc(sizeof(LNode));
	s = (LinkList)malloc(sizeof(LNode));
	p = L; 
	while (p&&j < i - 1){ p = p->next; ++j; }
	if (!p || j>i - 1)	return ERROR;
	//����p�ǵ�i-1���ڵ㣬Ȼ�������½�һ���ڵ���뵽����ڵ�֮�󣬾���һ���µ�i�ڵ���
	//����ܼ򵥣���������½ڵ�ָ��ԭ���ĵ�i��Ԫ�أ�Ȼ�����õ�i-1��Ԫ��ָ��s������
	s->data = e; s->next = p->next;	p->next = s;
	return OK;
}

void MergeList(LinkList *La,LinkList *Lb,LinkList *Lc){
	
	LinkList pa,pb,pc;
	pa = (LinkList)malloc(sizeof(LNode));
	pb = (LinkList)malloc(sizeof(LNode));
	pc = (LinkList)malloc(sizeof(LNode));
	*Lc = (LinkList)malloc(sizeof(LNode));
	printf("�����\n");
	pa = (*La)->next; pb = (*Lb)->next;
	(*Lc) = pc = (*La);
	while(pa && pb){
		if(pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else{
			pc->next=pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa?pa:pb;
	free(*Lb);
}



int main(){
	ElemType data;
	LinkList test,p,test_two,res_list;
	p = (LinkList)malloc(sizeof(LNode));
	//LNode node_one,node_two,node_three;
	//test = (LinkList)malloc(sizeof(LinkList));
	//�������������ֹ���������
	//node_one.data=1;node_one.next=&node_two;
	//node_two.data=2;node_two.next=&node_three;
	//node_three.data=3;node_three.next=0;

	//ʹ�ú�����������,�ɹ�
	printf("������һ������:\n");
	CreateList_L(&test,5);

	printf("�����ڶ�������:\n");
	CreateList_L(&test_two,6);

	//���Ժϲ�,������
	MergeList(&test,&test_two,&res_list);

	p = test;
	while(p->next){
		p = p->next;
		printf("%d\n",p->data);
	}

	//test->next=&node_one;
	ListInsert_L(test,2,11);
	GetELem_L(test,1,&data);
	printf("%d\n",data);
	return 0;
}