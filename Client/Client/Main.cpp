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

//int StartClient(std::string strServerAddr)
//{
//	IClient*  pClient = new Client();
//
//	if (!pClient->Configure(strServerAddr, 8888))
//	{
//		std::cout << pClient->GetErrorMsg() << std::endl;
//
//		pClient->Stop();
//
//		delete pClient;
//
//		pClient = nullptr;
//
//		return -1;
//	}
//
//	// Start client
//	if (!pClient->Start())
//	{
//		std::cout << pClient->GetErrorMsg() << std::endl;
//
//		pClient->Stop();
//
//		delete pClient;
//
//		pClient = nullptr;
//
//		return -1;
//	}
//
//	// Send something to the server
//	std::string TempData = "Hello,server,how are you?";
//
//	if (!pClient->Send(TempData.c_str(), static_cast<int>(TempData.length())))
//	{
//		std::cout << pClient->GetErrorMsg() << std::endl;
//
//		pClient->Stop();
//
//		delete pClient;
//
//		pClient = nullptr;
//
//		return -1;
//	}
//
//	// Get info from the server
//	char RevData[500] = { 0 };
//
//	if (!pClient->Receive(RevData, 500))
//	{
//		std::cout << pClient->GetErrorMsg() << std::endl;
//
//		pClient->Stop();
//
//		delete pClient;
//
//		pClient = nullptr;
//
//		return -1;
//	}
//
//	std::cout << "Read from server: <<" <<RevData << std::endl;
//
//	pClient->Stop();
//
//	delete pClient;
//
//	pClient = nullptr;
//
//	return 0;
//}
//
//int main(int args, char** argv)
//{
//	std::string strServerAddr = "192.168.1.12";
//
//	std::string strParallelNum = "90000";
//
//	if (args > 1)
//	{
//		strServerAddr = argv[1];
//
//		strParallelNum = argv[2];
//	}
//
//	/*int iRet = StartClient(strServerAddr);
//
//	return iRet;*/
//
//	/*std::thread t[500000];
//
//	for (int index = 0; index < 500000; ++index)
//	{
//		t[index] = std::thread([=, &strServerAddr]()->int {
//			int iRet = StartClient(strServerAddr);
//
//			return iRet;
//		});
//	}
//
//	for (int index = 0; index < 500000; ++index)
//	{
//		t[index].join();
//	}*/
//
//	int iProcNum = std::stoi(strParallelNum);
//
//	int iSuccessProcCount = 0;
//
//	int iFailedProcCount = 0;
//
//	while (iProcNum--)
//	{
//		pid_t iPid = fork();
//		if (iPid == 0)
//		{
//			int iRet = StartClient(strServerAddr);
//
//			return iRet;
//		}
//		else if (iPid > 0)
//		{
//			++iSuccessProcCount;
//		}
//		else
//		{
//			++iFailedProcCount;
//
//			std::cout << strerror(errno) << std::endl;
//		}
//	}
//
//	for (int index = 0; index < iSuccessProcCount; ++index)
//	{
//		wait(NULL);
//	}
//
//	std::cout << "Suceessfully fork process number is :" << iSuccessProcCount << std::endl;
//
//	std::cout << "Failed to fork process number is :" << iFailedProcCount << std::endl;
//
//	std::cout << "Finish all processes" << std::endl;
//
//	return 0;
//}

void Swap(int& a,int& b)
{
	int temp = a;

	a = b;

	b = temp;
}

// Bubble sort
bool BubbleSort(int* pData,int iArraySize,bool bAsc)
{
	if (pData==nullptr)
	{
		return false;
	}

	if (iArraySize<=0)
	{
		return false;
	}

	for (int count = 0; count < iArraySize - 1; ++count)
	{
		for (int index = count+1; index < iArraySize; ++index)
		{
			if (bAsc)
			{
				if (pData[count] > pData[index])
				{
					Swap(pData[count], pData[index]);
				}
			}
			else
			{
				if (pData[count] < pData[index])
				{
					Swap(pData[count], pData[index]);
				}
			}
		}
	}

	return true;
}

