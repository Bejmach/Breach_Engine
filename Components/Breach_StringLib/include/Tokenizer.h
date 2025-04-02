#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<StringDict.h>

enum class TokenType{Undefined, Keyword, Operator, Delimiter, Type, Number, Literal, Identyfier, End};

struct Token{
	TokenType type;
	std::string value;
};

class tok{
	private:
		static Element* DictFind(std::string str, Dict* dictionary);
		static Token ToToken(Element);

	public:
		static std::vector<Token> Tokenize(std::string str, Dict* dictionary);

};

#endif
