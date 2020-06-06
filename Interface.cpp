#include "Interface.h"

Interface::Interface()
{
	this->cpu = new CPU;
}

Interface::~Interface()
{
	delete this->cpu;
}

void Interface::shell()
{
for (;;)
{
	//Make sure we are working with a input var everytime
	this->input = "";
	std::cout << "$: ";
	std::getline(std::cin, this->input);

	if (this->input == "help")
	{
		std::cout << "Avalibable Commands" << std::endl;
		std::cout << "-------------------" << std::endl;
		std::cout << "write" << std::endl;
		std::cout << "dump" << std::endl;
		std::cout << "read" << std::endl;
		std::cout << "step" << std::endl;
		std::cout << "exit" << std::endl;
	} 
	else if (this->input == "write")
	{

	}
	else if (this->input == "dump" || this->input == "print")
	{
		std::cout << "$: Address to dump? ";
		//Needs input validation. No arg will cause a exception to trigger in std::stoi(int)
		std::getline(std::cin, arg1);
		this->cpu->print( std::stoi(arg1) );
	}
	else if (this->input == "read")
	{

	}
	else if (this->input == "step")
	{
		this->cpu->step();
		std::cout << std::endl;
	}
	else if (this->input == "exit")
	{
		exit(0);
	}
	else
	{
		std::cout << "Command Unknown" << std::endl;
	}
}
}