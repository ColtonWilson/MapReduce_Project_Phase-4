/*Colton Wilson and Anthony Redamonti
*CSE 687- Object Oriented Design
*Syracuse University
*MapReduce - Phase #1
*04/07/22
*This program contains the function definitions to the member functions located in FileManagement.h
*/
/*File Management*/
//Directives
#include "FileManagement.h"

#include <iostream>

#include <fstream>

//Namespaces
using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ofstream;

//default constructor
FileManagement::FileManagement()
{
	ifstream inStream;


}

//**********Destructor*********
FileManagement::~FileManagement(){}

void FileManagement::openFile(const string& userFile){}

void FileManagement::fileCorrupt(const string& userFile){}

void FileManagement::closeFile(const string& userFile){}
