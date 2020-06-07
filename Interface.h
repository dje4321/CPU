#pragma once
#include "CPU.h"

std::string getinput(std::string msg);

class Interface
{
public:
	Interface();
	~Interface();
	void shell();
private:
	void _dump();
	void _write();
	void _insert();
	CPU* cpu;
	std::string input;
	std::string arg1;
	std::string arg2;
	std::string arg3;
	std::string arg4;
	std::string arg5;
};