// Sort one section
int SortOneSection(int* pData, int iLeft, int iRight, bool bAsc)
{
	if (pData == nullptr)
	{
		return -1;
	}

	int iStartPos = iLeft;

	int iEndPos = iRight;

	int iTempData = pData[iLeft];

	while (iStartPos < iEndPos)
	{
		// Search right section at first so that we can stage the data to temp data position
		if (bAsc)
		{
			while (pData[iEndPos] >= iTempData && iStartPos < iEndPos)
			{
				iEndPos--;
			}
		}
		else
		{
			while (pData[iEndPos] < iTempData && iStartPos < iEndPos)
			{
				iEndPos--;
			}
		}

		if (iStartPos < iEndPos)
		{
			pData[iStartPos++] = pData[iEndPos];
		}

		// Search left section so that we can stage the data to not used data position at right section
		if (bAsc)
		{
			while (pData[iStartPos] < iTempData  && iStartPos < iEndPos)
			{
				iStartPos++;
			}
		}
		else
		{
			while (pData[iStartPos] >= iTempData && iStartPos < iEndPos)
			{
				iStartPos++;
			}
		}

		if (iStartPos < iEndPos)
		{
			pData[iEndPos--] = pData[iStartPos];
		}
	}

	pData[iStartPos] = iTempData;

	return iStartPos;
}

// Quick sort
bool QuickSort(int* pData,int iStartPos,int iEndPos,bool bAsc)
{
	if (pData==nullptr)
	{
		return false;
	}

	if (iStartPos < 0 || iEndPos < 0)
	{
		return false;
	}

	// This is a end condition for searching
	if (iStartPos > iEndPos)
	{
		return true;
	}

	int iMidPos = SortOneSection(pData, iStartPos, iEndPos,bAsc);

	// The do operations above again for the left array
	QuickSort(pData, iStartPos, iMidPos -1,bAsc);

	// The do operations above again for the right array
	return QuickSort(pData, iMidPos +1, iEndPos, bAsc);
}

struct Node
{
	int key;

	int value;

	int color;

	struct Node* pParent;

	struct Node* pLeft;

	struct Node* pRight;
};

struct RBTree 
{
	Node* pRoot;

	Node* pNil;
};

enum TREE_COLOR
{
	BLACK = 0,

	RED
};

void Initialize(RBTree*& pTree)
{
	pTree = new RBTree();

	pTree->pNil = new Node();

	pTree->pNil->key = 0;

	pTree->pNil->value = 0;

	pTree->pNil->color = BLACK;

	pTree->pRoot = pTree->pNil;
}

void Destory(RBTree*& pTree)
{
	
}

void Insert(RBTree* pTree, Node* pNode)
{
	Node* pRoot = pTree->pRoot;

	Node* pInsertNode=pTree->pNil;

	while (pRoot != pTree->pNil)
	{
		pInsertNode = pRoot;

		if (pNode->key < pRoot->key)
		{
			pRoot = pRoot->pLeft;
		}
		else
		{
			pRoot = pRoot->pRight;
		}
	}

	pNode->pParent = pInsertNode;

	if (pInsertNode==pTree->pNil)
	{
		pTree->pRoot = pNode;
	}
	else if (pNode->key < pInsertNode->key)
	{
		pInsertNode->pLeft = pNode;
	}
	else
	{
		pInsertNode->pRight = pNode;
	}

	pNode->pLeft = pTree->pNil;

	pNode->pRight = pTree->pNil;

	pNode->color = RED;
}

