#include <StringOperations.h>
#include<StringDict.h>
#include<iostream>
#include <vector>

int main(){
	std::string data = stro::ReadFile("../data/debug_dict_100.txt");
	//std::cout<<data<<std::endl<<std::endl;

	ExtendedMap map = strd::CreateExtendedMap(data);

	std::vector<Element> list = strd::CreateList(data);

	for(int i=0; i<list.size(); i++){
		std::cout<<list[i].key<<" "<<strd::FindValue(&map, list[i].key)<<std::endl;
	}

	return 0;
}
