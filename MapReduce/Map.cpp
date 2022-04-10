/*Colton Wilson and Anthony Redamonti
*CSE 687- Object Oriented Design
*Syracuse University
*MapReduce - Phase #1
*04/07/22
*This program contains the function definitions to the member functions located in Map.h
*/

//Directives
#include "Map.h"

#include <iostream>
#include <vector>

//Namespaces
using std::cout;
using std::string;
using std::vector;

//default constructor
Map::Map(){}
//constructor with two parameters
Map::Map(string fileName, vector<string> vec){}
//**********Destructor*********
Map::~Map(){}
vector<string> Map::tokenize(vector<string>& vec){}
void Map::write(string& fileName, vector<string>& vec){}