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


class FileManagement : public WorkFlow
{
public:
	//default constructor
	FileManagement();

	//**********Destructor*********
	~FileManagement();
	
	//**********Member Functions**********
	void openFile(const string& userFile);
	//Pre-condition: File Directorys has been given
	//Post-conditon:Files have been opened
	//Open the diractory files that user has given
	void fileCorrupt(const string& userFile);
	//Pre-condition: File Directorys has been given
	//Post-conditon:Failure message will print to screen if file open fails. 
	//Check to see if file failed to open
	void closeFile(const string& userFile);
	//Pre-condition: File Directory has been given
	//Post-conditon:File has been closed
	//Close the diractory files that user has given


private:


};
#endif
