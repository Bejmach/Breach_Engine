#include <StringOperations.h>
#include<StringDict.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <stack>
#include <string>
#include <sstream>
#include <unordered_map>

Element PreElement::ToElement(){
	Element element;
	element.key = this->key;
	element.value = this->value;
	return element;
}

BTNode::~BTNode(){
	if(left!=nullptr){
		delete left;
	}
	if(right!=nullptr){
		delete right;
	}
}

std::vector<PreElement> strd::PrepareData(std::string data){
	
	std::istringstream stream(data);

	unsigned int lineCount = std::count(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), '\n')+1;
	std::vector<PreElement> elements(lineCount);

	stream.clear();
	stream.seekg(0);

	std::string line;
	int i=0;

	int emptyLines = 0;
	while(std::getline(stream, line)){
		if(line == ""){
			emptyLines += 1;
			continue;
		}
		PreElement element;
		std::vector<std::string> elementValues = stro::Split(line, " ");
		if(elementValues.size() < 2){
			std::cout<<"Error on line"<<i<<". File not formated correctly. Line: \""<<line<<"\""<<std::endl;
			return {};
		}
		if(std::isdigit(elementValues[0][0]) || std::isdigit(elementValues[1][0])){
			std::cout<<"Error on line"<<i<<". Key or Value Can't start from number and symbols. Line: \""<<line<<"\""<<std::endl;
			return {};
		}
		element.key = elementValues[0];
		element.value = elementValues[1];
		element.id = stro::Value(elementValues[0]);
		elements[i] = element;
		i+=1;
	}
	elements.resize(elements.size()-1-emptyLines);
	return elements;
}
std::vector<Element> strd::PrepareRawData(std::string data){
	
	std::istringstream stream(data);

	unsigned int lineCount = std::count(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), '\n')+1;
	std::vector<Element> elements(lineCount);

	stream.clear();
	stream.seekg(0);

	std::string line;
	int i=0;

	int emptyLines = 0;
	while(std::getline(stream, line)){
		if(line == ""){
			emptyLines += 1;
			continue;
		}
		Element element;
		std::vector<std::string> elementValues = stro::Split(line, " ");
		if(elementValues.size() < 2){
			std::cout<<"Error on line"<<i<<". File not formated correctly. Line: \""<<line<<"\""<<std::endl;
			return {};
		}
		if(std::isdigit(elementValues[0][0]) || std::isdigit(elementValues[1][0])){
			std::cout<<"Error on line"<<i<<". Key or Value Can't start from number and symbols. Line: \""<<line<<"\""<<std::endl;
			return {};
		}
		element.key = elementValues[0];
		element.value = elementValues[1];
		elements[i] = element;
		i+=1;
	}
	elements.resize(elements.size()-1-emptyLines);
	return elements;
}
// Partition function for QuickSort
int strd::Partition(std::vector<PreElement>& arr, int low, int high) {
    int pivot = arr[high].id;  // Choosing the last element as pivot
    int i = low - 1;              // Index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j].id < pivot) { // Sorting in ascending order
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]); // Place pivot in correct position
    return i + 1;
}

// QuickSort function
void strd::QuickSort(std::vector<PreElement>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(arr, low, high);

        QuickSort(arr, low, pivotIndex - 1);  // Left subarray
        QuickSort(arr, pivotIndex + 1, high); // Right subarray
    }
}

// Helper function to sort a vector of PreElements
void strd::SortElements(std::vector<PreElement>& elements) {
    if (!elements.empty()) {
        QuickSort(elements, 0, elements.size() - 1);
    }
}

std::vector<ParsedElement> strd::ParseElements(std::vector<PreElement> elements){
	int differentIds = 0;
	int curId = -1;
	for(int i=0; i<elements.size(); i++){
		if(elements[i].id != curId){
			differentIds += 1;
			curId = elements[i].id;
		}
	}

	std::vector<ParsedElement> parsedElements(differentIds);

	int i = -1;
	curId = -1;
	for(int j=0; j<elements.size(); j++){
		if(elements[j].id != curId){
			i+=1;
			curId = elements[j].id;
		}
		parsedElements[i].id = curId;
		parsedElements[i].elements.push_back(elements[j].ToElement());
	}
	return parsedElements;
}

// Function to build a balanced BST from a sorted vector of ParsedElements
BTNode* strd::BuildBalancedTree(const std::vector<ParsedElement>& elements, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;
    BTNode* root = new BTNode(elements[mid]);

    root->left = BuildBalancedTree(elements, start, mid - 1);
    root->right = BuildBalancedTree(elements, mid + 1, end);

    return root;
}

// In-order traversal (for testing)
void strd::InorderTraversal(BTNode* root) {
    if (!root) return;
    InorderTraversal(root->left);
    std::cout << root->id << " ";
    InorderTraversal(root->right);
}

BTNode* strd::CreateBTree(std::string data){
	std::vector<PreElement> elementVec = PrepareData(data);
	SortElements(elementVec);
	std::vector<ParsedElement> parsedElements = strd::ParseElements(elementVec);
	return BuildBalancedTree(parsedElements, 0, parsedElements.size()-1);
}

