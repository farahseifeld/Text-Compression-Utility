#include <iostream>
#include <iomanip>
using namespace std;

template <class keyType, class dataType>
binaryTree<keyType, dataType>::binaryTree()
{
	root = NULL;
}


template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::search(const keyType &k) const
{
	return search2(root, k);
}


template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::search2(NodePointer aRoot, const keyType &k)	const
{
	if (aRoot == NULL)
		return false;
	else if (k == aRoot->key)
		return true;
	else if (k < aRoot->key) {
		return search2(aRoot->left, k, );
	}
	else {
		return search2(aRoot->right, k);
	}
}

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::getCode(const keyType &k, string &s) const
{
	return returnCode(root, k, s);
}

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::returnCode(NodePointer root, const keyType &k, string &s)const
{
	if (root == NULL)
		return false;
	else if (k == root->key)
		return true;
	else if (root->left->key.find(k) != string::npos) {
		s += '0';
		return returnCode(root->left, k, s);
	}
	else {
		s += '1';
		return returnCode(root->right, k, s);
	}
}



template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::retrieve(const keyType &k, dataType &d) const
{
	return retrieve2(root, k, d);
}


template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::retrieve2(NodePointer aRoot, const keyType &k, dataType &d)const
{
	if (aRoot == NULL)
		return false;
	else if (k == aRoot->key)
	{
		d = aRoot->data; return true;
	}
	else if (k < aRoot->key)
		return retrieve2(aRoot->left, k, d);
	else
		return retrieve2(aRoot->right, k, d);
}


template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::insert(const keyType &k, const dataType &d)
{
	return insert2(root, k, d);
}

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::empty() const
{
	return(root == NULL);
}
template <class keyType, class dataType>
void binaryTree<keyType, dataType>::traverse() const
{
	traverse2(root);
}


template <class keyType, class dataType>
void binaryTree<keyType, dataType>::traverse2(NodePointer aRoot) const
{
	if (aRoot != NULL)
	{
		traverse2(aRoot->left);
		cout << aRoot->key << " " << aRoot->data << endl;
		traverse2(aRoot->right);
	}

}

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::graph() const
{
	graph2(0, root);
}

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::graph2(int indent, NodePointer aRoot) const
{
	if (aRoot != NULL)
	{
		graph2(indent + 8, aRoot->right);
		cout << setw(indent) << " " << aRoot->key << endl;
		graph2(indent + 8, aRoot->left);
	}
}


template <class keyType, class dataType>
void binaryTree<keyType, dataType>::remove(const keyType &k)
{
	bool found;
	NodePointer x, parent;

	parentSearch(k, found, x, parent);
	if (!found)
	{
		cout << "Item not in BST\n";
		return;
	}

	if ((x->left != NULL) && (x->right != NULL))
	{
		NodePointer xSucc = x->right;
		parent = x;
		while (xSucc->left != NULL)
		{
			parent = xSucc; xSucc = xSucc->left;
		}

		x->key = xSucc->key; x->data = xSucc->data;
		x = xSucc;
	}
	NodePointer subtree = x->left;
	if (subtree == NULL) subtree = x->right;
	if (parent == NULL) root = subtree;
	else if (parent->left == x)
		parent->left = subtree;
	else parent->right = subtree;
	delete x;
}



template <class keyType, class dataType>
void binaryTree<keyType, dataType>::merge(keyType k, dataType d, binaryTree< keyType, dataType>b1, binaryTree< keyType, dataType> b2) {

	NodePointer r1=new treeNode, r2=new treeNode;
	r1 = copytree(b1.root);
	r2 = copytree(b2.root);
	root = new treeNode;
		root->left = b1.root;
		root->right = b2.root;
		root->key = k; 
		root->data = d;
	
}

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::parentSearch(const keyType &k, bool &found, NodePointer &locptr, NodePointer &parent) const
{
	locptr = root;  parent = NULL; found = false;
	while (!found && locptr != NULL)
	{
		if (k < locptr->key)
		{
			parent = locptr;	locptr = locptr->left;
		}
		else if (locptr->key < k)
		{
			parent = locptr;	locptr = locptr->right;
		}
		else found = true;
	}

}



template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::insert2(NodePointer &aRoot, const keyType &k, const dataType &d)
{

	if (aRoot == NULL)
	{
		aRoot = new treeNode;
		aRoot->left = NULL;
		aRoot->right = NULL;
		aRoot->key = k;
		aRoot->data = d;
		return true;
	}
	else if (k == aRoot->key)
		return false;
	else if (k < aRoot->key)
		return insert2(aRoot->left, k, d);
	else
		return insert2(aRoot->right, k, d);
}




