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
	std::string TempData = "Hello,server,how are you?";

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

	std::cout << "Read from server: <<" <<RevData << std::endl;

	pClient->Stop();

	delete pClient;

	pClient = nullptr;

	return 0;
}

int main(int args, char** argv)
{
	std::string strServerAddr = "192.168.1.12";

	std::string strParallelNum = "90000";

	if (args > 1)
	{
		strServerAddr = argv[1];

		strParallelNum = argv[2];
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

	int iProcNum = std::stoi(strParallelNum);

	int iSuccessProcCount = 0;

	int iFailedProcCount = 0;

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
			++iSuccessProcCount;
		}
		else
		{
			++iFailedProcCount;

			std::cout << strerror(errno) << std::endl;
		}
	}

	for (int index = 0; index < iSuccessProcCount; ++index)
	{
		wait(NULL);
	}

	std::cout << "Suceessfully fork process number is :" << iSuccessProcCount << std::endl;

	std::cout << "Failed to fork process number is :" << iFailedProcCount << std::endl;

	std::cout << "Finish all processes" << std::endl;

	return 0;
}
