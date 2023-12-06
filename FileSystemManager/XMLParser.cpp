#include "XMLParser.hpp"
#include "Helper.hpp"

XMLParser::XMLParser(const std::string& xmlFilePath)
    : xmlFilePath_(xmlFilePath) {}

bool XMLParser::hasValidRootDirectory() {
    // stubs 
    LOG_MESSAGE("Validating the root directory");
    return false;
}

bool XMLParser::hasValidFsElements() {
    // stubs 
    return false;
}

bool XMLParser::hasValidFsStructure() {
    // stubs 
    return false;
}