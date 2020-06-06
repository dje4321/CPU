#pragma once
#include <iostream>
#include <string>

enum ASM
{
	null = 0,
	write,
	add,
	sub,
	jump,
	jumpgt,
	jumplt,
	move,
	out,
	pause,
	halt
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
	int _ram_size = 255 * 255;
	int ram[255 * 255]{ 0 };
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
	void _dumpIns(int addr);
};

