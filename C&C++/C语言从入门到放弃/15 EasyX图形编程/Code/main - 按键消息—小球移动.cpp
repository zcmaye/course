#include<stdio.h>
//包含easyx头文件
#include<easyx.h>		//这个是只包含最新的API(函数)
//#include<graphics.h>	//这个头文件包含了<easyx.h> 还包含了已经不推荐使用了的函数

//定义消息结构体变量
ExMessage msg = { 0 };

void drawShape()
{
	//绘制一个点
	putpixel(50, 50, RED);

	//设置线条颜色
	setlinecolor(BLUE);
	//设置线条的样式
	setlinestyle(PS_SOLID, 3);
	//绘制一条线
	line(0, 0, getwidth(), getheight());

	//绘制一个正矩形
	rectangle(100, 0, 100 + 50, 0 + 50);			//无填充矩形

	//设置填充颜色
	setfillcolor(YELLOW);
	fillrectangle(100, 50, 100 + 50, 50 + 50);		//填充矩形
	solidrectangle(100, 100, 100 + 50, 100 + 50);	//无边框填充矩形

	//绘制一个圆角矩形
	roundrect(160, 0, 160 + 50, 0 + 50,10,10);
	fillroundrect(160, 50, 160 + 50, 50 + 50, 10, 10);
	solidroundrect(160, 100, 160 + 50, 100 + 50, 10, 10);

	//绘制一个圆形
	setfillcolor(GREEN);
	circle(50, 50, 50);
	fillcircle(50, 150, 50);
	solidcircle(50, 250, 50);

	//椭圆
	ellipse(200, 0, 200 + 50, 0 + 100);
	fillellipse(200, 200, 200 + 50, 200 + 100);
	solidellipse(200, 300, 200 + 50, 300 + 100);

	//绘制折线条
	POINT points[] = { {0,0},{20,20},{50,80},{10,60} };
	polyline(points, 4);

}
void drawText()
{
	printf("hello EasyX!");
	//设置文字大小
	settextstyle(48, 0, _T("微软雅黑"));
	//设置文字颜色
	settextcolor(BROWN);
	//设置背景模式
	setbkmode(TRANSPARENT);
	//绘制文字
	outtextxy(10, 10, "hello EasyX!");
	//error C2665: “outtextxy”: 2 个重载中没有一个可以转换所有参数类型
	//EasyX与字符串相关的函数，都有字符集问题  UNICODE  多字节字符集
	/*三种解决方法:
	* 1,在字符串的前面使用L进行转换				强制转换
	* 2,用带参宏(_T(),_TEXT())把字符串包裹起来		自适应转换			推荐使用这种
	* 3,菜单栏->项目->属性->高级->字符集->把UNICODE改为多字节字符集		大力推荐这一种
	* 
	*/

	outtextxy(0,200,"玩蛇老师");

	settextstyle(30, 0, _T("微软雅黑"));
	//现在有一个int类型的分数，需要输出到图形界面上面
	int score = 66;
	char str[50] = "";
	sprintf(str,"Score:%d", score);
	outtextxy(getwidth() - 100, 0, str);
}
void centerText()
{
	//来一个矩形
	int rx = 30;
	int ry = 380;
	int rw = 200;
	int rh = 60;
	setfillcolor(RGB(230, 231, 232));
	fillrectangle(rx, ry, rx + rw, ry + rh);

	//绘制文字
	settextcolor(RED);
	char str[] = "Center Text";
	int hSpace = (rw - textwidth(str)) / 2;
	int vSpace = (rh - textheight(str)) / 2;
	outtextxy(rx + hSpace, ry+vSpace, str);
}
//mx，my是否在指定的矩形区域
bool inArea(int mx, int my, int x, int y, int w, int h)
{
	if (mx > x && mx < x + w && my > y && my < y + h)
	{
		return true;
	}
	return false;
}

bool button(int x, int y, int w, int h, const char* text)
{
	if (inArea(msg.x, msg.y, x, y, w, h))
	{
		setfillcolor(RGB(93, 107, 153));
	}
	else
	{
		setfillcolor(RGB(230, 231, 232));
	}
	//绘制按钮
	fillroundrect(x, y, x + w, y + h, 5, 5);
	//绘制按钮文本
	int hSpace = (w - textwidth(text)) / 2;
	int vSpace = (h - textheight(text)) / 2;
	settextcolor(BLACK);
	outtextxy(x + hSpace, y + vSpace, text);

	//判断按钮是否被点击
	if (msg.message == WM_LBUTTONDOWN && inArea(msg.x,msg.y,x,y,w,h))
	{
		return true;
	}
	return false;
}

int main()
{
	//创建一个图形窗口 宽度*高度
	initgraph(640, 480,EX_SHOWCONSOLE | EX_DBLCLKS );
	//设置窗口的背景颜色
	setbkcolor(RGB(231, 114, 227));
	//用设置的背景颜色填充整个窗口
	cleardevice();
	//窗口的坐标体系：窗口左上角是坐标原点，x轴向右增大，y轴向下增大
	//设置背景模式
	setbkmode(TRANSPARENT);

	//drawShape();
	//drawText();
	//centerText();

	//定义小球的属性
	int x = 50;
	int y = 50;
	int r = 20;

	int speed = 3;	//速度
	int vx = 0;
	int vy = 0;


	int i = 0;
	while (true)
	{
		//获取消息
		if (peekmessage(&msg, EX_MOUSE | EX_KEY))
		{

		}
		//判断按键消息
		if (msg.message == WM_KEYDOWN)
		{
			printf("keydown\n");
			//具体判断是哪个键按下
			switch (msg.vkcode)
			{
			case VK_UP:
				vy = -1;
				break;
			case VK_DOWN:
				vy = 1;
				break;
			case VK_LEFT:
				vx = -1;
				break;
			case VK_RIGHT:
				vx = 1;
				break;
			case VK_SPACE:
				printf("space\n");
				break;
			case 'A':		//对于字母键，必须写大写的字符
				printf("AAA\n");
				break;
			}
		}
		else if (msg.message == WM_KEYUP)
		{
			switch (msg.vkcode)
			{
			case VK_UP:
				vy = 0;
				break;
			case VK_DOWN:
				vy = 0;
				break;
			case VK_LEFT:
				vx = 0;
				break;
			case VK_RIGHT:
				vx = 0;
				break;
			}
		}

		//双缓冲绘图:所有的绘图代码必须放在begin 和 end之间
		BeginBatchDraw();
		cleardevice();

		if (button(20, 20, 150, 35, "Start Game"))
		{
			printf("Start Game! %d\n",i++);
		}

		if (button(300, 20, 150, 35, "End Game"))
		{
			printf("End Game!\n");
		}

		//绘制小球
		setfillcolor(RGB(43, 145, 175));
		solidcircle(x, y, r);
		//更新小球的位置
		x += speed * vx;
		y += speed * vy;

		EndBatchDraw();
		Sleep(10);
		//把消息类型设置为0
		msg.message = 0;
	}


	//防止程序退出
	getchar();
	return 0;
}