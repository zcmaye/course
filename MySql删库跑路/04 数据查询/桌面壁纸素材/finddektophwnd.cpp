#include "finddektophwnd.h"
#include<QWidget>
FindDektopHwnd::FindDektopHwnd()
{

}

BOOL CALLBACK FindDektopHwnd::EnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle)
{
    HWND defview = FindWindowEx(tophandle, 0, L"SHELLDLL_DefView", NULL);
    if (defview != NULL)
    {
        _workerw = FindWindowEx(0, tophandle, L"WorkerW", 0);
    }
    return true;
}//遍历句柄的回调函数

HWND FindDektopHwnd::GetDesktopHandle()
{
    ULONG_PTR result;
    HWND windowHandle = FindWindow(L"Progman", NULL);
    SendMessageTimeout(windowHandle, 0x052c, 0, 0, SMTO_NORMAL, 0x3e8, (PDWORD_PTR)&result);
    EnumWindows(EnumWindowsProc, (LPARAM)NULL);
    ShowWindow(_workerw, SW_HIDE);
    return windowHandle;
}

void FindDektopHwnd::SetParent(QWidget *child, HWND parent)
{
    HWND dekstopHwnd = parent;
    if(parent == nullptr)
    {
        //获取桌面的窗口句柄
        dekstopHwnd = FindDektopHwnd::GetDesktopHandle();
    }

    //把dekstopHwnd设置为父对象
    ::SetParent((HWND)child->winId(),(HWND)dekstopHwnd);
}

