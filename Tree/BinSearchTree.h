#pragma once
#include "Tree.h"


class BsNode
{
private:

	friend class Tree<BsNode>;
	friend class BinSearchTree;

	BsNode* left, * right, * parent;
	int key;
	int countKeys;

	BsNode(int key, BsNode * parent = nullptr,
		BsNode* left = nullptr, BsNode* right = nullptr)
		: key(key), parent(parent), left(left), right(right), countKeys(1) {}

	int getCountKey() const { return countKeys; }
};


class BinSearchTree : public Tree<BsNode>
{
public:

	void insertElem(const int key) override;
	void deleteElem(const int key) override;

private:

	void innerDeleteElem(BsNode*& node);
};
