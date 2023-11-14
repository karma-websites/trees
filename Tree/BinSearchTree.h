#pragma once

#include <iostream>
#include <string>

#include "Constants.h"

using namespace std;

class BsNode
{
	friend class BinSearchTree;

	BsNode* left, * right, * parent;
	int key;
	int countKeys;

	BsNode(int key, BsNode * parent = nullptr, BsNode* left = nullptr, 
		BsNode* right = nullptr)
		: key(key), parent(parent), left(left), right(right), countKeys(1) {}

	int getCountKey() const { return countKeys; }
};

class BinSearchTree
{
public:

	BinSearchTree() : root(nullptr), countNodes(0) {}
	~BinSearchTree() { clear(); }

	bool fillTree(const int size, const int fillMode);
	void insert(int key);
	
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
	int getCountNodes() const { return countNodes; }
	int getHeight() const;
	
	void delElem(int key);
	void clear();

private:

	BsNode* root;
	int countNodes;

	BsNode* privatePrev(BsNode* node) const;
	BsNode* privateNext(BsNode* node) const;
	BsNode* privateMin(BsNode* iter) const;
	BsNode* privateMax(BsNode* iter) const;
	BsNode* privateSearch(int key) const;
	int getHeight(BsNode* node) const;

	void privatePrint(const BsNode* const node, bool equalElem) const;
	void privateInorder(const BsNode* const node, bool equalElem) const;
	void privatePreorder(const BsNode* const node, bool equalElem) const;
	void privatePostorder(const BsNode* const node, bool equalElem) const;

	void privateDelElem(BsNode* node);
	void privateClear(BsNode*& node);
};
