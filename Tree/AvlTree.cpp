#include "AvlTree.h"


// Методы отвечают за вставку элемента в дерево

void AvlTree::updateDepth(AvlNode* const node) const
{
	node->height = 1 + Max(getDepth(node->left), getDepth(node->right));
}

int AvlTree::getDepth(const AvlNode* const node) const
{
	return (node == nullptr) ? -1 : node->height;
}

int AvlTree::getBalance(const AvlNode* const node) const
{
	return (node == nullptr) ? 0 : getDepth(node->right) - getDepth(node->left);
}

void AvlTree::rightRotate(AvlNode* const node) const
{
	Swap(node->key, node->left->key);
	AvlNode* buffer = node->right;
	node->right = node->left;
	node->left = node->right->left;
	node->right->left = node->right->right;
	node->right->right = buffer;
	updateDepth(node->right);
	updateDepth(node);
}

void AvlTree::leftRotate(AvlNode* const node) const
{
	Swap(node->key, node->right->key);
	AvlNode* buffer = node->left;
	node->left = node->right;
	node->right = node->left->right;
	node->left->right = node->left->left;
	node->left->left = buffer;
	updateDepth(node->left);
	updateDepth(node);
}

void AvlTree::balance(AvlNode* const node) const
{
	int balance = getBalance(node);
	if (balance == -2)
	{
		if (getBalance(node->left) == 1)
		{
			leftRotate(node->left);
		}
		rightRotate(node);
	}
	else if (balance == 2)
	{
		if (getBalance(node->right) == -1)
		{
			rightRotate(node->right);
		}
		leftRotate(node);
	}
}

void AvlTree::insertElem(const int key)
{
	innerInsertElem(this->root, key);
}

void AvlTree::innerInsertElem(AvlNode*& iter, const int key)
{
	if (!iter)
	{
		countNodes++;
		iter = new AvlNode(key);
	}
	else if (key < iter->key)
	{
		innerInsertElem(iter->left, key);
	}
	else if (key > iter->key)
	{
		innerInsertElem(iter->right, key);
	}
	else
	{
		iter->countKeys++;
	}
	updateDepth(iter);
	balance(iter);
}


// Методы отвечают за удаление элемента из дерева

void AvlTree::deleteElem(const int key)
{
	this->root = innerDeleteElem(this->root, key);
}

AvlNode* AvlTree::innerDeleteElem(AvlNode* iter, const int key)
{
	if (!iter)
	{
		return nullptr;
	}
	else if (key < iter->key)
	{
		iter->left = innerDeleteElem(iter->left, key);
	}
	else if (key > iter->key)
	{
		iter->right = innerDeleteElem(iter->right, key);
	}
	else
	{
		if (!iter->left || !iter->right)
		{
			AvlNode* temp = iter;
			iter = (iter->left == nullptr) ? iter->right : iter->left;
			countNodes--;
			delete temp;
		}
		else
		{
			AvlNode* maxLeft = maxElem(iter->left);
			iter->key = maxLeft->key;
			iter->left = innerDeleteElem(iter->left, maxLeft->key);
		}
	}
	if (iter)
	{
		updateDepth(iter);
		balance(iter);
	}
	return iter;
}

