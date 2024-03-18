#ifndef CONSOLE_H_
#define CONSOLE_H_
#include<stdarg.h>
#define C(color,fmt,...) printf("\033[1;33m " fmt " \033[0m",__VA_ARGS__)

/**
 * 将光标移动到第y行，第x列，xy从0开始.
 */
#define gotoxy(x,y)      printf("\033[%d;%dH", y+1, x+1)

void printText(int x, int y, const char* fmt, ...);
void printTextWithCSI(int x, int y,const char*csi, const char* fmt, ...);
void format(const char* fmt, va_list list);

static void printText(int x, int y, const char* fmt, ...)
{
	printf("\033[%d;%dH", y, x);
	va_list list;
	va_start(list, fmt);
	format(fmt, list);
	va_end(list);

	printf("\033[0m");
}

static void printTextWithCSI(int x, int y, const char*csi, const char* fmt, ...)
{
	printf("\033[%d;%dH %s ", y, x,csi);
	va_list list;
	va_start(list, fmt);
	format(fmt, list);
	va_end(list);

	printf("\033[0m");

}

static void format(const char* fmt, va_list list)
{
	static	char buf[1024*10] = { 0 };
	vsnprintf(buf, 1024, fmt, list);
	printf(buf);
}


#endif // !CONSOLE_H_
