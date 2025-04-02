#include <Breach/BreachSL.h>
#include <StringOperations.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


std::string BSL::ReadFile(std::string path){
	std::ifstream file(path, std::ios::binary);
	if(!file){
		std::cout<<"Failed to open file "<<path<<". Check if the path is correct"<<std::endl;
		return "";
	}
	std::ostringstream content;
	content << file.rdbuf();
	return content.str();
}

Bshader BSL::ParseShader(std::string path){
	Bshader shaders;

	std::istringstream stream(BSL::ReadFile(path));

	std::string line;
	std::string vertexVariables, vertexCode;
	std::string fragmentVariables, fragmentCode;

	std::string tempVariables;

	std::string version = "#version 330 core\n";

	bool inFragment = false;
	bool inVertex = false;

	while(std::getline(stream, line)){
		std::vector<std::string> parsedLine = SO::Split(line, " ");

		if(parsedLine.size() == 0){
			continue;
		}

		else if(parsedLine[0].find("version") != std::string::npos){
			version = "#version " + SO::Merge(parsedLine, " ", 1, 0)+"\n";
		}

		else if(parsedLine[0] == "}"){
			inVertex = false;
			inFragment = false;
		}

		else if(inFragment){
			fragmentCode += line+"\n";
		}
		else if(inVertex){
			vertexCode += line+"\n";
		}

		else if(parsedLine[0] == "fragment(){" && !inVertex){
			fragmentVariables = tempVariables;
			tempVariables = "";
			inFragment = true;
		}
		else if(parsedLine[0] == "vertex(){" && !inFragment){
			vertexVariables = tempVariables;
			tempVariables = "";
			inVertex = true;
		}
			
		else if(!inVertex && !inFragment){
			tempVariables += SO::Merge(parsedLine)+"\n";
		}
	}

	shaders.vertex = version + vertexVariables + "void main(){\n" + vertexCode + "}\n";
	shaders.fragment = version + fragmentVariables + "void main(){\n" + fragmentCode + "}\n";

	return shaders;
}
