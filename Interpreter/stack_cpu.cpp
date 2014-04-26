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
#include <iomanip>


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
/*	
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
} // */

Instruct head_unpack(wchar_t arr) {
	assert(CODE_SIZE == 64);
	assert(REG_SIZE  == 8);
	
	debug( "#! head_unpack \n");
	debug( hex << arr);
	
	// swaps for big-small endian
	arr = ((arr << 8) & 0xff00) | ((arr >> 8) & 0x00ff);
	
	int has_arg = (arr >> (7 + 8)) & 0x1;
	
	int code = (arr >> (1 + 8)) & (CODE_SIZE - 1);
	
	int r1 = (arr >> 6) & (REG_SIZE- 1);
	int r2 = (arr >> 3) & (REG_SIZE- 1);
	int r3 = (arr >> 0) & (REG_SIZE- 1);
	
	debug( hex << arr );
	debug( has_arg );
	debug( code );
	debug( r1 );
	debug( r2 );
	debug( r3 );
	
	return Instruct(!(has_arg == 0), Code(code), Reg(r1), Reg(r2), Reg(r3));
} // */

}
////////////////////////////////////////////////////////////////////////	
	
namespace stack_cpu { // Stack_CPU::
	
//~ Com_Arg::execute_func_t Stack_CPU::commands_arg[CODE_SIZE] = {};
//~ Com_Non::execute_func_t Stack_CPU::commands_reg[CODE_SIZE] = {};
		
//~ void Stack_CPU::dump_instructions(ostream& stream) {
	//~ const char names[16] = {
		//~ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		//~ 'a', 'b', 'c', 'd', 'e', 'f' 
	//~ };
	//~ long count = 0;
	//~ 
	//~ for( vector<char>::const_iterator iter = instructions.begin();
			//~ iter != instructions.end(); iter++) {
		//~ stream << names[(*iter >> 4) & 0x0f];
		//~ stream << names[*iter & 0x0f];
		//~ stream << " ";
		//~ 
		//~ count++;
		//~ if(count % 16 == 0) stream << "\n";
	//~ }
//~ }

// may be
//~ void Stack_CPU::dump_regs(ostream& stream) {
	//~ stream << "#! dump of Stack_CPU registers" << endl;
	//~ for(int i = 0; i < REG_SIZE; i++) {
		//~ Reg reg = Reg(i);
		//~ 
		//~ stream << "#! register" << reg << ": ";
		//~ stream << regs[i];
		//~ stream << endl;
	//~ }
//~ }
		
//~ bool Stack_CPU::load_instructions(ifstream& stream) {
	//~ char ch = 0;
	//~ 
	//~ while( stream.read(&ch , 1) )
		//~ instructions.push_back(ch);
		//~ 
	//~ return true;
//~ }


void Stack_CPU::run_instructions() {
	Linker::reset_ip_register();
	
	while( Linker::has_instruction() ) {
		wchar_t head = Linker::read_head();
		
		debug( "#! run_instructions" );
		debug( hex << head << dec );
		
		// unnecessary packing-unpacking into Instruct
		Instruct instruct = head_unpack(head);
		
		bool has_arg = instruct.has_arg();
		Code    code = instruct.code();
		Reg       r1 = instruct.r1();
		Reg       r2 = instruct.r2();
		Reg       r3 = instruct.r3();
		
		if( !has_arg ) {
			debug( "#! no arguments\n" );
			Linker::run_command_reg(code, r1, r2, r3);
		} else {
			debug( "#! has an argument\n" );
			int arg = Linker::read_arg();
			Linker::run_command_arg(code, r1, arg);
		}
	}
	
}

/*
void Stack_CPU::run_instructions() {
	//vector<char>::const_iterator iter = Linker::instructions.begin();
	
	while( iter != instructions.end() ) {
		wchar_t com;
		
		//stream.read((char*) &com, 2);
		com  = 0;
		com  = *(iter ++) & 0xff;
		com |= *(iter ++) << 8;
		
		debug( "#! run_instructions" );
		debug( hex );
		debug( (int) *(iter - 2) << " " << (int) *(iter - 1) );
		debug( com );
		
		Instruct instruct = head_unpack(com);
	
		bool has_arg = instruct.has_arg();
		Code    code = instruct.code();
		Reg       r1 = instruct.r1();
		Reg       r2 = instruct.r2();
		Reg       r3 = instruct.r3();
		
		if( !has_arg ) {
			debug( "#! no arguments\n" );
			Stack_CPU::commands_reg[code.val](r1, r2, r3);
		} else {
			debug( "#! has an argument\n" );
			int arg;
			
			//stream.read((char*) &arg, 4);
			arg  = 0;
			arg |= (*(iter ++) & 0xff);
			arg |= (*(iter ++) & 0xff) <<  8;
			arg |= (*(iter ++) & 0xff) << (8 * 2);
			arg |= (*(iter ++) & 0xff) << (8 * 3);
			
			Stack_CPU::commands_arg[code.val](r1, arg);
		}
	}
	
}*/
	
//~ void Stack_CPU::add_commands_arg(pair<Code, Com_Arg::execute_func_t> p) {
	//~ Stack_CPU::commands_arg[p.first.val] = p.second;
//~ }
//~ 
//~ void Stack_CPU::add_commands_reg(pair<Code, Com_Non::execute_func_t> p) {
	//~ Stack_CPU::commands_reg[p.first.val] = p.second;
//~ }

//~ void Stack_CPU::dump_commands_arg(ostream& stream) {
	//~ stream << "#! dump of Stack_CPU.commands_arg\n";
	//~ assert(stream == cout);
	//~ for (int i = 0; i < CODE_SIZE; i++) {
		//~ stream << "#! [" << setw(3) << i << "] ";
		//~ printf("%p\n", commands_arg[i]);
	//~ }
//~ }
//~ 
//~ void Stack_CPU::dump_commands_reg(ostream& stream) {
	//~ stream << "#! dump of Stack_CPU.commands_reg\n";
	//~ assert(stream == cout);
	//~ for (int i = 0; i < CODE_SIZE; i++) {
		//~ stream << "#! [" << setw(3) << i << "] ";
		//~ printf("%p\n", commands_reg[i]);
	//~ }
//~ }

}
//////////////////////////////////////////////////////////////////////// 


#endif // _STACK_CPU_CPP_
