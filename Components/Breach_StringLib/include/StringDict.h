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

struct Dict{
	Dict *left;
	Dict *right;

	int id;
	std::vector<Element> elements;

	Dict(ParsedElement element) : id(element.id), elements(element.elements), left(nullptr), right(nullptr){}
	Dict(){};
	~Dict();
};

class strd{
	private:
		static std::vector<PreElement> PrepareData(std::string data);
		static int Partition(std::vector<PreElement>& arr, int low, int high);
		static void QuickSort(std::vector<PreElement>& arr, int low, int high);
		static void SortElements(std::vector<PreElement>& elements);
		static std::vector<ParsedElement> ParseElements(std::vector<PreElement> elements);
		static Dict* BuildBalancedTree(const std::vector<ParsedElement>& elements, int start, int end);

	public:
		static Dict* CreateBTree(std::string data);
		static std::vector<Element> CreateList(std::string data);
		static std::unordered_map<std::string, std::string> CreateUM(std::string data);
		static void InorderTraversal(Dict* root);
		static Element* Find(Dict* root, std::string key);
		static Element Find(std::vector<Element> root, std::string key);
		static std::string Find(std::unordered_map<std::string, std::string> root, std::string key);

		void Add(Dict* root, Element element);
};

#endif
