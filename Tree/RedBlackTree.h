#pragma once

#include "Tree.h"


enum Color { BLACK, RED };


class RbNode
{
	friend class Tree<RbNode>;
	friend class RedBlackTree;

	RbNode* left, * right, * parent;
	Color color;
	int key;

	RbNode(int key, Color color = RED, RbNode* parent = nullptr,
		RbNode* left = nullptr, RbNode* right = nullptr)
		: key(key), color(color), parent(parent),
		left(left), right(right) {}
};


class RedBlackTree : public Tree<RbNode>
{
public:

	void print(const string& message = "") const override;

	void insertElem(const int key) override;
	void deleteElem(const int key) override;

private:

	// Метод вывода дерева на экран
	void print(const RbNode* const node, int indent = 5) const;

	// Методы вставки элемента
	void leftRotate(RbNode* x);
	void rightRotate(RbNode* y);
	void insertFixUp(RbNode* node);

	// Методы удаления элемента
	void remove(RbNode* node);
	void removeFixUp(RbNode* node, RbNode* parent);
};
