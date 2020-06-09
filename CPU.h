#pragma once
#include <iostream>
#include <string>

enum Opcode
{
	null = 0, //CPU::_null()
	R_read,   //CPU::R_read()
	write,    //CPU::_write()
	R_write,  //CPU::R_write()
	add,      //CPU::_add()
	R_add,    //CPU::R_add()
	subtract, //CPU::_sub()
	jump,     //CPU::_jump()
	jumpgt,   //CPU::_jumpgt()
	jumplt,   //CPU::_jumplt()
	move,     //CPU::_move()
	out,      //CPU::_out()
	pause,    //CPU::_pause()
	halt      //CPU::_halt()
};

struct Instruction
{
	int opcode;
	int size;
	void (*funcPtr)();
};

struct ASM
{
	Instruction null;
	Instruction R_read;
	Instruction write;
	Instruction R_write;
	Instruction add;
	Instruction R_add;
	Instruction subtract;
	Instruction jump;
	Instruction jumpgt;
	Instruction jumplt;
	Instruction move;
	Instruction out;
	Instruction pause;
	Instruction halt;
};

struct Ram
{
	int size = 255 * 255;
	int memory[255 * 255]{ 0 };
};

struct Var
{
	int loc[255]{ 0 };
	int size = 255;
};

struct Registers
{
	bool halt = false;
	int pc = 0;
	Var var;
};

class CPU
{
public:
	CPU();
	~CPU();
	void run();
	void step();
	void print(int addr);
	void write(int arg1, int arg2);

private:
	Registers registers;
	Ram ram;
	ASM Assembly;

private:
	void _decode();
	void _null();
	void R_read();
	void _write();
	void R_write();
	void _add();
	void R_add();
	void _sub();
	void _jump();
	void _jumpgt();
	void _jumplt();
	void _move();
	void _out();
	void _pause();
	void _halt();
	void _dumpIns(int addr);
};

