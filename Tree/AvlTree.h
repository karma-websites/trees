#pragma once
#include <queue>
#include <iostream>
#include <string>

#include "Constants.h"

using namespace std;

class AvlNode
{
	friend class AvlTree;

	AvlNode* left, * right;
	int key;
    int height;
	int countKeys;

	AvlNode(int key, AvlNode* left = nullptr, AvlNode* right = nullptr)
		: key(key), left(left), right(right), countKeys(1), height(0) {}

	int getCountKey() const { return countKeys; }
};

class AvlTree
{
public:

	AvlTree() : root(nullptr), countNodes(0) {}
	~AvlTree() { clear(); }

	bool fillTree(const int size, const int fillMode);
	void insert(int key);
	int getHeightTree() const;

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

	AvlNode* root;
	int countNodes;

	// Вспомогательные методы для работы с деревом
	AvlNode* privatePrev(AvlNode* node) const;
	AvlNode* privateNext(AvlNode* node) const;
	AvlNode* privateMin(AvlNode* iter) const;
	AvlNode* privateMax(AvlNode* iter) const;
	AvlNode* privateSearch(int key) const;

	int getHeightTree(AvlNode* node) const;

	// Методы для вставки элемента в дерево с последующей балансировкой
	void privateInsert(AvlNode*& iter, int key);
	void updateHeight(AvlNode* const node) const;
	int getHeight(const AvlNode* const node) const;
	int getBalance(const AvlNode* const node) const;
	void rightRotate(AvlNode* const node) const;
	void leftRotate(AvlNode* const node) const;
	void balance(AvlNode* const node) const;
	int Max(const int& a, const int& b) const { return (a > b) ? a : b; }
	void Swap(int& a, int& b) const { a = a + b; b = a - b; a = a - b; }

	// Методы для вывода дерева на экран
	void privatePrint(const AvlNode* const node, bool equalElem) const;
	void privateInorder(const AvlNode* const node, bool equalElem) const;
	void privatePreorder(const AvlNode* const node, bool equalElem) const;
	void privatePostorder(const AvlNode* const node, bool equalElem) const;

	// Методы для удаления элементов из дерева
	AvlNode* privateDelElem(AvlNode* iter, int key);
	void privateClear(AvlNode*& node);
};

