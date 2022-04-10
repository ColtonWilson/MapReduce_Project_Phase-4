/*Colton Wilson and Anthony Redamonti
*CSE 687- Object Oriented Design
*Syracuse University
*MapReduce - Phase #1
*04/07/22
*This program contains the Workflow class ...........TODO.............
*/
//Identifier
#ifndef WORKFLOW_H
#define WORKFLOW_H
class WorkFlow
{
public:
	//default constructor
	WorkFlow();
	//WorkFlow constructor with three parameters
	WorkFlow(string inputFile, string intermediateFile, string outputFile);
	
	//**********Destructor*********
	~WorkFlow();

	//**********Setters**********
	void setInputFileLocation(const string& userInputFile);
	//Pre-condition: None
	//Post-conditon:inputFileLocation has value updated
	//update value in inputFileLocation
	void setIntermediateFileLocation(const string& userIntermediateFile);
	//Pre-condition: None
	//Post-conditon:intermediateFileLocation has value updated
	//update value in intermediateFileLocation
	void setOutputFileLocation(const string& userOutputFile);
	//Pre-condition: None
	//Post-conditon:outputFileLocation has value updated
	//update value in outputFileLocation

	//**********Getters**********
	const string getInputFileLocation(void);
	//Pre-condition: inputFileLocation has a value
	//Post-conditon: none
	//Return the value in inputFileLocation
	const string getIntermediateFileLocation(void);
	//Pre-condition: intermediateFileLocation has a value
	//Post-conditon: none
	//Return the value in intermediateFileLocation
	const string getOutputFileLocation(void);
	//Pre-condition: outputFileLocation has a value
	//Post-conditon: none
	//Return the value in outputFileLocation

private:
	string inputFileLocation{ "Unknown" }; //Data member to save location of input text file...just read from
	string intermediateFileLocation{ "Unknown" };//Data member to save location of intermediate file...will be written and then read
	string outputFileLocation{ "Unknown" };//Data member to save location of the output file...will be written too

};
#endif