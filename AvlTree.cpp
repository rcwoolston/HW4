#include "AvlTree.h"
#include <string>
#include <algorithm>

using namespace std;

AvlNode::AvlNode() {
	height = -1;
	ptrLeft = ptrRight = NULL;
	word = "";
}
AvlNode::AvlNode(string s) {
	height = 0;
	ptrLeft = ptrRight = NULL;
	word = s;
}
AvlTree::AvlTree() {
	root = NULL;
}
AvlTree::~AvlTree() {
	DeleteTree(root);
}
string AvlTree::GetRoot() {
	return root->word;
}
void AvlTree::DeleteTree(AvlNodeptr thisNode) {
	if (thisNode->ptrLeft != NULL) {
		DeleteTree(thisNode->ptrLeft);
	}
	if (thisNode->ptrRight != NULL) {
		DeleteTree(thisNode->ptrRight);
	}
	delete thisNode;
	root = NULL;
}
AvlTree::AvlTree(const AvlTree& tree) {
	if (tree.root == NULL) {
		root = NULL;
	}
	else {
		AvlNode* treeRoot = tree.root;
		CopyTree(this->root, treeRoot);
	}
}

void AvlTree::CopyTree(AvlNodeptr &thisNode, AvlNodeptr &source) {
	if (source == NULL) {
		thisNode = NULL;
	}
	else {
		thisNode = new AvlNode(source->word);
		CopyTree(thisNode->ptrLeft, source->ptrLeft);
		CopyTree(thisNode->ptrRight, source->ptrRight);
	}
}
void AvlTree::Insert(string s) {
	RInsert(root, s);
}
void AvlTree::RInsert(AvlNodeptr &thisNode, string s) {
	if (thisNode == NULL) {
		thisNode = new AvlNode(s);
	}
	else {
		int value = s.compare(thisNode->word);
		if (value == 0) {
			return;
		}
		else if (value < 0) {
			RInsert(thisNode->ptrLeft, s);
		}
		else {
			RInsert(thisNode->ptrRight, s);
		}
	}
	Balance(thisNode);
}

int AvlTree::GetHeight(AvlNodeptr thisNode) {
	if (thisNode == NULL) {
		return -1;
	}
	else {
		return thisNode->height;
	}
}

void AvlTree::Balance(AvlNodeptr &thisNode) {
	if (thisNode == NULL) {
		return;
	}
	if ((GetHeight(thisNode->ptrLeft) - GetHeight(thisNode->ptrRight)) > 1) {
		if (GetHeight(thisNode->ptrLeft->ptrLeft) >= GetHeight(thisNode->ptrLeft->ptrRight)) {
			RightRotate(thisNode);
		}
		else { //Left Right Case
			DoubleLeftRightRotate(thisNode);
		}
	}
	if ((GetHeight(thisNode->ptrRight) - GetHeight(thisNode->ptrLeft)) > 1) {
		if (GetHeight(thisNode->ptrRight->ptrRight) >= GetHeight(thisNode->ptrRight->ptrLeft)) {
			LeftRotate(thisNode);
		}
		else { //Left Right Case
			DoubleRightLeftRotate(thisNode);
		}
	}
	thisNode->height = 1 + max(GetHeight(thisNode->ptrLeft), GetHeight(thisNode->ptrRight));
}

void AvlTree::RightRotate(AvlNodeptr &k2) {
		AvlNodeptr k1 = k2->ptrLeft;
		k2->ptrLeft = k1->ptrRight;
		k1->ptrRight = k2;
	
		//Update height of K2
		k2 ->height = 1 + max(GetHeight(k2->ptrLeft), GetHeight(k2->ptrRight));
	
		//Update the height of k1
		k1 -> height = 1 + max(GetHeight(k1->ptrLeft), GetHeight(k1->ptrRight));
		k2 = k1;
}
void AvlTree::LeftRotate(AvlNodeptr &k2) {
		AvlNodeptr k1 = k2->ptrRight;
		k2->ptrRight = k1->ptrLeft;
		k1->ptrLeft = k2;
	
		//Update height of K2
		k2->height = 1 + max(GetHeight(k2->ptrLeft), GetHeight(k2->ptrRight));
	
		//Update the height of k1
		k1->height = 1 + max(GetHeight(k1->ptrLeft), GetHeight(k1->ptrRight));
		k2 = k1;

}
void AvlTree::DoubleLeftRightRotate(AvlNodeptr &thisNode) {
		LeftRotate(thisNode->ptrLeft);
		RightRotate(thisNode);
}
void AvlTree::DoubleRightLeftRotate(AvlNodeptr &thisNode) {
		RightRotate(thisNode->ptrRight);
		LeftRotate(thisNode);
}
int AvlTree::Size() { //Returns the number of nodes in the tree
	return FindSize(root);
}

int AvlTree::FindSize(AvlNodeptr thisNode) {
	if (thisNode == NULL) {
		return 0;
	}
	else {
		return FindSize(thisNode->ptrLeft) + FindSize(thisNode->ptrRight) + 1;
	}
}

