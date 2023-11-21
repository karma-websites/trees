#pragma once

#include "Tree.h"


class AvlNode
{
	friend class Tree<AvlNode>;
	friend class AvlTree;

	AvlNode* left, * right;
	int key;
    int height;

	AvlNode(int key, AvlNode* left = nullptr, AvlNode* right = nullptr)
		: key(key), left(left), right(right), height(0) {}
};


class AvlTree : public Tree<AvlNode>
{
public:

	void insertElem(const int key) override;
	void deleteElem(const int key) override;

private:

	// Методы вставки элемента с последующей балансировкой
	void innerInsertElem(AvlNode*& iter, const int key);
	void updateHgt(AvlNode* const node) const;
	int getHgt(const AvlNode* const node) const;
	int getBalance(const AvlNode* const node) const;
	void rightRotate(AvlNode* const node) const;
	void leftRotate(AvlNode* const node) const;
	void balance(AvlNode* const node) const;
	int Max(const int& a, const int& b) const { return (a > b) ? a : b; }
	void Swap(int& a, int& b) const { a = a + b; b = a - b; a = a - b; }

	// Метод удаления элемента
	AvlNode* innerDeleteElem(AvlNode* iter, const int key);
};
