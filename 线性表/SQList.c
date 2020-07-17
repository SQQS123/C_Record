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

typedef struct 
{
	ElemType *elem;		//�洢�ռ��ַ
	int length;			//��ǰ����
	int listsize;		//��ǰ����Ĵ洢��������sizeof(ElemType)Ϊ��λ��
}SqList;

void Init_Sq(SqList *L);
Status Insert_Sq(SqList *L, int i, ElemType e);
Status Destroy_Sq(SqList *L);
Status Delete_List(SqList *L, int i);
void Travse_Sq(SqList *L);
ElemType Next_Elem(SqList *L, int cur_elem);
ElemType Prior_Elem(SqList *L, int cur_elem);
ElemType GetElem(SqList *L, int i);					
Status GetElem_SQ(SqList *L, int i, int *e);		//�������ϵ�д��
int LocateElem_Sq(SqList *L, ElemType e);
Status compare(ElemType e1, ElemType e2);
int ListLength(SqList *L);
void union_Sq(SqList *La, SqList *Lb);
void Merge_Sq(SqList *La, SqList *Lb, SqList *Lc);
int LocateElem(SqList *L, ElemType e, Status(*compare)(ElemType,ElemType));		//ʹ�ûص������Ļ�����


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
		//����
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
	
	//���ǳ���ʹ�ûص�����
	i = LocateElem(&La,8,&compare);
	printf("ʹ�ûص������õ��Ľ��:%d\n",i);

 
	//union_Sq(&La, &Lb);   
 
//	printf("After unite La and Lb:\n");
//	Travse_Sq(&La);

	Merge_Sq(&La, &Lb, &Lc);
	printf("After merge La and Lb:\n");
	Travse_Sq(&Lc);

	//�����������Ա�
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
		exit(1);   //0��ʾ�����˳��������ʾ�쳣�˳�
	}
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
}
 
//�ڵ�i��λ�ò���Ԫ��e
Status Insert_Sq(SqList *L, int i, ElemType e)
{
	ElemType *newbase;   //ָ������˳�������ʼλ��
	ElemType *p;
	ElemType *q;
 
	if(i < 1 || i > L->length +  1)
	{
		printf("The location that inserted is illegal!\n");
		return ERROR;
	}
 
	if(!(L->length < L->listsize))   //���˳������˾�����
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
 
//����˳���
Status Destroy_Sq(SqList *L)
{
	if(L->length < 1)
		return FALSE;
	free(L->elem);
	L->elem = NULL;
	return TRUE;
}
 
//ɾ��˳�����ָ��Ԫ��
Status Delete_List(SqList *L, int i)
{
	ElemType *p;
	int j;
 
	if(i < 1 && i > L->length)
	{
		printf("The site that store element is not exist!\n");
		return FALSE;
	}
 
	p = &L->elem[i - 1];   //��ʼʹpָ��Ҫɾ����λ��
 
	for(j = i - 1; j < L->length - 1; j++)
	{
		*p = *(p+1);
		p++;
	}
	L->length --;
	return TRUE;
}
 
//����˳���
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
 
//���ص�i������
ElemType GetElem(SqList *L, int i)
{
	if(i < 1 || i > L->length)
		return ERROR;
	return L->elem[i - 1];
}
//��������ϵĶ���
Status GetElem_SQ(SqList *L, int i, int *e)
{
	if(i < 1|| i > L->length)
		return ERROR;
	*e = L->elem[i-1];
	return OK;
}
 
//���ص�cur_elem��Ԫ�ص�ֱ��ǰ��
ElemType Prior_Elem(SqList *L, int cur_elem)
{
	if(cur_elem == 1)
		return ERROR;
	else
		return L->elem[cur_elem - 2];
}
 
//���ص�cur_elem��Ԫ�ص�ֱ�Ӻ��
ElemType Next_Elem(SqList *L, int cur_elem)
{
	if(cur_elem == (L->length - 1))
		return FALSE;
	else
		return L->elem[cur_elem];
}
 
//��¼���Ա�ĳ���
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
	//�����������Ա�Lb�е�����La�е�����Ԫ�ز��뵽La��
	int La_len, Lb_len;
	int i;
	int Lb_cur_elem;   //��¼Lb��ȡ����Ԫ��
 
	La_len = ListLength(La);
	Lb_len = ListLength(Lb);
 
	//ע�⣬ȡ���ǵ�i��Ԫ�أ��Ǵ�������Ϥ��1��ʼ����
	//GetElem()�����л�����1����(������ļ�����ʽ)
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
 
//��˳�����Ա�L�в��ҵ�һ��ֵ��e����compare()��Ԫ�ص�λ��
//���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0
int LocateElem_Sq(SqList *L, ElemType e)
{
	int i;
	ElemType *p;
	i = 1;   //i�ĳ�ֵΪ��һ��Ԫ�ص�λ��
	p = L->elem;   //p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ��
	while(i <= L->length && (e != *p++))
		i++;
	if(i <= L->length)
		return i;
	else 
		return 0;
}

//�����û�õ�compare()�������������ʹ�ûص�����
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


 
//��֪˳�����Ա�La����Lb��Ԫ�ذ�ֵ�Ǽ�����
//�鲢La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ��Ҳ�ǰ�ֵ�Ǽ�����
void Merge_Sq(SqList *La, SqList *Lb, SqList *Lc)
{
	ElemType *pa;
	ElemType *pb;
	ElemType *pc;
	ElemType *pa_last;
	ElemType *pb_last;
 
	//��Lc��elemԪ�ط���ռ�
	Lc->elem = (ElemType *)malloc((La->length + Lb->length) * sizeof(ElemType));
	if(!Lc->elem)
	{
		printf("Error!\n");
		exit(1);
	}
 
	pa = La->elem;   //paָ��La�ĵ�һ��Ԫ��
	pb = Lb->elem;	 //pbָ��Lb�ĵ�һ��Ԫ��		
	pc = Lc->elem;   //pcָ��Lc���׵�ַ
	Lc->length = La->length + Lb->length;
	
	pa_last = &La->elem[La->length - 1];   //ָ��La�����һ��Ԫ�أ�La�е�����Ԫ�أ�
	pb_last = &Lb->elem[Lb->length - 1];   //ָ��Lb�����һ��Ԫ�أ�Lb�е�����Ԫ�أ�
 
	while(pa <= pa_last && pb <= pb_last)   //ʵ�ֹ鲢
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

//�����MergeList�о�������
