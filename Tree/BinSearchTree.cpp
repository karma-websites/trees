#include "BinSearchTree.h"


// Метод возвращает значение минимального элемента дерева
int BinSearchTree::minElem() const
{
	if (!isEmpty())
	{
		return privateMin(root)->key;
	}
	return CODE_ERROR;
}

// Метод возвращает указатель на минимальный элемент дерева
BsNode* BinSearchTree::privateMin(BsNode* iter) const
{
	while (iter->left)
	{
		iter = iter->left;
	}
	return iter;
}


// Метод возвращает значение максимального элемента дерева
int BinSearchTree::maxElem() const
{
	if (!isEmpty())
	{
		return privateMax(root)->key;
	}
	return CODE_ERROR;
}

// Метод возвращает указатель на максимальный элемент дерева
BsNode* BinSearchTree::privateMax(BsNode* iter) const
{
	while (iter->right)
	{
		iter = iter->right;
	}
	return iter;
}


// Метод выводит элементы всего дерева в виде дерева
// Центрированный (симметричный) обход дерева
void BinSearchTree::print(bool equalElem, string message) const
{
	cout << message;
	privatePrint(root, equalElem);
}

// Метод выводит элементы поддерева в виде дерева
// Центрированный (симметричный) обход поддерева
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


// Метод выводит элементы всего дерева в отсортированном порядке
// Центрированный (симметричный) обход дерева
void BinSearchTree::inorderPrint(bool equalElem, string message) const
{
	cout << message;
	privateInorder(root, equalElem);
}

// Метод выводит элементы поддерева в отсортированном порядке
// Центрированный (симметричный) обход поддерева
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


// Метод выводит элементы всего дерева в порядке: вершина, левое поддерево, правое поддерево,
// Обход дерева в прямом порядке
void BinSearchTree::preorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePreorder(root, equalElem);
}

// Метод выводит элементы поддерева в порядке: вершина, левое поддерево, правое поддерево
// Обход поддерева в прямом порядке
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


// Метод выводит элементы всего дерева в порядке: левое поддерево, правое поддерево, вершина
// Обход дерева в обратном порядке
void BinSearchTree::postorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePostorder(root, equalElem);
}

// Метод выводит элементы поддерева в порядке: левое поддерево, правое поддерево, вершина
// Обход поддерева в обратном порядке
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


// Метод удаляет все элементы дерева
// Обход поддерева в обратном порядке
void BinSearchTree::clear()
{
	privateClear(root);
}

// Метод удаляет только элементы поддерева. 
// Обход поддерева в обратном порядке
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


// Метод возврашает значение предыдущего элемента
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

// Метод возврашает указатель на предыдущий элемент
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


// Метод возврашает значение следующего элемента
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

// Метод возврашает указатель на следующий элемент
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


// Метод возвращает количество элементов в дереве
int BinSearchTree::search(int key) const
{
	BsNode* node = privateSearch(key);
	if (node)
	{
		return node->getCountKey();
	}
	return 0;
}

// Метод возвращает указатель на найденный элемент
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


// Метод производит вставку элемента в дерево
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


// Метод удаляет один элемент дерева по его значению
void BinSearchTree::delElem(int key)
{
	BsNode* node = privateSearch(key);
	if (node)
	{
		privateDelElem(node);
	}
}

// Метод удаляет один элемент дерева по указателю на него
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
		cout << "Ошибка: выбранного режима не существует." << endl;
		return false;
	}
	return true;
}