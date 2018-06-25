#pragma once
#include <algorithm>

template <typename Comparable>
class AVL_Tree
{
public:
	
	AVL_Tree() : root(nullptr)
	{

	}
	AVL_Tree(const AVL_Tree&rhs) : root(nullptr)
	{
		root = clone(rhs.root);
	}

	AVL_Tree(AVL_Tree&&rhs) : root(nullptr)
	{
		std::swap(root, rhs.root);
	}
	~AVL_Tree()
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

	std::ostream & printTree(std::ostream &os) const
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

	AVL_Tree& operator=(const AVL_Tree &rhs)
	{

	}
	AVL_Tree& operator=(AVL_Tree && rhs)
	{

	}
	

private:
	static const int ALLOWED_IMBALANCE = 1;
	struct AvlNode
	{
		Comparable element;
		AvlNode *left;
		AvlNode *right;
		int height;

		AvlNode(const Comparable &e = Comparable(), AvlNode *l = nullptr,
			AvlNode *r = nullptr, int h = 0) : element(e), left(l), right(r), height(h)
		{

		}
		AvlNode(Comparable &&e, AvlNode *l = nullptr,
			AvlNode *r = nullptr, int h = 0) : element(std::move(e)), left(l), right(r), height(h)
		{

		}
	};
	AvlNode *root;
	int height(const AvlNode *t) const
	{
		return t == nullptr ? -1 : t->height;
	}
	void insert(const Comparable& x, AvlNode *&t)
	{
		if (t == nullptr)
		{
			t = new AvlNode(x);
			return;
		}
		else if (x < t->element)
			insert(x, t->left);
		else if (x > t->element)
			insert(x, t->right);
		balance(t);
	}
	void balance(AvlNode *&t)
	{
		if (t == nullptr)
			return;
		if ((height(t->left) - height(t->right)) > ALLOWED_IMBALANCE)
		{
			if (height(t->left->left) > height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		}
		else if ((height(t->right) - height(t->left)) > ALLOWED_IMBALANCE)
		{
			if (height(t->right->right) > height(t->right->left))
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}
		t->height = std::max<int>(height(t->left), height(t->right)) + 1;
	}
	void rotateWithLeftChild(AvlNode *&k2)
	{
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = std::max(height(k2->left), height(k2->right)) + 1;
		k1->height = std::max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void doubleWithLeftChild(AvlNode *&k3)
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	void rotateWithRightChild(AvlNode *&k2)
	{
		AvlNode *k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;
		k2->height = std::max(height(k2->left), height(k2->right)) + 1;
		k1->height = std::max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void doubleWithRightChild(AvlNode *&k3)
	{
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}
	void remove(const Comparable& x, AvlNode *&t)
	{
		if (t == nullptr) return;
		if (x < t->element)
			remove(x, t->left);
		else if (x > t->element)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			AvlNode *oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}
		balance(t);
	}
	AvlNode* findMin(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr) return t;
		else findMin(t->left);
	}
	AvlNode* findMax(AvlNode *t) const
	{
		if (t == nullptr)
			return nullptr;
		if (t->right == nullptr) return t;
		else findMax(t->right);
	}
	bool contains(const Comparable &x, AvlNode *t) const
	{
		if (t == nullptr) return false;
		if (x < t->element)
			return contain(x, t->left);
		else if (x > t->element)
			return contain(x, t->right);
		else
			return true;
	}
	void  makeEmpty(AvlNode *&t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}
	std::ostream & printTree(AvlNode *t, std::ostream &os) const
	{
		if (t != nullptr)
		{
			printTree(t->left, os);
			os << t->element << " ";
			printTree(t->right, os);
		}
		return os;
	}
	AvlNode* clone(AvlNode *t) const
	{
		if (t == nullptr) return;
		else
			return new AvlNode(t->element, clone(t->left), clone(t->right));
	}
};