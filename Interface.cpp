#include "Interface.h"

std::string getinput(std::string msg)
{
	std::string tmp = "";
	std::cout << "$: " << msg;
	std::getline(std::cin, tmp);

	if (tmp == "")
	{
		std::cout << "Invalid Input!" << std::endl;
		//Use recursion to until we get a valid input
		tmp = getinput(msg);
	}

	return tmp;
}

Interface::Interface()
{
	this->cpu = new CPU;
}

Interface::~Interface()
{
	delete this->cpu;
}

void Interface::_dump()
{
	this->arg1 = getinput("What address to dump? ");
	this->cpu->print( std::stoi(this->arg1) );
}

//Needs a MASSIVE REWRITE
void Interface::shell()
{
	this->input = ""; this->arg1 = ""; this->arg2 = ""; this->arg3 = ""; this->arg4 = "";
	this->input = getinput("");

	if (this->input == "help")
	{
		std::cout << "Avalibable Commands" << std::endl;
		std::cout << "-------------------" << std::endl;
		std::cout << "help" << std::endl;
		std::cout << "run" << std::endl;
		std::cout << "write" << std::endl;
		std::cout << "insert" << std::endl;
		std::cout << "dump" << std::endl;
		std::cout << "step" << std::endl;
		std::cout << "exit" << std::endl;
		return;

	}

	if (this->input == "run")
	{
		this->cpu->run();
		return;
	}

	if (this->input == "write")
	{
		std::cout << "Not Yet Implemented!" << std::endl;
		return;
	}

	if (this->input == "insert")
	{
		std::cout << "Not Yet Implemented!" << std::endl;
		return;
	}

	if (this->input == "step")
	{
		this->cpu->step();
		return;
	}

	if (this->input == "dump")
	{
		this->_dump();
		return;
	}

	if (this->input == "exit")
	{
		exit(0);
	}
}