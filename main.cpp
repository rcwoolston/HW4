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