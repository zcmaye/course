#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define ROW 10
#define COL 10
void initMap(int map[ROW][COL]);
void loadImg(IMAGE img[]);
void drawMap(int map[ROW][COL], IMAGE img[]);
void mouseEvent(int map[ROW][COL]);
void openNull(int map[ROW][COL], int row, int col);
void judge(int map[ROW][COL], int row, int col);
void showMap(int map[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			printf("%2d ", map[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}
bool isOver = false;	//�㵽���ˣ���Ϸ�������
bool isWin = false;
int main()
{
	initgraph(COL*40, ROW*40,EW_SHOWCONSOLE);

	mciSendString("open ./images/start.mp3", NULL, 0, NULL);
	mciSendString("play ./images/start.mp3", NULL, 0, NULL);


	//�������������
	srand((unsigned)time(NULL));

	//ɨ����Ϸ������
	int map[ROW][COL] = { 0 };
	//ͨ�����������չ�ָ��û�
	IMAGE img[12];

	initMap(map);
	loadImg(img);

	showMap(map);
	while (true)
	{
		mouseEvent(map);
		drawMap(map, img);
		
		//if (isOver)
		//{
		//	int ret = MessageBox(GetHWnd(), "��㵽����,�Ƿ�����һ�ѣ�", "��ʾ", MB_OKCANCEL);
		//	if (ret == IDOK)
		//	{
		//		initMap(map);
		//		isOver = false;
		//	}
		//	else
		//	{
		//		exit(0);//�˳�����
		//	}
		//}
		//else if(isWin)
		//{
		//	int ret = MessageBox(GetHWnd(), "�������,�Ƿ�����һ�ѣ�", "��ʾ", MB_OKCANCEL);
		//	if (ret == IDOK)
		//	{
		//		initMap(map);
		//		isWin = false;
		//	}
		//	else
		//	{
		//		exit(0);//�˳�����
		//	}
		//}

		if (isOver || isWin)
		{
			char text[50] = { 0 };
			if (isOver)
				strcpy(text, "��㵽���ˣ��Ƿ�����һ�ѣ�");
			else
				strcpy(text, "�������,�Ƿ�����һ�ѣ�");

			int ret = MessageBox(GetHWnd(), text, "��ʾ", MB_OKCANCEL);
			if (ret == IDOK)
			{
				initMap(map);
				isWin = false;
				isOver = false;
			}
			else
			{
				exit(0);//�˳�����
			}
		}
	}
		
		

	getchar();
	return 0;
}

void initMap(int map[ROW][COL])
{
	//������Ԫ��ȫ����ʼ��Ϊ0
	memset(map, 0, ROW*COL*sizeof(map));
	//����������������� ����-1��ʾ ֻҪ10��
	for (int i = 0; i < 10; )
	{
		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			i++;			//ֻ�гɹ�������һ���ף�i�Ż�����
		}
	}

	//����Χ�ľŹ������ֶ���1�����Լ����� -1��
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			//�ҵ�ÿһ����
			if (map[i][k] == -1)
			{
				//��������Χ�ľŹ���
				for (int r = i - 1; r <= i + 1; r++)
				{
					for (int c = k - 1; c <= k + 1; c++)
					{
						if ((r >= 0 && r < ROW && c >= 0 && c < COL) && map[r][c] != -1)
						{
							map[r][c] ++;
						}
					}
				}

			}
		}
	}

	//���ܸ���
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			map[i][k] += 20;
		}
	}
}
void loadImg(IMAGE img[])
{
	//����ͼƬ
	for (int i = 0; i < 12; i++)
	{
		char imgName[50] = { 0 };
		sprintf(imgName, "./images/%d.jpg", i);
		loadimage(img + i, imgName, 40, 40);
	}
}
void drawMap(int map[ROW][COL], IMAGE img[])
{
	//��ͼƬ
	for (int i = 0; i < ROW; i++)			//��Ӧy
	{
		for (int k = 0; k < COL; k++)		//��Ӧx
		{
			if (map[i][k] >= 0 && map[i][k] <= 8)
			{
				putimage(k * 40, i * 40, &img[map[i][k]]);
			}
			else if (map[i][k] == -1)
			{
				putimage(k * 40, i * 40, img + 9);
			}
			else if (map[i][k] >= 19 && map[i][k] <= 28)
			{
				putimage(k * 40, i * 40, img + 10);
			}
			else if(map[i][k] > 28)
			{
				putimage(k * 40, i * 40, img + 11);
			}
		}
	}
}
void mouseEvent(int map[ROW][COL])
{
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		//���msg ������x��y����û���к��У��Լ���һ��
		int r = msg.y/40;
		int c = msg.x/40;
		//����������򿪶�Ӧ�ĸ���,������Ԫ��-20
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			mciSendString("close click",NULL,0,NULL);
			mciSendString("open ./images/click.wav alias click", NULL, 0, NULL);
			mciSendString("play click", NULL, 0, NULL);
			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] -= 20;
				if (map[r][c] == 0)
				{
					mciSendString("close search", NULL, 0, NULL);
					mciSendString("open ./images/search.wav alias search", NULL, 0, NULL);
					mciSendString("play search", NULL, 0, NULL);
				}
				openNull(map,r, c);
				judge(map, r, c);
				showMap(map);
			}		
		}
		//����Ҽ���Ǹ���
		else if (msg.uMsg == WM_RBUTTONDOWN)
		{
			mciSendString("close rightClick", NULL, 0, NULL);
			mciSendString("open ./images/rightClick.wav alias rightClick", NULL, 0, NULL);
			mciSendString("play rightClick", NULL, 0, NULL);
			if (map[r][c] >= 19 && map[r][c] <= 28)	//���û�д򿪣�Ҳû�б�ǣ��ͱ��һ��
			{
				map[r][c] += 20;
				showMap(map);
			}
			else if(map[r][c]>28)	//�Ѿ���ǹ��ˣ�ȡ�����
			{
				map[r][c] -= 20;
			}
		}
	}
}
void openNull(int map[ROW][COL],int row, int col)
{
	if (map[row][col] == 0)
	{
		for (int i = row-1; i <= row+1; i++)
		{
			for (int k = col-1; k <= col+1; k++)
			{
				//�����Χ�ĸ���û�б��򿪣��ʹ�
				if ((i>=0 &&i<ROW && k>=0 &&k<COL) &&map[i][k] > 19 && map[i][k]<=28)
				{
					map[i][k] -= 20;
					openNull(map, i, k);
				}
			}
		}
	}
}
void judge(int map[ROW][COL], int row, int col)
{
	//����㵽����
	if (map[row][col] == -1)
	{
		//�����е��׶���
		for (int i = 0; i < ROW; i++)
		{
			for (int k = 0; k < COL; k++)
			{
				//��û�д򿪣�����Ҳû�б����
				if (map[i][k] == 19)
				{
					map[i][k] -= 20;
				}
				//����˵���ҲҪ��
				else if (map[i][k] == 39)
				{
					map[i][k] -= 40;
				}
			}
		}
		isOver = true;
	}

	//��Ӧ�õ㿪�ĸ��Ӷ��㿪�ˣ���Ϸ��ʤ����
	int cnt = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			if (map[i][k] >= 0 && map[i][k] <= 8)
			{
				cnt++;
			}
		}
	}
	if (cnt == ROW * COL - 10)
	{
		isWin = true;
	}
	printf("cnt:%d\n", cnt);
}