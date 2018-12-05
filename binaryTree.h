#pragma once
#ifndef BIN_TREE_H
#define BIN_TREE_H
#include <string>
using namespace std;


template <class keyType, class dataType>
class binaryTree
{

public:
	
	binaryTree();

	

	bool getCode(const keyType &k, string &s)const;

	
	bool insert(const keyType &, const dataType &);


	bool empty() const;

	void merge(keyType k, dataType d, binaryTree< keyType, dataType> b1, binaryTree< keyType, dataType> b2);
	bool search(const keyType &) const;

	
	bool retrieve(const keyType &, dataType &) const;


	void traverse() const;


	void graph() const;


	void remove(const keyType &);

	


private:
	
	class treeNode
	{
		public:
			keyType key; 		
			dataType data;		
			treeNode *left;		       
			treeNode *right;	
	};

	typedef treeNode * NodePointer;
	
	NodePointer root;


	
	bool search2(NodePointer, const keyType &) const;

	bool retrieve2(NodePointer, const keyType &, dataType &) const;
	
	
	bool insert2(NodePointer &, const keyType &, const dataType &);

	bool returnCode(NodePointer roott, const keyType &k, string &s)const;
	
	void traverse2(NodePointer) const;

	
	void graph2(int, NodePointer) const;


	void parentSearch(const keyType &k, bool &found,NodePointer &locptr, NodePointer &parent) const;

	treeNode* copytree(treeNode* root) {
		treeNode* new_root;
		if (root != NULL) {
			new_root = new treeNode;
			new_root->key = root->key;
			new_root->key = root->data;
			new_root->left = copytree(root->left);
			new_root->right = copytree(root->right);
		}
		else return NULL;
		return new_root;
	}
};

#endif 
#include "binaryTree.cpp"

