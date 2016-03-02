#include <iostream>
#include <fstream>
#include <string>
#include "AvlTree.h"
#include "BSTree.h"

using namespace std;

int main() {

	ifstream finDictionary, hw4Input;
	string tempString,tempValue;
	AvlTree Tree, DriverTree;
	int i, tempInt;
	char tempChar;
	bool done = false;

	finDictionary.open("dictionary.txt");
	hw4Input.open("hw4_input.txt");

	while (!finDictionary.eof()) {
		finDictionary >> tempString;
		i = 0;
		while (i < tempString.length()-1) {
			tempString[i] = tolower(tempString[i]);
			i++;
		}
		Tree.Insert(tempString);
		//stop++;
	}

	while (!hw4Input.eof()) {
		hw4Input >> tempString;
		while (i < tempString.length() - 1) {
			tempString[i] = tolower(tempString[i]);
			i++;
		}
		hw4Input >> tempValue;
		
		if (tempString == "insert") {
			DriverTree.Insert(tempValue);
		}
		else if (tempString == "remove") {
			DriverTree.Delete(tempValue);
		}
	}
	cout << endl << "DRIVER TREE SECTION" << endl << endl;
	cout << " Pre order traversal: ";
	tempString = DriverTree.Traverse();
	cout << endl << " Descending order: " << tempString;
	cout << endl <<" Driver Tree Root: "<< DriverTree.GetRoot();
	cout << endl <<" Driver Tree Height: " << DriverTree.Height();
	cout << endl <<" Driver Tree Size: "<< DriverTree.Size();
	cout << endl <<" Driver Tree two children count: "<< DriverTree.CountTwoChildren();
	cout << endl <<" Driver Tree, one child count: "<< DriverTree.CountOneChild();
	cout << endl <<" Driver Tree, number of leaves: "<< DriverTree.CountLeaves();


	cout << Tree.Height() << endl;
	cout << Tree.Size()<<endl;
	cout << Tree.GetRoot()<<endl;
	tempString = Tree.Traverse();
	cout << endl << Tree.CountTwoChildren();

	Tree.Delete("abandon");
	Tree.Delete("a");

	system("pause");

	finDictionary.close();

	return 0;
}