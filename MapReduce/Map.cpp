/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Map.cpp

---Note: This file does include the BOOST library in order to compile. 

Below is the Map.cpp.
The Map class is called by the Workflow class.
The constructor will take a string reference of the file to write too and a string reference of a line of raw data.
This will then call the tokenize() function to remove punctuation, whitespace, and capitalization.
Each word will then be given to the exportt() function to be written into the output file. 

Example input data:  The dog likes to jump.
Example output data: ("the", 1), ("dog", 1), ("likes", 1), ("to", 1), ("jump", 1)

*/

//Directives
#include "Map.h"
#include "FileManagement.h"
#include<boost/tokenizer.hpp>//boost library

#include <iostream>
#include <fstream>
#include<string>

//Namespaces
using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;

using boost::tokenizer;

//default constructor
Map::Map() {}
//constructor with two parameters
Map::Map(string& fileName, string& lineOfData) { tokenize(fileName, lineOfData); }

//**********Destructor*********
Map::~Map() {}

//tokenize function to remove punctuation, whitespace and capitalization
void Map::tokenize(string& fileName, string& lineOfData)
{
	//Work through the sting and make everything lower case
	std::for_each(lineOfData.begin(), lineOfData.end(), [](char& c) {
		c = ::tolower(c);
		});
	
	//intitate a tokenizer object with the raw data
	tokenizer<> tok(lineOfData);
	//Work through the tokenizer and call exportt() with each word
	for (tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg)
	{
		exportt(fileName, beg);
	}
	
}
//Write the word into the output file
void Map::exportt(string& fileName, tokenizer<>::iterator& word)
{
	//Initiate an output stream
	ofstream outputFileStream;
	//Create an object of the FileManagement class
	FileManagement FileStreamSystem;
	//Open the stream with the output file
	FileStreamSystem.openFileOutstream(outputFileStream, fileName);
	//Write to the temp file with the given word
	FileStreamSystem.writeToTempFile(outputFileStream, *word);


}