#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include "IClient.h"
#include "Client.h"

std::mutex g_mutex;

int StartClient(std::string strServerAddr)
{
	IClient*  pClient = new Client();

	if (!pClient->Configure(strServerAddr, 8888))
	{
		std::cout << pClient->GetErrorMsg() << std::endl;

		return -1;
	}

	// Start client
	if (!pClient->Start())
	{
		std::cout << pClient->GetErrorMsg() << std::endl;

		return -1;
	}

	// Send something to the server
	std::string TempData = "Hello,server, i am fine !";

	if (!pClient->Send(TempData.c_str(), static_cast<int>(TempData.length())))
	{
		std::cout << pClient->GetErrorMsg() << std::endl;

		return -1;
	}

	// Get info from the server
	char RevData[500] = { 0 };

	if (!pClient->Receive(RevData, 500))
	{
		std::cout << pClient->GetErrorMsg() << std::endl;

		return -1;
	}

	std::cout << "Receive server's data:" << RevData << std::endl;

	// Write the text to file
	{
		std::lock_guard<std::mutex> GlobalLock(g_mutex);

		std::fstream fStreamer;

		fStreamer.open("data.txt", std::ios::out);

		fStreamer << RevData<<std::endl;

		fStreamer.write(RevData, strlen(RevData)+1);

		fStreamer.close();
	}

	pClient->Stop();

	delete pClient;

	pClient = nullptr;

	return 0;
}

int main(int args,char** argv)
{
	std::string strServerAddr = "192.168.1.12";

	if (args > 1)
	{
		strServerAddr = argv[1];
	}

	/*int iRet = StartClient(strServerAddr);

	return iRet;*/

	std::thread t[10000];

	for (int index = 0; index < 10000; ++index)
	{
		t[index] = std::thread([=, &strServerAddr]()->int {
			int iRet = StartClient(strServerAddr);

			return iRet;
		});
	}

	for (int index = 0; index < 10000; ++index)
	{
		t[index].join();
	}

	return 0;
}

