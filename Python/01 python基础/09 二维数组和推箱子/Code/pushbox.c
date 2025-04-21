#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>

#define SPACE  0	//�յ�
#define WALL   1	//ǽ
#define DEST   2	//Ŀ�ĵ�
#define BOX    3	//����
#define PLAYER 4	//���
//��ǰ���ڹؿ�
int level = 0;
//���������ӵ�ͼ
int initMap[3][10][10] =
{
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,0},
		{0,0,0,1,2,1,0,0,0,0},
		{0,0,0,1,3,1,1,1,1,0},
		{0,1,1,1,0,0,3,2,1,0},
		{0,1,2,3,4,3,1,1,1,0},
		{0,1,1,1,1,0,1,0,0,0},
		{0,0,0,0,1,2,1,0,0,0},
		{0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	},
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,1,1,0,0},
		{0,1,2,0,1,1,0,0,1,0},
		{1,0,0,0,3,0,0,0,0,1},
		{1,0,0,3,4,3,0,0,2,1},
		{0,1,2,0,3,0,0,0,1,0},
		{0,0,1,0,0,0,0,1,0,0},
		{0,0,0,1,2,0,1,0,0,0},
		{0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	},
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,1,1,0},
		{0,1,2,0,0,0,0,2,1,0},
		{0,1,0,0,0,0,0,0,1,0},
		{0,1,0,3,0,3,0,0,1,0},
		{0,1,0,0,4,0,0,0,1,0},
		{0,1,0,3,0,3,0,0,1,0},
		{0,1,2,0,0,0,0,2,1,0},
		{0,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0}
	}
};

int map[3][10][10];

//��initMap��ֵ��map
void init()
{
	for (int l = 0; l < 3; l++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int k = 0; k < 10; k++)
			{
				map[l][i][k] = initMap[l][i][k];
			}
		}
	}
}

//���Ƶ�ͼ
void drawMap()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			/*
			if (map[level][i][k] == 0)
			{
				printf("  ");
			}
			else if(map[level][i][k] ==1)
			{
				//printf("%d ", map[level][i][k]);
				printf("ǽ");
			}
			else if(map[level][i][k] == 2)
			{
				printf("��");
			}*/
			switch (map[level][i][k])
			{
			case SPACE:
				printf("  ");
				break;
			case WALL:
				printf("�� ");
				break;
			case DEST:
				printf("��");
				break;
			case BOX:
				printf("��");
				break;
			case PLAYER:
				printf("��");
				break;
			case DEST + BOX:				//������Ŀ�ĵ���
				printf("��");
				break;
			case DEST + PLAYER:				//�����Ŀ�ĵ���
				printf("��");
				break;
			}
		}
		printf("\n");
	}
}
//�ж�ͨ����ǰ�ؿ�
bool jude()
{
	for (int  i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (map[level][i][k] == BOX)
			{
				return false;
			}
		}
	}
	return true;
}
int main()
{
	//��ʼ������
	init();
	//�����ͼ
	drawMap();

	//������
	//��ȡ���̰�����getchar()  scanf()  ->��������֮����Ҫ���س����ܼ���
	//��һ������֮����Ҫ���س��ĺ�����_getch();  ��Ҫͷ�ļ�conio.h,ע�⣺��ͷ�ļ�����C���Ա�׼ͷ�ļ�
	//72 80 75 77 ��  ��  �� ��  _getch()��һ����������
	while (true)
	{
		int r = 0, c = 0;	//������ڵ��±�
		for (int i = 0; i < 10; i++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (map[level][i][k] == PLAYER)
				{
					r = i;
					c = k;
				}
			}
		}


		char userkey = _getch();
		//printf("%d %c\n", userkey, userkey);
		switch (userkey)
		{
		case 72:
		case 'W':
		case 'w':
			//��ҵ�ǰ���ǿյ�
			if (map[level][r - 1][c] == SPACE || map[level][r-1][c] == DEST)
			{
				map[level][r - 1][c] += PLAYER;
				map[level][r][c] -= PLAYER;
			}
			//��ҵ�ǰ��������
			else if (map[level][r - 1][c] == BOX || map[level][r-1][c] ==BOX+DEST)	
			{
				//���ӵ�ǰ���ǿյأ�����Ŀ�ĵ�
				if (map[level][r - 2][c] == SPACE || map[level][r - 2][c] == DEST)
				{
					//1���ƶ�����
					map[level][r - 2][c] += BOX;
					map[level][r - 1][c] -= BOX;
					//2���ƶ����
					map[level][r - 1][c] += PLAYER;
					map[level][r][c] -= PLAYER;
				}
			}
			break;
		case 80:
		case 's':
		case 'S':
			//��ҵ�ǰ���ǿյ�
			if (map[level][r + 1][c] == SPACE || map[level][r + 1][c] == DEST)
			{
				map[level][r + 1][c] += PLAYER;
				map[level][r][c] -= PLAYER;
			}
			//��ҵ�ǰ��������
			else if (map[level][r + 1][c] == BOX || map[level][r + 1][c] == BOX + DEST)
			{
				//���ӵ�ǰ���ǿյأ�����Ŀ�ĵ�
				if (map[level][r + 2][c] == SPACE || map[level][r + 2][c] == DEST)
				{
					//1���ƶ�����
					map[level][r + 2][c] += BOX;
					map[level][r + 1][c] -= BOX;
					//2���ƶ����
					map[level][r + 1][c] += PLAYER;
					map[level][r][c] -= PLAYER;
				}
			}
			break;
		case 75:
		case 'a':
		case 'A':
			//��ҵ�ǰ���ǿյ�
			if (map[level][r][c - 1] == SPACE || map[level][r][c - 1] == DEST)
			{
				map[level][r][c - 1] += PLAYER;
				map[level][r][c] -= PLAYER;
			}
			//��ҵ�ǰ��������
			else if (map[level][r][c - 1] == BOX || map[level][r][c - 1] == BOX + DEST)
			{
				//���ӵ�ǰ���ǿյأ�����Ŀ�ĵ�
				if (map[level][r][c - 2] == SPACE || map[level][r][c - 2] == DEST)
				{
					//1���ƶ�����
					map[level][r][c - 2] += BOX;
					map[level][r][c - 1] -= BOX;
					//2���ƶ����
					map[level][r][c - 1] += PLAYER;
					map[level][r][c] -= PLAYER;
				}
			}
			break;
		case 77:
		case 'd':
		case 'D':
			//��ҵ�ǰ���ǿյ�
			if (map[level][r][c + 1] == SPACE || map[level][r][c + 1] == DEST)
			{
				map[level][r][c + 1] += PLAYER;
				map[level][r][c] -= PLAYER;
			}
			//��ҵ�ǰ��������
			else if (map[level][r][c + 1] == BOX || map[level][r][c + 1] == BOX + DEST)
			{
				//���ӵ�ǰ���ǿյأ�����Ŀ�ĵ�
				if (map[level][r][c + 2] == SPACE || map[level][r][c + 2] == DEST)
				{
					//1���ƶ�����
					map[level][r][c + 2] += BOX;
					map[level][r][c + 1] -= BOX;
					//2���ƶ����
					map[level][r][c + 1] += PLAYER;
					map[level][r][c] -= PLAYER;
				}
			}
			break;
		}
		system("cls");
		drawMap();
		if (jude())
		{
			if (level > 2)
			{
				level = -1;
				init();
			}
			level++;
			printf("��ϲ�㣬������\n");
		}
	}


	return 0;
}