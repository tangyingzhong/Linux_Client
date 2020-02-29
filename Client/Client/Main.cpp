#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "IClient.h"
#include "Client.h"

int main(int args,char** argv)
{
	std::string strServerAddr = "192.168.1.12";

	if (args > 1)
	{
		strServerAddr = argv[1];
	}

	std::cout << strServerAddr << std::endl;

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

	std::cout << "Rev server's data:" << RevData << std::endl;

	pClient->Stop();

	delete pClient;

	pClient = nullptr;

	return 0;
}

