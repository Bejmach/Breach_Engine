#ifndef PARSER_H
#define PARSER_H

#include "Tokenizer.h"
#include <vector>
#include<StringDict.h>

struct OrderTree{
	OrderTree(Token _root = {TokenType::Undefined, ""}, OrderTree* _parent = nullptr);
	~OrderTree();
	void Print(int spaces = 0);

	OrderTree* parent;
	Token root;
	std::vector<OrderTree*> childs;
};

namespace par{
	OrderTree* Parse(std::vector<Token> tokens);
}

#endif
