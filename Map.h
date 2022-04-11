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

using std::string;

class Map
{
public:
	//default constructor
	Map();
	//constructor with two parameters
	Map(string fileName, string vec);
	//**********Destructor*********
	~Map();
	string tokenize(string& vec);
	void write(string& fileName, string vec);


private:


};




#endif