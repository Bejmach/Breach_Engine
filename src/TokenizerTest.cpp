#include <StringDict.h>
#include<Tokenizer.h>
#include<chrono>

int main(){
	std::string data = stro::ReadFile("../data/dictionary.txt");

	Dict* dictionary = strd::CreateBTree(data);

	std::vector<Element> dictionaryList = strd::CreateList(data);

	std::string code = stro::ReadFile("../data/debug_script.brs");
		
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<Token> tokenized = tok::Tokenize(code, dictionary);
	auto stop = std::chrono::high_resolution_clock::now();
	auto durationCh = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

	std::cout<<"Char: "<<durationCh<<"μs"<<std::endl;

	for(int i=0; i<tokenized.size(); i++){
		std::cout<<tokenized[i].value<<": "<<static_cast<int>(tokenized[i].type)<<std::endl;
	}
}
