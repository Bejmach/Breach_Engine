#ifndef BREACHSL_H
#define BREACHSL_H

#include <iostream>

struct Bshader{
	std::string vertex;
	std::string fragment;
};

namespace BSL{
	std::string ReadFile(std::string path);
	
	Bshader ParseShader(std::string path);
}

#endif
