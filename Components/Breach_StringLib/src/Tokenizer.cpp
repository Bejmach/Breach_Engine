#include "StringDict.h"
#include "StringOperations.h"
#include <Tokenizer.h>
#include <algorithm>
#include <ostream>
#include <sstream>

Element* tok::DictFind(std::string str, Dict* dictionary){
	return strd::Find(dictionary, str);
}

Token tok::ToToken(Element element){
	Token token;
	token.value = element.key;
	if(element.value == "KEYWORD"){
		token.type = TokenType::Keyword;
	}
	else if(element.value == "OPERATOR"){
		token.type = TokenType::Operator;
	}
	else if(element.value == "TYPE"){
		token.type = TokenType::Type;
	}
	else if(element.value == "DELIMITER"){
		token.type = TokenType::Delimiter;
	}
	else if(element.value == "LITERAL"){
		token.type = TokenType::Literal;
	}
	else if(element.value == "IDENTYFIER"){
		if(stro::IsInt(element.key) || stro::IsFloat(element.key) || stro::IsDouble(element.key)){
			token.type = TokenType::Number;
		}
		else{
			token.type = TokenType::Identyfier;
		}
	}
	else{
		return {TokenType::Undefined, "null"};
	}

	return token;
}

std::vector<Token> tok::Tokenize(std::string data, Dict* dictionary){
	std::vector<Token> tokens;

	std::stringstream stream(data);

	std::string iterated = "";
	char forwardBuffer = 0;
	char ch;
	char curChar;

	while(stream.get(ch)){
		curChar = forwardBuffer;
		forwardBuffer = ch;
		if(curChar == 0){
			continue;
		}
		std::string charStr(1, curChar);
		if(strd::Find(dictionary, iterated+charStr+forwardBuffer) != nullptr){
			if(stream.get(ch)){
				tokens.push_back(ToToken(*strd::Find(dictionary, iterated+charStr+forwardBuffer)));
				iterated.clear();
				curChar = forwardBuffer;
				forwardBuffer = ch;
			}
			else{
				tokens.push_back(ToToken(*strd::Find(dictionary, iterated+forwardBuffer)));
				return tokens;
			}
		}
		else if(strd::Find(dictionary, iterated+charStr)!=nullptr){
			tokens.push_back(ToToken(*strd::Find(dictionary, iterated+charStr)));
			iterated.clear();
		}
		else if(strd::Find(dictionary, charStr+forwardBuffer)!=nullptr){
			if(iterated!=""){
				tokens.push_back(ToToken({iterated, "IDENTYFIER"}));
				iterated.clear();
			}
			if(stream.get(ch)){
				tokens.push_back(ToToken(*strd::Find(dictionary, charStr+forwardBuffer)));
				curChar = forwardBuffer;
				forwardBuffer = ch;

			}
			else{
				tokens.push_back(ToToken(*strd::Find(dictionary, charStr+forwardBuffer)));
				return tokens;
			}
		}
		else if(strd::Find(dictionary, charStr)!=nullptr){
			if(iterated!=""){
				tokens.push_back(ToToken({iterated, "IDENTYFIER"}));
				iterated.clear();
			}
			tokens.push_back(ToToken(*strd::Find(dictionary, charStr)));		
		}
		else if(charStr == " " || charStr == "\n" || charStr == "\t"){
			if(iterated!=""){
				tokens.push_back(ToToken({iterated, "IDENTYFIER"}));
				iterated.clear();
			}
			if(charStr == "\n"){
				tokens.push_back({TokenType::End, "\\n"});
			}
		}
		else{
			iterated+=curChar;
		}
	}

	return tokens;
}
