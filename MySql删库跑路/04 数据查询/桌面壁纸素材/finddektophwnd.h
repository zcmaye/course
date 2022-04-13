///////////////////////////////////////////
//*  @file    finddesktophwnd.h
//*  @date    2021/10/02 23:16
//*  @brief   查找桌面窗口句柄
//*
//*  @author  Maye(顽石老师)
//*  @contact zcmaye@gmail.com
//*  @微信公众号 C语言Plus
///////////////////////////////////////////
#ifndef FINDDEKTOPHWND_H
#define FINDDEKTOPHWND_H
#include<qt_windows.h>
class QWidget;
class FindDektopHwnd
{
public:
    FindDektopHwnd();
    static BOOL CALLBACK EnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle);
    static HWND GetDesktopHandle();

    static void SetParent(QWidget*child,HWND parent);

    inline static HWND _workerw = NULL;
};

#endif // FINDDEKTOPHWND_H
