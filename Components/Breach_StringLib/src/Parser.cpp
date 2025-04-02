#include "StringDict.h"
#include <Parser.h>

OrderTree::OrderTree(Element _root, OrderTree* _parent){
	root = _root;
	parent = _parent;
}
void OrderTree::Print(int spaces){
	for(int i=0; i<spaces; i++){
		std::cout<<"  ";
	}
	std::cout<<this->root.key<<"{";
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

OrderTree* par::Parse(std::vector<Element> elements){
	OrderTree* tree = new OrderTree();
	tree->parent = nullptr;
	tree->root = {"root", "root"};
	OrderTree* currentRoot = tree;
	for(int i=0; i<elements.size(); i++){
		/*std::cout<<currentRoot->root.value<<":"<<currentRoot->root.key<<std::endl;
		std::cout<<elements[i].value<<":"<<elements[i].key<<std::endl;
		std::cout<<std::endl;*/
		if(elements[i].value == "parameter" || elements[i].value == "funcInit" ||
				elements[i].value == "open" || elements[i].value == "cOpen" ||
				elements[i].value == "comOpen" || elements[i].value == "loop" ||
				elements[i].value == "func" || elements[i].value == "return" ||
				elements[i].value == "lf"){
			OrderTree* typeTree = new OrderTree();
			typeTree->parent = currentRoot;
			typeTree->root = elements[i];
			currentRoot->childs.push_back(typeTree);
			currentRoot = typeTree;
		}
		else if(elements[i].value == "op" || elements[i].value == "bOp" ||
				elements[i].value == "lOp" || elements[i].value == "local"){
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
	}

	return tree;
}
