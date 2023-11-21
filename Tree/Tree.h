#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <queue>

#include "Constants.h"

using namespace std;

/*
	Объявление шаблонного класса
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

	// Метод заполнения дерева случайными или отсортированными данными
	bool fillTree(vector<int>& vec, const int size, const int fillMode);

	// Методы вставки и удаления элемента
	virtual void insertElem(const int key) = 0;
	virtual void deleteElem(const int key) = 0;

	// Методы вывода дерева на экран
	virtual void print(const string& message = "") const;
	void widthPrint(const string& message = "") const;
	void inorderPrint(const string& message = "") const;
	void preorderPrint(const string& message = "") const;
	void postorderPrint(const string& message = "") const;

	// Вспомогательные методы
	int minElem() const;
	int maxElem() const;
	int prevElem(const int key) const;
	int nextElem(const int key) const;
	int searchElem(const int key) const;
	bool isEmpty() const { return root == nullptr; }
	int getCountNodes() const { return countNodes; }
	int getHeight() const { return getHeight(root); }

	void exportDotFile(ofstream& filename) const;

	// Методы удаления всех элементов
	void deleteTree();
	void deleteTreeOptim();

protected:

	T* root;
	int countNodes;

	// Вспомогательные методы работы с деревом
	T* prevElem(T* node) const;
	T* nextElem(T* node) const;
	T* minElem(T* iter) const;
	T* maxElem(T* iter) const;
	T* searchElem(T* iter, const int key) const;
	int getHeight(T* const node) const;

	int Max(const int& a, const int& b) const { return (a > b) ? a : b; }
	template <typename T>
	void Swap(T& a, T& b) const { T temp = a; a = b; b = temp; }

	void generateDotFile(ofstream& dotFile, T* node) const;

	// Методы вывода дерева на экран
	void print(const T* const node) const;
	void widthPrint(T* const node) const;
	void inorderPrint(const T* const node) const;
	void preorderPrint(const T* const node) const;
	void postorderPrint(const T* const node) const;

	// Метод удаления всех элементов дерева
	void deleteTree(T*& node);
	void deleteTreeOptim(T*& node);
};


/*
	Определение шаблонного класса
*/

// Метод возвращает значение минимального элемента дерева
template<typename T>
int Tree<T>::minElem() const
{
	if (!isEmpty())
	{
		return minElem(this->root)->key;
	}
	return CODE_ERROR;
}

// Метод возвращает указатель на минимальный элемент дерева
template<typename T>
T* Tree<T>::minElem(T* iter) const
{
	while (iter->left)
	{
		iter = iter->left;
	}
	return iter;
}


// Метод возвращает значение максимального элемента дерева
template<typename T>
int Tree<T>::maxElem() const
{
	if (!isEmpty())
	{
		return maxElem(this->root)->key;
	}
	return CODE_ERROR;
}

// Метод возвращает указатель на максимальный элемент дерева
template<typename T>
T* Tree<T>::maxElem(T* iter) const
{
	while (iter->right)
	{
		iter = iter->right;
	}
	return iter;
}


// Метод выводит элементы всего дерева в виде дерева
// Центрированный (симметричный) обход дерева
template<typename T>
void Tree<T>::print(const string& message) const
{
	cout << message;
	print(this->root);
	cout << endl;
}

// Метод выводит элементы поддерева в виде дерева
// Центрированный (симметричный) обход поддерева
template<typename T>
void Tree<T>::print(const T* const node) const
{
	static int tabs = 0;

	if (!node) return;

	tabs += 10;

	print(node->right);

	for (size_t i = 0; i < tabs; i++)
	{
		cout << " ";
	}
	cout << node->key << " -\n";

	print(node->left);

	tabs -= 10;
}

// Обход дерева в ширину
template<class T>
void Tree<T>::widthPrint(const string& message) const
{
	cout << message;
	widthPrint(this->root);
	cout << endl;
}

