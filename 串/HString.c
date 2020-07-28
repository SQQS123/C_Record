#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  
#define OVERFLOW -2

typedef int Status;

//串的对分配存储表示
typedef struct{
	char *ch;		//非空串则按串长分配存储区，否则ch为NULL
	int length;
}HString;

Status StrInit(HString *T);
Status StrAssign(HString *T,char *chars);
int StrLength(HString S);
int StrCompare(HString S,HString T);
Status ClearString(HString *S);
Status Concat(HString *T, HString S1, HString S2);
//HString SubString(HString S, int pos, int len);
Status SubString(HString *Sub, HString S, int pos, int len);

int main(){
	int res;
	HString S,T;
	char *ch = "Princess Connect";
	char *th = "FGO";
	//S.ch = (char *)malloc(sizeof(char));		//我们的字符串需要初始化
	StrInit(&S);
	StrInit(&T);
	
	StrAssign(&S,ch);
	StrAssign(&T,th);
	res = StrCompare(S,T);
	printf("%d",res);
	return 0;
}

Status StrInit(HString *T){
	T->ch = NULL;
	T->length = 0;
	return OK;
}

Status StrAssign(HString *T,char *chars){
	int i,j;
	char *c;
	//c = (char*)malloc(sizeof(char));
	
	//这里有问题,如果字符串没有初始化时下面会报错
	if(T->ch)		free(T->ch);
	
	for(i=0,c=chars;*c;++i,++c);
	if(!i){ T->ch=NULL; T->length = 0; }
	else{
		if(!(T->ch = (char *)malloc(i * sizeof(char))))	exit(OVERFLOW);
		for(j=0;j<i;j++){
			T->ch[j] = chars[j];
		}
		T->ch[j] = '\0';
		T->length = i;
	}
	
	return OK;
}

int StrLength(HString S){
	return S.length;
}

int StrCompare(HString S, HString T){
	int i;
	for(i=0;i<S.length&&i<T.length;++i){
		if(S.ch[i]!=T.ch[i])		return S.ch[i]-T.ch[i];
	}
	return S.length-T.length;
}

Status ClearString(HString *S){
	if(S->ch)	{free(S->ch);	S->ch=NULL;}
	S->length = 0;
	return OK;
}

Status Concat(HString *T, HString S1, HString S2){
	int i,j;
	if(T->ch)	free(T->ch);
	if(!(T->ch=(char*)malloc((S1.length + S2.length)*sizeof(char))))
		exit(OVERFLOW);
	for(i=0;i<S1.length;i++)
		(*T).ch[i] = S1.ch[i];
	(*T).length = S1.length + S2.length;
	for(i=S1.length,j=0;i<(*T).length;i++,j++)
		(*T).ch[i] = S2.ch[j];
	return OK;
}

Status SubString(HString *Sub, HString S, int pos, int len){
	int i,j;
	if(pos<1 || pos>S.length || len<0 || len>S.length-pos+1)
		return ERROR;
	if(Sub->ch)		free(Sub->ch);
	if(!len){ Sub->ch=NULL;	Sub->length=0; }
	else{
		Sub->ch = (char *)malloc(len * sizeof(char));
		for(i=0,j=pos-1;i<len;i++,j++){
			Sub->ch[i] = S.ch[j];
		}
		Sub->length = len;
	}
	return OK;
}