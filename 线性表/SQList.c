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

typedef struct 
{
	ElemType *elem;		//存储空间地址
	int length;			//当前长度
	int listsize;		//当前分配的存储容量（以sizeof(ElemType)为单位）
}SqList;

void Init_Sq(SqList *L);
Status Insert_Sq(SqList *L, int i, ElemType e);
Status Destroy_Sq(SqList *L);
Status Delete_List(SqList *L, int i);
void Travse_Sq(SqList *L);
ElemType Next_Elem(SqList *L, int cur_elem);
ElemType Prior_Elem(SqList *L, int cur_elem);
ElemType GetElem(SqList *L, int i);					
Status GetElem_SQ(SqList *L, int i, int *e);		//按照书上的写法
int LocateElem_Sq(SqList *L, ElemType e);
Status compare(ElemType e1, ElemType e2);
int ListLength(SqList *L);
void union_Sq(SqList *La, SqList *Lb);
void Merge_Sq(SqList *La, SqList *Lb, SqList *Lc);
int LocateElem(SqList *L, ElemType e, Status(*compare)(ElemType,ElemType));		//使用回调函数的话……


void main()
{	
 
	/*SqList L;
	int i;
	Init_Sq(&L);
	if(	Insert_Sq(&L, 1, 4))
	{
		printf("The element is %d\n", GetElem(&L, 1));
	}
	if(	Insert_Sq(&L, 2, 5))
	{
		printf("The element is %d\n", GetElem(&L, 2));
	}
	if(	Insert_Sq(&L, 3, 6))
	{
		printf("The element is %d\n", GetElem(&L, 3));
	}
	if(	Insert_Sq(&L, 4, 8))
	{
		printf("The element is %d\n", GetElem(&L, 4));
	}
	if(	Insert_Sq(&L, 5, 18))
	{
		printf("The element is %d\n", GetElem(&L, 5));
	}
	Travse_Sq(&L);
	printf("Current number:  ");
	scanf("%d", &i);
	printf("The prior of No.%d is %d\n", i, Prior_Elem(&L, i));
	
	if(Delete_List(&L,1))
	{
		printf("After delete:\n");
		Travse_Sq(&L);
	}
	*/
	int e,i;
	SqList La;
	SqList Lb;
	SqList Lc;
 
	Init_Sq(&La);
	Init_Sq(&Lb);
 
	if(	Insert_Sq(&La, 1, 4))
	{
		GetElem_SQ(&La,1,&e);
		printf("The element in La is %d\n", e);
		//或者
		printf("The element in La is %d\n", GetElem(&La, 1));
	}
	if(	Insert_Sq(&La, 2, 5))
	{
		printf("The element in La is %d\n", GetElem(&La, 2));
	}
	if(	Insert_Sq(&La, 3, 6))
	{
		printf("The element in La is %d\n", GetElem(&La, 3));
	}
	if(	Insert_Sq(&La, 4, 8))
	{
		printf("The element in La is %d\n", GetElem(&La, 4));
	}
	if(	Insert_Sq(&La, 5, 18))
	{
		printf("The element in La is %d\n", GetElem(&La, 5));
	}
 
	printf("\n");
	if(	Insert_Sq(&Lb, 1, 4))
	{
		printf("The element in Lb is %d\n", GetElem(&Lb, 1));
	}
	if(	Insert_Sq(&Lb, 2, 15))
	{
		printf("The element in Lb is %d\n", GetElem(&Lb, 2));
	}
	printf("\n");
	
	//我们尝试使用回调函数
	i = LocateElem(&La,8,&compare);
	printf("使用回调函数得到的结果:%d\n",i);

 
	//union_Sq(&La, &Lb);   
 
//	printf("After unite La and Lb:\n");
//	Travse_Sq(&La);

	Merge_Sq(&La, &Lb, &Lc);
	printf("After merge La and Lb:\n");
	Travse_Sq(&Lc);

	//销毁三个线性表
	Destroy_Sq(&La);
	Destroy_Sq(&Lb);
	Destroy_Sq(&Lc);
}
 
void Init_Sq(SqList *L)
{
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(L->elem == NULL)
	{
		printf("Memory allocation is error!");
		exit(1);   //0表示正常退出，非零表示异常退出
	}
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
}
 
//在第i个位置插入元素e
Status Insert_Sq(SqList *L, int i, ElemType e)
{
	ElemType *newbase;   //指向新增顺序表后的起始位置
	ElemType *p;
	ElemType *q;
 
	if(i < 1 || i > L->length +  1)
	{
		printf("The location that inserted is illegal!\n");
		return ERROR;
	}
 
	if(!(L->length < L->listsize))   //如果顺序表满了就扩充
		newbase = (ElemType *)realloc(&L->elem, (L->length + LISTINCREMENT) * sizeof(ElemType));
 
	p = &L->elem[i-1];
 
	for(q = &L->elem[L->length - 1]; p <= q; q--)
	{
		*(q + 1) = *q;
	}
 
	*p = e;
	L->length ++;
	return TRUE;
}
 
//销毁顺序表
Status Destroy_Sq(SqList *L)
{
	if(L->length < 1)
		return FALSE;
	free(L->elem);
	L->elem = NULL;
	return TRUE;
}
 
