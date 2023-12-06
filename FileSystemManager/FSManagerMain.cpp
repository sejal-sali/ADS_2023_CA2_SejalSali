#include "Helper.hpp"
#include "FileSystemTests.hpp"

int main(int argc, char** argv)
{
	//the below code block is used to test the functionality of XML Validation for Stage1
	FileSystemTests fsTests;
	fsTests.runXMLvalidationTests();

	return 0;
}