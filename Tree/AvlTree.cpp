#include "AvlTree.h"

// ����� ���������� �������� ������������ �������� ������
int AvlTree::minElem() const
{
	if (!isEmpty())
	{
		return privateMin(root)->key;
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ����������� ������� ������
AvlNode* AvlTree::privateMin(AvlNode* iter) const
{
	while (iter->left)
	{
		iter = iter->left;
	}
	return iter;
}


// ����� ���������� �������� ������������� �������� ������
int AvlTree::maxElem() const
{
	if (!isEmpty())
	{
		return privateMax(root)->key;
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ������������ ������� ������
AvlNode* AvlTree::privateMax(AvlNode* iter) const
{
	while (iter->right)
	{
		iter = iter->right;
	}
	return iter;
}


// ����� ������� �������� ����� ������ � ���� ������
// �������������� (������������) ����� ������
void AvlTree::print(bool equalElem, string message) const
{
	cout << message;
	privatePrint(root, equalElem);
}

// ����� ������� �������� ��������� � ���� ������
// �������������� (������������) ����� ���������
void AvlTree::privatePrint(const AvlNode* const node, bool equalElem) const
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
void AvlTree::inorderPrint(bool equalElem, string message) const
{
	cout << message;
	privateInorder(root, equalElem);
}

// ����� ������� �������� ��������� � ��������������� �������
// �������������� (������������) ����� ���������
void AvlTree::privateInorder(const AvlNode* const node, bool equalElem) const
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
void AvlTree::preorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePreorder(root, equalElem);
}

// ����� ������� �������� ��������� � �������: �������, ����� ���������, ������ ���������
// ����� ��������� � ������ �������
void AvlTree::privatePreorder(const AvlNode* const node, bool equalElem) const
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
void AvlTree::postorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePostorder(root, equalElem);
}

// ����� ������� �������� ��������� � �������: ����� ���������, ������ ���������, �������
// ����� ��������� � �������� �������
void AvlTree::privatePostorder(const AvlNode* const node, bool equalElem) const
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
void AvlTree::clear()
{
	privateClear(root);
}

// ����� ������� ������ �������� ���������. 
// ����� ��������� � �������� �������
void AvlTree::privateClear(AvlNode*& node)
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
int AvlTree::prev(int key) const
{
	AvlNode* node = privateSearch(key);
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
AvlNode* AvlTree::privatePrev(AvlNode* node) const
{
	if (node->left)
	{
		return privateMax(node->left);
	}

	/*AvlNode* iter = node->parent;
	while (iter && node == iter->left)
	{
		node = iter;
		iter = iter->parent;
	}

	return iter;*/
}


// ����� ���������� �������� ���������� ��������
int AvlTree::next(int key) const
{
	AvlNode* node = privateSearch(key);
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
AvlNode* AvlTree::privateNext(AvlNode* node) const
{
	if (node->right)
	{
		return privateMin(node->right);
	}

	/*AvlNode* iter = node->parent;
	while (iter && node == iter->right)
	{
		node = iter;
		iter = iter->parent;
	}

	return iter;*/
}


// ����� ���������� ���������� ��������� � ������
int AvlTree::search(int key) const
{
	AvlNode* node = privateSearch(key);
	if (node)
	{
		return node->getCountKey();
	}
	return 0;
}

// ����� ���������� ��������� �� ��������� �������
AvlNode* AvlTree::privateSearch(int key) const
{
	AvlNode* iter = root;
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


void AvlTree::updateHeight(AvlNode* const node) const
{
	node->height = 1 + Max(getHeight(node->left), getHeight(node->right));
}

int AvlTree::getHeight(const AvlNode* const node) const
{
	return (node == nullptr) ? -1 : node->height;
}

int AvlTree::getBalance(const AvlNode* const node) const
{
	return (node == nullptr) ? 0 : getHeight(node->right) - getHeight(node->left);
}

void AvlTree::rightRotate(AvlNode* const node) const
{
	Swap(node->key, node->left->key);
	AvlNode* buffer = node->right;
	node->right = node->left;
	node->left = node->right->left;
	node->right->left = node->right->right;
	node->right->right = buffer;
	updateHeight(node->right);
	updateHeight(node);
}

void AvlTree::leftRotate(AvlNode* const node) const
{
	Swap(node->key, node->right->key);
	AvlNode* buffer = node->left;
	node->left = node->right;
	node->right = node->left->right;
	node->left->right = node->left->left;
	node->left->left = buffer;
	updateHeight(node->left);
	updateHeight(node);
}

void AvlTree::balance(AvlNode* const node) const
{
	int balance = getBalance(node);
	if (balance == -2)
	{
		if (getBalance(node->left) == 1)
		{
			leftRotate(node->left);
		}
		rightRotate(node);
	}
	else if (balance == 2)
	{
		if (getBalance(node->right) == -1)
		{
			rightRotate(node->right);
		}
		leftRotate(node);
	}
}

// ����� ���������� ������� �������� � ������
void AvlTree::insert(int key)
{
	privateInsert(root, key);
}

void AvlTree::privateInsert(AvlNode*& iter, int key)
{
	if (!iter)
	{
		countNodes++;
		iter = new AvlNode(key);
	}
	else if (key < iter->key)
	{
		privateInsert(iter->left, key);
	}
	else if (key > iter->key)
	{
		privateInsert(iter->right, key);
	}
	else
	{
		iter->countKeys++;
	}
	updateHeight(iter);
	balance(iter);
}


// ����� ������� ���� ������� ������ �� ��� ��������
void AvlTree::delElem(int key)
{
	root = privateDelElem(root, key);
}

// ����� ������� ���� ������� ������ �� ��������� �� ����
AvlNode* AvlTree::privateDelElem(AvlNode* iter, int key)
{
	if (!iter)
	{
		return nullptr;
	}
	else if (key < iter->key)
	{
		iter->left = privateDelElem(iter->left, key);
	}
	else if (key > iter->key)
	{
		iter->right = privateDelElem(iter->right, key);
	}
	else
	{
		if (!iter->left || !iter->right)
		{
			AvlNode* temp = iter;
			iter = (iter->left == nullptr) ? iter->right : iter->left;
			countNodes--;
			delete temp;
		}
		else
		{
			AvlNode* maxLeft = privateMax(iter->left);
			iter->key = maxLeft->key;
			iter->left = privateDelElem(iter->left, maxLeft->key);
		}
	}
	if (iter)
	{
		updateHeight(iter);
		balance(iter);
	}
	return iter;
}

bool AvlTree::fillTree(const int size, const int fillMode)
{
	switch (fillMode)
	{
	case 0:
		for (int i = 0; i < size; ++i)
		{
			insert(i + 10);
		}
		break;
	case 1:
		for (int i = 0; i < size; ++i)
		{
			insert(rand() % 100 + 10);
		}
		break;
	default:
		cout << "������: ���������� ������ �� ����������." << endl;
		return false;
	}
	return true;
}

int AvlTree::getHeightTree() const
{
	return getHeightTree(root);
}

int AvlTree::getHeightTree(AvlNode* node) const
{
	if (!node)
	{
		return 0;
	}
	int leftHeight = getHeightTree(node->left);
	int rightHeight = getHeightTree(node->right);
	return 1 + Max(leftHeight, rightHeight);

}