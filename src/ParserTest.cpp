#include <StringDict.h>
#include<Tokenizer.h>
#include<Parser.h>
#include<chrono>

int main(){
	std::string data = stro::ReadFile("../data/dictionary.txt");

	Dict* dictionary = strd::CreateBTree(data);

	std::vector<Element> dictionaryList = strd::CreateList(data);

	std::string code = stro::ReadFile("../data/debug_script.brs");
		
	std::vector<Token> tokens = tok::Tokenize(code, dictionary);

	auto start = std::chrono::high_resolution_clock::now();
	OrderTree* tree = par::Parse(tokens);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

	std::cout<<"Parser: "<<duration<<"μs"<<std::endl;

	if(tree!=nullptr){tree->Print();}

}
