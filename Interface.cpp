#include "Interface.h"

std::string getinput(std::string msg)
{
	std::string tmp = "";
	std::cout << "$: " << msg;
	std::getline(std::cin, tmp);

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

void Interface::shell()
{
	bool loop = true;
	do {
		argv = splitString( getinput("") , ' ' );
		
		if (this->argv[0] == "help")  { this->_help(); }
		if (this->argv[0] == "exit")  { loop = false; }
		if (this->argv[0] == "dump")  { this->_dump(); }
		if (this->argv[0] == "write") { this->_write(); }
		if (this->argv[0] == "run") { this->cpu->run(); }
	} while (loop != false);
}

void Interface::_help()
{
	if (this->argv.size() <= 1)
	{
		std::cout << "Avalible Commands" << std::endl;
		std::cout << "-----------------" << std::endl;
		std::cout << "help" << std::endl;
		std::cout << "exit" << std::endl;
		std::cout << "dump" << std::endl;
		std::cout << "write" << std::endl;
		std::cout << "run" << std::endl;
		return;
	}
	
	if (this->argv[1] == "help")
	{
		std::cout << "help command" << std::endl;
		std::cout << "-----------------" << std::endl;
		std::cout << "Provides a help page for a command" << std::endl;
		return;
	}

	if (this->argv[1] == "exit")
	{
		std::cout << "exit" << std::endl;
		std::cout << "-----------------" << std::endl;
		std::cout << "Exits the shell interface" << std::endl;
		return;
	}	
	
	if (this->argv[1] == "dump")
	{
		std::cout << "dump addr" << std::endl;
		std::cout << "-----------------" << std::endl;
		std::cout << "Dumps the instruction or data value from the specified address" << std::endl;
		return;
	}	
	
	if (this->argv[1] == "write")
	{
		std::cout << "write addr value" << std::endl;
		std::cout << "-----------------" << std::endl;
		std::cout << "Writes the value to the address" << std::endl;
		return;
	}	
	
	if (this->argv[1] == "run")
	{
		std::cout << "run" << std::endl;
		std::cout << "-----------------" << std::endl;
		std::cout << "Hands over execution to the CPU until a HALT instruction" << std::endl;
		return;
	}
}

void Interface::_dump()
{
	int addr = 0;
	if (this->argv.size() > 1)
	{
		addr = std::stoi( argv[1] );
	}
	this->cpu->print(addr);
}

void Interface::_write()
{
	int addr;
	int value;
	if (this->argv.size() > 2)
	{
		addr = std::stoi(argv[1]);
		value = std::stoi(argv[2]);
	}
	this->cpu->write(addr, value);
}

void Interface::_insert()
{

}