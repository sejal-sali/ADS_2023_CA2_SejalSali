#include "Helper.hpp"
#include "FileSystemTests.hpp"
#include "XMLParser.hpp"

int main(int argc, char** argv)
{
	//the below code block is used to test the functionality of XML Validation for Stage1
	FileSystemTests fsTests;
	fsTests.runXMLvalidationTests();

	if (argc == 2)
	{
		XMLParser xmlParser(argv[1]);
		auto fsTree = xmlParser.buildFSTree();
		if (fsTree == nullptr)
		{
			LOG_MESSAGE("Invaild XML File provided !!!");
		}
		else
		{
			LOG_MESSAGE("Given File system structure is valid");
		}
	}
	

    return 0;
}