void InsertFixup(RBTree* pTree,Node* pNode)
{
	while (pNode->pParent->color==RED)
	{
		// If current node's parent is grandpa's left node so that we can know which side is uncle node on
		if (pNode->pParent== pNode->pParent->pParent->pLeft)
		{
			Node* pUncle = pNode->pParent->pParent->pRight;

			if (pUncle->color==RED)
			{
				pNode->pParent->color = BLACK;

				pNode->pParent->pParent->color = RED;

				pUncle->color = BLACK;

				pNode = pNode->pParent->pParent;
			}
			else
			{
				if (pNode==pNode->pParent->pRight)
				{
					pNode = pNode->pParent;

					LeftRotation(pTree, pNode);
				}

				pNode->pParent->color = BLACK;

				pNode->pParent->pParent->color = RED;

				RightRotation(pTree, pNode->pParent->pParent);
			}
		}
		else
		{
			Node* pUncle = pNode->pParent->pParent->pLeft;

			if (pUncle->color==RED)
			{
				pNode->pParent->color = BLACK;

				pNode->pParent->pParent->color = RED;

				pUncle->color = BLACK;

				pNode = pNode->pParent->pParent;
			}
			else
			{
				if (pNode == pNode->pParent->pLeft)
				{
					pNode = pNode->pParent;

					RightRotation(pTree, pNode);
				}

				pNode->pParent->color = BLACK;

				pNode->pParent->pParent->color = RED;

				LeftRotation(pTree, pNode->pParent->pParent);
			}
		}
	}

	pTree->pRoot->color = BLACK;
}

void Add(RBTree* pTree, int key,int value)
{
	Node* pNode = new Node();

	pNode->key = key;

	pNode->value = value;

	// Insert the node to the tree
	Insert(pTree, pNode);

	// Fixup the tree to be rb tree
	InsertFixup(pTree, pNode);
}

void LeftRotation(RBTree* pTree, Node* pNode)
{
	Node* pRightNode = pNode->pRight;

	pNode->pRight = pRightNode->pLeft;

	if (pRightNode->pLeft != pTree->pNil)
	{
		pRightNode->pLeft->pParent = pNode;
	}

	pRightNode->pParent = pNode->pParent;

	if (pNode->pParent==pTree->pNil)
	{
		pTree->pRoot = pRightNode;
	}
	else if (pNode==pNode->pParent->pLeft)
	{
		pRightNode->pParent = pNode->pParent->pLeft;
	}
	else
	{
		pRightNode->pParent = pNode->pParent->pRight;
	}

	pRightNode->pLeft = pNode;

	pNode->pParent = pRightNode;
}

void RightRotation(RBTree* pTree, Node* pNode)
{
	Node* pLeftNode = pNode->pLeft;

	pNode->pLeft = pLeftNode->pRight;

	if (pLeftNode->pRight != pTree->pNil)
	{
		pLeftNode->pRight->pParent = pNode;
	}

	pLeftNode->pParent = pNode->pParent;

	if (pNode->pParent == pTree->pNil)
	{
		pTree->pRoot = pLeftNode;
	}
	else if (pNode==pNode->pParent->pLeft)
	{
		pLeftNode->pParent = pNode->pParent->pLeft;
	}
	else
	{
		pLeftNode->pParent = pNode->pParent->pRight;
	}
	
	pLeftNode->pRight = pNode;

	pNode->pParent = pLeftNode;
}

void DisplayTree(RBTree* pTree,Node* pNode)
{
	if (pTree==nullptr)
	{
		return;
	}

	if (pNode==pTree->pNil)
	{
		return;
	}

	DisplayTree(pTree, pNode->pLeft);

	std::cout << "Key:"
		<< pNode->key
		<< " -> Value:"
		<< pNode->value
		<< std::endl;

	DisplayTree(pTree, pNode->pRight);
}

int main()
{
	int ArrayTest[] = {1,3,5,7,8,10,12,14,16,18,17,15,13,11,9,6,4,2};

	int iTotalSize = sizeof(ArrayTest) / sizeof(int);

	//BubbleSort(ArrayTest, iTotalSize, false);

	//QuickSort(ArrayTest, 0, iTotalSize - 1, false);

	/*for (int index = 0; index < iTotalSize; ++index)
	{
		std::cout << ArrayTest[index] << " ";
	}

	std::cout << std::endl;*/

	RBTree* pTree = nullptr;

	Initialize(pTree);

	Add(pTree, 10, 2);

	Add(pTree, 11, 2);

	Add(pTree, 20, 2);

	Add(pTree, 27, 2);

	Add(pTree, 40, 2);

	

	return 0;
}