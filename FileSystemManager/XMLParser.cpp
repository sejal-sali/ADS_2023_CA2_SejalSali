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
    FSTreeNode* rootTree = buildFSTreeImpl();
    if (rootTree == nullptr)
    {
        return false;
    }

    return true; 
}

FSTreeNode* XMLParser::buildFSTreeImpl() {

    FSTreeNode* rootNode = nullptr;
    FSTreeNode* currDirNode = nullptr;

    // declares the regular expression to read name, length and
    // file type of a tree node.
    std::regex nameRegex("<name>(.*?)</name>");
    std::regex lengthRegex("<length>(\\d+)\\s*\\w*</length>");
    std::regex fileTypeRegex("<type>(.*?)</type>");

    std::string line;
    int numDirectoriesStarted = 0;
    int numDirectoriesEnded = 0;
    int numFilesStarted = 0;
    int numFilesEnded = 0;

    while (std::getline(xmlFileStream_, line)) {
        std::string trimmedLine = trim(line);
        std::string nestedLine;

        // Check if it is a directory then read the next line as name 
        if (trimmedLine == "<dir>") {
            numDirectoriesStarted++;
            if (std::getline(xmlFileStream_, nestedLine)) {
                std::string trimmedLine = trim(nestedLine);
                std::smatch match;
                if (std::regex_search(trimmedLine, match, nameRegex)) {
                    std::string dirName = match[1].str();
                    FSTreeNode* dirNode = createFSTreeNode(dirName, FSNodeType::DIRECTORY_NODE);
                    dirNode->setParent(currDirNode);
                    if (currDirNode != nullptr) {
                        currDirNode->addChild(dirNode); // insert as a child 
                    }

                    //now the created node becomes the current node to add its children
                    currDirNode = dirNode;
                    if (rootNode == nullptr) {
                        // Initialize the root node here only ONCE
                        rootNode = currDirNode;
                    }
                }
            }  
        }
        else if (trimmedLine == "<file>") {
            numFilesStarted++;

            std::string fileName;
            int fileLength;
            std::string fileExtensionType;

            int invalidElement = 0;

            while (std::getline(xmlFileStream_, nestedLine)) {
                std::string trimmedLine = trim(nestedLine);
                if (trimmedLine == "</file>")
                {
                    numFilesEnded++;
                    break;
                }

                std::smatch match;
                if (std::regex_search(trimmedLine, match, nameRegex)) {
                    fileName = match[1].str();
                }
                else if (std::regex_search(trimmedLine, match, lengthRegex)) {
                    std::string fileLengthStringValue = match[1].str();
                    fileLength = std::stoi(fileLengthStringValue);
                }
                else if (std::regex_search(trimmedLine, match, fileTypeRegex)) {
                    fileExtensionType = match[1].str();
                }
                else {
                    invalidElement = 1;
                    break;
                }
            }

            if (invalidElement) {
                LOG_MESSAGE("Invalid Element Found = " + nestedLine);
                return nullptr;
            }

            // Make a file Node 
            FSTreeNode* fileNode = createFSTreeNode(fileName, FSNodeType::FILE_NODE);
            fileNode->setFileExtension(fileExtensionType);
            fileNode->setFileLength(fileLength);
            fileNode->setParent(currDirNode);
            currDirNode->addChild(fileNode);
        }
        else if (trimmedLine == "</dir>") {
            numDirectoriesEnded++;
            if (currDirNode->getParent())
                currDirNode = currDirNode->getParent();
            // Reset back the level of the directory to the parent one now
        }
    }
    LOG_MESSAGE("DirStarted=" + std::to_string(numDirectoriesStarted) + ", dirEnded=" + std::to_string(numDirectoriesEnded));
    LOG_MESSAGE("fileStarted=" + std::to_string(numFilesStarted) + ", fileEnded=" + std::to_string(numFilesEnded));

    if (numDirectoriesStarted == numDirectoriesEnded && numFilesStarted == numFilesEnded)
    {
        return rootNode;
    }

    return nullptr;
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


FSTreeNode* XMLParser::createFSTreeNode(const std::string& name, FSNodeType type)
{
    return new FSTreeNode(name, type);
}

FSTreeNode* XMLParser::buildFSTree()
{
    if (!xmlFileStream_.is_open()) {
        LOG_MESSAGE("Failed to open the file!");
        return nullptr;
    }
    xmlFileStream_.seekg(0, std::ios::beg);

    return buildFSTreeImpl();
}

