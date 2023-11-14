#include "RedBlackTree.h"

// Метод возвращает значение минимального элемента дерева
int RedBlackTree::minElem() const
{
	if (!isEmpty())
	{
		return privateMin(root)->key;
	}
	return CODE_ERROR;
}

// Метод возвращает указатель на минимальный элемент дерева
RbNode* RedBlackTree::privateMin(RbNode* iter) const
{
	while (iter->left)
	{
		iter = iter->left;
	}
	return iter;
}


// Метод возвращает значение максимального элемента дерева
int RedBlackTree::maxElem() const
{
	if (!isEmpty())
	{
		return privateMax(root)->key;
	}
	return CODE_ERROR;
}

// Метод возвращает указатель на максимальный элемент дерева
RbNode* RedBlackTree::privateMax(RbNode* iter) const
{
	while (iter->right)
	{
		iter = iter->right;
	}
	return iter;
}


// Метод выводит элементы всего дерева в виде дерева
// Центрированный (симметричный) обход дерева
void RedBlackTree::print(bool equalElem, string message) const
{
	cout << message;
	privatePrint(root, equalElem);
}

// Метод выводит элементы поддерева в виде дерева
// Центрированный (симметричный) обход поддерева
void RedBlackTree::privatePrint(const RbNode* const node, bool equalElem, int indent) const
{
	if (!node)
	{
		return;
	}

	privatePrint(node->right, equalElem, indent + 4);

	cout << setw(indent) << " ";
	if (node->right)
	{
		cout << " /\n" << setw(indent) << " ";
	}
	cout << node->key << (node->color == RED ? " (R)" : " (B)") << "\n ";
	if (node->left)
	{
		cout << setw(indent) << " " << " \\\n";
	}

	privatePrint(node->left, equalElem, indent + 4);
}


// Метод выводит элементы всего дерева в отсортированном порядке
// Центрированный (симметричный) обход дерева
void RedBlackTree::inorderPrint(bool equalElem, string message) const
{
	cout << message;
	privateInorder(root, equalElem);
}

// Метод выводит элементы поддерева в отсортированном порядке
// Центрированный (симметричный) обход поддерева
void RedBlackTree::privateInorder(const RbNode* const node, bool equalElem) const
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
void RedBlackTree::preorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePreorder(root, equalElem);
}

// Метод выводит элементы поддерева в порядке: вершина, левое поддерево, правое поддерево
// Обход поддерева в прямом порядке
void RedBlackTree::privatePreorder(const RbNode* const node, bool equalElem) const
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
void RedBlackTree::postorderPrint(bool equalElem, string message) const
{
	cout << message;
	privatePostorder(root, equalElem);
}

// Метод выводит элементы поддерева в порядке: левое поддерево, правое поддерево, вершина
// Обход поддерева в обратном порядке
void RedBlackTree::privatePostorder(const RbNode* const node, bool equalElem) const
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
void RedBlackTree::clear()
{
	privateClear(root);
}

// Метод удаляет только элементы поддерева. 
// Обход поддерева в обратном порядке
void RedBlackTree::privateClear(RbNode*& node)
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
int RedBlackTree::prev(int key) const
{
	RbNode* node = privateSearch(key);
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
RbNode* RedBlackTree::privatePrev(RbNode* node) const
{
	if (node->left)
	{
		return privateMax(node->left);
	}

	RbNode* iter = node->parent;
	while (iter && node == iter->left)
	{
		node = iter;
		iter = iter->parent;
	}
	return iter;
}


// Метод возврашает значение следующего элемента
int RedBlackTree::next(int key) const
{
	RbNode* node = privateSearch(key);
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
RbNode* RedBlackTree::privateNext(RbNode* node) const
{
	if (node->right)
	{
		return privateMin(node->right);
	}

	RbNode* iter = node->parent;
	while (iter && node == iter->right)
	{
		node = iter;
		iter = iter->parent;
	}
	return iter;
}


// Метод возвращает количество элементов в дереве
int RedBlackTree::search(int key) const
{
	RbNode* node = privateSearch(key);
	if (node)
	{
		return node->getCountKey();
	}
	return 0;
}

// Метод возвращает указатель на найденный элемент
RbNode* RedBlackTree::privateSearch(int key) const
{
	RbNode* iter = root;
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
void RedBlackTree::insert(int key)
{
	RbNode* new_node = new RbNode(key, RED);

	RbNode* parent = nullptr;
	RbNode* current = root;
	while (current) 
	{
		parent = current;
		if (key < current->key) 
		{
			current = current->left;
		}
		else 
		{
			current = current->right;
		}
	}

	new_node->parent = parent;
	if (!parent) 
	{
		root = new_node;
		countNodes++;
	}
	else if (key < parent->key) 
	{
		parent->left = new_node;
		countNodes++;
	}
	else if (key > parent->key)
	{
		parent->right = new_node;
		countNodes++;
	}
	else
	{
		parent->countKeys++;
	}

	fixInsert(new_node);
}

void RedBlackTree::rotateLeft(RbNode*& node) 
{
	RbNode* newRoot = node->right;
	node->right = newRoot->left;
	if (node->right)
	{
		node->right->parent = node;
	}
	newRoot->parent = node->parent;
	if (!node->parent)
	{
		this->root = newRoot;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = newRoot;
	}
	else {
		node->parent->right = newRoot;
	}
	newRoot->left = node;
	node->parent = newRoot;
}

void RedBlackTree::rotateRight(RbNode*& node)
{
	RbNode* newRoot = node->left;
	node->left = newRoot->right;
	if (node->left)
	{
		node->left->parent = node;
	}
	newRoot->parent = node->parent;
	if (!node->parent)
	{
		this->root = newRoot;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = newRoot;
	}
	else 
	{
		node->parent->right = newRoot;
	}
	newRoot->right = node;
	node->parent = newRoot;
}

void RedBlackTree::fixInsert(RbNode*& node)
{
	RbNode* parent = nullptr;
	RbNode* grandparent = nullptr;
	while ((node != this->root) && (node->color != BLACK) && (node->parent->color == RED))
	{
		parent = node->parent;
		grandparent = node->parent->parent;
		if (parent == grandparent->left) 
		{
			RbNode* uncle = grandparent->right;
			if (uncle != nullptr && uncle->color == RED) 
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandparent;
			}
			else 
			{
				if (node == parent->right)
				{
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				rotateRight(grandparent);
				Swap(parent->color, grandparent->color);
				node = parent;
			}
		}
		else 
		{
			RbNode* uncle = grandparent->left;
			if ((uncle != nullptr) && (uncle->color == RED)) 
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandparent;
			}
			else 
			{
				if (node == parent->left)
				{
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				rotateLeft(grandparent);
				Swap(parent->color, grandparent->color);
				node = parent;
			}
		}
	}
	this->root->color = BLACK;
}


// Метод удаляет один элемент дерева по его значению
void RedBlackTree::delElem(int key)
{
	RbNode* node = privateSearch(key);
	if (node)
	{
		privateDelElem(node);
	}
}

// Метод удаляет один элемент дерева по указателю на него
void RedBlackTree::privateDelElem(RbNode* node)
{
	// Нельзя использовать
	RbNode* delNode, * temp;

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

bool RedBlackTree::fillTree(const int size, const int fillMode)
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


int RedBlackTree::getHeight() const
{
	return getHeight(root);
}

int RedBlackTree::getHeight(RbNode* node) const
{
	if (!node)
	{
		return 0;
	}
	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);
	return 1 + max(leftHeight, rightHeight);
}