// Обход поддерева в ширину
template<class T>
void Tree<T>::widthPrint(T* const node) const
{
	if (!node) return;

	queue<T*> queue;
	queue.push(node);

	while (!queue.empty())
	{
		T* current = queue.front();
		cout << current->key << " ";
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


// Метод выводит элементы всего дерева в отсортированном порядке
// Центрированный (симметричный) обход дерева
template<typename T>
void Tree<T>::inorderPrint(const string& message) const
{
	cout << message;
	inorderPrint(this->root);
	cout << endl;
}

// Метод выводит элементы поддерева в отсортированном порядке
// Центрированный (симметричный) обход поддерева
template<typename T>
void Tree<T>::inorderPrint(const T* const node) const
{
	if (!node) return;

	inorderPrint(node->left);

	cout << node->key << " ";

	inorderPrint(node->right);
}


// Метод выводит элементы всего дерева в порядке: вершина, левое поддерево, правое поддерево,
// Обход дерева в прямом порядке
template<typename T>
void Tree<T>::preorderPrint(const string& message) const
{
	cout << message;
	preorderPrint(this->root);
	cout << endl;
}

// Метод выводит элементы поддерева в порядке: вершина, левое поддерево, правое поддерево
// Обход поддерева в прямом порядке
template<typename T>
void Tree<T>::preorderPrint(const T* const node) const
{
	if (!node) return;

	cout << node->key << " ";

	preorderPrint(node->left);
	preorderPrint(node->right);
}


// Метод выводит элементы всего дерева в порядке: левое поддерево, правое поддерево, вершина
// Обход дерева в обратном порядке
template<typename T>
void Tree<T>::postorderPrint(const string& message) const
{
	cout << message;
	postorderPrint(this->root);
	cout << endl;
}

// Метод выводит элементы поддерева в порядке: левое поддерево, правое поддерево, вершина
// Обход поддерева в обратном порядке
template<typename T>
void Tree<T>::postorderPrint(const T* const node) const
{
	if (!node) return;

	postorderPrint(node->left);
	postorderPrint(node->right);

	cout << node->key << " ";
}


// Метод удаляет все элементы дерева
// Обход поддерева в обратном порядке
template<typename T>
void Tree<T>::deleteTree()
{
	deleteTree(this->root);
}


// Метод удаляет только элементы поддерева. 
// Обход поддерева в обратном порядке
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

// Метод удаляет все элементы дерева
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


// Метод возврашает значение предыдущего элемента
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

// Метод возврашает указатель на предыдущий элемент
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


// Метод возврашает значение следующего элемента
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

// Метод возврашает указатель на следующий элемент
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


// Метод возвращает количество элементов в дереве
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

// Метод возвращает указатель на найденный элемент
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


// Метод заполняет дерево случайными или отсортированными данными
template<typename T>
bool Tree<T>::fillTree(vector<int>& vec, const int size, const int fillMode)
{
	switch (fillMode)
	{
	case 0:
		for (int i = 0; i < size; i++)
		{
			insertElem(i + 10);
		}
		break;
	case 1:
		for (int i = 0; i < size; i++)
		{
			insertElem(vec[i]);
		}
		break;
	default:
		cout << "Ошибка: выбранного режима не существует." << endl;
		return false;
	}
	return true;
}


// Метод возвращает высоту дерева
template<typename T>
int Tree<T>::getHeight(T* const node) const
{
	int height = -1;

	if (!node) return height;

	queue<T*> q;
	q.push(node);
	T* current = nullptr;

	while (!q.empty())
	{
		size_t node_count = q.size();
		while (node_count)
		{
			current = q.front();
			q.pop();
			if (current->left)
			{
				q.push(current->left);
			}
			if (current->right)
			{
				q.push(current->right);
			}
			node_count--;
		}
		height++;
	}

	return height;
}

template<typename T>
void Tree<T>::generateDotFile(ofstream& dotFile, T* node) const
{
	if (!node) return;
	if (node->left) 
	{
		dotFile << "\"" << node->key << "\" -> \"" << node->left->key << "\";\n";
	}
	if (node->right) 
	{
		dotFile << "\"" << node->key << "\" -> \"" << node->right->key << "\";\n";
	}
	generateDotFile(dotFile, node->left);
	generateDotFile(dotFile, node->right);
}


template<typename T>
void Tree<T>::exportDotFile(ofstream& fileTree) const
{
	fileTree << "digraph Tree {\n";
	generateDotFile(fileTree, this->root);
	fileTree << "}\n\n";
}