std::vector<Element> strd::CreateList(std::string data){
	std::vector<PreElement> elementVec = PrepareData(data);
	std::vector<Element> elements(elementVec.size());
	for(int i=0; i<elementVec.size(); i++){
		elements[i] = elementVec[i].ToElement();
	}
	return elements;
}

std::unordered_map<std::string, std::string> strd::CreateUM(std::string data){
	std::vector<PreElement> elementVec = PrepareData(data);
	std::unordered_map<std::string, std::string> um;
	for(int i=0; i<elementVec.size(); i++){
		um.insert({elementVec[i].key, elementVec[i].value});
	}
	return um;
}


Element* strd::Find(BTNode* root, std::string key){
	int keyId = stro::Value(key);

	while (root){
		if(keyId < root->id){
			root = root->left;
		}
		else if(keyId > root->id){
			root = root->right;
		}
		else{
			for(int i=0; i<root->elements.size(); i++){
				if(root->elements[i].key == key){
					return &root->elements[i];
				}
			}
			break;
		}
	}
	return nullptr;
}
Element strd::Find(std::vector<Element> root, std::string key){
	for(int i=0; i<root.size(); i++){
		if(root[i].key == key){
			return root[i];
		}
	}

	return {"",""};
}

std::string strd::Find(std::unordered_map<std::string, std::string> um, std::string key){
	auto it = um.find(key);
	if(it!=um.end()){
		return it->second;
	}
	return nullptr;
}

void strd::Add(BTNode* root, Element element){
	if(root == nullptr){
		return;
	}
	
	int elementValue = stro::Value(element.key);
	
	while(true){
		if(root->id<elementValue){
			if(root->right == nullptr){
				BTNode* newBTNode = new BTNode();
				newBTNode->id = elementValue;
				newBTNode->elements.push_back(element);
				root->right = newBTNode;
				return;
			}
			else{
				root = root->right;
			}
		}
		else if(root->id>elementValue){
			if(root->left == nullptr){
				BTNode* newBTNode = new BTNode();
				newBTNode->id = elementValue;
				newBTNode->elements.push_back(element);
				root->left = newBTNode;
				return;
			}
			else{
				root = root->left;
			}
		}
		else{
			root->elements.push_back(element);
			return;
		}
	}
}

ExtendedMap strd::CreateExtendedMap(std::string data){
	ExtendedMap map;

	std::vector<Element> elements = PrepareRawData(data);
	for(int i=0; i<elements.size(); i++){
		AddElement(&map, elements[i]);
	}
	return map;
}

ExtendedMap* strd::AddChar(ExtendedMap* node, char ch, std::string value){
	if(node->map.find(ch)==node->map.end()){
		ExtendedMap* newMap = new ExtendedMap(value);
		node->map.insert({ch, newMap});
		return newMap;
	}
	return nullptr;
}
void strd::AddElement(ExtendedMap* root, Element element){
	ExtendedMap* node = root;
	for(int i=0; i<element.key.size(); i++){
		auto mapFound = node->map.find(element.key[i]);
		if(mapFound!=node->map.end()){
			node = mapFound->second;
		}
		else{
			node = AddChar(node, element.key[i]);
		}
	}
	node->value = element.value;
}

ExtendedMap* strd::GetNode(ExtendedMap* root, std::string key){
	ExtendedMap* node = root;
	for(int i=0; i<key.size(); i++){
		auto mapFound = node->map.find(key[i]);
		if(mapFound!=node->map.end()){
			node = mapFound->second;
		}
		else{
			return nullptr;
		}
	}
	return node;
}
std::string strd::FindValue(ExtendedMap* root, std::string key){
	ExtendedMap* node = GetNode(root, key);

	if(!node){
		return "";
	}

	return node->value;
}

std::vector<Element> strd::CollectAll(ExtendedMap* node, std::string prefix) {
    std::vector<Element> results;
    if (node == nullptr) return results;

    std::stack<std::pair<ExtendedMap*, std::string>> stack;
    stack.push(std::make_pair(node, node->value));

    while (!stack.empty()) {
        std::pair<ExtendedMap*, std::string> current = stack.top();
        stack.pop();

        ExtendedMap* node = current.first;
        std::string path = current.second;

        if (!node->value.empty()) {
			Element element;
			element.key = prefix+path;
			element.value = node->value;
            results.push_back(element);
        }

        for (std::unordered_map<char, ExtendedMap*>::iterator it = node->map.begin(); it != node->map.end(); ++it) {
            char key = it->first;
            ExtendedMap* child = it->second;
            std::string newPath = path + key;
            stack.push(std::make_pair(child, newPath));
        }
    }

    return results;
}

std::vector<Element> strd::FindByPrefix(ExtendedMap* root, std::string prefix){
	ExtendedMap* node = GetNode(root, prefix);
	if(!node){
		return {};
	}
	return CollectAll(node, prefix);
}

