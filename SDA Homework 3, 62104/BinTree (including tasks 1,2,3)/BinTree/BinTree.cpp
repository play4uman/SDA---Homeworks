// BinTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <queue>

using namespace std;

template<class T>
struct Node {
	T inf;
	Node<T>* left;
	Node<T>* right;
};

template <class T>
class BinTree {
	Node<T>* root;
	void deleteBinTree(Node<T>* &) const;
	void copy(Node<T> * &, Node<T>* const &) const;
	void copyBinTree(BinTree<T> const &) ;
	void pr(Node<T>* const) const; 
	void CreateBinTree(Node<T>* & )const;
public:
	BinTree();
	~BinTree();
	BinTree(BinTree<T> const &);
	BinTree& operator= (BinTree<T> const &);
	BinTree<T> leftBinTree() const;
	BinTree<T> rightBinTree() const;
	T rootBinTree() const;
	Node<T>* getRoot();
	bool empty() const;
	void print() const;
	void create();
	void create3(T, BinTree<T>, BinTree<T>);
	int getHeight(Node<T>* const &) const;
	void levelOrder(Node<T>* const &) const;
	Node<T>* lowComAncestor(Node<T>* const &, int, int) const;
	void swap(Node<T>* &);
};

template <typename T>
BinTree<T>::BinTree() {
	root = NULL;
}

template<typename T>
BinTree<T>::~BinTree() {
	deleteBinTree(root);
}

template<typename T>
BinTree<T>::BinTree(BinTree<T> const & r) {
	copyBinTree(r);
}

template<typename T>
BinTree<T>& BinTree<T>::operator=(BinTree<T> const & r) {
	if (this != &r) {
		deleteBinTree(root);
		copyBinTree(r);
	}
	return *this;
}

template<typename T>
void BinTree<T>::deleteBinTree(Node<T>* & r) const {
	if (r) {
		deleteBinTree(r->left);
		deleteBinTree(r->right);
		delete r;
		r = NULL;
	}
}

template<typename T>
void BinTree<T>::copy(Node<T>* & pos, Node<T>* const & r) const {
	pos = NULL;
	if (r) {
		pos = new Node<T>;
		pos->inf = r->inf;
		copy(pos->left, r->left);
		copy(pos->right, r->right);
	}
}

template<typename T>
void BinTree<T>::copyBinTree(BinTree<T> const & r) {
	copy(root, r.root);
}

template<typename T>
bool BinTree<T>::empty() const {
	return root == NULL;
}

template<typename T>
T BinTree<T>::rootBinTree() const {
	return root->inf;
}

template<typename T>
BinTree<T> BinTree<T>::leftBinTree() const {
	BinTree<T> t;
	copy(t.root, root->left);
	return t;
}

template<typename T>
BinTree<T> BinTree<T>::rightBinTree() const {
	BinTree<T> t;
	copy(t.root, root->right);
	return t;
}

template<typename T>
void BinTree<T>::pr(Node<T>* const r) const {
	if (r != NULL) {
		pr(r->left);
		cout << r->inf << " ";
		pr(r->right);
	}
}

template<typename T>
void BinTree<T>::print() const {
	pr(root);
}

template<typename T>
void BinTree<T>::create3(T x, BinTree<T> l, BinTree<T> r) {
	root = new Node<T>;
	root->inf = x;
	copy(root->left, l.root);
	copy(root->right, r.root);
}

template<typename T>
void BinTree<T>::CreateBinTree(Node<T>* & pos) const {
	T x;
	char c;
	cout << "root: ";
	cin >> x;

	pos = new Node<T>;
	pos->inf = x;
	pos->left = NULL;
	pos->right = NULL;

	cout << "Do you want to add an element to the left of " << x << " ? y/n: ";
	cin >> c;
	if (c == 'y') {
		CreateBinTree(pos->left);
	}
	cout << "Do you want to add an element to the right of " << x << " ? y/n: ";
	cin >> c;
	if (c == 'y') {
		CreateBinTree(pos->right);
	}
}

template<typename T>
void BinTree<T>::create() {
	CreateBinTree(root);
}

template<typename T>
Node<T>* BinTree<T>::getRoot() {
	return root;
}

template<typename T>
int BinTree<T>::getHeight(Node<T>* const & root) const {
	int lpdHeight = 1;
	int rpdHeight = 1;
	if (root->left == NULL && root->right == NULL) return 0;
	int max = 0;
	if (root->left) {
		lpdHeight += getHeight(root->left);
	}
	if (root->right) {
		rpdHeight += getHeight(root->right);
	}
	max = lpdHeight >= rpdHeight ? lpdHeight : rpdHeight;
	return max;
}

template<typename T>
void BinTree<T>::levelOrder(Node<T>* const & root) const {
	queue<Node<T>*> q;
	q.push(root);
	while (!q.empty()) {
		Node<T>* temp = q.front();
		cout << temp->inf << " ";
		q.pop();
		if (temp->left != NULL)
			q.push(temp->left);
		if (temp->right != NULL)
			q.push(temp->right);
	}
}

template<typename T>
Node<T>* BinTree<T>::lowComAncestor(Node<T>* const & root, int v1, int v2) const {
	if (root->inf < v1 && root->inf < v2)
		lowComAncestor(root->right, v1, v2);
	if (root->inf > v1 && root->inf > v2)
		lowComAncestor(root->left, v1, v2);
	return root;
}

template<typename T>
BinTree<T> BinTree<T>::swap(Node<T>* & r) {
	BinTree<T> nt;
	BinTree<T> ntL;
	ntL.copy(ntL.root, r->left);
	BinTree<T> ntR;											//Not ready yet!
	ntR.copy(ntR.root, r->right);
	nt.create3(r->inf, ntR, ntL);
}


int main()
{
	BinTree<int> t;
	t.create();
	Node<int>* root = t.getRoot();
    return 0;
}

