#include "CPU.h"

CPU::CPU()
{
	this->registers.pc = 0;
	this->registers.halt = false;

	//Set each instruction to the proper opcode and set the instruction size
	this->Assembly.null.opcode = Opcode::null;
	this->Assembly.null.size = 1;

	this->Assembly.R_read.opcode = Opcode::R_read;
	this->Assembly.R_read.size = 3;

	this->Assembly.write.opcode = Opcode::write;
	this->Assembly.write.size = 3;

	this->Assembly.R_write.opcode = Opcode::write;
	this->Assembly.R_write.size = 3;

	this->Assembly.add.opcode = Opcode::add;
	this->Assembly.add.size = 4;

	this->Assembly.R_add.opcode = Opcode::R_add;
	this->Assembly.R_add.size = 4;

	this->Assembly.subtract.opcode = Opcode::subtract;
	this->Assembly.subtract.size = 4;

	this->Assembly.jump.opcode = Opcode::jump;
	this->Assembly.jump.size = 2;

	this->Assembly.jumpgt.opcode = Opcode::jumpgt;
	this->Assembly.jumpgt.size = 4;

	this->Assembly.jumplt.opcode = Opcode::jumplt;
	this->Assembly.jumplt.size = 4;

	this->Assembly.move.opcode = Opcode::move;
	this->Assembly.move.size = 3;

	this->Assembly.out.opcode = Opcode::out;
	this->Assembly.out.size = 1;

	this->Assembly.pause.opcode = Opcode::pause;
	this->Assembly.pause.size = 1;

	this->Assembly.halt.opcode = Opcode::halt;
	this->Assembly.halt.size = 1;

	//Set the ram to the HALT opcode
	for (int i = 0; i < this->ram.size; i++)
	{
		this->ram.memory[i] = this->Assembly.halt.opcode;
	}

	this->ram.memory[0] = Opcode::R_write;
	this->ram.memory[1] = 'A';
	this->ram.memory[2] = 40;
	this->ram.memory[3] = Opcode::R_write;
	this->ram.memory[4] = 'B';
	this->ram.memory[5] = 29;
	this->ram.memory[6] = Opcode::R_add;
	this->ram.memory[7] = 'A';
	this->ram.memory[8] = 'B';
	this->ram.memory[9] = 'z';
	this->ram.memory[10] =  Opcode::write;
	this->ram.memory[11] = 256;
	this->ram.memory[12] = 0;
	this->ram.memory[13] = Opcode::R_read;
	this->ram.memory[14] = 'z';
	this->ram.memory[15] = 256;
	this->ram.memory[16] = Opcode::out;
	this->ram.memory[17] = 256;
	this->ram.memory[18] = Opcode::halt;

	//Calculates a part of the fib seq and then HALTS
	//this->ram.memory[0] = Opcode::write;
	//this->ram.memory[1] = 256;
	//this->ram.memory[2] = 0;
	//this->ram.memory[3] = Opcode::write;
	//this->ram.memory[4] = 257;
	//this->ram.memory[5] = 1;
	//this->ram.memory[6] = Opcode::write;
	//this->ram.memory[7] = 259;
	//this->ram.memory[8] = 102334155;
	//this->ram.memory[9] = Opcode::write;
	//this->ram.memory[10] = 260;
	//this->ram.memory[11] = 0;
	//this->ram.memory[12] = Opcode::add;
	//this->ram.memory[13] = 256;
	//this->ram.memory[14] = 257;
	//this->ram.memory[15] = 258;
	//this->ram.memory[16] = Opcode::move;
	//this->ram.memory[17] = 257;
	//this->ram.memory[18] = 256;
	//this->ram.memory[19] = Opcode::move;
	//this->ram.memory[20] = 258;
	//this->ram.memory[21] = 257;
	//this->ram.memory[22] = Opcode::jumpgt;
	//this->ram.memory[23] = 258;
	//this->ram.memory[24] = 259;
	//this->ram.memory[25] = 30;
	//this->ram.memory[26] = Opcode::out;
	//this->ram.memory[27] = 258;
	//this->ram.memory[28] = Opcode::jump;
	//this->ram.memory[29] = 12;
	//this->ram.memory[30] = Opcode::halt;
	//this->ram.memory[31] = Opcode::jump;
	//this->ram.memory[32] = 0;
}

void CPU::run()
{
	//Run until a halt instruction is triggered
	do {
		this->_decode();
	} while (this->registers.halt != true);

	//Set halt to false incase we want to resume control
	this->registers.halt = false;
}

