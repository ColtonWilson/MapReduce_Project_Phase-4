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
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

//default constructor
FileManagement::FileManagement(){}

//**********Destructor*********
FileManagement::~FileManagement(){}

void FileManagement::openFileInstream(const string& userFile)
{
	ifstream inStream;
	inStream.open(userFile);
	fileCorrupt(inStream);
	
	


}
void FileManagement::openFileOutstream(const string& userFile)
{
	ofstream outStream;
	outStream.open(userFile);

}

void FileManagement::fileCorrupt(const ifstream& fileToCheck)
{
	//Check to see if file failed to open
	if (fileToCheck.fail())
	{
		//If true, print fail to screen and EXIT
		cout << "Input file failed to open" << endl;
		exit(EXIT_FAILURE);


	}
	else
	{
		cout << "Input file succesfully opened." << endl;
	}

}

void FileManagement::closeFile(ifstream& fileToClose) { fileToClose.close(); }
const ifstream& FileManagement::getInputStreamSaved(void) { return inStreamSaved; }
//const ofstream FileManagement::getOutputStreamSaved(void) { return outStreamSaved; }
