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
	void openFileInstream(const string& userFile);
	//Pre-condition: File Directorys has been given
	//Post-conditon:Files have been opened as an instream
	//Open the diractory files that user has given and read
	void openFileOutstream(const string& userFile);
	//Pre-condition: File Directorys has been given
	//Post-conditon:Files have been opened as an outstream
	//Open the diractory files that user has given and read
	void fileCorrupt(const ifstream& fileToCheck);
	//Pre-condition: File Directorys has been given
	//Post-conditon:Failure message will print to screen if file open fails. 
	//Check to see if file failed to open
	void closeFile(ifstream& fileToClose);
	//Pre-condition: File Directory has been given
	//Post-conditon:File has been closed
	//Close the diractory files that user has given

	
	const ifstream& getInputStreamSaved(void);
	//Pre-condition: inputStreamSaved has a value
	//Post-conditon: none
	//Return the value in inputStreamSaved
	//const ofstream getOutputStreamSaved(void);
	//Pre-condition: outputStreamSaved has a value
	//Post-conditon: none
	//Return the value in outputStreamSaved


private:
	ifstream inStreamSaved;
	//ofstream outStreamSaved;

};
#endif
