#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  
#define OVERFLOW -2

#define MAXSTRLEN 255
typedef int Status;
typedef unsigned char SString[MAXSTRLEN + 1];	//0��Ԫ��Ŵ���

Status Concat(SString *T, SString S1, SString S2);
Status SubString(SString *Sub, SString S, int pos, int len);

int main(){
	SString res,S1,S2,Sub;
	S1[0] = 2;
	S1[1] = 'a';
	S1[2] = 'b';
	S2[0] = 3;
	S2[1] = 'a';
	S2[2] = 'b';
	S2[3] = 'c';
	Concat(&res,S1,S2);
	SubString(&Sub,res,2,4);
	printf("%c\n",Sub[5]);
	return 0;
}

//ƴ�������ַ���
Status Concat(SString *T, SString S1, SString S2){
	int i,j;
	//S1��S2�ĳ�����ӷ�Ϊ���������һ�ֳ��Ȳ�����MAXSTRLEN����һ�������
	if(S1[0] + S2[0] <= MAXSTRLEN){
		//ֱ��ƴ��
		//����S1
		for(i=1;i<=S1[0];i++){
			(*T)[i] = S1[i];
		}
		//��ƴ��S2
		for(i=S1[0]+1,j=1;i<=S1[0]+S2[0];i++,j++){
			(*T)[i] = S2[j];
		}
		(*T)[0] = S1[0]+S2[0];
	}
	//�������ǳ�����Χ�Ĵ���������Χ���԰��յ�һ����S1�ĳ��ȷ�Ϊ�������
	//1.S1���ȱ�MAXSTRLENС�����Ǽ��Ϻ���Ļ����MAXSTRLEN
	else if(S1[0] < MAXSTRLEN){
		for(i=1;i<=S1[0];i++){
			(*T)[i] = S1[i];
		}
		for(i=S1[0]+1,j=1;i<=MAXSTRLEN;i++,j++){
			(*T)[i] = S2[j];
		}
	}
	//2.S1����=MAXSTRLEN
	else{
		for(i=1;i<=MAXSTRLEN;i++){
			(*T)[i] = S1[i];
		}
	}
	return 0;
}

//�Ӵ�
Status SubString(SString *Sub, SString S, int pos, int len){
	int i,j;
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0]-pos+1)	return ERROR;
	for(i=1,j=pos; i<=len;i++,j++){
		(*Sub)[i] = S[j];
	}
	(*Sub)[0] = len;
	return OK;
}