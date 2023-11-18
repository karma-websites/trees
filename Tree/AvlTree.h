#pragma once
#include "Tree.h"


class AvlNode
{
	friend class Tree<AvlNode>;
	friend class AvlTree;

	AvlNode* left, * right;
	int key;
    int height;
	int countKeys;

	AvlNode(int key, AvlNode* left = nullptr, AvlNode* right = nullptr)
		: key(key), left(left), right(right), countKeys(1), height(0) {}

	int getCountKey() const { return countKeys; }
};


class AvlTree : public Tree<AvlNode>
{
public:

	void insertElem(const int key) override;
	void deleteElem(const int key) override;

private:

	// Методы вставки элемента в дерево с последующей балансировкой
	void innerInsertElem(AvlNode*& iter, const int key);
	void updateDepth(AvlNode* const node) const;
	int getDepth(const AvlNode* const node) const;
	int getBalance(const AvlNode* const node) const;
	void rightRotate(AvlNode* const node) const;
	void leftRotate(AvlNode* const node) const;
	void balance(AvlNode* const node) const;
	int Max(const int& a, const int& b) const { return (a > b) ? a : b; }
	void Swap(int& a, int& b) const { a = a + b; b = a - b; a = a - b; }

	// Метод удаления элемента дерева
	AvlNode* innerDeleteElem(AvlNode* iter, const int key);
};

