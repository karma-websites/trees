#pragma once
#include "Tree.h"


enum Color { RED, BLACK };


class RbNode
{
	friend class Tree<RbNode>;
	friend class RedBlackTree;

	RbNode* left, * right, * parent;
	bool color;
	int key;
	int countKeys;

	RbNode(int key, bool color = RED, RbNode* parent = nullptr,
		RbNode* left = nullptr, RbNode* right = nullptr)
		: key(key), color(color), parent(parent),
		left(left), right(right), countKeys(1) {}

	int getCountKey() const { return countKeys; }
};


class RedBlackTree : public Tree<RbNode>
{
public:

	void insertElem(const int key) override;
	void deleteElem(const int key) override;

private:

	// Методы вставки элемента в дерево
	void fixInsert(RbNode*& node);
	void rotateLeft(RbNode*& node);
	void rotateRight(RbNode*& node);
	void fixDelete(RbNode*& node);

	// Метод удаления элемента дерева
	void innerInsertElem(const int key);
	void innerDeleteElem(RbNode* node);
};
