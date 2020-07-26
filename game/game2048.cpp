#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define TRUE	1
#define FALSE	0

#define ROW		4
#define COL		4

static int get_number=0;


void map_init(int **map);		//��ʼ����ͼ��ȫΪ0��
void draw_map(int **map);		//���ն���ʾ��ͼ
void update(int **map);	//���������(ֵΪ��)�ĵ�Ԫ������2

//�����߼�
void move_number(char ch,int **map);
void Up(int **map);
void Down(int **map);
void Left(int **map);
void Right(int **map);

int main(){
	int **map;
	char ch = 0;
	map = (int **)malloc(ROW*COL*sizeof(int));
	
	map_init(map);
	draw_map(map);

	while(1){
		ch = getch();			//������Բ��ûس�ֱ�ӻ�ȡ�ַ�
		move_number(ch,map);
		system("cls");
		update(map);
		draw_map(map);
	}
	
	return 0;
}

//��ʼ����ͼ��ȫ����0
void map_init(int **map){
	int row1,col1,row2,col2;
	//�������������������
	srand(time(NULL));
	row1 = rand()%ROW;
	col1 = rand()%ROW;
	row2 = rand()%ROW;
	col2 = rand()%ROW;

	//��ÿһ�з����ڴ�
	for(int row = 0; row<ROW; row++)
		map[row] = (int *)malloc(COL*sizeof(int));
	
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			if((row1 == i&&col1 == j)||(row2 == i&&col2 == j)){
				map[i][j] = ((rand()%2)+1) *2;
			}
			else{
				map[i][j]=0;
			}
		}
	}
}

//���Ƶ�ͼ
void draw_map(int **map){
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			printf("%6d\t",map[i][j]);
		}
		printf("\n");
	}
	printf("\n���ĵ÷�Ϊ:%d\n",get_number);
}

void update(int **map){
	int row1,col1;
	int row_flag=FALSE,col_flag=FALSE;
	int flag = TRUE;
	for(int i=0; i< ROW;i++){
		for(int j=0;j<COL;j++){
			if(map[i][j]==0){
				flag = FALSE;
				break;
			}
		}//for col
	}//for row

	//flagΪTrue��ʾȫ��״̬
	if(flag){
		//����к���û��������ͬ�����֣����ж�ʧ��
		//��
		for(int i=0;i<ROW;i++){
			for(int j=0;j<COL-1;j++){
				if(map[i][j] == map[i][j+1])
					break;
			}
			if((i==ROW-1)&&(j==COL-1))
				row_flag=TRUE;
		}
		//��
		for(int k=0;k<ROW-1;k++){
			for(int l=0;l<COL;l++){
				if(map[k][l] == map[k+1][l])
					break;
			}
			if((k==ROW-2)&&(l==COL))
				col_flag=TRUE;
		}
		//printf("%d,%d\n",row_flag,col_flag);
		if(row_flag&&col_flag)
			printf("you lose\n");
		return;
	}
	//�ڿ��е�Ԫ���������2����4
	row1 = rand() % ROW;
	col1 = rand() % COL;
	if(map[row1][col1] !=0){
		update(map);
	}
	else{
		map[row1][col1] = ((rand()%2)+1) *2;
	}
}

void move_number(char ch,int **map){
	switch(ch){
		case 'w':
			Up(map);
			break;
		case 's':
			Down(map);
			break;
		case 'a':
			Left(map);
			break;
		case 'd':
			Right(map);
			break;
		case 'q':
			exit(0);
		default:
			printf("������w,a,s,d\n");

	}
}

void Up(int **map){
	for(int k=0; k<ROW-1;++k){
		for(int i=0; i<ROW-1;++i){
			for(int j=0;j<ROW;++j){
				if(map[i][j] == 0){
					map[i][j] = map[i+1][j];
					map[i+1][j] = 0;
				}
				else if(map[i][j] == map[i+1][j]){
					map[i][j] = map[i][j] + map[i+1][j];
					map[i+1][j] = 0;
					get_number+=map[i][j];
				}
			}
		}
	}
}

void Down(int **map){
	for(int k=0; k<ROW-1;++k){
		for(int i=ROW-1; i>0;i--){
			for(int j=0;j<ROW;++j){
				if(map[i][j] == 0){
					map[i][j] = map[i-1][j];
					map[i-1][j] = 0;
				}
				else if(map[i][j] == map[i-1][j]){
					map[i][j] = map[i][j] + map[i-1][j];
					map[i-1][j] = 0;
					get_number+=map[i][j];
				}
			}
		}
	}
}

void Left(int **map){
	for(int k=0; k<ROW-1;++k){
		for(int i=0; i<ROW;i++){
			for(int j=0;j<ROW-1;j++){
				if(map[i][j] == 0){
					map[i][j] = map[i][j+1];
					map[i][j+1] = 0;
				}
				else if(map[i][j] == map[i][j+1]){
					map[i][j] = map[i][j] + map[i][j+1];
					map[i][j+1] = 0;
					get_number+=map[i][j];
				}
			}
		}
	}
}

void Right(int **map){
	for(int k=0; k<ROW-1;++k){
		for(int i=0; i<ROW;i++){
			for(int j=ROW-1;j>0;j--){
				if(map[i][j] == 0){
					map[i][j] = map[i][j-1];
					map[i][j-1] = 0;
				}
				else if(map[i][j] == map[i][j-1]){
					map[i][j] = map[i][j] + map[i][j-1];
					map[i][j-1] = 0;
					get_number+=map[i][j];
				}
			}
		}
	}
}
