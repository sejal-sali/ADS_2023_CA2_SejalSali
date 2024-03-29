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

	// function 2 
	int totalMemory = fsManager.getTotalMemorySize(".maven");
	LOG_MESSAGE("Total Memory required for a dir=" + std::to_string(totalMemory));

	// print entire FS tree for the searched element - function e
	fsManager.searchAndPrintDirectoryContents(".maven");

	// print entire FS Tree from the root 
	LOG_MESSAGE("Print The complete FS Tree =>");
	fsManager.printFileSystem();

	// print filepath - function d
	auto filePath = fsManager.findCompletePath("readme");
	LOG_MESSAGE("FilePath for readme=>"+filePath);
	
	// Function d is searching for a partial file name 
	auto newFilePath = fsManager.findCompletePath("read");
	LOG_MESSAGE("FilePath for patial readme=>" + newFilePath);

	// Function c : Purge the empty directories 
	fsManager.purgeEmptyDirectories();
	LOG_MESSAGE("Print The complete FS Tree after purging empty directories =>");
	fsManager.printFileSystem();

    return 0;
}