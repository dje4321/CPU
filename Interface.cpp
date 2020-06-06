#include "Interface.h"

std::string input(std::string msg)
{
	std::string tmp;
	std::cout << "$: " << msg;
	std::getline(std::cin, tmp);

	if (tmp == "")
	{
		std::cout << "Invalid Input!" << std::endl;
		tmp = input(msg);
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

//Needs a MASSIVE REWRITE
void Interface::shell()
{
for (;;)
{
	//Make sure we are working with a blank input var everytime
	this->input = "";
	std::cout << "$: ";
	std::getline(std::cin, this->input);

	if (this->input == "help")
	{
		std::cout << "Avalibable Commands" << std::endl;
		std::cout << "-------------------" << std::endl;
		std::cout << "write" << std::endl;
		std::cout << "insert" << std::endl;
		std::cout << "dump" << std::endl;
		std::cout << "step" << std::endl;
		std::cout << "exit" << std::endl;
	} 

	else if (this->input == "write")
	{
		this->arg1 == ""; this->arg2 = "";
		std::cout << "$: Address to write? ";
		std::getline(std::cin, this->arg1);

		std::cout << "$: Value to write? ";
		std::getline(std::cin, this->arg2);

		//Needs input validation. No arg will cause a exeption in std::stoi(int)
		this->cpu->write( std::stoi(this->arg1), std::stoi(this->arg2) );
	}

	else if (this->input == "insert")
	{
		this->arg1 = ""; this->arg2 = ""; this->arg3 = ""; this->arg4 = "";
		std::cout << "Avalibable Instructions" << std::endl;
		std::cout << "-----------------------" << std::endl;
		std::cout << "write, add, subtract, jump, jumpgt, jumplt, move, output" << std::endl;
		std::cout << "$: What instruction to insert? ";

		std::getline(std::cin, this->arg1);
		if (this->arg1 == "write")
		{

		}
	}

	else if (this->input == "dump" || this->input == "print" || this->input == "read")
	{
		this->arg1 = "";

		std::cout << "$: Address to " << this->input << "? ";
		std::getline(std::cin, this->arg1);

		//Needs input validation. No arg will cause a exception to trigger in std::stoi(int)
		this->cpu->print( std::stoi(this->arg1) );
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