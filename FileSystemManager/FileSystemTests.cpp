#include "Helper.hpp"
#include "FileSystemTests.hpp"
#include "XMLParser.hpp"



void FileSystemTests::runXMLvalidationTests() {
    // Negative Test cases 
    // Validate if the root is invalid 
    XMLParser xmlParser("tests/invalidRoot.xml");
    if (!xmlParser.hasValidRootDirectory()) {
        LOG_MESSAGE("invalidRoot test failed !");
    }


    // Positive Test cases 
    // validateXML("tests/validRoot.xml", true /*pass*/);
    // validateXML("tests/validFsStructure.xml", true /*pass*/);
    // validateXML("tests/validLargeFsLayout.xml", true /*pass*/)
}