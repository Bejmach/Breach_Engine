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


//Extended Binary Tree
void strd::UpdateHeight(EBTNode* node){
	if(node){
		node->height = std::max(GetHeight(node->left), GetHeight(node->right))+1;
	}
}
int strd::GetHeight(EBTNode* node){
	return node?node->height:0;
}

int strd::GetBalanceFactor(EBTNode* node){
	return node?GetHeight(node->left) - GetHeight(node->right) : 0;
}

EBTNode* strd::RotateRight(EBTNode* y){
	EBTNode* x = y->left;
	EBTNode* T2 = x->right;

	x->right = y;
	x->left = T2;

	UpdateHeight(x);
	UpdateHeight(y);

	return x;
}

EBTNode* strd::RotateLeft(EBTNode* x){
	EBTNode* y = x->right;
	EBTNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	UpdateHeight(x);
	UpdateHeight(y);

	return y;
}

EBTNode* strd::InsertChar(EBTNode* root, char ch) {
    if (!root) return new EBTNode(ch);
    
    std::vector<EBTNode**> path;  // Keep track of pointers to nodes
    EBTNode** current = &root;

    while (*current) {
        path.push_back(current);
        if (ch < (*current)->ch)
            current = &((*current)->left);
        else if (ch > (*current)->ch)
            current = &((*current)->right);
        else
            return root; // Char already exists
    }

    *current = new EBTNode(ch);

    // Balance tree iteratively
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        EBTNode*& node = **it;
        UpdateHeight(node);
        int balance = GetBalanceFactor(node);

        if (balance > 1) {
            if (GetBalanceFactor(node->left) < 0)
                node->left = RotateLeft(node->left);
            node = RotateRight(node);
        }
        if (balance < -1) {
            if (GetBalanceFactor(node->right) > 0)
                node->right = RotateRight(node->right);
            node = RotateLeft(node);
        }
    }

    return root;
}
EBTNode* strd::InsertElement(EBTNode* root, Element element) {
	std::string word = element.key;
    if (!root) root = new EBTNode(word[0]);
    EBTNode* node = root;

    for (int i=0; i<word.size(); i++) {
        node = InsertChar(node, word[i]);
        if (!node->nextTree)
            node->nextTree = new EBTNode('\0');  // Create next level node
        node = node->nextTree;
    }
    node->value = element.value;
    return root;
}
std::string strd::GetValue(EBTNode* root, std::string key) {
    EBTNode* node = root;
    for (int i=0; i<key.size(); i++) {
        while (node && node->ch != key[i])
            node = (key[i] < node->ch) ? node->left : node->right;
        if (!node) return "";
        node = node->nextTree;
    }
    return node ? node->value : "";
}
EBTNode* strd::GetNode(EBTNode* root, std::string key) {
    EBTNode* node = root;
    for (int i=0; i<key.size(); i++) {
        while (node && node->ch != key[i])
            node = (key[i] < node->ch) ? node->left : node->right;
        if (!node) return node;
        node = node->nextTree;
    }
    return node;
}

// Iterative traversal to collect words
std::vector<std::string> strd::CollectWords(EBTNode* root, std::string prefix) {
	root = GetNode(root, prefix);
    std::vector<std::string> words;
    if (!root) return words;

    std::stack<std::pair<EBTNode*, std::string>> stack;
    stack.push({root, ""});

    while (!stack.empty()) {
        auto [node, prefix] = stack.top();
        stack.pop();

        while (node) {
            std::string new_prefix = prefix;
            if (node->ch != '\0') new_prefix += node->ch;

            if (node->value!="") words.push_back(new_prefix);

            if (node->right) stack.push({node->right, prefix});
            if (node->nextTree) stack.push({node->nextTree, new_prefix});
            node = node->left;
        }
    }

    return words;
}

EBTNode* strd::CreateEBTree(std::string data) {
	std::vector<Element> elements = strd::PrepareRawData(data);
    EBTNode* root = nullptr;
    for (int i=0; i<elements.size(); i++)
        root = InsertElement(root, elements[i]);
    return root;
}
