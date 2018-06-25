#pragma once
#include <iostream>

template <typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree(): root(nullptr)
	{

	}
	BinarySearchTree(const BinarySearchTree&rhs) : root(nullptr)
	{
		root = clone(rhs.root);
	}

	BinarySearchTree(BinarySearchTree&&rhs) : root(nullptr)
	{
		std::swap(root, rhs.root);
	}
	~BinarySearchTree()
	{
		makeEmpty();
	}
	
	const Comparable & findMin() const
	{
		return findMin(root);
	}
	const Comparable & findMax() const
	{
		return findMax(root);
	}
	bool contains(const Comparable& x) const
	{
		return contains(x, root);
	}
	bool isEmpty() const
	{
		return root == NULL;
	}

	std::ostream& printTree(std::ostream &os) const
	{
		return printTree(root, os);
	}

	void makeEmpty()
	{
		return makeEmpty(root);
	}
	void insert(const Comparable &x)
	{
		return insert(x, root);
	}
	void insert(Comparable&& x)
	{
		return insert(x, root);
	}
	void remove(const Comparable & x)
	{
		remove(x, root);
	}

	BinarySearchTree& operator=(const BinarySearchTree &rhs)
	{

	}
	BinarySearchTree& operator=(BinarySearchTree && rhs)
	{

	}

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode(const Comparable& e = Comparable(),
			BinaryNode *l = nullptr,
			BinaryNode *r = nullptr) : element(e), left(l), right(r)
		{

		}
		BinaryNode(Comparable&& e,
			BinaryNode *l = nullptr,
			BinaryNode *r = nullptr) : element(std::move(e)), left(l), right(r)
		{

		}
	};
	BinaryNode *root;

	void insert(const Comparable &x, BinaryNode *&t)
	{
		if (t == nullptr)
			t = new BinaryNode(x);
		else if (x < t->element)
			insert(x, t->left);
		else if (x > t->element)
			insert(x, t->right);
		else
			;  // duplicate; 
	}
	void insert(Comparable &&x, BinaryNode *&t)
	{
		if (t == nullptr)
			t = new BinaryNode(std::move(x));
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (x > t->element)
			insert(std::move(x), t->right);
		else
			;  // duplicate;
	}
	void remove(const Comparable & x, BinaryNode *&t)
	{
		if (t == nullptr)
			return;
		if (x < t->element)
			return remove(x, t->left);
		else if (x > t->element)
			return remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)
		{
			BinaryNode *minNode = findMin(t->right);
			t->element = minNode->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode *oldNode = t;
			t = (t->left == nullptr) ? t->right : t->left;
			delete oldNode;
		}
	}
	BinaryNode* findMin(BinaryNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr) return t;
		else findMin(t->left);
	}
	BinaryNode* findMax(BinaryNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->right == nullptr) return t;
		else findMax(t->right);
	}
	bool contains(const Comparable &x, BinaryNode *t) const
	{
		if (t == nullptr) return false;
		if (x < t->element)
			return contain(x, t->left);
		else if (x > t->element)
			return contain(x, t->right);
		else
			return true;
	}
	void  makeEmpty(BinaryNode *&t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}
	std::ostream& printTree(BinaryNode *t, std::ostream &os) const
	{
		if (t != nullptr)
		{
			printTree(t->left, os);
			os << t->element << " ";
			printTree(t->right, os);
		}
		return os;
	}

	BinaryNode *clone(BinaryNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new BinaryNode(t->element, clone(t->left), clone(t->right));
	}
};