#include "CPU.h"

CPU::CPU()
{
	for (int i = 0; i < this->_ram_size; i++)
	{
		this->ram[i] = 0;
	}
	this->ram[0] = ASM::write;
	this->ram[1] = 4;
	this->ram[2] = -5;
	this->ram[3] = ASM::jump;
	this->ram[4] = 0;
}

void CPU::run()
{
	std::string null;
for (;;)
{
	this->_decode();
	std::getline(std::cin, null);
}
}

void CPU::print(int addr)
{
	//Needs to validate that we are inbounds since we are a public function
	if (addr < 0 || addr > this->_ram_size)
	{
		return;
	}
	this->_dump(addr);
}

void CPU::write(int arg1, int arg2)
{
	//Do out of bounds checking
	if (arg1 < 0 || arg1 > this->_ram_size)
	{
		return;
	}
	this->ram[arg1] = arg2;
}

void CPU::step()
{
	for (int i = this->pc; i < this->pc + 3; i++)
	{
		std::cout << "Addr :" << i << std::endl;
		this->_dump(i);
		std::cout << std::endl;
	}
	this->_decode();
}

void CPU::_dump(int addr)
{
	switch (this->ram[addr])
	{
	case ASM::add:
		std::cout << "Ins: " << "ADD" << std::endl;
		std::cout << "Data: " << this->ram[addr] << std::endl;
		break;
	case ASM::sub:
		std::cout << "Ins: " << "SUB" << std::endl;
		std::cout << "Data: " << this->ram[addr] << std::endl;
		break;
	case ASM::jump:
		std::cout << "Ins: " << "JUMP" << std::endl;
		std::cout << "Data: " << this->ram[addr] << std::endl;
		break;
	case ASM::jumpgt:
		std::cout << "Ins: " << "JUMPGT" << std::endl;
		std::cout << "Data: " << this->ram[addr] << std::endl;
		break;
	case ASM::jumplt:
		std::cout << "Ins: " << "JUMPLT" << std::endl;
		std::cout << "Data: " << this->ram[addr] << std::endl;
		break;
	case ASM::write:
		std::cout << "Ins: " << "WRITE" << std::endl;
		std::cout << "Data: " << this->ram[addr] << std::endl;;
		break;
	case ASM::move:
		std::cout << "Ins: " << "MOVE" << std::endl;
		std::cout << "Data: " << this->ram[addr] << std::endl;
		break;
	case ASM::null:
		std::cout << "Data: " << this->ram[addr] << std::endl;
		break;
	default:
		std::cout << "Data: " << this->ram[addr] << std::endl;
		break;
	}
}

CPU::~CPU()
{

}

void CPU::_decode()
{
	//Check if the program counter has gone out of bounds and if it has, return to entrypoint
	if (this->pc < 0 || this->pc > this->_ram_size)
	{
		this->pc = 0;
	}

	//Execute the instruction depending on what data is in the program counter
	switch (this->ram[this->pc])
	{
	case ASM::null:
		this->_null();
		return;
	case ASM::write:
		this->_write();
		return;
	case ASM::add:
		this->_add();
		return;
	case ASM::sub:
		this->_sub();
		return;
	case ASM::jump:
		this->_jump();
		return;
	case ASM::jumpgt:
		this->_jumpgt();
		break;
	case ASM::jumplt:
		this->_jumplt();
		break;
	case ASM::move:
		this->_move();
		return;
	default: //Should never reach this and if we do, assume we encountered a NOP instruction
		this->_null();
		return;
	}
}

void CPU::_null()
{
	//NOP Instruction. NOP Chain until it hits a valid instruction
	this->pc += 1;
}

void CPU::_write()
{
	// X = Instruction
	// X+1 = Address
	// X+2 = Value

	//Grab the dest addr
	int dest = this->ram[this->pc + 1];

	//Check if we are writing out of bounds and if we are, increment to the next instruction
	if (dest < 0 || dest > this->_ram_size)
	{
		this->pc += 3;
		return;
	}
	//Write to the dest addr of the 
	this->ram[dest] = this->ram[this->pc + 2];

	//3 Byte Instruction
	this->pc += 3;
}

