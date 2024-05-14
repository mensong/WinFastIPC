#include "../FastIpcLib/fast_ipc/ipc.h"
#include <tchar.h>
#include <stdio.h>

#define IpcChannel  _T("MyTestIpcChannel")


DWORD WINAPI LoopSend(void* pParm)
{
	LPCWSTR Message = L"Wow. There is Client One Msg ...";
	DWORD MessageSize = (DWORD)((wcslen(Message) + 1) * sizeof(WCHAR));
	BOOL AnswerBool;

	while (TRUE)
	{
		if (!IpcSendIpcMessage(IpcChannel,
			(LPVOID)Message,
			MessageSize,
			&AnswerBool,
			sizeof(AnswerBool),
			INFINITE,
			FALSE))
		{
			printf("thread %d exit\n", GetCurrentThreadId());
			return 1;
		}
	}
	return 0;
}

int main(int agrc, char** agrv)
{
	printf("This is Client One \n");

	const DWORD NumOfThreads = 8;
	HANDLE ThreadHandles[NumOfThreads];

	for (int i = 0; i < NumOfThreads; ++i)
	{
		ThreadHandles[i] = CreateThread(NULL, 0, LoopSend, NULL, 0, NULL);
	}

	getchar();

	for (int i = 0; i < NumOfThreads; ++i)
	{
		CloseHandle(ThreadHandles[i]);
	}

	printf("all tests done\n");
	getchar();
	return 0;
}
