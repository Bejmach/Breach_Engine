#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include<StringDict.h>

struct OrderTree{
	OrderTree(Element _root = {"", ""}, OrderTree* _parent = nullptr);
	~OrderTree();
	void Print(int spaces = 0);

	OrderTree* parent;
	Element root;
	std::vector<OrderTree*> childs;
};

namespace par{
	OrderTree* Parse(std::vector<Element> elements);
}

#endif
