/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Map.h

---Note: This file does include the BOOST library in order to compile.

Below is the "Map" class.
The Map class is called by the Workflow class.
The constructor will take a string reference of the file to write too and a string reference of a line of raw data.
This will then call the tokenize() function to remove punctuation, whitespace, and capitalization.
Each word will then be given to the exportt() function to be written into the output file.

Example input data:  The dog likes to jump.
Example output data: ("the", 1), ("dog", 1), ("likes", 1), ("to", 1), ("jump", 1)

*/

// Header Guard
#ifndef MAP_H
#define MAP_H

//Directives
#include<string>
#include <vector>
#include<boost/tokenizer.hpp>

//Namespaces
using std::string;
using std::vector;
using boost::tokenizer;


class Map
{
public:
	//default constructor
	Map();
	//constructor with two parameters string file name and string line of raw data
	Map(string& fileName, string& lineOfData);
	//**********Destructor*********
	~Map();

	//**********Member Functions**********
	void tokenize(string& fileName, string& lineOfData);
	//Pre-Condition:File name has been created and is open. Line of raw data taken from input file
	//Post-Condition:N/A
	//remove punctuation, whitespace and capitalization from line of data

	void exportt(string& fileName, tokenizer<>::iterator& word);
	//Pre-Condition:File name has been created and is open. one word from raw data has been taken from string
	//Post-Condition:file name has been appended with the word
	//Write into temporary  file

};




#endif