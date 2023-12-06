#include "Helper.hpp"
#include "FileSystemTests.hpp"
#include "XMLParser.hpp"



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

    // Positive Test cases 
    // validateXML("tests/validRoot.xml", true /*pass*/);
    // validateXML("tests/validFsStructure.xml", true /*pass*/);
    // validateXML("tests/validLargeFsLayout.xml", true /*pass*/)
}