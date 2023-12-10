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
	std::vector<std::string> returnElements;

	auto findDirNode = searchNode(fsRoot_, dirname);
	if (findDirNode == nullptr) {
		LOG_MESSAGE("Given dirname NOT FOUND !");
		return returnElements;
	}

	for (const auto& child : findDirNode->getChildren()) {
		returnElements.push_back(child->getName());
	}

	LOG_MESSAGE("Total Elements =" + std::to_string(returnElements.size()));
	return returnElements;
}

FSTreeNode* FSManager::searchNode(FSTreeNode* currentNode, const std::string& searchName) { 
	if (currentNode == nullptr) {
		return nullptr;
	}

	if (currentNode->getName() == searchName) {
		return currentNode;
	}

	// Look 'searchName' into it's children
	for (const auto& child : currentNode->getChildren()) {
		auto fsTreeNode = searchNode(child, searchName);
		if (fsTreeNode != nullptr) {
			return fsTreeNode;
		}
	}

	// In my own depth of the tree; I have not found searchName;
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