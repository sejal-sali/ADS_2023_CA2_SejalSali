#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#ifndef FSNODE_TREE_HEADER_H
#define FSNODE_TREE_HEADER_H

enum FSNodeType {
    FILE_NODE = 0,
    DIRECTORY_NODE = 1,
};

class FSTreeNode {
public:
    FSTreeNode(const std::string& name, FSNodeType type) :
        name(name), fsNodeType(type), fileLength(0), fileExtensionName("") {}

    const std::string getName() {
        return name;
    }

    FSNodeType getNodeType() {
        return fsNodeType;
    }

    const std::string getFileExtension() {
        return fileExtensionName;
    }

    int getFileLength() {
        return fileLength;
    }

    void setFileLength(int length) {
        fileLength = length;
    }

    void setFileExtension(const std::string& fileTypeName) {
        fileExtensionName = fileTypeName;
    }

    std::vector<FSTreeNode*> getChildren() {
        return children;
    }

    void setParent(FSTreeNode* inParent) {
        parent = inParent;
    }

    FSTreeNode* getParent() {
        return parent;
    }

    void addChild(FSTreeNode* node) {
        children.push_back(node);
    }

    // This returns the vector ref for the children
    std::vector<FSTreeNode*>& getChildrenRef() {
        return children;
    }

    void removeChild(const std::string& dirName) {
        for (auto it = children.begin(); it != children.end(); ++it) {
            if ((*it)->getName() == dirName) {
                // Free memory for the child node
                delete* it;
                children.erase(it);
            }
        }
    }

private:
   // FSTreeNode();

    std::string name;
    FSNodeType fsNodeType;
    unsigned int fileLength; // If it is a FILE node then this value will be filled
    std::string fileExtensionName; // In case of FILE node this will be empty 
    std::vector<FSTreeNode*> children;
    FSTreeNode* parent = nullptr;
};

#endif