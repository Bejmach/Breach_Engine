#include <StringOperations.h>
#include<StringDict.h>
#include<iostream>
#include <vector>
#include<chrono>

int main(){
	std::string data = stro::ReadFile("../data/debug_dict_10k.txt");
	//std::cout<<data<<std::endl<<std::endl;

	ExtendedMap map = strd::CreateExtendedMap(data);

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<Element> prefixFind = strd::FindByPrefix(&map, "");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
	
	for(int i=0; i<prefixFind.size(); i++){
		std::cout<<i<<". Key: "<<prefixFind[i].key<<", Value: "<<prefixFind[i].value<<std::endl;
	}

	std::cout<<"Lookup: "<<duration<<"μs"<<std::endl;

	return 0;
}
