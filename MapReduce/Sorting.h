/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Sorting.h

Below is the "Sorting" class, which is called by the Workflow class.
The constructor takes the intermediate file path as an argument.
The public data member function "format" will format the data for
the Reduce class.

Example input data: ("a", 1), ("the", 1), ("is", 1), ("the", 1), ("a", 1)
Example output data: ("a", [1, 1]), ("the", [1, 1]), ("is", [1])

*/

// Header Guard
#ifndef SORTING_H
#define SORTING_H

// include the iostream and fstream namespaces
#include <iostream>
#include <fstream>
#include <string>
#include <list>

// using the ofstream class from the standard namespace.
using std::ofstream;
using std::ifstream;
using std::string;
using std::list;
using std::to_string;
using std::getline;

class Sorting {
public:
	// Public Data Member Functions

	// Constructor takes a pointer to the intermediate file path as an argument. 
	Sorting(string* intermediateFilePath);

	// Destructor
	virtual ~Sorting();

	// get a pointer to the intermediate file path
	string* getIntermediateFilePath();

	// set the intermediate file path
	void setIntermediateFilePath(string* outputFilePath);

	// formats the data for the Reduce class.
	void format();

private:

	// a private struct "word"
	struct word {
		string key;
		int numberOfOccurrences;
	};

	// a linked list of words
	list<word> wordList;

	// Private Data Member Variables
	string intermediateFilePath;
};

#endif
