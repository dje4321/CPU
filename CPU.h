#pragma once
#include <iostream>
#include <string>

enum ASM
{
	null = 0, //CPU::_null()
	write,    //CPU::_write()
	add,      //CPU::_add()
	sub,      //CPU::_sub()
	jump,     //CPU::_jump()
	jumpgt,   //CPU::_jumpgt()
	jumplt,   //CPU::_jumplt()
	move,     //CPU::_move()
	out,      //CPU::_out()
	pause,    //CPU::_pause()
	halt      //CPU::_halt()
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
	int pc{ 0 };
	bool halt;
	int _ram_size = 255 * 255;
	int ram[255 * 255];
	void _decode();
	void _null();
	void _write();
	void _add();
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

