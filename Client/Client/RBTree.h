///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Define the rb tree's function
///</describe>
/// <date>2020/3/9</date>
///***********************************************************************
#ifndef RBTREE_H
#define RBTREE_H

#include <string>

enum RB_COLOR_ENUM
{
	RED=0,

	BLACK
};

template <class T1,class T2>
struct TreeNode
{
	// Key 
	T1 key;

	// Value
	T2 value;

	// Node's color
	RB_COLOR_ENUM color;

	// Parent node
	TreeNode* pParent;

	// Left node
	TreeNode* pLeft;

	// Right node
	TreeNode* pRight;
};

template <class T1,class T2>
class RBTree
{
public:
	using KeyType = T1;
	using ValueType = T2;
	using NodeType = TreeNode<KeyType, ValueType>;

public:
	// Construct the RBTree
	explicit RBTree();
	
	// Detructe the RBTree
	~RBTree();
	
public:
	// Insert the key and value
	bool Insert(KeyType& key, ValueType& value);

	// Remove the key
	void Remove(KeyType& key);

	// Search the key
	bool Search(KeyType& key, ValueType& value);

	// Modify the key's data
	bool Modify(KeyType& key, ValueType& value);

	// Get the error message
	std::string GetErrorMsg();

private:
	// Initialize the tree
	void Initialize();

	// Destory the tree
	void Destory();

	// Insert the key and value
	bool Insert(NodeType* pCurNode);

	// Insert fixup
	void InsertFixup(NodeType* pRoot,NodeType* pCurNode);

	// Remove fixup
	void RemoveFixup(NodeType* pRoot, NodeType* pCurNode);

	// Max node
	NodeType* Maximum();

	// Minimize node
	NodeType* Minimum();

	// Destory node
	void DestoryNode(NodeType* pNode);

	// Get min node
	NodeType* GetMinNode(NodeType* pNode);

	// Get max node
	NodeType* GetMaxNode(NodeType* pNode);

	// Create node
	NodeType* CreateNode(KeyType& key, 
		ValueType& value,
		RB_COLOR_ENUM eColor=RED,
		NodeType* pParent=nullptr,
		NodeType* pLeft=nullptr,
		NodeType* pRight=nullptr);

	// Search the node
	NodeType* Search(KeyType& key);

	// Remove the node
	void Remove(NodeType* pNode);

	// Get prodromal node
	NodeType* GetProdromal(NodeType* pCurNode);

	// Get successor node
	NodeType* GetSuccessor(NodeType* pCurNode);

	// Delete node
	void DeleteNode(NodeType*& pNode);

	// Enter delete mode1: current node has two child
	void EnterDeleteMode1(NodeType*& pRoot,NodeType*& pNode);

	// Enter delete mode2: current node has only one child
	void EnterDeleteMode2(NodeType*& pRoot, NodeType*& pNode);

	// Enter delete mode3: current node has no any child
	void EnterDeleteMode3(NodeType*& pRoot, NodeType*& pNode);

private:
	// Get the disposed status
	inline bool GetDisposed() const
	{
		return m_bDisposed;
	}
	
	// Set the disposed status
	inline void SetDisposed(bool bDisposed)
	{
		m_bDisposed = bDisposed;
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

	// Get the Root
	inline NodeType*& GetRootNode() const
	{
		return m_pRoot;
	}

	// Set the Root
	inline void SetRootNode(NodeType* pRoot)
	{
		m_pRoot = pRoot;
	}

private:
	// Root node
	NodeType* m_pRoot;
	
	// Error message
	std::string m_strErrorText;
	
	// Disposed status
	bool m_bDisposed;	
};

/**********Implement section*************/

// Construct the RBTree
template <class T1, class T2>
RBTree<T1,T2>::RBTree():
	m_pRoot(nullptr),
	m_strErrorText(""),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the RBTree
template <class T1, class T2>
RBTree<T1, T2>::~RBTree()
{
	Destory();
}

// Initialize the tree
template <class T1, class T2>
void RBTree<T1, T2>::Initialize()
{

}

// Destory the tree
template <class T1, class T2>
void RBTree<T1, T2>::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		DestoryNode(GetRootNode());
	}
}

