#include "StringDict.h"
#include "Tokenizer.h"
#include <Parser.h>

OrderTree::OrderTree(Token _root, OrderTree* _parent){
	root = _root;
	parent = _parent;
}
void OrderTree::Print(int spaces){
	for(int i=0; i<spaces; i++){
		std::cout<<"  ";
	}
	std::cout<<this->root.value<<"{";
	for(int i=0; i<this->childs.size(); i++){
		std::cout<<std::endl;
		childs[i]->Print(spaces+1);
		std::cout<<std::endl;
	}
	for(int i=0; i<spaces; i++){
		std::cout<<"  ";
	}
	std::cout<<"}";
}

OrderTree* par::Parse(std::vector<Token> tokens){
	/*OrderTree* tree = new OrderTree();
	tree->parent = nullptr;
	tree->root = {TokenType::Undefined, "root"};
	OrderTree* currentRoot = tree;
	for(int i=0; i<tokens.size(); i++){
		if(tokens[i].type == TokenType::Keyword || tokens[i].type == TokenType::Type || tokens[i].type == TokenType::Delimiter){
			OrderTree* typeTree = new OrderTree();
			typeTree->parent = currentRoot;
			typeTree->root = elements[i];
			currentRoot->childs.push_back(typeTree);
			if(tokens[i].value != "break" ||){ 
				currentRoot = typeTree;
			}
		}
		else if(elements[i].value == "LITERAL"){
			OrderTree* typeTree = new OrderTree();
			typeTree->parent = currentRoot;
			typeTree->root = elements[i];
			currentRoot->childs.push_back(typeTree);
		}
		else if(elements[i].value == "close"){
			if(currentRoot->root.value != "open" && currentRoot->root.value != "parameter"){
				std::cout<<"Syntax error "<<currentRoot->root.value<<" : "<<elements[i].value<<std::endl;
				return nullptr;
			}
			else if(currentRoot->root.value == "open"){
				currentRoot = currentRoot->parent;
			}
			else if(currentRoot->root.value == "parameter"){
				currentRoot = currentRoot->parent->parent;
			}
		}
		else if(elements[i].value == "cClose"){
			if(currentRoot->root.value != "cOpen" && currentRoot->root.value != "parameter"){
				std::cout<<"Syntax error "<<currentRoot->root.value<<" : "<<elements[i].value<<std::endl;
				return nullptr;
			}
			else{
				currentRoot = currentRoot->parent->parent;
			}
		}
		else if(elements[i].value == "eol"){
			if(currentRoot->root.value == "open" || currentRoot->root.value == "cOpen"){
				std::cout<<"Syntax error "<<currentRoot->root.value<<" : "<<elements[i].value<<std::endl;
				return nullptr;
			}
			else{
				currentRoot = currentRoot->parent;
			}
		}
		else if(elements[i].value == "separator"){
			if(currentRoot->root.value != "parameter" && currentRoot->root.value != "open"){
				std::cout<<"Syntax error "<<currentRoot->root.value<<" : "<<elements[i].value<<std::endl;
				return nullptr;
			}
			else if(currentRoot->root.value == "parameter"){
				currentRoot = currentRoot->parent;
			}
		}
	}*/

	return nullptr;
}
