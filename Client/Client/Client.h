///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It is a client to be connected to a server
///</describe>
/// <date>2020/2/21</date>
///***********************************************************************
#ifndef CLIENT_H
#define CLIENT_H

#include "IClient.h"

class Client :public IClient
{
public:
	// Construct the Client
	Client();
	
	// Detructe the Client
	~Client();

public:
	// Configure the client
	virtual bool Configure(std::string& strServerAddr, int iServerPortNo);

	// Start the client
	virtual bool Start();

	// Send the data to server
	virtual bool Send(const char* pData,int iSendSize);

	// Receive data from the server
	virtual bool Receive(char* pData,int iRevSize);

	// Stop the client
	virtual bool Stop();

	// Get the error message 
	virtual std::string GetErrorMsg();

private:
	// Get disposed status
	inline bool GetDisposed() const
	{
		return m_bDisposed;
	}
	
	// Set the disposed status
	inline void SetDisposed(bool bDisposed)
	{
		m_bDisposed = bDisposed;
	}

	// Get the ServerAddr
	inline std::string GetServerAddr() const
	{
		return m_strServerAddr;
	}

	// Set the ServerAddr
	inline void SetServerAddr(std::string strServerAddr)
	{
		m_strServerAddr = strServerAddr;
	}

	// Get the ServerPortNo
	inline int GetServerPortNo() const
	{
		return m_iServerPortNo;
	}

	// Set the ServerPortNo
	inline void SetServerPortNo(int iServerPortNo)
	{
		m_iServerPortNo = iServerPortNo;
	}

	// Get the ErrorText
	inline std::string GetErrorText() const
	{
		return m_strErrorText;
	}

	// Set the ErrorText
	inline void SetErrorText(std::string strErrorText)
	{
		m_strErrorText = strErrorText;
	}

	// Get the Socket
	inline int GetSocket() const
	{
		return m_iSocket;
	}

	// Set the Socket
	inline void SetSocket(int iSocket)
	{
		m_iSocket = iSocket;
	}

private:
	// Socket
	int m_iSocket;

	// Server address
	std::string m_strServerAddr;
	
	// Server port
	int m_iServerPortNo;
	
	// Error message 
	std::string m_strErrorText;
	
	// Disposed status
	bool m_bDisposed;	
};

#endif //CLIENT_H
