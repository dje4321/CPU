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

void Interface::_write()
{
	this->arg1 = getinput("What address to write? ");
	this->arg2 = getinput("What value to write? ");
	
	this->cpu->write(std::stoi(this->arg1), std::stoi(this->arg2));
}

void Interface::_insert()
{
	bool loop = true;
	do {
		this->arg1 = getinput("What instruction to insert? ");
		if (this->arg1 == "help") 
		{
			std::cout << "Avalible Commands" << std::endl;
			std::cout << "-----------------" << std::endl;
			std::cout << "write" << std::endl;
			std::cout << "add" << std::endl;
			std::cout << "subtract" << std::endl;
			std::cout << "jump" << std::endl;
			std::cout << "jumpgt" << std::endl;
			std::cout << "jumplt" << std::endl;
			std::cout << "move" << std::endl;
			std::cout << "output" << std::endl;
			std::cout << "pause" << std::endl;
			std::cout << "halt" << std::endl;
		}
		if (this->arg1 == "write") 
		{
			//X = Instruction
			//X+1 = Dest Addr
			//X+2 = Value
			int startAddr;
			this->arg2 = getinput("Insert Address? ");
			this->arg3 = getinput("What addr to write to? ");
			this->arg4 = getinput("What value to write to the address? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::write);
			//Write the first argument offset by 1
			this->cpu->write(startAddr + 1, std::stoi(this->arg3));
			//Write the second argument offset by 2
			this->cpu->write(startAddr + 2, std::stoi(this->arg4));
			loop = false;
		}
		if (this->arg1 == "add") 
		{
			//X = Instruction
			//X+1 = Source Addr 1
			//X+2 = Source Addr 2
			//X+3 = Dest Addr
			int startAddr;
			this->arg2 = getinput("Insert Address? ");
			this->arg3 = getinput("Source Addr 1? ");
			this->arg4 = getinput("Source Addr 2? ");
			this->arg5 = getinput("Dest address? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::add);
			//Write each argument offest by the argument location
			this->cpu->write(startAddr + 1, std::stoi(this->arg3));
			this->cpu->write(startAddr + 2, std::stoi(this->arg4));
			this->cpu->write(startAddr + 3, std::stoi(this->arg5));
			loop = false;
		}
		if (this->arg1 == "subtract") 
		{
			//X = Instruction
			//X+1 = Source Addr 1
			//X+2 = Source Addr 2
			//X+3 = Dest Addr
			int startAddr;
			this->arg2 = getinput("Insert Address? ");
			this->arg3 = getinput("Source Addr 1? ");
			this->arg4 = getinput("Source Addr 2? ");
			this->arg5 = getinput("Dest address? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::sub);
			//Write each argument offest by the argument location
			this->cpu->write(startAddr + 1, std::stoi(this->arg3));
			this->cpu->write(startAddr + 2, std::stoi(this->arg4));
			this->cpu->write(startAddr + 3, std::stoi(this->arg5));
			loop = false;
		}
		if (this->arg1 == "jump") 
		{
			//X = Instruction
			//X+1 = Jump Addr
			int startAddr;
			this->arg2 = getinput("Insert Address? ");
			this->arg3 = getinput("Jump Addr? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::jump);
			//Write each argument offest by the argument location
			this->cpu->write(startAddr + 1, std::stoi(this->arg3));
			loop = false;
		}
		if (this->arg1 == "jumpgt") 
		{
			//X = Instruction
			//X+1 = Cmp Addr 1
			//X+2 = Cmp Addr 2
			//X+3 = Dest Addr
			int startAddr;
			this->arg2 = getinput("Insert Address? ");
			this->arg3 = getinput("Cmp Addr 1? ");
			this->arg4 = getinput("Cmp Addr 2? ");
			this->arg5 = getinput("Jump Addr? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::jumpgt);
			//Write each argument offest by the argument location
			this->cpu->write(startAddr + 1, std::stoi(this->arg3));
			this->cpu->write(startAddr + 2, std::stoi(this->arg4));
			this->cpu->write(startAddr + 3, std::stoi(this->arg5));
			loop = false;
		}
		if (this->arg1 == "jumplt") 
		{
			//X = Instruction
			//X+1 = Cmp Addr 1
			//X+2 = Cmp Addr 2
			//X+3 = Dest Addr
			int startAddr;
			this->arg2 = getinput("Insert Address? ");
			this->arg3 = getinput("Cmp Addr 1? ");
			this->arg4 = getinput("Cmp Addr 2? ");
			this->arg5 = getinput("Jump Addr? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::jumplt);
			//Write each argument offest by the argument location
			this->cpu->write(startAddr + 1, std::stoi(this->arg3));
			this->cpu->write(startAddr + 2, std::stoi(this->arg4));
			this->cpu->write(startAddr + 3, std::stoi(this->arg5));
			loop = false;
		}
		if (this->arg1 == "move") 
		{
			//X = Instruction
			//X+1 = Source Addr
			//X+2 = Dest Addr
			int startAddr;
			this->arg2 = getinput("Insert Address? ");
			this->arg3 = getinput("Source Addr? ");
			this->arg4 = getinput("Dest Addr? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::move);
			//Write each argument offest by the argument location
			this->cpu->write(startAddr + 1, std::stoi(this->arg3));
			this->cpu->write(startAddr + 2, std::stoi(this->arg4));
			loop = false;
		}
		if (this->arg1 == "output") 
		{
			//X = Instruction
			//X+1 = Output Addr
			int startAddr;
			this->arg2 = getinput("Insert Address? ");
			this->arg3 = getinput("Output Addr? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::out);
			//Write each argument offest by the argument location
			this->cpu->write(startAddr + 1, std::stoi(this->arg3));
			loop = false;
		}
		if (this->arg1 == "pause") 
		{
			//X = Instruction
			int startAddr;
			this->arg2 = getinput("Insert Address? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::pause);
			loop = false;
		}
		if (this->arg1 == "halt") 
		{
			//X = Instruction
			int startAddr;
			this->arg2 = getinput("Insert Address? ");

			startAddr = std::stoi(this->arg2);

			//Write the instruction to the start address
			this->cpu->write(startAddr, ASM::halt);
			loop = false;
		}
	} while (loop != false);
}

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
		this->_write();
		return;
	}

	if (this->input == "insert")
	{
		this->_insert();
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