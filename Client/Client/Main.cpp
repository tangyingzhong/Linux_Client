#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <wait.h>
#include "IClient.h"
#include "Client.h"

std::mutex g_mutex;

int StartClient(std::string strServerAddr)
{
	IClient*  pClient = new Client();

	if (!pClient->Configure(strServerAddr, 8888))
	{
		std::cout << pClient->GetErrorMsg() << std::endl;

		pClient->Stop();

		delete pClient;

		pClient = nullptr;

		return -1;
	}

	// Start client
	if (!pClient->Start())
	{
		std::cout << pClient->GetErrorMsg() << std::endl;

		pClient->Stop();

		delete pClient;

		pClient = nullptr;

		return -1;
	}

	// Send something to the server
	std::string TempData = "Hello,server, i am fine !";

	if (!pClient->Send(TempData.c_str(), static_cast<int>(TempData.length())))
	{
		std::cout << pClient->GetErrorMsg() << std::endl;

		pClient->Stop();

		delete pClient;

		pClient = nullptr;

		return -1;
	}

	// Get info from the server
	char RevData[500] = { 0 };

	if (!pClient->Receive(RevData, 500))
	{
		std::cout << pClient->GetErrorMsg() << std::endl;

		pClient->Stop();

		delete pClient;

		pClient = nullptr;

		return -1;
	}

	std::cout << "Receive server's data:" << RevData << std::endl;

	//// Write the text to file
	//{
	//	std::lock_guard<std::mutex> GlobalLock(g_mutex);

	//	std::fstream fStreamer;

	//	fStreamer.open("data.txt", std::ios::out);

	//	fStreamer << RevData<<std::endl;

	//	fStreamer.write(RevData, strlen(RevData)+1);

	//	fStreamer.close();
	//}

	pClient->Stop();

	delete pClient;

	pClient = nullptr;

	return 0;
}

int main(int args, char** argv)
{
	std::string strServerAddr = "192.168.1.12";

	if (args > 1)
	{
		strServerAddr = argv[1];
	}

	/*int iRet = StartClient(strServerAddr);

	return iRet;*/

	/*std::thread t[500000];

	for (int index = 0; index < 500000; ++index)
	{
		t[index] = std::thread([=, &strServerAddr]()->int {
			int iRet = StartClient(strServerAddr);

			return iRet;
		});
	}

	for (int index = 0; index < 500000; ++index)
	{
		t[index].join();
	}*/

	const int TOTAL_PROCESS = 60000;

	int iProcNum = TOTAL_PROCESS;

	int iSuccessCount = 0;

	int iFailedCount = 0;

	while (iProcNum--)
	{
		pid_t iPid = fork();
		if (iPid == 0)
		{
			int iRet = StartClient(strServerAddr);

			return iRet;
		}
		else if (iPid > 0)
		{
			++iSuccessCount;
		}
		else
		{
			++iFailedCount;

			std::cout << strerror(errno) << std::endl;
		}
	}

	for (int index = 0; index < iSuccessCount; ++index)
	{
		wait(NULL);
	}

	std::cout << "Suceessfully fork process number is :" << iSuccessCount << std::endl;

	std::cout << "Failed to fork process number is :" << iFailedCount << std::endl;

	std::cout << "Finish all processes" << std::endl;

	return 0;
}
