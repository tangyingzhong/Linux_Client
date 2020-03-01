#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <errno.h> 
#include "Client.h"

extern int errno;

// Construct the Client
Client::Client():m_iSocket(0),
m_strServerAddr(""),
m_iServerPortNo(0),
m_strErrorText(""),
m_bDisposed(false)
{

}

// Detructe the Client
Client::~Client()
{

}

// Configure the client
bool Client::Configure(std::string& strServerAddr, int iServerPortNo)
{
	if (strServerAddr.empty())
	{
		SetErrorText("Server address is empty!");

		return false;
	}

	if (iServerPortNo<=0)
	{
		SetErrorText("Server portNo must >0 !");

		return false;
	}

	SetServerAddr(strServerAddr);

	SetServerPortNo(iServerPortNo);

	return true;
}

// Start the client
bool Client::Start()
{
	// Create socket
	int iSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (iSocket<0)
	{
		char* strErrorMsg = strerror(errno);

		SetErrorText(strErrorMsg);

		return false;
	}

	// Set the socket
	SetSocket(iSocket);

	// Set the socket info
	struct sockaddr_in ServerAddr;

	memset(&ServerAddr, 0, sizeof(ServerAddr));

	ServerAddr.sin_family = AF_INET;

	ServerAddr.sin_port = htons(static_cast<uint16_t>(GetServerPortNo()));

	ServerAddr.sin_addr.s_addr = inet_addr(GetServerAddr().c_str());

	// Connect to the server
	int iRet = connect(GetSocket(), (struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
	if (iRet<0)
	{
		char* strErrorMsg = strerror(errno);

		SetErrorText(strErrorMsg);

		return false;
	}

	return true;
}

// Send the data to server
bool Client::Send(const char* pData,int iSendSize)
{
	if (pData == nullptr)
	{
		SetErrorText("Data to be sent is null !");

		return false;
	}

	if (iSendSize <= 0)
	{
		SetErrorText("Inalid data size !");

		return false;
	}

	if (GetSocket() == 0)
	{
		SetErrorText("Inalid client !");

		return false;
	}

	size_t lTotalSize = static_cast<size_t>(iSendSize);

	ssize_t lWrittenSize = write(GetSocket(), pData, lTotalSize);
	if (lWrittenSize == -1)
	{
		if (errno == EAGAIN)
		{
			return true;
		}

		char* pErrorMsg = strerror(errno);

		SetErrorText(pErrorMsg);

		return false;
	}

	return true;
}

// Receive data from the server
bool Client::Receive(char* pData,int iRevSize)
{
	if (pData == nullptr)
	{
		SetErrorText("Data buffer to store receive data is null !");

		return false;
	}

	if (iRevSize <= 0)
	{
		SetErrorText("Inalid size to get data !");

		return false;
	}

	if (GetSocket() == 0)
	{
		SetErrorText("Inalid client !");

		return false;
	}

	size_t lTotalSize = static_cast<size_t>(iRevSize);

	ssize_t lReadSize = read(GetSocket(), pData, lTotalSize);
	if (lReadSize < 0)
	{
		if (errno==EAGAIN)
		{
			return true;
		}

		char* pErrorMsg = strerror(errno);

		SetErrorText(pErrorMsg);

		return false;
	}

	return true;
}

// Stop the client
bool Client::Stop()
{
	if (GetSocket()==0)
	{
		SetErrorText("Socket is null !");

		return false;
	}

	close(GetSocket());

	SetSocket(0);

	return true;
}

// Get the error message 
std::string Client::GetErrorMsg()
{
	return GetErrorText();
}
