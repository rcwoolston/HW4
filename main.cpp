#include <iostream>
#include <fstream>
#include <string>
#include "AvlTree.h"
#include "BSTree.h"
#include <vector>
#include <algorithm>

vector<string> readInWordsAndShuffle(vector<string> words);
vector<string> readInLetter(vector<string> letter);
void misspelledWordsB(BSTree& truthTree, vector<string> letter);
void misspelledWordsA(AvlTree& truthTree, vector<string> letter);

using namespace std;

int main() {

	ifstream hw4Input;
	string tempString,tempValue;
	AvlTree ATree, DriverTree;
	BSTree BTree, BDriverTree;
	vector <string> dictionaryVect, letterVect;
	int i, tempInt;
	char tempChar;
	bool done = false;

	hw4Input.open("hw4_input.txt");

	//Read in driver file
	while (!hw4Input.eof()) {
		//Read in instructions for the value
		hw4Input >> tempString;
		//Ensure lowercase for string match
		i = 0;
		while (i < tempString.length()) {
			tempString[i] = tolower(tempString[i]);
			i++;
		}
		//Read in input value
		hw4Input >> tempValue;
		
		//Perform operation on read in value
		if (tempString == "insert") {
			DriverTree.Insert(tempValue);
			BDriverTree.Insert(tempValue);
		}
		else if (tempString == "remove") {
			DriverTree.Delete(tempValue);
			BDriverTree.Delete(tempValue);
		}
	}

	hw4Input.close();

	cout << endl << "AVL DRIVER TREE SECTION" << endl << endl;
	cout << " Pre order traversal: ";
	tempString = DriverTree.Traverse();
	cout << endl << " Descending order: " << tempString;
	cout << endl <<" Driver Tree Root: "<< DriverTree.GetRoot();
	cout << endl <<" Driver Tree Height: " << DriverTree.Height();
	cout << endl <<" Driver Tree Size: "<< DriverTree.Size();
	cout << endl <<" Driver Tree two children count: "<< DriverTree.CountTwoChildren();
	cout << endl <<" Driver Tree, one child count: "<< DriverTree.CountOneChild();
	cout << endl <<" Driver Tree, number of leaves: "<< DriverTree.CountLeaves();

	cout << endl << endl;
	cout << endl << "BSTree DRIVER TREE SECTION" << endl << endl;
	cout << " Pre order traversal: ";
	tempString = BDriverTree.Traverse();
	cout << endl << " Descending order: " << tempString;
	cout << endl << " Driver Tree Root: " << BDriverTree.GetRoot();
	cout << endl << " Driver Tree Height: " << BDriverTree.Height();
	cout << endl << " Driver Tree Size: " << BDriverTree.Size();
	cout << endl << " Driver Tree two children count: " << BDriverTree.CountTwoChildren();
	cout << endl << " Driver Tree, one child count: " << BDriverTree.CountOneChild();
	cout << endl << " Driver Tree, number of leaves: " << BDriverTree.CountLeaves();

	//Read in dictionary of words
	dictionaryVect = readInWordsAndShuffle(dictionaryVect);

	//Create BS Tree/Avl Tree
	int j = 0;
	while (j < dictionaryVect.size()) {

		tempString = dictionaryVect[j];
		i = 0;
		while (i < tempString.length()) {
			tempString[i] = tolower(tempString[i]);
			i++;
		}
		ATree.Insert(tempString);
		BTree.Insert(tempString);
		j++;
		
	}


	//Read in Letter
	letterVect = readInLetter(letterVect);

	cout << endl << endl;
	cout << "MISSPELLED WORDS";
	cout << endl << "BSTree";
	misspelledWordsB(BTree, letterVect);
	cout << endl;
	cout << endl << "AvlTree";
	misspelledWordsA(ATree, letterVect);


	//Output area
	cout << endl << endl;
	cout << "DICTIONARY SECTION";
	cout << endl << endl;
	cout << "BSTree root:  " << BTree.GetRoot() << "      ATree root: " << ATree.GetRoot() << endl;
	cout << "BSTree size:  " << BTree.Size() << "      ATree size: " << ATree.Size() << endl;
	cout << "BSTree height:  " << BTree.Height() << "      ATree height: " << ATree.Height() << endl;
	cout << "BSTree 2 children:  " << BTree.CountTwoChildren() << "      2 children: " << ATree.CountTwoChildren() << endl;
	cout << "BSTree 1 child:  " << BTree.CountOneChild() << "      ATree 1 child: " << ATree.CountOneChild() << endl;
	cout << "BSTree leaf count:  " << BTree.CountLeaves() << "      ATree leaf count: " << ATree.CountLeaves() << endl;
	cout << endl << endl;

	
	cout << "COMPARISONS " << endl;
	i = 0;
	int a=0, aTotal =0, b = 0, bTotal=0;
	int count = 0;
	while (i < letterVect.size()) {
		count++;
		a = ATree.FindComparisons(letterVect[i]);
		b = BTree.FindComparisons(letterVect[i]);
		cout << "WORD: " << letterVect[i] << "    BSTree comparisons: " << b << "    AvlTree comparisons: " << a << endl;
		aTotal += a;
		bTotal += b;
		i++;
	}
	cout << endl;
	cout<<"BSTree average comparison: " << bTotal/count << "    AvlTree average comparison: " << aTotal/count << endl;

	int choice;
	string insertValue;
	bool found;
	AvlTree tempTree;

	while (!done) {
		found = false;
		cout << endl << endl << "MAIN MENU to test all functions" << endl;
		cout << "(0) Exit" << endl;
		cout << "(1) Constructor, copy constructor, and destructor" << endl;
		cout << "(2) Size" << endl;
		cout << "(3) Hieght" << endl;
		cout << "(4) Traverse" << endl;
		cout << "(5) Find" << endl;
		cout << "(6) Delete" << endl;
		cout << "(7) Insert" << endl;

		cout << endl << endl << "Driver Tree:  ";
		DriverTree.Traverse();
		cout << endl;
		cout << endl;
		cout << "Choice: ";

		cin >> choice;

		switch (choice)
		{
		case 0: done = true;
			break;
		case 1: cout << "Tree before copy: " << tempTree.Traverse() << endl;
			tempTree = DriverTree; //Contains the constructor, copy constructor, and destructor
			cout << "Tree after copy: ";
			tempTree.Traverse();
			cout <<endl<< "Driver Tree: ";
			DriverTree.Traverse();
			cout << endl;
			break;
		case 2:cout << "Example Size of Driver Tree:  " << DriverTree.Size();
			break;
		case 3:cout << "Example Height of Driver Tree: " << DriverTree.Height();
			break;
		case 4: cout << "Driver Tree pre-order Traverse: " << DriverTree.Traverse();
			break;
		case 5: cout << "Find Value in driver tree:  ";
			cin >> insertValue;
			found = DriverTree.Find(insertValue);
			if (found) {
				cout << endl << "Found " << insertValue;
			}
			else {
				cout << endl << "Did not find " << insertValue;
			}
			break;
		case 6: cout << "Delete value in driver tree: ";
			cin >> insertValue;
			cout << "Before deleting:  ";
			DriverTree.Traverse();
			DriverTree.Delete(insertValue);
			cout << endl << "After deleting: ";
			DriverTree.Traverse();
			break;
		case 7: cout << "Insert value in driver tree: ";
			cin >> insertValue;
			for (int i = 0; i < insertValue.length(); i++) {
				insertValue[i] = tolower(insertValue[i]);
			}
			cout << "Before inserting:  ";
			DriverTree.Traverse();
			DriverTree.Insert(insertValue);
			cout << endl << "After inserting: ";
			DriverTree.Traverse();
			break;
		default: cout << endl << endl << "Invalid choice" << endl;
			break;
		}
	}


	system("pause");

	return 0;
}

