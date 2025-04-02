#include <StringOperations.h>

#include <algorithm>
#include <cctype>

#include<fstream>
#include<sstream>

std::string stro::ReadFile(std::string path){
	std::ifstream file(path, std::ios::binary);

	if(!file){
		std::cout<<"failed to open file: "<<path<<std::endl;
		return{};
	}

	std::ostringstream content;
	content << file.rdbuf();
	file.close();
	return content.str();
}

std::vector<std::string> stro::Split(std::string str, std::string delimiter){
	std::string pushed;

	std::vector<std::string> holder;
		int startPosition = 0;
		int endPosition = str.find(delimiter);
		while(endPosition!=std::string::npos){
			endPosition = endPosition+startPosition;
			pushed = str.substr(startPosition, endPosition-startPosition);
			if(pushed!=""){
				holder.push_back(str.substr(startPosition, endPosition-startPosition));
			}
			startPosition = endPosition+1;
			if(startPosition>=str.length()){
				return holder;
			}
			endPosition = str.substr(startPosition).find(delimiter);
		}
	pushed = str.substr(startPosition, endPosition-startPosition);
	if(pushed!=""){
		holder.push_back(str.substr(startPosition, endPosition-startPosition));
	}
	return holder;
}
std::string stro::Merge(std::vector<std::string> vec, std::string delimiter, int skipFront, int skipEnd){
	std::string returner;
	if(skipFront+skipEnd < vec.size()-1 && skipFront>=0 && skipEnd>=0){
		for(int i=skipFront; i<vec.size()-skipEnd; i++){
			returner += (i==skipFront) ? vec[i] : delimiter+vec[i];
		}
	}
	return returner;
}

std::string stro::ToLower(std::string str){
	std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c){return std::tolower(c); });

	return str;
}
std::string stro::ToUpper(std::string str){
	std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c){return std::toupper(c); });

	return str;
}
bool stro::Numeric(std::string str){
	return (std::to_string(std::stoi(str)) == str);
}

int stro::Value(std::string str){
	int value = 0;
	for(int i=0; i<str.size(); i++){
		value+=(int)str[i];
	}
	return value;
}

bool stro::IsInt(std::string str){
	int i = 0;
	if(str[0] == '-'){
		i=1;
	}
	for(int i=0; i<str.size(); i++){
		if(!std::isdigit(str[i])){
			return false;
		}
	}
	return true;
}

bool stro::IsFloat(std::string str){
	int i=0;
	if(str[0] == '-'){
		i=1;
	}
	bool foundDot = false;
	for(int i=0; i<str.size(); i++){
		if(!std::isdigit(str[i])){
			if(str[i] == '.' && !foundDot){
				foundDot = true;
			}
			else if(i == str.size()-1 && str[i] == 'f'){
				break;
			}
			else{
				return false;
			}
		}
	}
	return true;
}
bool stro::IsDouble(std::string str){
	int i=0;
	if(str[0] == '-'){
		i=1;
	}
	bool foundDot = false;
	for(int i=0; i<str.size(); i++){
		if(!std::isdigit(str[i])){
			if(str[i] == '.' && !foundDot){
				foundDot = true;
			}
			else{
				return false;
			}
		}
	}
	return true;
}

int stro::ToInt(std::string str){
	
}
