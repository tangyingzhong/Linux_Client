///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Offer the common interfaces for client
///</describe>
/// <date>2020/2/21</date>
///***********************************************************************
#ifndef ICLIENT_H
#define ICLIENT_H

#include <iostream>

class IClient
{
public:
	// Detructe the IClient
	virtual ~IClient(){	}
	
public:
	// Configure the client
	virtual bool Configure(std::string& strServerAddr,int iServerPortNo) = 0;

	// Start the client
	virtual bool Start() = 0;

	// Send the data to server
	virtual bool Send(const char* pData,int iSendSize) = 0;

	// Receive data from the server
	virtual bool Receive(char* pData,int iRevSize) = 0;

	// Stop the client
	virtual bool Stop() = 0;

	// Get the error message 
	virtual std::string GetErrorMsg() = 0;
};

#endif // ICLIENT_H