//删除顺序表中指定元素
Status Delete_List(SqList *L, int i)
{
	ElemType *p;
	int j;
 
	if(i < 1 && i > L->length)
	{
		printf("The site that store element is not exist!\n");
		return FALSE;
	}
 
	p = &L->elem[i - 1];   //初始使p指向将要删除的位置
 
	for(j = i - 1; j < L->length - 1; j++)
	{
		*p = *(p+1);
		p++;
	}
	L->length --;
	return TRUE;
}
 
//遍历顺序表
void Travse_Sq(SqList *L)
{
	int i;
	if(L->length == 0)
	{
		printf("The sequence list is empty!\n");
	}
	else
		for(i = 0; i < L->length; i++)
			printf("The No.%d is %d.\n", i, L->elem[i]);
}
 
//返回第i个数据
ElemType GetElem(SqList *L, int i)
{
	if(i < 1 || i > L->length)
		return ERROR;
	return L->elem[i - 1];
}
//如果按书上的定义
Status GetElem_SQ(SqList *L, int i, int *e)
{
	if(i < 1|| i > L->length)
		return ERROR;
	*e = L->elem[i-1];
	return OK;
}
 
//返回第cur_elem个元素的直接前驱
ElemType Prior_Elem(SqList *L, int cur_elem)
{
	if(cur_elem == 1)
		return ERROR;
	else
		return L->elem[cur_elem - 2];
}
 
//返回第cur_elem个元素的直接后继
ElemType Next_Elem(SqList *L, int cur_elem)
{
	if(cur_elem == (L->length - 1))
		return FALSE;
	else
		return L->elem[cur_elem];
}
 
//记录线性表的长度
int ListLength(SqList *L)
{
	if(L->length == 0)
	{
		printf("The sequence list is empty!\n");
		return 0;
	}
	else 
		return L->length;
 
}
 

void union_Sq(SqList *La, SqList *Lb)
{
	//将所有在线性表Lb中但不在La中的数据元素插入到La中
	int La_len, Lb_len;
	int i;
	int Lb_cur_elem;   //记录Lb中取出的元素
 
	La_len = ListLength(La);
	Lb_len = ListLength(Lb);
 
	//注意，取的是第i个元素，是从人们熟悉的1开始计数
	//GetElem()函数中会做减1处理(计算机的计数方式)
	for(i = 1; i <= Lb_len; i++)
	{
		Lb_cur_elem = GetElem(Lb, i);
		if(!LocateElem_Sq(La, Lb_cur_elem))
			Insert_Sq(La, ++La_len, Lb_cur_elem);
	}
}
 
Status compare(ElemType e1, ElemType e2)
{
	if(e1 == e2)
		return TRUE;
	else 
		return FALSE;
}
 
//在顺序线性表L中查找第一个值与e满足compare()的元素的位序
//若找到，则返回其在L中的位序，否则返回0
int LocateElem_Sq(SqList *L, ElemType e)
{
	int i;
	ElemType *p;
	i = 1;   //i的初值为第一个元素的位序
	p = L->elem;   //p的初值为第1个元素的存储位置
	while(i <= L->length && (e != *p++))
		i++;
	if(i <= L->length)
		return i;
	else 
		return 0;
}

//上面的没用到compare()函数，如果我们使用回调函数
int LocateElem(SqList *L, ElemType e, Status(*compare)(ElemType,ElemType))
{
	int i;
	ElemType *p;
	i=1;
	p = L->elem;
	while(i <= L->length && !(compare)(e,*p++)){
		i++;
	}
	if(i<=L->length)
		return i;
	else
		return 0;
}


 
//已知顺序线性表La，和Lb的元素按值非减排列
//归并La和Lb得到新的顺序线性表Lc，Lc的元素也是按值非减排列
void Merge_Sq(SqList *La, SqList *Lb, SqList *Lc)
{
	ElemType *pa;
	ElemType *pb;
	ElemType *pc;
	ElemType *pa_last;
	ElemType *pb_last;
 
	//给Lc的elem元素分配空间
	Lc->elem = (ElemType *)malloc((La->length + Lb->length) * sizeof(ElemType));
	if(!Lc->elem)
	{
		printf("Error!\n");
		exit(1);
	}
 
	pa = La->elem;   //pa指向La的第一个元素
	pb = Lb->elem;	 //pb指向Lb的第一个元素		
	pc = Lc->elem;   //pc指向Lc的首地址
	Lc->length = La->length + Lb->length;
	
	pa_last = &La->elem[La->length - 1];   //指向La的最后一个元素（La中的最大的元素）
	pb_last = &Lb->elem[Lb->length - 1];   //指向Lb的最后一个元素（Lb中的最大的元素）
 
	while(pa <= pa_last && pb <= pb_last)   //实现归并
	{
		if(*pa <= *pb)
		{
			*pc++ = *pa++;
		}
		else
			*pc++ = *pb++;
	}
	while(pa <= pa_last)
		*pc++ = *pa++;
	while(pb <= pb_last)
		*pc++ = *pb++;
}	 

//上面的MergeList感觉有问题
