#include "../FastIpcLib/fast_ipc/ipc.h"
#include <tchar.h>
#include <stdio.h>

#define IpcChannel  _T("MyTestIpcChannel")

CRITICAL_SECTION cs;
static UINT64 Counter = 0;

BOOL WINAPI TestIpcRoutine(
	LPCWSTR ChannelName,
	PVOID MessageBuf,
	DWORD MessageSize,
	PVOID AnswerBuf,
	DWORD AnswerSize
	)
{
	EnterCriticalSection(&cs);
	wprintf_s(L"[%llu] %s\n", ++Counter, (wchar_t*)MessageBuf);
	*((BOOL*)AnswerBuf) = rand() % 2 == 1;
	LeaveCriticalSection(&cs);
	return TRUE;
}

int main(int agrc, char** agrv)
{
	printf("I Am Server \n");
	InitializeCriticalSection(&cs);
	LPVOID ChannelData;
	bool bRet = IpcCreateIpcChannel(IpcChannel, &TestIpcRoutine, false, &ChannelData);
	if (bRet)
	{
		printf("Waiting Client Msg ... \n");
		// �ȴ��ڲ��̴߳������
		Sleep(1000);
		getchar();
		if (!IpcDestroyIpcChannel(ChannelData))
		{
			printf("DestroyIpcChannel() failed\n");
		}

		printf("all tests done\n");
		getchar();
	}
	else
	{
		printf("CreateIpcChannel() failed\n");
		getchar();
	}
	DeleteCriticalSection(&cs);
	return 0;
}
