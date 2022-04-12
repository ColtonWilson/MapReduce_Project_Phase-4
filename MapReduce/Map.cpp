/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Map.cpp

Below is the Map.cpp.
The Map class is called by the Workflow class.

Example input data:  The dog likes to jump.
Example output data: ("the", 1), ("dog", 1), ("likes", 1), ("to", 1), ("jump", 1)

*/

//Directives
#include "Map.h"
#include "FileManagement.h"
#include<boost/tokenizer.hpp>

#include <iostream>
#include <fstream>
#include<string>

using std::string;

//Namespaces
using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using boost::tokenizer;

//default constructor
Map::Map() {}
//constructor with two parameters
Map::Map(string& fileName, string& lineOfData) 
{
	
	tokenize(fileName, lineOfData);
	

}
//**********Destructor*********
Map::~Map() {}
void Map::tokenize(string& fileName, string& lineOfData)
{
	std::for_each(lineOfData.begin(), lineOfData.end(), [](char& c) {
		c = ::tolower(c);
		});

	tokenizer<> tok(lineOfData);
	for (tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg)
	{
		exportt(fileName, beg);
	}
	//exportt(fileName, );
	
}
void Map::writeToBuffer(string& vec){}

void Map::exportt(string& fileName, tokenizer<>::iterator& word)
{
	ofstream outputFileStream;
	FileManagement FileStreamSystem;
	FileStreamSystem.openFileOutstream(outputFileStream, fileName);
	FileStreamSystem.writeToTempFile(outputFileStream, *word);


}