void CPU::print(int addr)
{
	//Needs to validate that we are inbounds since we are a public function
	if (addr < 0 || addr > this->ram.size)
	{
		return;
	}
	this->_dumpIns(addr);
}

void CPU::write(int arg1, int arg2)
{
	//Do out of bounds checking
	if (arg1 < 0 || arg1 > this->ram.size)
	{
		return;
	}
	this->ram.memory[arg1] = arg2;
}

void CPU::step()
{
	this->_decode();
	std::cout << "Addr: " << this->registers.pc << std::endl;
	this->_dumpIns(this->registers.pc);
}

void CPU::_pause()
{
	std::string null;
	std::cout << "Paused. Press ENTER to continue";
	std::getline(std::cin, null);
	this->_null();
}

void CPU::_halt()
{
	std::cout << "HALTING!" << std::endl;

	if (this->registers.halt == true)
	{
		this->registers.halt = false;
		this->_null();
		return;
	}
	this->_null();
	this->registers.halt = true;
}

void CPU::_dumpIns(int addr)
{
	switch (this->ram.memory[addr])
	{
	case Opcode::add:
		std::cout << "Ins: " << "ADD" << std::endl;
		std::cout << "Src Addr A: " << this->ram.memory[addr + 1] << std::endl;
		std::cout << "Src Addr B: " << this->ram.memory[addr + 2] << std::endl;
		std::cout << "Dest Addr: " << this->ram.memory[addr + 3] << std::endl;
		break;
	case Opcode::R_add:
		std::cout << "Ins: " << "Register ADD" << std::endl;
		std::cout << "Reg 1: " << (char)this->ram.memory[addr + 1] << std::endl;
		std::cout << "Reg 2: " << (char)this->ram.memory[addr + 2] << std::endl;
		std::cout << "Dest Reg: " << (char)this->ram.memory[addr + 3] << std::endl;
		break;
	case Opcode::R_read:
		std::cout << "Ins: " << "Register READ" << std::endl;
		std::cout << "Reg: " << (char)this->ram.memory[addr + 1] << std::endl;
		std::cout << "Dest Addr: " << this->ram.memory[addr + 2] << std::endl;
		break;
	case Opcode::R_write:
		std::cout << "Ins: " << "Register WRITE" << std::endl;
		std::cout << "Reg: " << (char)this->ram.memory[addr + 1] << std::endl;
		std::cout << "Value: " << this->ram.memory[addr + 2] << std::endl;
		break;
	case Opcode::subtract:
		std::cout << "Ins: " << "SUBTRACT" << std::endl;
		std::cout << "Src Addr A: " << this->ram.memory[addr + 1] << std::endl;
		std::cout << "Src Addr B: " << this->ram.memory[addr + 2] << std::endl;
		std::cout << "Dest Addr: " << this->ram.memory[addr + 3] << std::endl;
		break;
	case Opcode::jump:
		std::cout << "Ins: " << "JUMP" << std::endl;
		std::cout << "Jump Addr: " << this->ram.memory[addr + 1] << std::endl;
		break;
	case Opcode::jumpgt:
		std::cout << "Ins: " << "JUMPGT" << std::endl;
		std::cout << "Cmp Addr A: " << this->ram.memory[addr + 1] << std::endl;
		std::cout << "Cmp Addr B: " << this->ram.memory[addr + 2] << std::endl;
		std::cout << "Jump Addr: " << this->ram.memory[addr + 3] << std::endl;
		break;
	case Opcode::jumplt:
		std::cout << "Ins: " << "JUMPLT" << std::endl;
		std::cout << "Cmp Addr A: " << this->ram.memory[addr + 1] << std::endl;
		std::cout << "Cmp Addr B: " << this->ram.memory[addr + 2] << std::endl;
		std::cout << "Jump Addr: " << this->ram.memory[addr + 3] << std::endl;
		break;
	case Opcode::write:
		std::cout << "Ins: " << "WRITE" << std::endl;
		std::cout << "Dest Addr: " << this->ram.memory[addr + 1] << std::endl;
		std::cout << "Value: " << this->ram.memory[addr + 2] << std::endl;
		break;
	case Opcode::move:
		std::cout << "Ins: " << "MOVE" << std::endl;
		std::cout << "Src Addr A: " << this->ram.memory[addr + 1] << std::endl;
		std::cout << "Dest Addr B: " << this->ram.memory[addr + 2] << std::endl;
		break;
	case Opcode::null:
		std::cout << "Ins: " << "NULL" << std::endl;
		break;
	case Opcode::out:
		std::cout << "Ins: " << "OUTPUT" << std::endl;
		std::cout << "Out Addr: " << this->ram.memory[addr + 1] << std::endl;
		break;
	case Opcode::pause:
		std::cout << "Ins: " << "PAUSE" << std::endl;	
		break;
	case Opcode::halt:
		std::cout << "Ins: " << "HALT!" << std::endl;
		break;
	default:
		std::cout << "Data: " << this->ram.memory[addr] << std::endl;
		break;
	}
}

