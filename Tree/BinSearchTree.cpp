#include "BinSearchTree.h"


// Метод производит вставку элемента в дерево
void BinSearchTree::insertElem(const int key)
{
	BsNode* iter = this->root;

	if (!iter)
	{
		this->root = new BsNode(key);
		countNodes++;
	}

	while (iter)
	{
		if (key == iter->key)
		{
			iter->countKeys++;
			break;
		}
		else if (key < iter->key)
		{
			if (iter->left)
			{
				iter = iter->left;
			}
			else
			{
				iter->left = new BsNode(key, iter);
				countNodes++;
				break;
			}
		}
		else
		{
			if (iter->right)
			{
				iter = iter->right;
			}
			else
			{
				iter->right = new BsNode(key, iter);
				countNodes++;
				break;
			}
		}
	}
}


// Метод удаляет один элемент дерева по его значению
void BinSearchTree::deleteElem(const int key)
{
	BsNode* node = searchElem(this->root, key);
	if (node)
	{
		innerDeleteElem(node);
	}
}

// Метод удаляет один элемент дерева по указателю на него
void BinSearchTree::innerDeleteElem(BsNode*& node)
{
	BsNode* delNode, * temp;

	if (!node->left || !node->right)
		delNode = node;
	else
		delNode = nextElem(node);

	if (delNode->left)
		temp = delNode->left;
	else
		temp = delNode->right;

	if (temp)
		temp->parent = delNode->parent;

	if (!delNode->parent)
		root = temp;
	else if (delNode == delNode->parent->left)
		delNode->parent->left = temp;
	else
		delNode->parent->right = temp;

	if (delNode != node)
		node->key = delNode->key;

	delete delNode;
	delNode = nullptr;
	countNodes--;
}

