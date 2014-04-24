/* stack_cpu.cpp
 * 
 * !!! OUT OF USE !!!
 * 
 * Classes for imulating my stack_cpu
 * 
 */
 
#ifndef _STACK_CPU_CPP_
#define _STACK_CPU_CPP_

#include <stack>
#include <vector>
#include <cstring>
#include <fstream>

#include <consts.hpp>
#include <command.hpp>

using namespace std;
using namespace command;

namespace stack_spu {
	
Instruct::Instruct(wchar_t arr) {
	assert(CODE_SIZE == 64);
	assert(REG_SIZE  == 8);
	
	// swaps for big-small endian
	arr = ((arr << 8) & 0xff00) | ((arr >> 8) & 0x00ff);
	
	_has_arg = bytes((arr >> (7 + 8)), 1) == 1;
	
	_code = Code( bytes((arr >> (1 + 8)), CODE_SIZE) );
	
	_r1 = Reg(bytes((arr >> 6), REG_SIZE));
	_r1 = Reg(bytes((arr >> 3), REG_SIZE));
	_r1 = Reg(bytes((arr >> 0), REG_SIZE));
	
	
};

/*
bool Stack_CPU::load_instruct(ifstream& stream) {
	wchar_t com;
	int arg;
	
	stream.read((char*) &com, 2);
	
	return true;
} // */
	
}
//////////////////////////////////////////////////////////////////////// 


#endif // _STACK_CPU_HPP_
