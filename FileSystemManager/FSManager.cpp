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

void FSManager::viewFS() {
	LOG_MESSAGE("This presents the current FS view !");
	printView(fsRoot_);
}

void FSManager::searchAndPrintDirectoryContents(const std::string& dirName) {
	auto fsTreeNode = searchNode(fsRoot_, dirName);
	if (fsTreeNode != nullptr) {
		printView(fsTreeNode);
	}
	else {
		LOG_MESSAGE("Directory Not found !");
	}
}

void FSManager::printView(FSTreeNode* treeNode) {
	static int tabCount = 1;
	if (treeNode == nullptr) {
		--tabCount;
		return;
	}

	auto printTabs = [&]() -> std::string {
		std::string tabIndent = "";
		for (int index = 0; index < tabCount; ++index) {
			tabIndent += "-";
		}
		return tabIndent;
	};

	// Process the current node
	if (treeNode->getNodeType() == FSNodeType::FILE_NODE) {
	
		LOG_MESSAGE(printTabs()+" name="+ treeNode->getName()+" legnth="+
			std::to_string(treeNode->getFileLength()));
	}
	else {
		LOG_MESSAGE(printTabs()+ " dirName="+treeNode->getName());
	}

	// Recursively traverse children
	for (const auto& child : treeNode->getChildren()) {
		// (child->getNodeType() == FSNodeType::DIRECTORY_NODE) {
			++tabCount;
		//}
		printView(child);
	}

	--tabCount;
	return;
}

void FSManager::purgeEmptyDirectories() {
	// stubs
	LOG_MESSAGE("This would purge the empty directories !");
}