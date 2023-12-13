#include "Helper.hpp"
#include "FileSystemTests.hpp"
#include "XMLParser.hpp"
#include "FSManager.hpp"



void FileSystemTests::runXMLvalidationTests() {
    // Negative Test cases 
    // Validate if the root is invalid 
    {
        XMLParser xmlParser("ValidRootFS.xml");
        if (!xmlParser.hasValidRootDirectory()) {
            LOG_MESSAGE("invalidRoot test failed !");
        }
    }
    //test Case 2
    {
        XMLParser xmlParser("ValidRootFS.xml");
        if (!xmlParser.hasValidFsElements()) {
            LOG_MESSAGE("invalidRoot test failed !");
        }
    }

    //test Case 3
    {
        XMLParser xmlParser("ValidRootFS.xml");
        if (!xmlParser.hasValidFsStructure()) {
            LOG_MESSAGE("invalid FS failed");
        }
    }

    //test Case 4
    {
        XMLParser xmlParser("CompleteSample.xml");
        auto fsTree = xmlParser.buildFSTree();
        if (fsTree == nullptr)
        {
            LOG_MESSAGE("Test Failed to Build File System Tree !!!");
        }
        else
        {
            LOG_MESSAGE("File System Tree Succesfully Built");
        }
    }


    //test Case for FS Manager
    {
        FSManager fsManager("ValidRootFS.xml");
        fsManager.initialize();
        fsManager.searchAndPrintDirectoryContents("emptydirectory");
        fsManager.purgeEmptyDirectories();
        fsManager.searchAndPrintDirectoryContents("emptydirectory");
    }

    //test case for FS file path validation
    {
        FSManager fsManager("ValidRootFS.xml");
        fsManager.initialize();
        auto filePath = fsManager.findCompletePath("readme");
        if (filePath == "ADS_Single_LinkedList_Exercises/.maven/additional_dir/readme")
        {
            LOG_MESSAGE("File path sucessfully found");
        }
        else
        {
            LOG_MESSAGE("File path not found !!!");
        }
    }



    // Positive Test cases 
    // validateXML("tests/validRoot.xml", true /*pass*/);
    // validateXML("tests/validFsStructure.xml", true /*pass*/);
    // validateXML("tests/validLargeFsLayout.xml", true /*pass*/)
}