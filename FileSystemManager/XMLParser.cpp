#include "XMLParser.hpp"
#include "Helper.hpp"
#include <sstream>
#include <stack>
#include <regex>

XMLParser::XMLParser(const std::string& xmlFilePath)
    : xmlFilePath_(xmlFilePath) {
    xmlFileStream_.open(xmlFilePath_);
}


bool XMLParser::hasValidRootDirectory() {
    // stubs 
    LOG_MESSAGE("Validating the root directory");
    if (!hasValidFsElements())
    {
        LOG_MESSAGE("Input file doesnot have valid XML Elements");
        return false;
    }

    xmlFileStream_.seekg(0, std::ios::beg);
    LOG_MESSAGE("XML has valid FS Elements");
    std::string firstLine;

    if (std::getline(xmlFileStream_, firstLine))
    {
        std::string trimmedLine = trim(firstLine);
        LOG_MESSAGE("line=>"+trimmedLine);
        // Check if it is a directory then read the next line as name 
        if (trimmedLine == "<dir>")
        {
            return true;
        }
    }

     return false;
}

bool XMLParser::hasValidFsElements() {
    // stubs 
    if (!xmlFileStream_.is_open()) {
        LOG_MESSAGE("Failed to open the file!");
        return false;
    }
    xmlFileStream_.seekg(0, std::ios::beg);
    std::stringstream xmlContentBuffer;
    xmlContentBuffer << xmlFileStream_.rdbuf();
    std::string xmlContents = xmlContentBuffer.str();

    return hasClosingTags(xmlContents);
}


bool XMLParser::hasValidFsStructure() {
    // stubs 

    
    if (!hasValidFsElements())
    {
        LOG_MESSAGE("Input file doesnot have valid XML Elements");
        return false;
    }

    xmlFileStream_.seekg(0, std::ios::beg);

    LOG_MESSAGE("XML has valid FS Elements");

    std::regex nameRegex("<name>(.*?)</name>");
    std::regex lengthRegex("<length>(.*?)</length>");
    std::regex fileTypeRegex("<type>(.*?)</type>");
    std::string line;
    int numDirectoriesStarted = 0;
    int numDirectoriesEnded = 0;
    int numFilesStarted = 0;
    int numFilesEnded = 0;

    while (std::getline(xmlFileStream_, line)) {
        std::string trimmedLine = trim(line);

        // Check if it is a directory then read the next line as name 
        if (trimmedLine == "<dir>") {
            //printMe("Directory Started !");
            numDirectoriesStarted++;
#if 0
            std::string nestedLine;
            // Go ahead and read the name of the directory ? 
            if (std::getline(xmlFileStream_, nestedLine)) {
                std::string trimmedLine = trim(nestedLine);
                std::smatch match;
                if (std::regex_search(trimmedLine, match, nameRegex)) {
                    std::string fileName = match[1].str();
                    printMe("DirName=" + fileName);
                }
            }
#endif
        }

        else if (trimmedLine == "<file>") {
            //printMe("File Started !");
            numFilesStarted++;
            std::string nestedLine;
            int nameFound = 0;
            int lengthFound = 0;
            int fileTypeFound = 0;
            int invalidElement = 0;

            while (std::getline(xmlFileStream_, nestedLine)) {
                std::string trimmedLine = trim(nestedLine);
                LOG_MESSAGE("Printing trimline = " + trimmedLine);
                if (trimmedLine == "</file>")
                {
                    numFilesEnded++;
                    break;
                }

                std::smatch match;
                if (std::regex_search(trimmedLine, match, nameRegex)) {
                    nameFound++;
                }
                else if (std::regex_search(trimmedLine, match, lengthRegex)) {
                    lengthFound++;
                }
                else if (std::regex_search(trimmedLine, match, fileTypeRegex)) {
                    fileTypeFound++;
                }
                else {
                    invalidElement = 1;
                    LOG_MESSAGE("Invalid Element found " + trimmedLine);
                    break;
                }
            }

            if (invalidElement) {
                LOG_MESSAGE("Invalid Element Found = " + nestedLine);
                return false;
            }
        }
        else if (trimmedLine == "</file>") {
            //printMe("File ended !");
            numFilesEnded++;
        }
        else if (trimmedLine == "</dir>") {
            //printMe("Directory Ended !");
            numDirectoriesEnded++;
        }
    }
    LOG_MESSAGE("DirStarted=" + std::to_string(numDirectoriesStarted) + ", dirEnded=" + std::to_string(numDirectoriesEnded));
    LOG_MESSAGE("fileStarted=" + std::to_string(numFilesStarted) + ", fileEnded=" + std::to_string(numFilesEnded));

    return (numDirectoriesStarted== numDirectoriesEnded && numFilesStarted == numFilesEnded);
}


bool XMLParser::hasClosingTags(const std::string& xml) {
    std::stack<std::string> tagStack;
    size_t pos = 0;

    while (pos < xml.length()) {
        // Find the next opening tag
        size_t openTagStart = xml.find('<', pos);
        if (openTagStart == std::string::npos) {
            break;  // No more opening tags
        }

        // Find the closing angle bracket of the opening tag
        size_t openTagEnd = xml.find('>', openTagStart);
        if (openTagEnd == std::string::npos) {
            break;  // Malformed XML: opening tag not closed
        }

        // Extract the opening tag
        std::string openTag = xml.substr(openTagStart + 1, openTagEnd - openTagStart - 1);

        // Check if it is a closing tag
        if (openTag.length() > 0 && openTag[0] == '/') {
            // It's a closing tag, check against the stack
            if (tagStack.empty() || tagStack.top() != openTag.substr(1)) {
                return false;  // Mismatched closing tag
            }
            tagStack.pop();
        }
        else {
            // It's an opening tag, push onto the stack
            tagStack.push(openTag);
        }

        // Move to the next position after the opening tag
        pos = openTagEnd + 1;
    }

    // If the stack is empty, all tags were properly closed
    return tagStack.empty();
}