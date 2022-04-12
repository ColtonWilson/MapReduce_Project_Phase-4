/*Colton Wilson and Anthony Redamonti
*CSE 687- Object Oriented Design
*Syracuse University
*MapReduce - Phase #1
*04/07/22
*This program contains the Map class ...........TODO.............
*/

//Identifier
#ifndef MAP_H
#define MAP_H
//Directives
#include<string>
#include <vector>
#include<boost/tokenizer.hpp>

using std::string;
using std::vector;
using boost::tokenizer;


class Map
{
public:
	//default constructor
	Map();
	//constructor with two parameters
	Map(string& fileName, string& lineOfData);
	//**********Destructor*********
	~Map();
	void tokenize(string& fileName, string& vec);
	void writeToBuffer(string& vec);
	void exportt(string& fileName, tokenizer<>::iterator& word);
	


private:
	vector<string> buffer; //data memeber to act as a memory

};




#endif