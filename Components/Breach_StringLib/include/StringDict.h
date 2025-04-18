#ifndef STRINGDICT_H
#define STRINGDICT_H

#include<iostream>
#include <unordered_map>
#include<vector>
#include<fstream>

#include<StringOperations.h>


struct Element{
	std::string key;
	std::string value;
};

struct PreElement{
	int id;
	std::string key;
	std::string value;

	Element ToElement();
};

struct ParsedElement{
	int id;
	std::vector<Element> elements;
};

struct BTNode{
	BTNode *left;
	BTNode *right;

	int id;
	std::vector<Element> elements;

	BTNode(ParsedElement element) : id(element.id), elements(element.elements), left(nullptr), right(nullptr){}
	BTNode(){};
	~BTNode();
};

struct ExtendedMap{
	std::string value = "";

	std::unordered_map<char, ExtendedMap*> map;
	ExtendedMap(std::string value = ""): value(value){}
};

class strd{
	private:
		static std::vector<PreElement> PrepareData(std::string data);
		static std::vector<Element> PrepareRawData(std::string data);
		static int Partition(std::vector<PreElement>& arr, int low, int high);
		static void QuickSort(std::vector<PreElement>& arr, int low, int high);
		static void SortElements(std::vector<PreElement>& elements);
		static std::vector<ParsedElement> ParseElements(std::vector<PreElement> elements);
		static ExtendedMap* GetNode(ExtendedMap* root, std::string key);
		static BTNode* BuildBalancedTree(const std::vector<ParsedElement>& elements, int start, int end);

		static std::vector<Element> CollectAll(ExtendedMap* node, std::string prefix = "");

	public:
		static BTNode* CreateBTree(std::string data);
		static std::vector<Element> CreateList(std::string data);
		static std::unordered_map<std::string, std::string> CreateUM(std::string data);
		static void InorderTraversal(BTNode* root);
		static Element* Find(BTNode* root, std::string key);
		static Element Find(std::vector<Element> root, std::string key);
		static std::string Find(std::unordered_map<std::string, std::string> root, std::string key);


		static void Add(BTNode* root, Element element);

		static ExtendedMap CreateExtendedMap(std::string data);
		static ExtendedMap* AddChar(ExtendedMap* node, char ch, std::string value = "");
		static void AddElement(ExtendedMap* root, Element element);

		static std::string FindValue(ExtendedMap* root, std::string key);
		static std::vector<Element> FindByPrefix(ExtendedMap* root, std::string prefix);
};

#endif
