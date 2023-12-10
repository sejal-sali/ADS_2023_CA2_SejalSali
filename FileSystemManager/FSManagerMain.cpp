#include "Helper.hpp"
#include "FileSystemTests.hpp"
#include "XMLParser.hpp"
#include "FSManager.hpp"

int main(int argc, char** argv)
{
	//the below code block is used to test the functionality of XML Validation for Stage1
	FileSystemTests fsTests;
	fsTests.runXMLvalidationTests();

	FSManager fsManager("ValidRootFS.xml");
	fsManager.initialize();

	// Stage 2 functions would be called here 
	// Function 1
	fsManager.showDirectoryElements(".maven");

	
    return 0;
}