CPU::~CPU()
{

}

void CPU::_decode()
{
	//Check if the program counter has gone out of bounds and if it has, return to entrypoint
	if (this->registers.pc < 0 || this->registers.pc > this->ram.size)
	{
		this->registers.pc = 0;
	}

	//Execute the instruction depending on what data is in the program counter
	switch (this->ram.memory[this->registers.pc])
	{
	case Opcode::null:
		this->_null();
		return;
	case Opcode::R_read:
		this->R_read();
		return;
	case Opcode::write:
		this->_write();
		return;
	case Opcode::R_write:
		this->R_write();
		return;
	case Opcode::add:
		this->_add();
		return;
	case Opcode::R_add:
		this->R_add();
		return;
	case Opcode::subtract:
		this->_sub();
		return;
	case Opcode::jump:
		this->_jump();
		return;
	case Opcode::jumpgt:
		this->_jumpgt();
		break;
	case Opcode::jumplt:
		this->_jumplt();
		break;
	case Opcode::move:
		this->_move();
		return;
	case Opcode::out:
		this->_out();
		return;
	case Opcode::pause:
		this->_pause();
		return;
	case Opcode::halt:
		this->_halt();
		return;
	default: //Should never reach this and if we do, assume we encountered a NOP instruction
		this->_null();
		return;
	}
}

void CPU::_out()
{
	// X = Instruction
	// X+1 = Output Addr

	int dest = this->ram.memory[this->registers.pc + 1];

	std::cout << "Addr: " << dest << " Value: " << this->ram.memory[dest] << std::endl;

	// 2 Byte Instruction
	this->registers.pc += this->Assembly.out.size;
}

void CPU::_null()
{
	//NOP Instruction. NOP Chain until it hits a valid instruction
	this->registers.pc += this->Assembly.null.size;
}

void CPU::R_read()
{
	// X = Instruction
	// X+1 = Src Reg
	// X+2 = Dest Addr

	int reg = this->ram.memory[this->registers.pc + 1];
	int addr = this->ram.memory[this->registers.pc + 2];

	this->ram.memory[addr] = this->registers.var.loc[reg];
	this->registers.pc += this->Assembly.R_read.size;
}

void CPU::_write()
{
	// X = Instruction
	// X+1 = Address
	// X+2 = Value

	//Grab the dest addr
	int dest = this->ram.memory[this->registers.pc + 1];

	//Check if we are writing out of bounds and if we are, increment to the next instruction
	if (dest < 0 || dest > this->ram.size)
	{
		this->registers.pc += this->Assembly.write.size;
		return;
	}
	//Write to the dest addr the value
	this->ram.memory[dest] = this->ram.memory[this->registers.pc + 2];

	//3 Byte Instruction
	this->registers.pc += this->Assembly.write.size;
}

void CPU::R_write()
{
	// X = Instruction
	// X+1 = Register
	// X+2 = Value

	int reg = this->ram.memory[this->registers.pc + 1];
	int value = this->ram.memory[this->registers.pc + 2];

	this->registers.var.loc[reg] = value;
	this->registers.pc += this->Assembly.R_write.size;
}

void CPU::_add()
{
	// X = Instruction
	// X+1 = Source Addr 1
	// X+2 = Source Addr 2
	// X+3 = Dest Addr

	//Grab the value from the first src addr
	int src1 = this->ram.memory[this->registers.pc + 1];
	//Grab the value from from the second source addr
	int src2 = this->ram.memory[this->registers.pc + 2];
	// Grab the addr of the dest
	int dest = this->ram.memory[this->registers.pc + 3];

	//Check if we are writing out of bounds and if we are, increment to the next instruction
	if (dest < 0 || dest > this->ram.size)
	{
		this->registers.pc += this->Assembly.add.size;
		return;
	}

	//Add the values of the first source addr to the second src addr
	this->ram.memory[dest] = this->ram.memory[src1] + this->ram.memory[src2];

	//4 Byte Instruction
	this->registers.pc += this->Assembly.add.size;
}