void CPU::_add()
{
	// X = Instruction
	// X+1 = Source Addr 1
	// X+2 = Source Addr 2
	// X+3 = Dest Addr

	//Grab the value from the first src addr
	int src1 = this->ram[this->pc + 1];
	//Grab the value from from the second source addr
	int src2 = this->ram[this->pc + 2];
	// Grab the addr of the dest
	int dest = this->ram[this->pc + 3];

	//Check if we are writing out of bounds and if we are, increment to the next instruction
	if (dest < 0 || dest > this->_ram_size)
	{
		this->pc += 4;
		return;
	}

	//Add the values of the first source addr to the second src addr
	this->ram[dest] = this->ram[src1] + this->ram[src2];

	//4 Byte Instruction
	this->pc += 4;
}

void CPU::_sub()
{
	// X = Instruction
	// X+1 = Source Addr 1
	// X+2 = Source Addr 2
	// X+3 = Dest Addr

	//Grab the value from the first src addr
	int src1 = this->ram[this->pc + 1];
	//Grab the value from from the second source addr
	int src2 = this->ram[this->pc + 2];
	// Grab the addr of the dest
	int dest = this->ram[this->pc + 3];

	//Check if we are writing out of bounds and if we are, increment to the next instruction
	if (dest < 0 || dest > this->_ram_size)
	{
		this->pc += 4;
		return;
	}

	//Add the values of the first source addr to the second src addr
	this->ram[dest] = this->ram[src1] - this->ram[src2];

	//4 Byte Instruction
	this->pc += 4;
}

void CPU::_jump()
{
	// X = Instruction
	// X+1 = Dest Addr

	//Grab the value of where we are jumping too
	int dest = this->ram[this->pc + 1];

	//Check if we are jumping out of bounds and if we are, increment to the next instruction
	if (dest < 0 || dest > this->_ram_size)
	{
		this->pc += 2;
		return;
	}
	//Set current instruction to the value
	this->pc = dest;
}

void CPU::_jumpgt()
{
	// X = Instruction
	// X+1 = Compare Address 1
	// X+2 = Compare Address 2
	// X+3 = Conditional Address

	//Get address to compare
	int cmp1 = this->ram[this->pc + 1];
	int cmp2 = this->ram[this->pc + 2];

	//Get the condidtional jump address
	int jump = this->ram[this->pc + 3];

	//Out of bounds checking
	if (jump < 0 || jump > this->_ram_size)
	{
		this->pc += 2;
		return;
	}

	//If cmp1 is greater than cmp2, set the program counter to the value at the third arg
	if (this->ram[cmp1] > this->ram[cmp2])
	{
		this->pc = jump;
		return;
	}

	//Increment by 4 Bytes if check fails
	//4 Byte Instruction
	this->pc += 4;
}

void CPU::_jumplt()
{
	// X = Instruction
	// X+1 = Compare Address 1
	// X+2 = Compare Address 2
	// X+3 = Conditional Address

	//Get address to compare
	int cmp1 = this->ram[this->pc + 1];
	int cmp2 = this->ram[this->pc + 2];

	//Get the condidtional jump address
	int jump = this->ram[this->pc + 3];

	if (jump < 0 || jump > this->_ram_size)
	{
		this->pc += 2;
		return;
	}

	//If cmp1 is less than cmp2, set the program counter to the value at the third arg
	if (this->ram[cmp1] < this->ram[cmp2])
	{
		this->pc = jump;
		return;
	}

	//Increment by 4 Bytes if check fails
	//4 Byte Instruction
	this->pc += 4;
}

void CPU::_move()
{
	// X = Instruction
	// X+1 = Source Addr
	// X+2 = Dest Addr

	//Grab the src addr containing the data
	int src = this->ram[this->pc + 1];
	//Grab the dest addr of where to store the data
	int dest = this->ram[this->pc + 2];	

	//Check if the dest is out of bounds
	if (dest < 0 || dest > this->_ram_size)
	{
		this->pc += 2;
		return;
	}

	//Read the value of the src addr and write it to the dest addr
	this->ram[dest] = this->ram[src];

	//3 Byte Instruction
	this->pc += 3;
}