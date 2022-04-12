/*Colton Wilson and Anthony Redamonti
*CSE 687- Object Oriented Design
*Syracuse University
*MapReduce - Phase #1
*04/07/22
*This program contains the 'main' function.......TODO......
*/

//Directives
#include "Workflow.h"
#include "FileManagement.h"
#include "Map.h"
#include "Reduce.h"
#include "Sorting.h"
#include "Workflow.h"

#include <iostream>
#include <string>
#include<boost/tokenizer.hpp>



using std::cout;
using std::cin;
using std::string;



int main()
{

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
	cout << "\nInsert the input directory, intermediate directory, and output directory locations."
		<< "\n>>>";
	//cin >> inputFileName >> intermediateFileName >> outputFileName;

	//WorkFlow workFlow(inputFileName, intermediateFileName, outputFileName);
	WorkFlow workFlow("input.txt", "intermediate.txt", "output.txt");

	/*string s = "This is,  a test";
	boost::tokenizer<> tok(s);
	for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
		cout << *beg << "\n";
	}*/


}//End of Program


