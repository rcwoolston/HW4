#pragma once

#ifndef ALVTREE_H
#define AVLTREE_H
#include <iostream>
#include <string>

using namespace std;

class AvlNode {
public:
	string word;
	int height;
	AvlNode *ptrLeft, *ptrRight;
	AvlNode(); //Default Constructor
	AvlNode(string s); //Constructor with one parameter
};

typedef AvlNode* AvlNodeptr;

class AvlTree {
private:
	AvlNodeptr root;

public:
	AvlTree(); //Initializes root to NULL
	AvlTree(const AvlTree& tree); //Copy constructor
	~AvlTree(); //Destructor
	string GetRoot();
	void Insert(string s);
	int GetHeight(AvlNodeptr thisNode);
	int Size(); //Returns the number of nodes in the tree
	int Height(); //Returns the path from the root to the dppest leaf node in the Tree
	void Delete(string s);
	bool Find(string s);
	int FindComparisons(string s);
	string Traverse();
	int CountTwoChildren();
	int CountOneChild();
	int CountLeaves();


private:
	void CopyTree(AvlNodeptr &thisNode, AvlNodeptr &source);
	void DeleteTree(AvlNodeptr thisNode);
	void RInsert(AvlNodeptr &thisNode, string s);
	void Balance(AvlNodeptr &thisNode);
	void RightRotate(AvlNodeptr &k2);
	void LeftRotate(AvlNodeptr &k2);
	void DoubleLeftRightRotate(AvlNodeptr &thisNode);
	void DoubleRightLeftRotate(AvlNodeptr &thisNode);
	int FindSize(AvlNodeptr thisNode);
	int FindHeight(AvlNodeptr thisNode);
	void Remove(AvlNodeptr &thisNode, string s);
	void DelNode(AvlNodeptr &thisNode);
	bool RFind(AvlNodeptr thisNode, string s);
	int RFindComparisons(AvlNodeptr thisNode, string s);
	string RPreOrderTraverse(AvlNodeptr thisNode);
	int RCountTwoChildren(AvlNodeptr thisNode);
	int RCountOneChild(AvlNodeptr thisNode);
	int RCountLeaves(AvlNodeptr thisNode);

};

#endif // !ALVTREE_H