vector<string> readInWordsAndShuffle(vector<string> words) {
	ifstream fin;
	fin.open("dictionary.txt");
	string temp;

	while (!fin.eof()) {
		fin >> temp;
		for (int i = 0; i < temp.length(); i++) {
			temp[i] = tolower(temp[i]);
		}
		words.push_back(temp);
	}

	random_shuffle(words.begin(), words.end());

	fin.close();

	return words;
}

vector<string> readInLetter(vector<string> letter) {
	ifstream finLetter;
	finLetter.open("letter.txt");
	string temp;

	while (!finLetter.eof()) {
		finLetter >> temp;
		for (int i = 0; i < temp.length(); i++) {
			temp[i] = tolower(temp[i]);
		}
		letter.push_back(temp);
	}

	finLetter.close();

	return letter;
}

void misspelledWordsB(BSTree& truthTree, vector<string> letter) {
	bool match = true;
	cout << endl << endl << "Misspelled words: ";
	for (int i = 0; i < letter.size(); i++) {
		match = (truthTree).Find(letter[i]);
		if (!match) {
			cout << letter[i] << " ";
		}
	}
}
void misspelledWordsA(AvlTree& truthTree, vector<string> letter) {
	bool match = true;
	cout << endl << endl << "Misspelled words: ";
	for (int i = 0; i < letter.size(); i++) {
		match = (truthTree).Find(letter[i]);
		if (!match) {
			cout << letter[i] << " ";
		}
	}
}