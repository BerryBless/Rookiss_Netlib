#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"


#include "SocketUtils.h"
#include "Listener.h"

int main()
{
	Listener listener;
	listener.StartAccept(NetAddress(L"127.0.0.1", 7777));

	for (int i = 0; i < 5; i++) {
		GThreadManager->Launch([=]() {
			DWORD TID = GetCurrentThreadId();
			printf_s("TID[%d] start\n", TID);
			for (;;) {
				GIocpCore.Dispatch();
			}
			printf_s("TID[%d] end\n", TID);
			});
	}
	GThreadManager->Join();
}