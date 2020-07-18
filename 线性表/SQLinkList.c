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


typedef int Status;		//Status是函数的类型，其值是函数结果状态码
typedef int ElemType;   //顺序表存储元素类型， 考虑到可移植性， 若改变存储类型， 只需修改这一处，比较方便

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;


//纯C里没有传引用，我们都用指针来实现
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

//在单链线性表L中第i个位置之前插入元素e，课本p29下面
Status ListInsert_L(LinkList L, int i, ElemType e){
	int j = 0;
	LinkList p,s;
	p = (LinkList)malloc(sizeof(LNode));
	s = (LinkList)malloc(sizeof(LNode));
	p = L; 
	while (p&&j < i - 1){ p = p->next; ++j; }
	if (!p || j>i - 1)	return ERROR;
	//这里p是第i-1个节点，然后我们新建一个节点插入到这个节点之后，就是一个新的i节点了
	//插入很简单，先让这个新节点指向原来的第i个元素，然后再让第i-1个元素指向s就行了
	s->data = e; s->next = p->next;	p->next = s;
	return OK;
}

void MergeList(LinkList *La,LinkList *Lb,LinkList *Lc){
	
	LinkList pa,pb,pc;
	pa = (LinkList)malloc(sizeof(LNode));
	pb = (LinkList)malloc(sizeof(LNode));
	pc = (LinkList)malloc(sizeof(LNode));
	*Lc = (LinkList)malloc(sizeof(LNode));
	printf("到这儿\n");
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
	//以下三行属于手工生成链表
	//node_one.data=1;node_one.next=&node_two;
	//node_two.data=2;node_two.next=&node_three;
	//node_three.data=3;node_three.next=0;

	//使用函数创建链表,成功
	printf("创建第一个链表:\n");
	CreateList_L(&test,5);

	printf("创建第二个链表:\n");
	CreateList_L(&test_two,6);

	//尝试合并,有问题
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