#include <iostream>

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

private:
    const std::string xmlFilePath_;
};