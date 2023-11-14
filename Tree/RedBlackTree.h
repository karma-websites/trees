#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include "Constants.h"

using namespace std;

enum Color { RED, BLACK };

class RbNode
{
	friend class RedBlackTree;

	RbNode* left, * right, * parent;
	Color color;
	int key;
	int countKeys;

	RbNode(int key, Color color, RbNode* parent = nullptr, RbNode* left = nullptr, RbNode* right = nullptr)
		: key(key), color(color), parent(parent), left(left), right(right), countKeys(1) {}

	int getCountKey() const { return countKeys; }
};

class RedBlackTree
{
public:

	RedBlackTree() : root(nullptr), countNodes(0) {}
	~RedBlackTree() { clear(); }

	bool fillTree(const int size, const int fillMode);
	void insert(int key);
	int getHeight() const;

	void print(bool equalElem = false, string message = "") const;
	void inorderPrint(bool equalElem = false, string message = "") const;
	void preorderPrint(bool equalElem = false, string message = "") const;
	void postorderPrint(bool equalElem = false, string message = "") const;

	int minElem() const;
	int maxElem() const;
	int prev(int key) const;
	int next(int key) const;
	int search(int key) const;
	bool isEmpty() const { return root == nullptr; }
	int getCountNodes()  const { return countNodes; }

	void delElem(int key);
	void clear();

private:

	RbNode* root;
	int countNodes;

	// Вспомогательные методы для работы с деревом
	RbNode* privatePrev(RbNode* node) const;
	RbNode* privateNext(RbNode* node) const;
	RbNode* privateMin(RbNode* iter) const;
	RbNode* privateMax(RbNode* iter) const;
	RbNode* privateSearch(int key) const;

	int getHeight(RbNode* node) const;

	// Методы для вставки элемента в дерево с последующей балансировкой
	void fixInsert(RbNode*& node);
	void rotateLeft(RbNode*& node);
	void rotateRight(RbNode*& node);
	template <typename T>
	void Swap(T& a, T& b) const { T temp = a; a = b; b = temp; }

	// Методы для вывода дерева на экран
	void privatePrint(const RbNode* const node, bool equalElem, int indent = 10) const;
	void privateInorder(const RbNode* const node, bool equalElem) const;
	void privatePreorder(const RbNode* const node, bool equalElem) const;
	void privatePostorder(const RbNode* const node, bool equalElem) const;

	// Методы для удаления элементов из дерева
	void privateDelElem(RbNode* node);
	void privateClear(RbNode*& node);
};

