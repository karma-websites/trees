#include "RedBlackTree.h"


// Метод производит вставку элемента в дерево
void RedBlackTree::insertElem(const int key)
{
	RbNode* new_node = new RbNode(key, RED);

	RbNode* parent = nullptr;
	RbNode* current = this->root;
	while (current) 
	{
		parent = current;
		if (key < current->key) 
		{
			current = current->left;
		}
		else 
		{
			current = current->right;
		}
	}

	new_node->parent = parent;
	if (!parent) 
	{
		this->root = new_node;
		countNodes++;
	}
	else if (key < parent->key) 
	{
		parent->left = new_node;
		countNodes++;
	}
	else if (key > parent->key)
	{
		parent->right = new_node;
		countNodes++;
	}
	else
	{
		parent->countKeys++;
	}

	fixInsert(new_node);
}

void RedBlackTree::rotateLeft(RbNode*& node) 
{
	RbNode* newRoot = node->right;
	node->right = newRoot->left;
	if (node->right)
	{
		node->right->parent = node;
	}
	newRoot->parent = node->parent;
	if (!node->parent)
	{
		this->root = newRoot;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = newRoot;
	}
	else {
		node->parent->right = newRoot;
	}
	newRoot->left = node;
	node->parent = newRoot;
}

void RedBlackTree::rotateRight(RbNode*& node)
{
	RbNode* newRoot = node->left;
	node->left = newRoot->right;
	if (node->left)
	{
		node->left->parent = node;
	}
	newRoot->parent = node->parent;
	if (!node->parent)
	{
		this->root = newRoot;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = newRoot;
	}
	else 
	{
		node->parent->right = newRoot;
	}
	newRoot->right = node;
	node->parent = newRoot;
}

void RedBlackTree::fixInsert(RbNode*& node)
{
	RbNode* parent = nullptr;
	RbNode* grandparent = nullptr;
	while ((node != this->root) && (node->color != BLACK) && (node->parent->color == RED))
	{
		parent = node->parent;
		grandparent = node->parent->parent;
		if (parent == grandparent->left) 
		{
			RbNode* uncle = grandparent->right;
			if (uncle != nullptr && uncle->color == RED) 
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandparent;
			}
			else 
			{
				if (node == parent->right)
				{
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				rotateRight(grandparent);
				Swap(parent->color, grandparent->color);
				node = parent;
			}
		}
		else 
		{
			RbNode* uncle = grandparent->left;
			if ((uncle != nullptr) && (uncle->color == RED)) 
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandparent;
			}
			else 
			{
				if (node == parent->left)
				{
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				rotateLeft(grandparent);
				Swap(parent->color, grandparent->color);
				node = parent;
			}
		}
	}
	this->root->color = BLACK;
}


// Метод удаляет один элемент дерева по его значению
void RedBlackTree::deleteElem(const int key)
{
	RbNode* node = searchElem(this->root, key);;
	if (node)
	{
		innerDeleteElem(node);
	}
}

// Метод удаляет один элемент дерева по указателю на него
void RedBlackTree::innerDeleteElem(RbNode* node)
{

}
