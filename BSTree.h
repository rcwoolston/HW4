#ifndef BSTREE_H
#define BSTREE_H
#include <string>
#include <iostream>

using namespace std;
class TreeNode
{
public:
	string word;
	TreeNode *ptrLeft, *ptrRight;
	int height;
	TreeNode(); // Default constructor.
	TreeNode(string s); // Constructor with one parameter
};
typedef TreeNode* TreeNodeptr;

class BSTree
{
private:
	TreeNodeptr root;
public:
	BSTree(); // Initializes root to NULL.
	BSTree(const BSTree &tree); //Copy constructor
	~BSTree(); // Destructor.
	int Size(); // Return the number of nodes in the tree.
	int Height(); // Return the path length from the root node to a deepest leaf node in the tree.
	void Delete(string s); // Delete a string.
	string Traverse(); // return a string containing all strings stored in the binary search tree in the descending order.
	void Insert(string s); // Insert a string into the binary search tree.
	bool Find(string s); // search s in the list. Return true if s is found; otherwise, return false.
	void Printp();
	string GetRoot();
	int CountTwoChildren();
	int CountOneChild();
	int CountLeaves();
	int GetHeight(TreeNodeptr thisNode);
	int FindComparisons(string s);

private:
	// You need to add private functions to implement the recursive solutions.
	int FindHeight(TreeNode* node);
	int FindSize(TreeNode* node);
	void DeleteRec(TreeNode* node);
	TreeNode* Remove(TreeNode* node, string temp);
	void copyTree(TreeNode *&thisRoot,TreeNode *&source);
	string preorderTraverse(TreeNodeptr thisNode);
	TreeNode* FindMax(TreeNode *node);
	void PrintPrivate(TreeNode* p, int indent = 0);
	int RCountTwoChildren(TreeNodeptr thisNode);
	int RCountOneChild(TreeNodeptr thisNode);
	int RCountLeaves(TreeNodeptr thisNode);
	void RInsert(TreeNodeptr &thisNode, string s);
	int RFindComparisons(TreeNodeptr thisNode, string s);
};
#endif