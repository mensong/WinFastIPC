#include <Windows.h>
#include <thread>
#include "Pipe.h"

bool g_bExit = false;

void th_pipeWrite()
{
	Pipe pipe;
	pipe.CreatePipe("test_pipe");
	int nCount = 1;
	char szNum[10] = { 0 };
	do 
	{
		_itoa_s(nCount, szNum, 10);
		nCount++;
		std::string strMsg = "WinPip����123_����";
		strMsg.append(szNum);
		pipe.PipeSendMessage(strMsg);

		std::string res;
		pipe.ReadMessage(res);
		if (res.length() > 0)
		{
			printf("Get: %s \n", res.c_str());
		}

		// д��ʱ���Ҫ���ڶ���ʱ����
		Sleep(500);
	} while (!g_bExit);
}

void th_pipeRead()
{
	Pipe pipe;
	pipe.ConnectToPipe("test_pipe");
	do
	{
		std::string  str;
		pipe.ReadMessage(str);
		if (str.length()>0)
		{
			printf("Get: %s \n", str.c_str());
		}

		pipe.PipeSendMessage("WinPip����123_����2");

		// д��ʱ���Ҫ���ڶ���ʱ����
		Sleep(150);
	} while (!g_bExit);
}

int main(int agrc,char* agrv[])
{
	if (agrc == 1)
	{
		std::thread t1(th_pipeWrite);
		//t1.detach();
		t1.join();
	}
	else
	{
		std::thread t2(th_pipeRead);
		t2.join();
	}

	return 0;
}