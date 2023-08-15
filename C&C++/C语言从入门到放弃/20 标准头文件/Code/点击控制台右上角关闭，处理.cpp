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
        MessageBox(NULL, "ȷ���رմ�����", " Close", MB_OK);
        isExit = FALSE;
        //while (1);�ô�����
        /*ע�⣺����������£�ϵͳ��������Ƴ�ʱ��ǳ�����,��ʹ����ѭ���������Ժ󣬴���Ҳ�ᱻ����*/
        return TRUE;
     }

    /*
        CTRL_C_EVENT            ����Ctrl+C 
        CTRL_CLOSE_EVENT        ���Ͻǹرտ���̨����
        Other messages:
        CTRL_BREAK_EVENT         Ctrl + Break pressed
        CTRL_LOGOFF_EVENT        ע��
        CTRL_SHUTDOWN_EVENT      �ػ�
    */

    return FALSE;
}

int main(void)
{
    //���ÿ���̨������
    BOOL ok = SetConsoleCtrlHandler(ConsoleHandler, TRUE);
  
    while (isExit);//���û��֪ͨ���ڹرգ���ôһֱ�ȴ�
    return 0;
}