// Destory node
template <class T1, class T2>
void RBTree<T1, T2>::DestoryNode(NodeType* pNode)
{
	if (pNode==nullptr)
	{
		return;
	}

	if (pNode->pLeft != nullptr)
	{
		DestoryNode(pNode->pLeft);
	}
	else if (pNode->pRight != nullptr)
	{
		DestoryNode(pNode->pRight);
	}

	delete pNode;

	pNode = nullptr;
}

// Insert fixup
template <class T1, class T2>
void RBTree<T1, T2>::InsertFixup(NodeType* pRoot, NodeType* pCurNode)
{

}

// Remove fixup
template <class T1, class T2>
void RBTree<T1, T2>::RemoveFixup(NodeType* pRoot, NodeType* pCurNode)
{

}

// Get min node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::GetMinNode(NodeType* pNode)
{
	if (pNode==nullptr)
	{
		return nullptr;
	}

	while (pNode->pLeft !=nullptr)
	{
		pNode = pNode->pLeft;
	}

	return pNode;
}

// Get max node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::GetMaxNode(NodeType* pNode)
{
	if (pNode == nullptr)
	{
		return nullptr;
	}

	while (pNode->pRight != nullptr)
	{
		pNode = pNode->pRight;
	}

	return pNode;
}

// Max node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::Maximum()
{
	return GetMaxNode(GetRootNode());
}

// Minimize node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::Minimum()
{
	return GetMinNode(GetRootNode());
}

// Create node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::CreateNode(KeyType& key,
	ValueType& value,
	RB_COLOR_ENUM eColor,
	NodeType* pParent,
	NodeType* pLeft,
	NodeType* pRight)
{
	NodeType* pNode = new NodeType();	
	if (pNode != nullptr)
	{
		pNode->key = key;

		pNode->value = value;

		pNode->color = eColor;

		pNode->pParent = pParent;

		pNode->pLeft = pLeft;

		pNode->pRight = pRight;
	}

	return pNode;
}

// Insert the key and value
template <class T1, class T2>
bool RBTree<T1, T2>::Insert(NodeType* pCurNode)
{

}

// Insert the key and value
template <class T1, class T2>
bool RBTree<T1, T2>::Insert(KeyType& key, ValueType& value)
{
	// Create a node
	NodeType* pNode = CreateNode(key, value);
	if (pNode==nullptr)
	{
		return false;
	}

	// Insert the data to the tree
	Insert(pNode);

	// Fix the tree to be balanced
	InsertFixup(GetRootNode(),pNode);

	return true;
}

// Search the key
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::Search(KeyType& key)
{

}

// Get prodromal node(in-order: left max node)
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::GetProdromal(NodeType* pCurNode)
{
	if (pCurNode==nullptr)
	{
		return nullptr;
	}

	if (pCurNode->pLeft!=nullptr)
	{
		return GetMaxNode(pCurNode->pLeft);
	}

	NodeType* pParent = pCurNode->pParent;

	while (pParent !=nullptr && (pCurNode== pParent->pLeft))
	{
		pCurNode = pParent;

		pParent = pCurNode->pParent;
	}

	return pParent;
}

// Get successor node(in-order: right min node)
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::GetSuccessor(NodeType* pCurNode)
{
	if (pCurNode == nullptr)
	{
		return nullptr;
	}

	if (pCurNode->pRight != nullptr)
	{
		return GetMinNode(pCurNode->pRight);
	}

	NodeType* pParent = pCurNode->pParent;

	while (pParent != nullptr && (pCurNode == pParent->pRight))
	{
		pCurNode = pParent;

		pParent = pCurNode->pParent;
	}

	return pParent;
}

