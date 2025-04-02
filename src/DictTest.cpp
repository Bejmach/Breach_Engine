#include<StringDict.h>
#include<chrono>

int main(){
	std::cout<<"creation time - list size: 100"<<std::endl;

	std::string data = stro::ReadFile("../data/debug_dict_100.txt");
	auto start = std::chrono::high_resolution_clock::now();
	Dict* dictionary = strd::CreateBTree(data);
	auto stop = std::chrono::high_resolution_clock::now();
	auto durationBt = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
	std::cout<<"BTree: "<<durationBt<<"μs"<<std::endl;

	start = std::chrono::high_resolution_clock::now();
	std::vector<Element> list = strd::CreateList(data);
	stop = std::chrono::high_resolution_clock::now();
	auto durationL = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
	std::cout<<"List: "<<durationL<<"μs"<<std::endl;

	start = std::chrono::high_resolution_clock::now();
	std::unordered_map<std::string, std::string> um = strd::CreateUM(data);
	stop = std::chrono::high_resolution_clock::now();
	auto durationUM = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
	std::cout<<"UM: "<<durationUM<<"μs"<<std::endl;
	
	double UMRatio = static_cast<double>(durationL)/durationUM;
	double BTRatio = static_cast<double>(durationL)/durationBt;

	std::cout<<"List: 1.0 times faster that list"<<std::endl<<"Unordered map: "<<UMRatio<<" times faster than list"<<std::endl<<"BTree: "<<BTRatio<<" times faster than list"<<std::endl<<std::endl;

	for(int i=1; i<=151; i+=5){

		std::cout<<"list size: "<<list.size()<<"; repetitions: "<<i<<"; total iterations: "<<list.size()*i<<std::endl;
		start = std::chrono::high_resolution_clock::now();
		for(int j=0; j<list.size(); j++){
			for(int k=0; k<i; k++){
				strd::Find(dictionary, list[j].key);
			}
		}
		stop = std::chrono::high_resolution_clock::now();
		durationBt = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout<<"BTree: "<<durationBt<<"μs"<<std::endl;

		start = std::chrono::high_resolution_clock::now();
		for(int j=0; j<list.size(); j++){
			for(int k=0; k<i; k++){
				strd::Find(um, list[j].key);
			}
		}
		stop = std::chrono::high_resolution_clock::now();
		durationL = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout<<"List: "<<durationL<<"μs"<<std::endl;

		start = std::chrono::high_resolution_clock::now();
		for(int j=0; j<list.size(); j++){
			for(int k=0; k<i; k++){
				strd::Find(list, list[j].key);
			}
		}
		stop = std::chrono::high_resolution_clock::now();
		durationUM = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout<<"UM: "<<durationUM<<"μs"<<std::endl;

		UMRatio = static_cast<double>(durationL)/durationUM;
		BTRatio = static_cast<double>(durationL)/durationBt;

		std::cout<<"List: 1.0 times faster that list"<<std::endl<<"Unordered map: "<<UMRatio<<" times faster than list"<<std::endl<<"BTree: "<<BTRatio<<" times faster than list"<<std::endl<<std::endl;
	}
	

	delete dictionary;
	return 0;
}
