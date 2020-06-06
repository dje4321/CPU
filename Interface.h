#pragma once
#include "CPU.h"

std::string input(std::string msg);

class Interface
{
public:
	Interface();
	~Interface();
	void shell();
private:
	CPU* cpu;
	std::string input;
	std::string arg1;
	std::string arg2;
	std::string arg3;
	std::string arg4;
};