void CPU::R_add()
{
	//X = Instruction
	//X+1 = Src Reg 1
	//X+2 = Src Reg 2
	//X+3 = Dest Reg

	int reg1 = this->ram.memory[this->registers.pc + 1];
	int reg2 = this->ram.memory[this->registers.pc + 2];
	int dest = this->ram.memory[this->registers.pc + 3];

	this->registers.var.loc[dest] = this->registers.var.loc[reg1] + this->registers.var.loc[reg2];
	this->registers.pc += this->Assembly.R_add.size;

}

void CPU::_sub()
{
	// X = Instruction
	// X+1 = Source Addr 1
	// X+2 = Source Addr 2
	// X+3 = Dest Addr

	//Grab the value from the first src addr
	int src1 = this->ram.memory[this->registers.pc + 1];
	//Grab the value from from the second source addr
	int src2 = this->ram.memory[this->registers.pc + 2];
	// Grab the addr of the dest
	int dest = this->ram.memory[this->registers.pc + 3];

	//Check if we are writing out of bounds and if we are, increment to the next instruction
	if (dest < 0 || dest > this->ram.size)
	{
		this->registers.pc += this->Assembly.subtract.size;
		return;
	}

	//Add the values of the first source addr to the second src addr
	this->ram.memory[dest] = this->ram.memory[src1] - this->ram.memory[src2];

	//4 Byte Instruction
	this->registers.pc += this->Assembly.subtract.size;
}

void CPU::_jump()
{
	// X = Instruction
	// X+1 = Dest Addr

	//Grab the value of where we are jumping too
	int dest = this->ram.memory[this->registers.pc + 1];

	//Check if we are jumping out of bounds and if we are, increment to the next instruction
	if (dest < 0 || dest > this->ram.size)
	{
		this->registers.pc += this->Assembly.jump.size;
		return;
	}
	//Set current instruction to the value
	this->registers.pc = dest;
}

void CPU::_jumpgt()
{
	// X = Instruction
	// X+1 = Compare Address 1
	// X+2 = Compare Address 2
	// X+3 = Conditional Address

	//Get address to compare
	int cmp1 = this->ram.memory[this->registers.pc + 1];
	int cmp2 = this->ram.memory[this->registers.pc + 2];

	//Get the condidtional jump address
	int jump = this->ram.memory[this->registers.pc + 3];

	//Out of bounds checking
	if (jump < 0 || jump > this->ram.size)
	{
		this->registers.pc += this->Assembly.jumpgt.size;
		return;
	}

	//If cmp1 is greater than cmp2, set the program counter to the value at the third arg
	if (this->ram.memory[cmp1] > this->ram.memory[cmp2])
	{
		this->registers.pc = jump;
		return;
	}

	//Increment by 4 Bytes if check fails
	//4 Byte Instruction
	this->registers.pc += this->Assembly.jumpgt.size;
}

void CPU::_jumplt()
{
	// X = Instruction
	// X+1 = Compare Address 1
	// X+2 = Compare Address 2
	// X+3 = Conditional Address

	//Get address to compare
	int cmp1 = this->ram.memory[this->registers.pc + 1];
	int cmp2 = this->ram.memory[this->registers.pc + 2];

	//Get the condidtional jump address
	int jump = this->ram.memory[this->registers.pc + 3];

	if (jump < 0 || jump > this->ram.size)
	{
		this->registers.pc += this->Assembly.jumplt.size;
		return;
	}

	//If cmp1 is less than cmp2, set the program counter to the value at the third arg
	if (this->ram.memory[cmp1] < this->ram.memory[cmp2])
	{
		this->registers.pc = jump;
		return;
	}

	//Increment by 4 Bytes if check fails
	//4 Byte Instruction
	this->registers.pc += this->Assembly.jumplt.size;
}

void CPU::_move()
{
	// X = Instruction
	// X+1 = Source Addr
	// X+2 = Dest Addr

	//Grab the src addr containing the data
	int src = this->ram.memory[this->registers.pc + 1];
	//Grab the dest addr of where to store the data
	int dest = this->ram.memory[this->registers.pc + 2];	

	//Check if the dest is out of bounds
	if (dest < 0 || dest > this->ram.size)
	{
		this->registers.pc += this->Assembly.move.size;
		return;
	}

	//Read the value of the src addr and write it to the dest addr
	this->ram.memory[dest] = this->ram.memory[src];

	//3 Byte Instruction
	this->registers.pc += this->Assembly.move.size;
}	