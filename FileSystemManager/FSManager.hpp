#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "XMLParser.hpp"

class FSManager
{
public:
    FSManager(const std::string& fsFileName);
    ~FSManager();

    // This function initilaizes the complete FS Tree built 
    // from the given XML filename in the FSManager's constructor 
    void initialize();

    // This returns all the elements belongs to the given direName 
    // including files and directories 
    std::vector<std::string> showDirectoryElements(const std::string& dirname);

    // This function search the given name as a directory/foldername 
    // in the built FS Tree and return the found node. 
    FSTreeNode* searchNode(FSTreeNode* currentNode, 
        const std::string& searchName, bool partialSearch = false);


    // This function calculates the total number of bytes required for 
    // all the files and sub-directory level files of a given directory. 
    int getTotalMemorySize(const std::string& dirname);

    // This function is responsible in showing the current view of FS
    void printFileSystem();

    std::string findCompletePath(const std::string& fileName);

    void searchAndPrintDirectoryContents(const std::string& dirName);

    // This function will be purging the empty directories in case 
    // those directories exists in the FS Tree 
    void purgeEmptyDirectories();

private: 
    void printFileSystem(FSTreeNode* fsTreeNode, int tabCount);
    std::string getTabIndents(int tabCount);
    void purgeEmptyDirectories(FSTreeNode* fsTreeNode);

private:
    // No element we are stroing 
    const std::string fsFileName_;
    FSTreeNode* fsRoot_; 
};

