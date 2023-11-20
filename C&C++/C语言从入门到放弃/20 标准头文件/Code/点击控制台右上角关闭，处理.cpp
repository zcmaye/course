#include <Windows.h>
#include <stdio.h>

BOOL isExit = TRUE;
BOOL WINAPI ConsoleHandler(DWORD msgType)
{
    if (msgType == CTRL_C_EVENT)
    {
        printf("CTRL_C_EVENT\n");
        isExit = FALSE;
        return TRUE;
    }
    else if (msgType == CTRL_CLOSE_EVENT)
     {
        printf("Close console window!\n");
        MessageBox(NULL, "确定关闭窗口吗？", " Close", MB_OK);
        isExit = FALSE;
        //while (1);用处不大
        /*注意：在这种情况下，系统留给你的推出时间非常有限,即使用死循环卡主，稍后，窗口也会被销毁*/
        return TRUE;
     }

    /*
        CTRL_C_EVENT            按下Ctrl+C 
        CTRL_CLOSE_EVENT        左上角关闭控制台窗口
        Other messages:
        CTRL_BREAK_EVENT         Ctrl + Break pressed
        CTRL_LOGOFF_EVENT        注销
        CTRL_SHUTDOWN_EVENT      关机
    */

    return FALSE;
}

int main(void)
{
    //设置控制台处理函数
    BOOL ok = SetConsoleCtrlHandler(ConsoleHandler, TRUE);
  
    while (isExit);//如果没有通知窗口关闭，那么一直等待
    return 0;
}