int AvlTree::Height() {
	return FindHeight(root);
}
int AvlTree::FindHeight(AvlNodeptr thisNode) {
	if (thisNode == NULL) {
		return -1;
	}
	int leftValue = FindHeight(thisNode->ptrLeft); 
	int rightValue = FindHeight(thisNode->ptrRight);

	if (leftValue > rightValue) {
		return leftValue + 1;
	}
	else {
		return rightValue + 1;
	}
}

void AvlTree::Delete(string s) {
	Remove(root, s);
}

void AvlTree::Remove(AvlNodeptr &thisNode, string s) {
	if (thisNode == NULL) {
		return;
	}
	else if (thisNode != NULL) {
		int value = s.compare(thisNode->word);

		if (value == 0) {
			DelNode(thisNode);
		}
		else if (value < 0) {
			Remove(thisNode->ptrLeft, s);
		}
		else {
			Remove(thisNode->ptrRight, s);
		}
		Balance(thisNode);
	}
}
void AvlTree::DelNode(AvlNodeptr &thisNode) {
	if (thisNode->ptrLeft == NULL && thisNode->ptrRight == NULL) {
		delete thisNode;
		thisNode = NULL;
	}
	else if (thisNode->ptrLeft == NULL) {
		AvlNodeptr temp = thisNode;
		thisNode = thisNode->ptrRight;
		delete temp;
	}
	else if (thisNode->ptrRight == NULL) {
		AvlNodeptr temp;
		thisNode = thisNode->ptrLeft;
		delete temp;
	}
	else {
		AvlNodeptr temp = thisNode->ptrRight; //Find smallest value in the right subtree of the node
		while (temp->ptrLeft!=NULL)
		{
			temp = temp->ptrLeft;
		}
		thisNode->word = temp->word;
		Remove(thisNode->ptrRight, temp->word);
	}
}

bool AvlTree::Find(string s) {
	return RFind(root, s);
}

bool AvlTree::RFind(AvlNodeptr thisNode, string s) {
	if (thisNode == NULL) {
		return false;
	}
	else if (thisNode != NULL) {
		int value = s.compare(thisNode->word);

		if (value == 0) {
			return true;
		}
		else if (value < 0) {
			RFind(thisNode->ptrLeft, s);
		}
		else {
			RFind(thisNode->ptrRight, s);
		}
	}
}

int AvlTree::FindComparisons(string s) {
	return RFindComparisons(root, s);
}

int AvlTree::RFindComparisons(AvlNodeptr thisNode, string s) {
	if (thisNode == NULL) {
		return 1;
	}
	else if (thisNode != NULL) {
		int value = s.compare(thisNode->word);

		if (value == 0) {
			return 1;
		}
		else if (value < 0) {
			return 1 + RFindComparisons(thisNode->ptrLeft, s);
		}
		else {
			return 1 + RFindComparisons(thisNode->ptrRight, s);
		}
	}
}

string AvlTree::Traverse() {
	return RPreOrderTraverse(root);
}

string AvlTree::RPreOrderTraverse(AvlNodeptr thisNode) {
	string ls,rs;
	
	if (thisNode == NULL) {
		return " ";
	}
	else if (thisNode)
	{
		cout << thisNode->word << " ";
		ls = RPreOrderTraverse(thisNode->ptrLeft);
		rs = RPreOrderTraverse(thisNode->ptrRight);
		return (ls + thisNode->word + rs);
	}
}

int AvlTree::CountTwoChildren() {
	return RCountTwoChildren(root);
}

int AvlTree::RCountTwoChildren(AvlNodeptr thisNode) {
	int count = 0;
	if (thisNode == NULL) {
		return count;
	}
	else {
		if (thisNode->ptrLeft != NULL && thisNode->ptrRight != NULL) {
			count = 1;
		}
		count += RCountTwoChildren(thisNode->ptrLeft);
		count += RCountTwoChildren(thisNode->ptrRight);
		return count;
	}
}

int AvlTree::CountOneChild() {
	return RCountOneChild(root);
}

int AvlTree::RCountOneChild(AvlNodeptr thisNode) {
	int count = 0;
	if (thisNode == NULL) {
		return count;
	}
	else {
		if (thisNode->ptrLeft != NULL && thisNode->ptrRight == NULL) {
			count = 1;
		}
		else if (thisNode->ptrLeft == NULL && thisNode->ptrRight != NULL) {
			count = 1;
		}
		count += RCountOneChild(thisNode->ptrLeft);
		count += RCountOneChild(thisNode->ptrRight);
		return count;
	}
}

int AvlTree::CountLeaves() {
	return RCountLeaves(root);
}

int AvlTree::RCountLeaves(AvlNodeptr thisNode) {
	int count = 0;
	if (thisNode == NULL) {
		return count;
	}
	else {
		if (thisNode->ptrLeft == NULL && thisNode->ptrRight == NULL) {
			count = 1;
		}
		count += RCountLeaves(thisNode->ptrLeft);
		count += RCountLeaves(thisNode->ptrRight);
		return count;
	}
}