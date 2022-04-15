/*
Anthony Redamonti & Colton Wilson
Professor Scott Roueche
CSE 687 Object Oriented Design
Syracuse University
Project 1
4/9/2022

Executive.cpp

Below is Executive.cpp file. 
This file has the main() function.
It will print to screen a banner message for the user.
Prompt the user to input three directories: input, temporary, and output.
It will then create a Workflow class object with these file directories.  



//Namespaces
using std::cout;
using std::cin;
using std::string;

struct Files
{
	string inputFile;
	string intermediateFile;
	string outputFile;

	Files(){}

	explicit Files(const string input, const string intermediate, const string output)
		:inputFile{ input }, intermediateFile{ intermediate }, outputFile{ output }
	{

	}

};



*/


//Directives
#include "Workflow.h"

#include <iostream>
#include <string>
#include <fstream>


//Namespaces
using std::cout;
using std::cin;
using std::string;

int main(int argc, char* argv[])
{
	
	//Boost logging
	//BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	//BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	//BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	//BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	//BOOST_LOG_TRIVIAL(error) << "An error severity message";
	//BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

	//Initate variables to hold the names of the directory locations
	string inputFileName{ "Unknown" };
	string intermediateFileName{ "Unknwon" };
	string outputFileName{ "Unknown" };

	//Banner Message
	cout << "*************************************************************************************"
		<< "\n*\t\t\tWelcome to the MapReduce!                                    *"
		<< "\n*----------------------------------------------------------------------------------- *"
		<< "\n*This program will allow a user to input their input input directory                 *"
		<< "\n*where text files are stored and will ultimately produce a single output file that   *"
		<< "\n*contains a list of words and their associated counts in the originating input files.*"
		<< "\n**************************************************************************************";
	cout.flush();
	//Standalone command-line to get user text file input and output directory location
	cout << "\nInsert the input directory, intermediate directory, and output directory locations.(Separate by a space)"
		<< "\n>>>";
	cin >> inputFileName >> intermediateFileName >> outputFileName;

	WorkFlow workFlow(inputFileName, intermediateFileName, outputFileName);
	//WorkFlow workFlow("c:\\FileTest\\Input\\input111.txt", "c:\\FileTest\\Temp\\intermediate.txt", "c:\\FileTest\\Output\\output.txt");//Test example of inputes

}//End of Program


