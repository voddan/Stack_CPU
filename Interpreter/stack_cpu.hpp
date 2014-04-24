/* stack_cpu.hpp
 * 
 * Classes for imulating my stack_cpu
 * 
 */
 
#ifndef _STACK_CPU_HPP_
#define _STACK_CPU_HPP_

#include <stack>
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>

#include <consts.hpp>
#include <command.hpp>

using namespace std;
using namespace command;

namespace stack_cpu {
	
struct Instruct {
	Instruct(bool has_arg, Code code, Reg r1, Reg r2, Reg r3)
		: _has_arg(has_arg), _code(code.val), _r1(r1.val), _r2(r2.val), _r3(r3.val) {}
	
	/*	
	Instruct(bool has_arg, Code code, Reg r1, Reg r2, Reg r3) { 
		_has_arg = has_arg;
		_code    = code.val;
		_r1      = r1.val;
		_r2      = r2.val;
		_r3      = r3.val;
	} // */
		
	//~ Instruct() : _has_arg(false), _code(0), _r1(0), _r2(0), _r3(0) {}
	//~ Instruct(const Instruct& instr) 
		//~ : _has_arg(instr._has_arg), _code(instr._code.val), 
		//~ _r1(instr._r1.val), _r2(instr._r2.val), _r3(instr._r3.val) {}
		
	//Instruct(wchar_t arr);

	private:
		bool _has_arg;
		Code _code;
		Reg  _r1;
		Reg  _r2;
		Reg  _r3;
};
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
	
	
class Stack_CPU {
	public:
		Stack_CPU(): ip_reg(0), ret_reg(0) {
			memset(regs, 0, REG_SIZE*sizeof(int)); 
			instruct.reserve(100);
		}
		
		//------------------
		bool load_instruct(ifstream& stream);
		void run_instruct();
		
		void dump_instruct(ostream& stream) {
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
		
		void dump_regs(ostream& stream);
		void dump_user_stack(ostream& stream);
		void dump_prog_stack(ostream& stream);
	private:
		const stack<int> user_stack;
		const stack<int> prog_stack;
		
		int ip_reg;
		int ret_reg;
		
		int regs[REG_SIZE];
		
		vector<char> instruct;
};

bool Stack_CPU::load_instruct(ifstream& stream) {
	char ch = 0;
	
	while( stream.read(&ch , 1) )
		instruct.push_back(ch);
		
	return true;
}

void Stack_CPU::run_instruct() {
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
		Code code	= Code( bytes((com >> (1 + 8)), 6) );
		Reg r1 		= Reg(bytes((com >> 6), 3));
		Reg r2 		= Reg(bytes((com >> 3), 3));
		Reg r3 		= Reg(bytes((com >> 0), 3));
		
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


	
}
//////////////////////////////////////////////////////////////////////// 


#endif // _STACK_CPU_HPP_
