#include <string>
#include "BSTree.h"
#include <iostream>
#include <vector>
#include <iomanip>

TreeNode::TreeNode() {  // Default constructor.
	ptrRight = NULL;
	ptrLeft = NULL;
	word = "";
}
TreeNode::TreeNode(string s) { // Constructor with one parameter
	ptrRight = NULL;
	ptrLeft = NULL;
	word = s;
}

BSTree::BSTree() { // Initializes root to NULL.
	root = NULL;
}
BSTree::BSTree(const BSTree &tree) { //Copy constructor
	if (tree.root == NULL) {
		root = NULL;
	}
	else {
		TreeNode* treeRoot = tree.root;
		copyTree(this->root, treeRoot);
	}
}
void BSTree::copyTree(TreeNode *& thisRoot, TreeNode *& source) {
	if (source == NULL) {
		thisRoot = NULL;
	}
	else
	{
		thisRoot = new TreeNode;
		thisRoot->word = source->word;
		copyTree(thisRoot->ptrLeft, source->ptrLeft);
		copyTree(thisRoot->ptrRight, source->ptrRight);
	}
}
BSTree::~BSTree() { // Destructor.
	DeleteRec(root);
}
int BSTree::Size() { // Return the number of nodes in the tree.
	return FindSize(root);
}
int BSTree::Height() { // Return the path length from the root node to a deepest leaf node in the tree.
	return FindHeight(root);
}
void BSTree::Delete(string s) { // Delete a string.
	Remove(root, s);
}
string BSTree::Traverse() { // return a string containing all strings stored in the binary search tree in
	return preorderTraverse();		   // the descending order.
}
string BSTree::preorderTraverse() {		
	string words="";
	PreOrder(root, words);
	return words;
}
void BSTree::PreOrder(TreeNode *node, string &words) {
	if (node == NULL) {
		return;
	}
	words.append(" " + node->word);
	PreOrder(node->ptrLeft, words);
	PreOrder(node->ptrRight, words);
}
void BSTree::Insert(string s) { // Insert a string into the binary search tree.
		TreeNode *temp = new TreeNode(s);

	if (root == NULL) {
		root = new TreeNode(s);
		temp = root;
	}
	else {
		bool inserted = false;
		TreeNode* node = root;

		while (!inserted) {
			int value = temp->word.compare(node->word);
			if (value == 0) {
				delete temp;
				inserted = true;
			}
			else if (value < 0) {
				if (node->ptrLeft == NULL) {
					node->ptrLeft = temp;
					inserted = true;
				}
				else {
					node = node->ptrLeft;
				}
			}
			else {
				if (node->ptrRight == NULL) {
					node->ptrRight = temp;
					inserted = true;
				}
				else {
					node = node->ptrRight;
				}
			}
		}
	}
}


bool BSTree::Find(string s) { // search s in the list. Return true if s is found; otherwise, return false.
	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(s[i]);
	}
	TreeNode *temp = new TreeNode(s);
	bool found = false;

	if (root == NULL) {
		return found;
	}
	else {
		TreeNode* node = root;
		while (node!=NULL && !found) {
			int value = temp->word.compare(node->word);
			if (value == 0) {
				found = true;
				return found;
			}
			else if (value < 0) {
				node = node->ptrLeft;
			}
			else {
				node = node->ptrRight;	
			}
		}
	}
	return found;
}

int BSTree::FindHeight(TreeNode* node) {

	if (node == NULL) {
		return -1;
	}

	int leftValue = FindHeight(node->ptrLeft);
	int rightValue = FindHeight(node->ptrRight);

	if (leftValue > rightValue)
		return leftValue + 1;
	else
		return rightValue + 1;

}

int BSTree::FindSize(TreeNode* node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return FindSize(node->ptrLeft) + FindSize(node->ptrRight) + 1;
	}
}
void BSTree::DeleteRec(TreeNode* node)
{
	if (node->ptrLeft != NULL) {
		DeleteRec(node->ptrLeft);
	}
	if (node->ptrRight != NULL) {
		DeleteRec(node->ptrRight);
	}
	delete node;
	root = NULL;
}

TreeNode* BSTree::Remove(TreeNode* node,string temp)
{

	if (node == NULL) {
		return node;
	}
	else {
		int value = node->word.compare(temp);
		if (value > 0) {
			node->ptrLeft = Remove(node->ptrLeft, temp);
		}
		else if (value < 0) {
			node->ptrRight = Remove(node->ptrRight, temp);
		}
		else if (value == 0) {
			if (node->ptrLeft == NULL && node->ptrRight == NULL) {
				delete node;
				node = NULL;
				//return NULL;
			}
			else if (node->ptrLeft == NULL) {
				TreeNode *temp = node;
				node = node->ptrRight;
				delete temp;
				//return node;
			}
			else if (node->ptrRight == NULL) {
				TreeNode *temp = node;
				node = node->ptrLeft;
				delete temp;
				//return node;
			}
			else {
				TreeNode *temp = FindMax(node->ptrLeft);
				node->word= temp->word;
				node->ptrLeft = Remove(node->ptrLeft, temp->word);
				//delete temp;
			}
		}
	}
	return node;
}

TreeNode* BSTree::FindMax(TreeNode *node) {
	while (node->ptrRight != NULL) {
		node = node->ptrRight;
	}
	return node;
}

void BSTree::PrintPrivate(TreeNode* p, int indent)
{
	if (p != NULL) {
		if (p->ptrLeft) PrintPrivate(p->ptrLeft, indent + 10);
		if (p->ptrRight) PrintPrivate(p->ptrRight, indent + 10);
		if (indent) {
			std::cout << setw(indent) << ' ';
		}
		cout << p->word << "\n ";
	}
}


void BSTree::Printp() {
	PrintPrivate(root, 0);
}