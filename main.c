#include <stdio.h>
#include <stdlib.h>


//宏定义

#define BROADWIDTH 15
#define WIDTH (BROADWIDTH + 1) 

#define BLACK_TURN 0
#define WHITE_TURN 1

#define NO_CHESS 0
#define BLACK_CHESS 1
#define WHITE_CHESS 2

#define NONE_WIN 0
#define BLACK_WIN 1
#define WHITE_WIN 2

#define CHECK_X 0
#define CHECK_Y 1
#define CHECK_DIAG_LEFT 2
#define CHECK_DIAG_RIGHT 3


//全局变量

//棋盘交点阵
int map[WIDTH][WIDTH] = {{0, 0}};

//记录执子方
int turn = BLACK_TURN;

//落子位置
int x = 0, y = 0;

//棋子类型
int chess_kind = BLACK_CHESS;


//函数声明

void Chess_Play(void);

void Chess_DrawMap(void);

int Chess_Move(void);

int Chess_CheckNum(int check_type);


int main()
{
	Chess_Play();

	return 0;
}


//进行一局五子棋游戏
//参数：无
//返回值：无
void Chess_Play(void)
{
	int res = NONE_WIN;

	Chess_DrawMap();

	while (1)
	{
		res = Chess_Move();

		if (res == BLACK_WIN)
		{
			printf("黑棋胜利！");
			break;
		}
		else if (res == WHITE_WIN)
		{
			printf("白棋胜利！");
			break;
		}
	}
}


//打印棋盘
//参数：无
//返回值：无
void Chess_DrawMap(void)
{
	int i, j;

	for (i = 0; i < WIDTH; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			if (i == 0 && j == 0)
				printf("   ");
			else if (i == 0)
				printf("%3d", j);
			else if (j == 0)
				printf("%3d", i);
			else if (map[i][j] == BLACK_CHESS)
				printf("%3c", 'O');
			else if (map[i][j] == WHITE_CHESS)
				printf("%3c", 'X');
			else if (map[i][j] == NO_CHESS)
				printf("%3c", '*');
		}

		printf("\n");
	}
}


//玩家落子，并返回此次的胜负
//参数：无
//返回值：NONE_WIN BLACK_WIN WHITE_WIN
int Chess_Move(void)
{
	printf("现在轮到玩家%d，请落子：", turn == BLACK_TURN ? 1 : 2);
	scanf("%d %d", &x, &y);

	while (map[x][y] != NO_CHESS)
	{
		printf("这个位置已经有棋子了，请重新输入：");
		scanf("%d %d", &x, &y);
	}

	while ((x < 0 || x >= WIDTH) || (y < 0 || y >= WIDTH))
	{
		printf("无效区域，请重新输入：");
		scanf("%d %d", &x, &y);
	}

	chess_kind = map[x][y] = turn == BLACK_TURN ? BLACK_CHESS : WHITE_CHESS;

	system("CLS"); //清屏
	Chess_DrawMap();

	turn = !turn; //更换执子方

	//判断胜负
	if (
		Chess_CheckNum(CHECK_X) >= 5 ||
		Chess_CheckNum(CHECK_Y) >= 5 ||
		Chess_CheckNum(CHECK_DIAG_LEFT) >= 5 ||
		Chess_CheckNum(CHECK_DIAG_RIGHT) >= 5
		)
	{
		return chess_kind == BLACK_CHESS ? BLACK_WIN : WHITE_WIN;
	}
	else
	{
		return NONE_WIN;
	}
}


//检查某个方向上的连子数
//参数：检查方向
//返回值：连子数
int Chess_CheckNum(int check_type)
{
	int temp_x = x, temp_y = y;
	int num = 0;

	while (temp_x >= 0 && temp_x < WIDTH && temp_y >= 0 && temp_y < WIDTH && map[temp_x][temp_y] == chess_kind)
	{
		num++;

		switch (check_type)
		{
		case CHECK_X: temp_x--; break;
		case CHECK_Y: temp_y--; break;
		case CHECK_DIAG_LEFT: temp_x--; temp_y--; break;
		case CHECK_DIAG_RIGHT: temp_x--; temp_y++;
		}
	}

	switch (check_type)
	{
	case CHECK_X: temp_x = x + 1; break;
	case CHECK_Y: temp_y = y + 1;; break;
	case CHECK_DIAG_LEFT: temp_x = x + 1; temp_y = y + 1; break;
	case CHECK_DIAG_RIGHT: temp_x = x + 1; temp_y = y - 1;
	}

	while (temp_x >= 0 && temp_x < WIDTH && temp_y >= 0 && temp_y < WIDTH && map[temp_x][temp_y] == chess_kind)
	{
		num++;

		switch (check_type)
		{
		case CHECK_X: temp_x++; break;
		case CHECK_Y: temp_y++; break;
		case CHECK_DIAG_LEFT: temp_x++; temp_y++; break;
		case CHECK_DIAG_RIGHT: temp_x++; temp_y--;
		}
	}

	return num;
}
