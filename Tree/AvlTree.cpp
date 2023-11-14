#include "AvlTree.h"

// Метод возвращает значение минимального элемента дерева
int AvlTree::minElem() const
{
	if (!isEmpty())
	{
		return privateMin(root)->key;
	}
	return CODE_ERROR;
}

// Метод возвращает указатель на минимальный элемент дерева
AvlNode* AvlTree::privateMin(AvlNode* iter) const
{
	while (iter->left)
	{
		iter = iter->left;
	}
	return iter;
}


// Метод возвращает значение максимального элемента дерева
int AvlTree::maxElem() const
{
	if (!isEmpty())
	{
		return privateMax(root)->key;
	}
	return CODE_ERROR;
}

// Метод возвращает указатель на максимальный элемент дерева
AvlNode* AvlTree::privateMax(AvlNode* iter) const
{
	while (iter->right)
	{
		iter = iter->right;
	}
	return iter;
}


// Метод выводит элементы всего дерева в виде дерева
// Центрированный (симметричный) обход дерева
void AvlTree::print(bool equalElem, string message) const
{
	cout << message;
	privatePrint(root, equalElem);
}

// Метод выводит элементы поддерева в виде дерева
// Центрированный (симметричный) обход поддерева
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


// Метод выводит элементы всего дерева в отсортированном порядке
// Центрированный (симметричный) обход дерева
void AvlTree::inorderPrint(bool equalElem, string message) const
{
	cout << message;
	privateInorder(root, equalElem);
}

// Метод выводит элементы поддерева в отсортированном порядке
// Центрированный (симметричный) обход поддерева
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


// Метод выводит элементы всего дерева в порядке: вершина, левое поддерево, правое поддерево,
// Обход дерева в прямом порядке
void AvlTree::preorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePreorder(root, equalElem);
}

// Метод выводит элементы поддерева в порядке: вершина, левое поддерево, правое поддерево
// Обход поддерева в прямом порядке
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


// Метод выводит элементы всего дерева в порядке: левое поддерево, правое поддерево, вершина
// Обход дерева в обратном порядке
void AvlTree::postorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePostorder(root, equalElem);
}

// Метод выводит элементы поддерева в порядке: левое поддерево, правое поддерево, вершина
// Обход поддерева в обратном порядке
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


// Метод удаляет все элементы дерева
// Обход поддерева в обратном порядке
void AvlTree::clear()
{
	privateClear(root);
}

// Метод удаляет только элементы поддерева. 
// Обход поддерева в обратном порядке
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


// Метод возврашает значение предыдущего элемента
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

// Метод возврашает указатель на предыдущий элемент
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


// Метод возврашает значение следующего элемента
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

// Метод возврашает указатель на следующий элемент
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


// Метод возвращает количество элементов в дереве
int AvlTree::search(int key) const
{
	AvlNode* node = privateSearch(key);
	if (node)
	{
		return node->getCountKey();
	}
	return 0;
}

// Метод возвращает указатель на найденный элемент
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

// Метод производит вставку элемента в дерево
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


// Метод удаляет один элемент дерева по его значению
void AvlTree::delElem(int key)
{
	root = privateDelElem(root, key);
}

// Метод удаляет один элемент дерева по указателю на него
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
		cout << "Ошибка: выбранного режима не существует." << endl;
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