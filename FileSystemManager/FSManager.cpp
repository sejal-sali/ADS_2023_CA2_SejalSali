#include "FSManager.hpp"
#include "Helper.hpp"

FSManager::FSManager(const std::string& fileName) 
	: fsFileName_(fileName), fsRoot_(nullptr) {}
	
FSManager::~FSManager() {
	// We need to delte the entire FSTree here. 
}

void FSManager::initialize() {
	XMLParser xmlParser(fsFileName_);
	fsRoot_ = xmlParser.buildFSTree();
	if (fsRoot_ != nullptr) {
		LOG_MESSAGE("FS Manager is ready to operate !");
	}
	else {
		LOG_MESSAGE("FS Manager initialization failed !");
	}
}

std::vector<std::string> FSManager::showDirectoryElements(const std::string& dirname) {
	// This will search the elemnts 
	std::vector<std::string> returnElements = {};
	// This is a stubs 
	LOG_MESSAGE("Number of elements found in a directory=" + returnElements.size());
	return returnElements;
}

FSTreeNode* FSManager::searchNode(FSTreeNode* currentNode, const std::string& searchName) {
	// stubs 
	return nullptr;
}

int FSManager::getTotalMemorySize(const std::string& dirname) {
	// stubs 
	int totalMemorySize = 0;
	return totalMemorySize;
}

void FSManager::viewFS() {
	// stubs 
	LOG_MESSAGE("This presents the current FS view !");
}

void FSManager::purgeEmptyDirectories() {
	// stubs
	LOG_MESSAGE("This would purge the empty directories !");
}