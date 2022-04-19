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


*/


//Directives
#include "Workflow.h"

#include <iostream>
#include <string>
#include <fstream>
#include <boost/timer/timer.hpp>
#include <cmath>


//Name spaces
using std::cout;
using std::cin;
using std::string;

int main()
{
	//Start timer
	boost::timer::auto_cpu_timer t(3, "%w seconds\n");
	
	//Initiate variables to hold the names of the directory locations
	string inputFileName{ "Unknown" };
	string intermediateFileName{ "Unknown" };
	string outputFileName{ "Unknown" };

	//Banner Message
	cout << "*************************************************************************************"
		<< "\n*\t\t\tWelcome to the MapReduce!                                    *"
		<< "\n*----------------------------------------------------------------------------------- *"
		<< "\n*This program will allow a user to input their input directory                       *"
		<< "\n*where text files are stored and will ultimately produce a single output file that   *"
		<< "\n*contains a list of words and their associated counts in the originating input files.*"
		<< "\n**************************************************************************************";
	cout.flush();
	//Standalone command-line to get user text file input and output directory location
	cout << "\nInsert the input directory, intermediate directory, and output directory locations.(Separate by a space)"
		<< "\n>>>";
	//cin >> inputFileName >> intermediateFileName >> outputFileName;

	//WorkFlow workFlow(inputFileName, intermediateFileName, outputFileName);

	//**************Test to insert Directory**************
	//cout << "\n";
	//WorkFlow workFlow("C:\\Users\\Colton Wilson\\Desktop\\CIS687 OOD\\testFolder", "intermediate.txt", "output.txt");//Test example of inputs

	//**************Test to insert file**************
	WorkFlow workFlow("C:\\Users\\Colton Wilson\\Desktop\\CIS687 OOD\\testFolder\\New Text Document.txt", "intermediate.txt", "output.txt");//Test example of inputs

	//print to screen seconds to complete program
	cout << "\nTime to complete program: ";
	for (long i = 0; i < 100000000; ++i)
		std::sqrt(123.456L); // burn some time

}//End of Program