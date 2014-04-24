/* stack_cpu.cpp
 * 
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
#include <iostream>


#include <consts.hpp>
#include <command.hpp>

#include <stack_cpu.hpp>
#include "stack_cpu.hpp"

using namespace std;
using namespace command;

namespace stack_cpu { // constructors for Instruct
/*
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
	
	
} // */

}
////////////////////////////////////////////////////////////////////////

namespace stack_cpu { // head_unpack
	
Instruct head_unpack(wchar_t arr) {
	assert(CODE_SIZE == 64);
	assert(REG_SIZE  == 8);
	
	// swaps for big-small endian
	arr = ((arr << 8) & 0xff00) | ((arr >> 8) & 0x00ff);
	
	bool has_arg = bytes((arr >> (7 + 8)), 1) == 1;
	
	Code code = Code( bytes((arr >> (1 + 8)), 6) );
	
	Reg r1 = Reg(bytes((arr >> 6), 3));
	Reg r2 = Reg(bytes((arr >> 3), 3));
	Reg r3 = Reg(bytes((arr >> 0), 3));
	
	//~ Instruct result;
	//~ result._has_arg = has_arg;
	//~ result._code = code;
	//~ result._r1 = r1;
	//~ result._r2 = r2;
	//~ result._r3 = r3;
	
	//~ return result;
	
	return Instruct(has_arg, code, r1, r2, r3);
}

}
////////////////////////////////////////////////////////////////////////	
	
namespace stack_cpu { // Stack_CPU::
	
Com_Arg::execute_func_t Stack_CPU::commands_arg[CODE_SIZE] = {};
Com_Non::execute_func_t Stack_CPU::commands_non[CODE_SIZE] = {};
		
void Stack_CPU::dump_instruct(ostream& stream) {
	const char names[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f' 
	};
	long count = 0;
	
	for( vector<char>::const_iterator iter = instruct.begin();
			iter != instruct.end(); iter++) {
		stream << names[(*iter >> 4) & 0x0f];
		stream << names[*iter & 0x0f];
		stream << " ";
		
		count++;
		if(count % 16 == 0) stream << "\n";
	}
}
		
bool Stack_CPU::load_instruct(ifstream& stream) {
	char ch = 0;
	
	while( stream.read(&ch , 1) )
		instruct.push_back(ch);
		
	return true;
}

void Stack_CPU::run_one_instruct() {
	vector<char>::const_iterator iter = instruct.begin();
	
	wchar_t com;
	int arg;

	while( iter != instruct.end() ) {
		//stream.read((char*) &com, 2);
		com  = 0;
		com  = *(iter ++);
		com |= *(iter ++) << 8;
		
		com = ((com << 8) & 0xff00) | ((com >> 8) & 0x00ff);
		bool has_arg 	= bytes((com >> (7 + 8)), 1) == 1;
		//~ Code code	= Code( bytes((com >> (1 + 8)), 6) );
		//~ Reg r1 		= Reg(bytes((com >> 6), 3));
		//~ Reg r2 		= Reg(bytes((com >> 3), 3));
		//~ Reg r3 		= Reg(bytes((com >> 0), 3));
		
		if( has_arg ) {
			//stream.read((char*) &arg, 4);
			arg  = 0;
			arg |= *(iter ++);
			arg |= *(iter ++) <<  8;
			arg  = *(iter ++) << (8 * 2);
			arg |= *(iter ++) << (8 * 3);
		}
	}
	
}
	
void Stack_CPU::add_commands_arg(pair<Code, Com_Arg::execute_func_t> p) {
	Stack_CPU::commands_arg[p.first.val] = p.second;
}

void Stack_CPU::add_commands_non(pair<Code, Com_Non::execute_func_t> p) {
	Stack_CPU::commands_non[p.first.val] = p.second;
}

}
//////////////////////////////////////////////////////////////////////// 


#endif // _STACK_CPU_CPP_
