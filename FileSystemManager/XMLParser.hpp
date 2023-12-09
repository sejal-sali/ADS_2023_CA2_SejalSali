#include <iostream>
#include <fstream>
#include "FSTreeNode.hpp"

class XMLParser {

public:
    XMLParser(const std::string& xmlFilePath);

    // This will validate if the root element is a 
    // directory or not as every FS starts with root directory. 
    bool hasValidRootDirectory();

    // This will validate if the file has file and directory 
    // related elements and complete element tagging like 
    // open, close of every element tag. 
    bool hasValidFsElements();

    // This will validate the complete structure of the FileSystem 
    // like file can not be nested with directory. 
    // only directory can hold other nested directories 
    bool hasValidFsStructure();

    // build the complete File System Tree including the validation
    FSTreeNode* buildFSTree();

private:

    // this function is responsible for building the complete 
    // FS Layot tree.
    FSTreeNode* buildFSTreeImpl();
    FSTreeNode* createFSTreeNode(const std::string& name, FSNodeType type);

    //using stack this function validates the correctness of each xml elements
    bool hasClosingTags(const std::string& xmlContents);
    

    //these are the data members
    const std::string xmlFilePath_;
    std::ifstream xmlFileStream_;


};