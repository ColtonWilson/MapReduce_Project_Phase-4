/*Colton Wilson and Anthony Redamonti
*CSE 687- Object Oriented Design
*Syracuse University
*MapReduce - Phase #1
*04/07/22
*This program contains the FileManagement class ...........TODO.............
*/

//Identifier
#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

//Directives
#include "Workflow.h"
#include <fstream>

using std::ifstream;
using std::ofstream;



class FileManagement : public WorkFlow
{
public:
	//default constructor
	FileManagement();

	//**********Destructor*********
	~FileManagement();

	//**********Member Functions**********
	//template < typename T >
	void openFileInstream(ifstream& fileStream, const string userFile);
	//Pre-condition: File Directorys has been given
	//Post-conditon:Files have been opened as an instream
	//Open the diractory files that user has given and read
	void openFileOutstream(ofstream& fileStream, const string& userFile);
	//Pre-condition: File Directorys has been given
	//Post-conditon:Files have been opened as an outstream
	//Open the diractory files that user has given and read
	
	void fileCorrupt(ifstream& fileStream);
	//Pre-condition: File Directorys has been given
	//Post-conditon:Failure message will print to screen if file open fails. 
	//Check to see if file failed to open
	void closeInputFile(ifstream& fileToClose);
	//Pre-condition: File Directory has been given
	//Post-conditon:File has been closed
	//Close the diractory files that user has given
	void closeOutputFile(ofstream& fileToClose);
	//Pre-condition: File Directory has been given
	//Post-conditon:File has been closed
	//Close the diractory files that user has given
	void writeToTempFile(ofstream& fileStream, const string& data);

	void readFromFile(ifstream& fileStream, string& data);

	void clearFile(ofstream& fileStream);


private:
	

};
#endif