#include<stdio.h>
#include"Controller.h"
#include<iostream>
int main()
{

	initgraph(1300, 768,EW_SHOWCONSOLE);

	IMAGE img;
	loadimage(&img, L"./bk.png");
	putimage(0, 0, &img);

	Controller con;
	con.run();
	

	getchar();
	return 0;
}