#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <queue>

#include "Constants.h"

using namespace std;


/*
	���������� ���������� ������
*/

template <class T>
class Tree
{
public:

	Tree() : root(nullptr), countNodes(0) {}
	~Tree()
	{ 
		deleteTreeOptim();
	}

	// ����� ���������� ������ ���������� ��� ���������������� �������
	bool fillTree(const int size, const int fillMode);

	// ������ ������� � �������� �������� ������
	virtual void insertElem(const int key) = 0;
	virtual void deleteElem(const int key) = 0;

	// ������ ������ ������ �� �����
	void print(bool equalElem = false, string message = "") const;
	void widthPrint(bool equalElem = false, string message = "") const;
	void inorderPrint(bool equalElem = false, string message = "") const;
	void preorderPrint(bool equalElem = false, string message = "") const;
	void postorderPrint(bool equalElem = false, string message = "") const;

	// ��������������� ������ ������ � �������
	int minElem() const;
	int maxElem() const;
	int prevElem(const int key) const;
	int nextElem(const int key) const;
	int searchElem(const int key) const;
	bool isEmpty() const { return root == nullptr; }
	int getCountNodes() const { return countNodes; }
	int getHeight() const { return getHeight(root); }

	// ������ �������� ���� ��������� ������
	void deleteTree();
	void deleteTreeOptim();

protected:

	T* root;
	int countNodes;

	// ��������������� ������ ������ � �������
	T* prevElem(T* node) const;
	T* nextElem(T* node) const;
	T* minElem(T* iter) const;
	T* maxElem(T* iter) const;
	T* searchElem(T* iter, const int key) const;
	int getHeight(T* node) const;

	int Max(const int& a, const int& b) const { return (a > b) ? a : b; }
	template <typename T>
	void Swap(T& a, T& b) const { T temp = a; a = b; b = temp; }

	// ������ ������ ������ �� �����
	void print(const T* const node, bool equalElem) const;
	void widthPrint(T* const node, bool equalElem) const;
	void inorderPrint(const T* const node, bool equalElem) const;
	void preorderPrint(const T* const node, bool equalElem) const;
	void postorderPrint(const T* const node, bool equalElem) const;

	// ����� �������� ���� ��������� ������
	void deleteTree(T*& node);
	void deleteTreeOptim(T*& node);
};


/*
	����������� ���������� ������
*/

