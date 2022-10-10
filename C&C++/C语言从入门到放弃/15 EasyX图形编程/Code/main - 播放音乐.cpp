#include<stdio.h>
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

void playBackgroundMusic(const char* music,bool repeat = false,int volume = -1)
{
	static int i = 0;
	char cmd[100] = { 0 };
	sprintf(cmd, "open %s alias bgm%d", music,i);
	MCIERROR ret = mciSendString(cmd, NULL, 0, NULL);
	if (ret != 0)
	{
		//获取一下错误信息
		char err[100] = { 0 };
		mciGetErrorString(ret, err, sizeof(err));
		printf("[open]:%s", err);
	}
	sprintf(cmd, "play  bgm%d %s", i, repeat ? "repeat" : "");
	ret = mciSendString(cmd, NULL, 0, NULL);
	if (ret != 0)
	{
		//获取一下错误信息
		char err[100] = { 0 };
		mciGetErrorString(ret, err, sizeof(err));
		printf("[play]:%s", err);
	}
	if (volume != -1)
	{
		sprintf(cmd, "setaudio bgm%d volume to %d", i, volume);
		ret = mciSendString(cmd, NULL, 0, NULL);	//音量范围[0-1000]
		if (ret != 0)
		{
			//获取一下错误信息
			char err[100] = { 0 };
			mciGetErrorString(ret, err, sizeof(err));
			puts(err);
		}
	}

	i++;
}

int main()
{
	//播放音乐 m media c control i interface
	//无法播放音乐：
	//1，路径错误
	//2，系统驱动不支持
	//3，音乐格式错误，网易云下载的，不能播放

	/*MCIERROR ret = mciSendString("open assets/That-Girl.mp3 alias bgm", NULL, 0, NULL);
	if (ret != 0)
	{
		//获取一下错误信息
		char err[100] = { 0 };
		mciGetErrorString(ret, err, sizeof(err));
		puts(err);
	}
	mciSendString("play bgm", NULL, 0, NULL);
	//如果失败返回非0值，成功返回0
	ret = mciSendString("setaudio bgm volume  50",NULL,0,NULL);	//音量范围[0-1000]
	if (ret != 0)
	{
		//获取一下错误信息
		char err[100] = { 0 };
		mciGetErrorString(ret, err, sizeof(err));
		puts(err);
	}*/

	//playBackgroundMusic("assets/That-Girl.mp3",true,50);
	//playBackgroundMusic("assets/video_call.wav",true);

	//专门用来播放音效
	while (true)
	{
		PlaySound("assets/That-Girl.mp3", NULL, SND_FILENAME | SND_ASYNC);
		//PlaySound("assets/video_call.wav", NULL, SND_FILENAME | SND_ASYNC);
		//playBackgroundMusic("assets/video_call.wav");
		getchar();
	}



	getchar();
	return 0;
}