// Delete node
template <class T1, class T2>
void RBTree<T1, T2>::DeleteNode(NodeType*& pNode)
{
	if (pNode!=nullptr)
	{
		delete pNode;

		pNode = nullptr;
	}
}

// Enter delete mode1: current node has two child
template <class T1, class T2>
void RBTree<T1, T2>::EnterDeleteMode1(NodeType*& pRoot, NodeType*& pNode)
{
	if (pRoot == nullptr || pNode == nullptr)
	{
		return;
	}

	// If the node's color is red, it is no need to fixup the tree
	if (pNode->color == BLACK)
	{
		RemoveFixup(pRoot, pNode);
	}

	// Delete the node
	DeleteNode(pNode);
}

// Enter delete mode2: current node has only one child
template <class T1, class T2>
void RBTree<T1, T2>::EnterDeleteMode2(NodeType*& pRoot, NodeType*& pNode)
{
	if (pRoot==nullptr || pNode==nullptr)
	{
		return;
	}

	// Get current node's child
	NodeType* pChild = nullptr;

	if (pNode->pLeft != nullptr)
	{
		pChild = pNode->pLeft;
	}
	else
	{
		pChild = pNode->pRight;
	}

	// Get current node's parent
	NodeType* pParent = pRoot;

	if (pNode->pParent != nullptr)
	{
		pParent = pNode->pParent;
	}

	// Change this child's parent
	pChild->pParent = pParent;

	if (pNode == pParent->pLeft)
	{
		pParent->pLeft = pChild;
	}
	else
	{
		pParent->pRight = pChild;
	}

	// If the node's color is red, it is no need to fixup the tree
	if (pNode->color == BLACK)
	{
		RemoveFixup(pRoot, pNode);
	}

	// Delete the node
	DeleteNode(pNode);
}

// Enter delete mode3: current node has no any child
template <class T1, class T2>
void RBTree<T1, T2>::EnterDeleteMode3(NodeType*& pRoot, NodeType*& pNode)
{
	if (pRoot == nullptr || pNode == nullptr)
	{
		return;
	}

	// If the node's color is red, it is no need to fixup the tree
	if (pNode->color == BLACK)
	{
		RemoveFixup(pRoot, pNode);
	}

	// Delete the node
	DeleteNode(pNode);
}

// Remove the node
template <class T1, class T2>
void RBTree<T1, T2>::Remove(NodeType* pNode)
{
	if (pNode==nullptr)
	{
		return;
	}

	NodeType* pRoot = GetRootNode();

	// Deleted node has two children
	if (pNode->pLeft!=nullptr && pNode->pRight!=nullptr)
	{
		EnterDeleteMode1(pRoot, pNode);

		return;
	}

	// Deleted node has one child
	if (pNode->pLeft!=nullptr || pNode->pRight!=nullptr)
	{
		EnterDeleteMode2(pRoot, pNode);
	}
	else // Deleted node has no child
	{
		EnterDeleteMode3(pRoot, pNode);
	}
}

// Remove the key
template <class T1, class T2>
void RBTree<T1, T2>::Remove(KeyType& key)
{
	// Search the node with key
	NodeType* pNode = Search(key);

	// Remove the node
	if (!Remove(pNode))
	{
		return;
	}

	// Fix the tree to be balanced again
	RemoveFixup(GetRootNode(), pNode);
}

// Search the key
template <class T1, class T2>
bool RBTree<T1, T2>::Search(KeyType& key, ValueType& value)
{

}

// Modify the key's data
template <class T1, class T2>
bool RBTree<T1, T2>::Modify(KeyType& key, ValueType& value)
{

}

// Get the error message
template <class T1, class T2>
std::string RBTree<T1, T2>::GetErrorMsg()
{
	return GetErrorText();
}

#endif // RBTREE_H
