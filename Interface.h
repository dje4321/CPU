#pragma once
#include <string>
#include <vector>
#include "CPU.h"
#include "splitString.h"

std::string getinput(std::string msg);

class Interface
{
public:
	Interface();
	~Interface();
	void shell();
private:
	void _help();
	void _dump();
	void _write();
	void _insert();

	std::vector<std::string> argv;
	CPU* cpu;
};

