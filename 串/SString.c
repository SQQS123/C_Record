#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  
#define OVERFLOW -2

#define MAXSTRLEN 255
typedef int Status;
typedef unsigned char SString[MAXSTRLEN + 1];	//0单元存放串长

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

//拼接两个字符串
Status Concat(SString *T, SString S1, SString S2){
	int i,j;
	//S1和S2的长度相加分为两种情况，一种长度不大于MAXSTRLEN，另一种则大于
	if(S1[0] + S2[0] <= MAXSTRLEN){
		//直接拼接
		//先是S1
		for(i=1;i<=S1[0];i++){
			(*T)[i] = S1[i];
		}
		//再拼接S2
		for(i=S1[0]+1,j=1;i<=S1[0]+S2[0];i++,j++){
			(*T)[i] = S2[j];
		}
		(*T)[0] = S1[0]+S2[0];
	}
	//接下来是超出范围的处理，超出范围可以按照第一个串S1的长度分为两种情况
	//1.S1长度比MAXSTRLEN小，但是加上后面的会大于MAXSTRLEN
	else if(S1[0] < MAXSTRLEN){
		for(i=1;i<=S1[0];i++){
			(*T)[i] = S1[i];
		}
		for(i=S1[0]+1,j=1;i<=MAXSTRLEN;i++,j++){
			(*T)[i] = S2[j];
		}
	}
	//2.S1长度=MAXSTRLEN
	else{
		for(i=1;i<=MAXSTRLEN;i++){
			(*T)[i] = S1[i];
		}
	}
	return 0;
}

//子串
Status SubString(SString *Sub, SString S, int pos, int len){
	int i,j;
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0]-pos+1)	return ERROR;
	for(i=1,j=pos; i<=len;i++,j++){
		(*Sub)[i] = S[j];
	}
	(*Sub)[0] = len;
	return OK;
}