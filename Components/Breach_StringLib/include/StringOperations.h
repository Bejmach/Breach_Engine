#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <iostream>
#include <vector>

namespace stro{
	std::string ReadFile(std::string path);

	std::vector<std::string> Split(std::string str, std::string delimiter);
	std::string Merge(std::vector<std::string> vec, std::string delimiter = " ", int skipFront = 0, int skipEnd = 0);
	std::string ToLower(std::string str);
	std::string ToUpper(std::string str);
	bool Numeric(std::string str);
	bool IsFloat(std::string str);
	bool IsDouble(std::string str);
	bool IsInt(std::string str);

	int ToInt(std::string str);
	float ToFloat(std::string str);
	double ToDouble(std::string str);

	int Value(std::string str);
}

#endif
