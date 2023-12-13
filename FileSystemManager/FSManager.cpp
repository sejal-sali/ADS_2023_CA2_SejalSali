#include "FSManager.hpp"
#include "Helper.hpp"
#include <queue>

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

FSTreeNode* FSManager::searchNode(FSTreeNode* currentNode, const std::string& searchName, 
	bool partialSearch) { 
	if (currentNode == nullptr) {
		return nullptr;
	}

	if (currentNode->getName() == searchName) {
		return currentNode;
	}

	// If the partialSearch is enabled then search substring 
	if (partialSearch) {
		if (currentNode->getName().find(searchName) != std::string::npos) {
			return currentNode;
		}
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
	int totalFileSize = 0;

	// Lets find the dirName 
	auto fsTreeNode = searchNode(fsRoot_, dirname);
	if (fsTreeNode == nullptr) {
		return totalFileSize;
	}

	std::queue<FSTreeNode*> q;
	q.push(fsTreeNode);

	while (!q.empty()) {
		FSTreeNode* current = q.front();
		q.pop();


		// Enqueue children of the current node
		for (FSTreeNode* child : current->getChildren()) {
			if (child->getNodeType() == FSNodeType::DIRECTORY_NODE) {
				q.push(child);
			}
			else {
				// Process the current FILE NODE 
				totalFileSize += child->getFileLength();
			}
		}
	}

	return totalFileSize;
}


void FSManager::searchAndPrintDirectoryContents(const std::string& dirName) {
	auto fsTreeNode = searchNode(fsRoot_, dirName);
	if (fsTreeNode != nullptr) {
		printFileSystem(fsTreeNode, 0);
	}
	else {
		LOG_MESSAGE("Directory Not found !");
	}
}

std::string FSManager::findCompletePath(const std::string& fileName) {
	auto fsTreeNode = searchNode(fsRoot_, fileName, true);
	
	if (fsTreeNode == nullptr)
	{
		LOG_MESSAGE("Provided File name not found!!!");
		return "";
	}

	if (fsTreeNode->getNodeType() != FSNodeType::FILE_NODE) {
		LOG_MESSAGE("Provide file name instead of directory name !");
		return "";
	}

	// Now build the path 
	std::string filePath = "";

	if (fsTreeNode != nullptr) {

		while (fsTreeNode != nullptr) {
			filePath = fsTreeNode->getName() + filePath;
			if (fsTreeNode->getParent()) {
				filePath = "/" + filePath;
			}

			fsTreeNode = fsTreeNode->getParent();
		}
	}

	return filePath;
}

std::string FSManager::getTabIndents(int tabCount) {
	std::string tabIndents = "|";
	for (int index = 0; index < tabCount; ++index) {
		tabIndents += "----";
	}
	return tabIndents;
}

void FSManager::printFileSystem(FSTreeNode* fsTreeNode, int tabCount) {

	if (fsTreeNode == nullptr) {
		return;
	}

	if (fsTreeNode->getNodeType() == FSNodeType::FILE_NODE) {
		LOG_MESSAGE(getTabIndents(tabCount) + fsTreeNode->getName() +
			"(" + std::to_string(fsTreeNode->getFileLength()) + ")");
	}
	else {
		// print directory
		LOG_MESSAGE(getTabIndents(tabCount) + fsTreeNode->getName());
	}

	// Recursively traverse children
	for (const auto& child : fsTreeNode->getChildren()) {
		tabCount++;
		printFileSystem(child, tabCount);
	}

	--tabCount;
}

void FSManager::printFileSystem() {
	printFileSystem(fsRoot_, 0);
}

void FSManager::purgeEmptyDirectories() {
	purgeEmptyDirectories(fsRoot_);
}

// This is a recursive function in DFS form
void FSManager::purgeEmptyDirectories(FSTreeNode* fsTreeNode) {
	// Find the directory which is empty and then just drop it
	// remove it from it's parent's child vector 
	if (fsTreeNode == nullptr) {
		return;
	}

	// Recursively traverse children
	auto& children = fsTreeNode->getChildrenRef();
	for (auto childIt = children.begin(); childIt != children.end();) {
		if ((*childIt)->getNodeType() == FSNodeType::DIRECTORY_NODE) {
			auto childrenSize = (*childIt)->getChildren().size();
			if (childrenSize == 0) {
				delete* childIt;
				childIt = children.erase(childIt);
				continue;
			}
		}

		purgeEmptyDirectories(*childIt);
		childIt++;
	}
}