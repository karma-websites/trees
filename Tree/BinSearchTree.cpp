#include "BinSearchTree.h"


// ����� ���������� �������� ������������ �������� ������
int BinSearchTree::minElem() const
{
	if (!isEmpty())
	{
		return privateMin(root)->key;
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ����������� ������� ������
BsNode* BinSearchTree::privateMin(BsNode* iter) const
{
	while (iter->left)
	{
		iter = iter->left;
	}
	return iter;
}


// ����� ���������� �������� ������������� �������� ������
int BinSearchTree::maxElem() const
{
	if (!isEmpty())
	{
		return privateMax(root)->key;
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ������������ ������� ������
BsNode* BinSearchTree::privateMax(BsNode* iter) const
{
	while (iter->right)
	{
		iter = iter->right;
	}
	return iter;
}


// ����� ������� �������� ����� ������ � ���� ������
// �������������� (������������) ����� ������
void BinSearchTree::print(bool equalElem, string message) const
{
	cout << message;
	privatePrint(root, equalElem);
}

// ����� ������� �������� ��������� � ���� ������
// �������������� (������������) ����� ���������
void BinSearchTree::privatePrint(const BsNode* const node, bool equalElem) const
{
	static int tabs = 0;

	if (!node)
	{
		return;
	}

	tabs += 10;

	privatePrint(node->right, equalElem);

	for (size_t i = 0; i < tabs; i++)
	{
		cout << " ";
	}
	cout << node->key << " ";

	if (equalElem)
	{
		cout << "[" << node->getCountKey() << "] ";
	}
	cout << "-" << endl;

	privatePrint(node->left, equalElem);

	tabs -= 10;
}


// ����� ������� �������� ����� ������ � ��������������� �������
// �������������� (������������) ����� ������
void BinSearchTree::inorderPrint(bool equalElem, string message) const
{
	cout << message;
	privateInorder(root, equalElem);
}

// ����� ������� �������� ��������� � ��������������� �������
// �������������� (������������) ����� ���������
void BinSearchTree::privateInorder(const BsNode* const node, bool equalElem) const
{
	if (!node)
	{
		return;
	}

	privateInorder(node->left, equalElem);

	cout << node->key << " ";
	if (equalElem)
	{
		cout << "[" << node->getCountKey() << "] ";
	}

	privateInorder(node->right, equalElem);
}


// ����� ������� �������� ����� ������ � �������: �������, ����� ���������, ������ ���������,
// ����� ������ � ������ �������
void BinSearchTree::preorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePreorder(root, equalElem);
}

// ����� ������� �������� ��������� � �������: �������, ����� ���������, ������ ���������
// ����� ��������� � ������ �������
void BinSearchTree::privatePreorder(const BsNode* const node, bool equalElem) const
{
	if (!node)
	{
		return;
	}

	cout << node->key << " ";
	if (equalElem)
	{
		cout << "[" << node->getCountKey() << "] ";
	}

	privateInorder(node->left, equalElem);
	privateInorder(node->right, equalElem);
}


// ����� ������� �������� ����� ������ � �������: ����� ���������, ������ ���������, �������
// ����� ������ � �������� �������
void BinSearchTree::postorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePostorder(root, equalElem);
}

// ����� ������� �������� ��������� � �������: ����� ���������, ������ ���������, �������
// ����� ��������� � �������� �������
void BinSearchTree::privatePostorder(const BsNode* const node, bool equalElem) const
{
	if (!node)
	{
		return;
	}

	privateInorder(node->left, equalElem);
	privateInorder(node->right, equalElem);

	cout << node->key << " ";
	if (equalElem)
	{
		cout << "[" << node->getCountKey() << "] ";
	}
}


// ����� ������� ��� �������� ������
// ����� ��������� � �������� �������
void BinSearchTree::clear()
{
	privateClear(root);
}

// ����� ������� ������ �������� ���������. 
// ����� ��������� � �������� �������
void BinSearchTree::privateClear(BsNode*& node)
{
	if (!node)
	{
		return;
	}

	privateClear(node->left);
	privateClear(node->right);

	delete node;
	node = nullptr;
	countNodes--;
}


// ����� ���������� �������� ����������� ��������
int BinSearchTree::prev(int key) const
{
	BsNode* node = privateSearch(key);
	if (node)
	{
		node = privatePrev(node);
		if (node)
		{
			return node->key;
		}
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ���������� �������
BsNode* BinSearchTree::privatePrev(BsNode* node) const
{
	if (node->left)
	{
		return privateMax(node->left);
	}

	BsNode* iter = node->parent;
	while (iter && node == iter->left)
	{
		node = iter;
		iter = iter->parent;
	}
	return iter;
}


// ����� ���������� �������� ���������� ��������
int BinSearchTree::next(int key) const
{
	BsNode* node = privateSearch(key);
	if (node)
	{
		node = privateNext(node);
		if (node)
		{
			return node->key;
		}
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ��������� �������
BsNode* BinSearchTree::privateNext(BsNode* node) const
{
	if (node->right)
	{
		return privateMin(node->right);
	}

	BsNode* iter = node->parent;
	while (iter && node == iter->right)
	{
		node = iter;
		iter = iter->parent;
	}
	return iter;
}


// ����� ���������� ���������� ��������� � ������
int BinSearchTree::search(int key) const
{
	BsNode* node = privateSearch(key);
	if (node)
	{
		return node->getCountKey();
	}
	return 0;
}

// ����� ���������� ��������� �� ��������� �������
BsNode* BinSearchTree::privateSearch(int key) const
{
	BsNode* iter = root;
	while (iter && key != iter->key)
	{
		if (key < iter->key)
		{
			iter = iter->left;
		}
		else
		{
			iter = iter->right;
		}
	}
	return iter;
}


// ����� ���������� ������� �������� � ������
void BinSearchTree::insert(int key)
{
	BsNode* iter = root;

	if (!iter)
	{
		root = new BsNode(key);
	}

	while (iter)
	{
		if (key == iter->key)
		{
			iter->countKeys++;
			break;
		}
		else if (key < iter->key)
		{
			if (iter->left)
			{
				iter = iter->left;
			}
			else
			{
				iter->left = new BsNode(key, iter);
				countNodes++;
				break;
			}
		}
		else
		{
			if (iter->right)
			{
				iter = iter->right;
			}
			else
			{
				iter->right = new BsNode(key, iter);
				countNodes++;
				break;
			}
		}
	}
}


// ����� ������� ���� ������� ������ �� ��� ��������
void BinSearchTree::delElem(int key)
{
	BsNode* node = privateSearch(key);
	if (node)
	{
		privateDelElem(node);
	}
}

// ����� ������� ���� ������� ������ �� ��������� �� ����
void BinSearchTree::privateDelElem(BsNode* node)
{
	BsNode* delNode, * temp;

	if (!node->left || !node->right)
		delNode = node;
	else
		delNode = privateNext(node);

	if (delNode->left)
		temp = delNode->left;
	else
		temp = delNode->right;

	if (temp)
		temp->parent = delNode->parent;

	if (!delNode->parent)
		root = temp;
	else if (delNode == delNode->parent->left)
		delNode->parent->left = temp;
	else
		delNode->parent->right = temp;

	if (delNode != node)
		node->key = delNode->key;

	delete delNode;
	countNodes--;
}

int BinSearchTree::getHeight() const
{
	return getHeight(root);
}

int BinSearchTree::getHeight(BsNode* node) const
{
	if (!node)
	{
		return 0;
	}
	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);
	return 1 + max(leftHeight, rightHeight);
}

bool BinSearchTree::fillTree(const int size, const int fillMode)
{
	switch (fillMode)
	{
	case 0:
		for (size_t i = 0; i < size; ++i)
		{
			insert(i);
		}
		break;
	case 1:
		for (size_t i = 0; i < size; ++i)
		{
			insert(rand());
		}
		break;
	default:
		cout << "������: ���������� ������ �� ����������." << endl;
		return false;
	}
	return true;
}