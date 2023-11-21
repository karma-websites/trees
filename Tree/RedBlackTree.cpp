#include "RedBlackTree.h"


// Метод выводит элементы всего дерева в виде дерева
// Центрированный (симметричный) обход дерева
void RedBlackTree::print(const string& message) const
{
	cout << message;
	print(this->root);
	cout << endl;
}


// Метод вывода дерева на экран
void RedBlackTree::print(const RbNode* const node, int indent) const
{
	if (!node) return;

	if (node->right)
	{
		print(node->right, indent + 10);
	}

	if (indent > 0)
	{
		cout << setw(indent) << " ";
	}

	if (node->right) cout << " /\n" << setw(indent) << " ";
	cout << node->key << (node->color == RED ? " (R) " : " (B) ");

	cout << endl;

	if (node->left)
	{
		cout << setw(indent) << " " << " \\\n";
		print(node->left, indent + 10);
	}
}


void RedBlackTree::deleteElem(const int key)
{
	RbNode* delete_node = searchElem(this->root, key);
	if (delete_node)
	{
		remove(delete_node);
		countNodes--;
	}
}


void RedBlackTree::leftRotate(RbNode* x)
{
	RbNode* y = x->right;
	x->right = y->left;

	if (y->left)
		y->left->parent = x;

	y->parent = x->parent;

	if (!x->parent)
		this->root = y;
	else
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}


void RedBlackTree::rightRotate(RbNode* y)
{
	RbNode* x = y->left;
	y->left = x->right;

	if (x->right)
		x->right->parent = y;

	x->parent = y->parent;

	if (!y->parent)
		this->root = x;
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}

	x->right = y;
	y->parent = x;
}


void RedBlackTree::insertElem(const int key)
{
	RbNode* x = this->root;
	RbNode* y = nullptr;

	while (x)
	{
		y = x;
		if (key > x->key)
			x = x->right;
		else if (key < x->key)
			x = x->left;
		else return;
	}

	RbNode* new_node = new RbNode(key, RED, y);

	if (y)
	{
		if (new_node->key > y->key)
		{
			countNodes++;
			y->right = new_node;
		}
		else
		{
			countNodes++;
			y->left = new_node;
		}
	}
	else
	{
		countNodes++;
		this->root = new_node;
	}

	insertFixUp(new_node);
};


void RedBlackTree::insertFixUp(RbNode* node)
{
	RbNode* parent = node->parent;
	while (node != this->root && parent->color == RED)
	{
		RbNode* gparent = parent->parent;
		if (gparent->left == parent)
		{
			RbNode* uncle = gparent->right;
			if (uncle && uncle->color == RED)
			{
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					leftRotate(parent);
					Swap(node, parent);
				}
				rightRotate(gparent);
				gparent->color = RED;
				parent->color = BLACK;
				break;
			}
		}
		else
		{
			RbNode* uncle = gparent->left;
			if (uncle && uncle->color == RED)
			{
				gparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rightRotate(parent);
					Swap(parent, node);
				}
				leftRotate(gparent);
				parent->color = BLACK;
				gparent->color = RED;
				break;
			}
		}
	}
	this->root->color = BLACK;
}


void RedBlackTree::remove(RbNode* node)
{
	RbNode* child, * parent;
	Color color;

	if (node->left && node->right)
	{
		RbNode* replace = node;

		replace = node->right;
		while (replace->left)
			replace = replace->left;

		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			this->root = replace;

		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if (parent == node)
			parent = replace;
		else
		{
			if (child)
				child->parent = parent;

			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK && getCountNodes() > 1)
			removeFixUp(child, parent);

		delete node;
		return;
	}

	if (node->left)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;

	if (child)
		child->parent = parent;

	if (parent)
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		this->root = child;

	if (color == BLACK && getCountNodes() > 1)
		removeFixUp(child, parent);

	delete node;
}


void RedBlackTree::removeFixUp(RbNode* node, RbNode* parent)
{
	RbNode* sibling;
	while (node != this->root && (node == nullptr || node->color == BLACK))
	{
		if (node == parent->left)
		{
			sibling = parent->right;
			if (sibling->color == RED)
			{
				sibling->color = BLACK;
				parent->color = RED;
				leftRotate(parent);
				sibling = parent->right;
			}
			if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
				(sibling->right == nullptr || sibling->right->color == BLACK))
			{
				sibling->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (sibling->right == nullptr || sibling->right->color == BLACK)
				{
					sibling->left->color = BLACK;
					sibling->color = RED;
					rightRotate(sibling);
					sibling = parent->right;
				}
				sibling->color = parent->color;
				parent->color = BLACK;
				sibling->right->color = BLACK;
				leftRotate(parent);
				node = this->root;
				break;
			}
		}
		else
		{
			sibling = parent->left;
			if (sibling->color == RED)
			{
				sibling->color = BLACK;
				parent->color = RED;
				rightRotate(parent);
				sibling = parent->left;
			}
			if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
				(sibling->right == nullptr || sibling->right->color == BLACK))
			{
				sibling->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (sibling->left == nullptr || sibling->left->color == BLACK)
				{
					sibling->right->color = BLACK;
					sibling->color = RED;
					leftRotate(sibling);
					sibling = parent->left;
				}
				sibling->color = parent->color;
				parent->color = BLACK;
				sibling->left->color = BLACK;
				rightRotate(parent);
				node = this->root;
				break;
			}
		}
	}

	if (node)
	{
		node->color = BLACK;
	}
}
