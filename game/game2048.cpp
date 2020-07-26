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


void map_init(int **map);		//初始化地图，全为0；
void draw_map(int **map);		//在终端显示地图
void update(int **map);	//在随机空闲(值为零)的单元格生成2

//控制逻辑
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
		ch = getch();			//这个可以不用回车直接获取字符
		move_number(ch,map);
		system("cls");
		update(map);
		draw_map(map);
	}
	
	return 0;
}

//初始化地图，全部置0
void map_init(int **map){
	int row1,col1,row2,col2;
	//首先随机产生两个坐标
	srand(time(NULL));
	row1 = rand()%ROW;
	col1 = rand()%ROW;
	row2 = rand()%ROW;
	col2 = rand()%ROW;

	//给每一行分配内存
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

//绘制地图
void draw_map(int **map){
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			printf("%6d\t",map[i][j]);
		}
		printf("\n");
	}
	printf("\n您的得分为:%d\n",get_number);
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

	//flag为True表示全满状态
	if(flag){
		//如果行和列没有连续相同的数字，则判定失败
		//行
		for(int i=0;i<ROW;i++){
			for(int j=0;j<COL-1;j++){
				if(map[i][j] == map[i][j+1])
					break;
			}
			if((i==ROW-1)&&(j==COL-1))
				row_flag=TRUE;
		}
		//列
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
	//在空闲单元格随机生成2或者4
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
			printf("请输入w,a,s,d\n");

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
