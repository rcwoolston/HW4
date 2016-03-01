#include <iostream>
#include <fstream>
#include <string>
#include "AvlTree.h"

using namespace std;

int main() {

	ifstream finDictionary, hw4Input;
	string tempString,instructions,value;
	AvlTree Tree, TestTree;
	int i, j, stop = 0;
	char tempChar;
	bool done = false;

	finDictionary.open("dictionary.txt");
	//hw4Input.open("hw4_input.txt");

	while (!finDictionary.eof() && stop < 10) {
		finDictionary >> tempString;
		i = 0;
		while (i < tempString.length()-1) {
			tempString[i] = tolower(tempString[i]);
			i++;
		}
		Tree.Insert(tempString);
		stop++;
	}

	cout << Tree.Height() << endl;
	cout << Tree.Size()<<endl;
	cout << Tree.GetRoot()<<endl;
	tempString = Tree.Traverse();

	Tree.Delete("abandon");
	Tree.Delete("a");

	system("pause");

	finDictionary.close();

	return 0;
}