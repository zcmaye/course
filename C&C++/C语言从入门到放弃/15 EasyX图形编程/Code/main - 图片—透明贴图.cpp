#include<stdio.h>
#include<easyx.h>
#include"tool.h"
int main()
{
	initgraph(480, 800, EX_SHOWCONSOLE);
	setbkcolor(RGB(230, 231, 232));
	cleardevice();

	//定义图片变量	int a;
	IMAGE img_mm;
	//加载图片		scanf("%d",&a);
	//1，绝对路径:带盘符的路径   "C:\\Users\\Maye\\Desktop\\EasyxLearn\\assets\\mm.jpg"
	//2，相对路径				"assets/mm.jpg"	
	loadimage(&img_mm, "assets/mm.jpg");
	//输出图片		printf("%d",a);
	putimage(0, 0, &img_mm);

	//掩码图透明贴图
	IMAGE img_plane[2];
	loadimage(img_plane + 0, "assets/planeNormal_1.jpg");
	loadimage(img_plane + 1, "assets/planeNormal_2.jpg");

	putimage(50, 100, img_plane + 0,NOTSRCERASE);	//先绘制掩码图
	putimage(50, 100, img_plane + 1,SRCINVERT);		//再绘制原图

	//PNG图片透明贴图
	IMAGE img_png;
	loadimage(&img_png, "assets/enemy1.png");
	putimage(200, 100, &img_png);
	drawImg(200, 200, &img_png);

	getchar();
	return 0;
}