// ����� ���������� �������� ������������ �������� ������
template<typename T>
int Tree<T>::minElem() const
{
	if (!isEmpty())
	{
		return minElem(this->root)->key;
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ����������� ������� ������
template<typename T>
T* Tree<T>::minElem(T* iter) const
{
	while (iter->left)
	{
		iter = iter->left;
	}
	return iter;
}


// ����� ���������� �������� ������������� �������� ������
template<typename T>
int Tree<T>::maxElem() const
{
	if (!isEmpty())
	{
		return maxElem(this->root)->key;
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ������������ ������� ������
template<typename T>
T* Tree<T>::maxElem(T* iter) const
{
	while (iter->right)
	{
		iter = iter->right;
	}
	return iter;
}


// ����� ������� �������� ����� ������ � ���� ������
// �������������� (������������) ����� ������
template<typename T>
void Tree<T>::print(bool equalElem, string message) const
{
	cout << message;
	print(this->root, equalElem);
	cout << endl;
}

// ����� ������� �������� ��������� � ���� ������
// �������������� (������������) ����� ���������
template<typename T>
void Tree<T>::print(const T* const node, bool equalElem) const
{
	static int tabs = 0;

	if (!node) return;

	tabs += 10;

	print(node->right, equalElem);

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

	print(node->left, equalElem);

	tabs -= 10;
}

// ����� ������ � ������
template<class T>
void Tree<T>::widthPrint(bool equalElem, string message) const
{
	cout << message;
	widthPrint(this->root, equalElem);
	cout << endl;
}

// ����� ��������� � ������
template<class T>
void Tree<T>::widthPrint(T* const node, bool equalElem) const
{
	if (!node) return;

	queue<T*> queue;
	queue.push(node);

	while (!queue.empty())
	{
		T* current = queue.front();
		cout << current->key << " ";
		if (equalElem)
		{
			cout << "[" << node->getCountKey() << "] ";
		}
		if (current->left)
		{
			queue.push(current->left);
		}
		if (current->right)
		{
			queue.push(current->right);
		}
		queue.pop();
	}
}


// ����� ������� �������� ����� ������ � ��������������� �������
// �������������� (������������) ����� ������
template<typename T>
void Tree<T>::inorderPrint(bool equalElem, string message) const
{
	cout << message;
	inorderPrint(this->root, equalElem);
	cout << endl;
}

// ����� ������� �������� ��������� � ��������������� �������
// �������������� (������������) ����� ���������
template<typename T>
void Tree<T>::inorderPrint(const T* const node, bool equalElem) const
{
	if (!node) return;

	inorderPrint(node->left, equalElem);

	cout << node->key << " ";
	if (equalElem)
	{
		cout << "[" << node->getCountKey() << "] ";
	}

	inorderPrint(node->right, equalElem);
}


// ����� ������� �������� ����� ������ � �������: �������, ����� ���������, ������ ���������,
// ����� ������ � ������ �������
template<typename T>
void Tree<T>::preorderPrint(bool equalElem, string message) const
{
	cout << message;
	preorderPrint(this->root, equalElem);
	cout << endl;
}

// ����� ������� �������� ��������� � �������: �������, ����� ���������, ������ ���������
// ����� ��������� � ������ �������
template<typename T>
void Tree<T>::preorderPrint(const T* const node, bool equalElem) const
{
	if (!node) return;

	cout << node->key << " ";
	if (equalElem)
	{
		cout << "[" << node->getCountKey() << "] ";
	}

	preorderPrint(node->left, equalElem);
	preorderPrint(node->right, equalElem);
}


// ����� ������� �������� ����� ������ � �������: ����� ���������, ������ ���������, �������
// ����� ������ � �������� �������
template<typename T>
void Tree<T>::postorderPrint(bool equalElem, string message) const
{
	cout << message;
	postorderPrint(this->root, equalElem);
	cout << endl;
}

// ����� ������� �������� ��������� � �������: ����� ���������, ������ ���������, �������
// ����� ��������� � �������� �������
template<typename T>
void Tree<T>::postorderPrint(const T* const node, bool equalElem) const
{
	if (!node) return;

	postorderPrint(node->left, equalElem);
	postorderPrint(node->right, equalElem);

	cout << node->key << " ";
	if (equalElem)
	{
		cout << "[" << node->getCountKey() << "] ";
	}
}


// ����� ������� ��� �������� ������
// ����� ��������� � �������� �������
template<typename T>
void Tree<T>::deleteTree()
{
	deleteTree(this->root);
}


// ����� ������� ������ �������� ���������. 
// ����� ��������� � �������� �������
template<typename T>
void Tree<T>::deleteTree(T*& node)
{
	if (!node) return;

	deleteTree(node->left);
	deleteTree(node->right);

	delete node;
	node = nullptr;
	countNodes--;
}


template<class T>
inline void Tree<T>::deleteTreeOptim()
{
	deleteTreeOptim(this->root);
}

// ����� ������� ��� �������� ������
template<typename T>
void Tree<T>::deleteTreeOptim(T*& node)
{
	if (!node) return;

	queue<T*> queue;
	queue.push(node);

	T* front = nullptr;

	while (!queue.empty())
	{
		front = queue.front();
		queue.pop();

		if (front->left) 
		{
			queue.push(front->left);
		}

		if (front->right) 
		{
			queue.push(front->right);
		}

		delete front;
		countNodes--;
	}

	node = nullptr;
}


// ����� ���������� �������� ����������� ��������
template<typename T>
int Tree<T>::prevElem(const int key) const
{
	T* node = searchElem(this->root, key);
	if (node)
	{
		node = prevElem(node);
		if (node)
		{
			return node->key;
		}
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ���������� �������
template<typename T>
T* Tree<T>::prevElem(T* node) const
{
	/*if (node->left)
	{
		return maxElem(node->left);
	}

	T* iter = node->parent;
	while (iter && node == iter->left)
	{
		node = iter;
		iter = iter->parent;
	}

	return iter;*/

	T* current = this->root;
	T* predcessor = nullptr;
	while (current)
	{
		if (current->key < node->key)
		{
			predcessor = current;
			current = current->right;
		}
		else
		{
			current = current->left;
		}
	}
	return predcessor;
}


// ����� ���������� �������� ���������� ��������
template<typename T>
int Tree<T>::nextElem(const int key) const
{
	T* node = searchElem(this->root, key);
	if (node)
	{
		node = nextElem(node);
		if (node)
		{
			return node->key;
		}
	}
	return CODE_ERROR;
}

// ����� ���������� ��������� �� ��������� �������
template<typename T>
T* Tree<T>::nextElem(T* node) const
{
	/*if (node->right)
	{
		return minElem(node->right);
	}

	T* iter = node->parent;
	while (iter && node == iter->right)
	{
		node = iter;
		iter = iter->parent;
	}

	return iter;*/

	T* current = this->root;
	T* successor = nullptr;
	while (current)
	{
		if (current->key > node->key)
		{
			successor = current;
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}
	return successor;
}


// ����� ���������� ���������� ��������� � ������
template<typename T>
int Tree<T>::searchElem(const int key) const
{
	T* node = searchElem(this->root, key);
	if (node)
	{
		return node->getCountKey();
	}
	return 0;
}

// ����� ���������� ��������� �� ��������� �������
template<typename T>
T* Tree<T>::searchElem(T* iter, const int key) const
{
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


// ����� ��������� ������ ���������� ��� ���������������� �������
template<typename T>
bool Tree<T>::fillTree(const int size, const int fillMode)
{
	switch (fillMode)
	{
	case 0:
		for (int i = 0; i < size; ++i)
		{
			insertElem(i + 10);
		}
		break;
	case 1:
		for (int i = 0; i < size; ++i)
		{
			insertElem(rand() % 10000 + 10);
		}
		break;
	default:
		cout << "������: ���������� ������ �� ����������." << endl;
		return false;
	}
	return true;
}


// ����� ���������� ������ ������
template<typename T>
int Tree<T>::getHeight(T* node) const
{
	int maxHeight = 0;

	if (!node) return maxHeight;

	queue<T*> q;
	q.push(node);

	while (!q.empty())
	{
		size_t nodeCount = q.size();
		if (nodeCount > 0)
		{
			maxHeight++;
		}
		while (nodeCount > 0)
		{
			T* current = q.front();
			q.pop();
			if (current->left)
			{
				q.push(current->left);
			}
			if (current->right)
			{
				q.push(current->right);
			}
			nodeCount--;
		}
	}

	return maxHeight;
}