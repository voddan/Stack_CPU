/* linker.cpp
 * 
 * Implementation for linker.hpp
 * */
#include <BUILD.H>
 
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <iomanip>

#include <assert.h>

#include <utils.hpp>
#include <command.hpp>

#include <linker.hpp>

using namespace std;
using namespace utils;

namespace linker { // API
	
int Linker::get_reg(Reg reg) {
	assert(Linker::_registers[reg.val]);
	return *Linker::_registers[reg.val];
}

int* Linker::set_reg(Reg reg) {
	assert(Linker::_registers[reg.val]);
	return Linker::_registers[reg.val];
}

void Linker::set_ip_register(unsigned pos) {
	debug("set ip register" << pos << endl);
	assert(Linker::ip_register);
	*(Linker::ip_register) = pos;
}

unsigned Linker::get_ip_register() {
	debug("get ip register" << *(Linker::ip_register) << endl);
	assert(Linker::ip_register);
	return *(Linker::ip_register);
}

void Linker::set_ret_register(unsigned pos) {
	debug("set ret register" << pos << endl);
	assert(Linker::ret_register);
	*(Linker::ret_register) = pos;
}

unsigned Linker::get_ret_register() {
	debug("get ip register" << *(Linker::ret_register) << endl);
	assert(Linker::ret_register);
	return *(Linker::ret_register);
}
//----------------------
bool Linker::has_instruction() {
	return instructions.size() > (*ip_register);
}

unsigned Linker::end_instruction() {
	return instructions.size();
}
//---------------------------
void Linker::run_command_arg(Code code, Reg reg, int arg) {
	debug("Linker::run_command_arg");
	assert((Linker::commands_arg[code.val]) && "unsupported command");
	Linker::commands_arg[code.val](reg, arg);
}
void Linker::run_command_reg(Code code, Reg reg, Reg reg_1, Reg reg_2) {
	debug("Linker::run_command_reg");
	assert((Linker::commands_reg[code.val]) && "unsupported command");
	Linker::commands_reg[code.val](reg, reg_1, reg_2);
}
//-------------------------------
void Linker::run_assembly_arg(ostream& stream, Code code, Reg reg, int arg) {
	assert((Linker::assembly_arg[code.val]) && "unsupported command");
	Linker::assembly_arg[code.val](stream, reg, arg);
}
void Linker::run_assembly_reg(ostream& stream, Code code, Reg reg, Reg reg_1, Reg reg_2) {
	assert((Linker::assembly_reg[code.val]) && "unsupported command");
	Linker::assembly_reg[code.val](stream, reg, reg_1, reg_2);
}
//-------------------------------
wchar_t Linker::read_head() {
	wchar_t result  = 0;
	
	result  = (instructions[(*ip_register) ++] & 0xff);
	result |= (instructions[(*ip_register) ++] & 0xff) << 8;
	
	return result;
}

int Linker::read_arg() {
	int result = 0;
	
	result  = (instructions[(*ip_register) ++] & 0xff);
	result |= (instructions[(*ip_register) ++] & 0xff) <<  8;
	result |= (instructions[(*ip_register) ++] & 0xff) << (8 * 2);
	result |= (instructions[(*ip_register) ++] & 0xff) << (8 * 3);
	
	return result;
}

}
////////////////////////////////////////////////////////////////////////

namespace linker { // DATA

int* Linker::_registers[] = {};

Com_Arg::execute_func_t Linker::commands_arg[CODE_SIZE] = {};
Com_Non::execute_func_t Linker::commands_reg[CODE_SIZE] = {};

Com_Arg::assembly_func_t Linker::assembly_arg[CODE_SIZE] = {};
Com_Non::assembly_func_t Linker::assembly_reg[CODE_SIZE] = {};

vector<char> Linker::instructions;

unsigned* Linker::ip_register;
unsigned* Linker::ret_register;

}
////////////////////////////////////////////////////////////////////////

namespace linker { // loading
	
void Linker::load_ip_register(unsigned* reg) {
	ip_register = reg;
}

void Linker::load_ret_register(unsigned* reg) {
	ret_register = reg;
}
	
void Linker::load_registers(int arr[REG_SIZE]) {
	for(int i = 0; i < REG_SIZE; i++) {
		  _registers[i] = (arr + i);
		*(_registers[i]) = 0;
	}
}

bool Linker::load_instructions(ifstream& stream) {
	char ch = 0;
	
	while( stream.read(&ch , 1) )
		instructions.push_back(ch);
		
	return true;
}

void Linker::add_commands_arg(pair<Code, Com_Arg::execute_func_t> p) {
	Linker::commands_arg[p.first.val] = p.second;
}

void Linker::add_commands_reg(pair<Code, Com_Non::execute_func_t> p) {
	Linker::commands_reg[p.first.val] = p.second;
}

void Linker::add_assembly_arg(pair<Code, Com_Arg::assembly_func_t> p) {
	Linker::assembly_arg[p.first.val] = p.second;
}

void Linker::add_assembly_reg(pair<Code, Com_Non::assembly_func_t> p) {
	Linker::assembly_reg[p.first.val] = p.second;
}

}
////////////////////////////////////////////////////////////////////////

namespace linker { // dump_...
	
void Linker::dump_registers_val(ostream& stream) {
	stream << "#! dump of Linker::registers (values)" << endl;
	for(int i = 0; i < REG_SIZE; i++) {
		stream << "#! " << *(_registers[i]) << endl;
	}
}

void Linker::dump_registers(ostream& stream) {
	stream << "#! dump of Linker::registers (pointers)" << endl;
	for(int i = 0; i < REG_SIZE; i++) {
		stream << "#! " << _registers[i] << endl;
	}
}
	
void Linker::dump_instructions(ostream& stream) {
	debug("#! dump_instructions");
	
	const char names[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f' 
	};
	long count = 0;
	
	for( vector<char>::const_iterator iter = instructions.begin();
			iter != instructions.end(); iter++) {
		stream << names[(*iter >> 4) & 0x0f];
		stream << names[*iter & 0x0f];
		stream << " ";
		
		count++;
		if(count % 16 == 0) stream << "\n";
	}
	stream << endl;
	debug("#! dump_instructions finished");
}
	
void Linker::dump_commands_arg(ostream& stream) {
	stream << "#! dump of Linker.commands_arg\n";
	assert(stream == cout);
	for (int i = 0; i < CODE_SIZE; i++) {
		stream << "#! [" << setw(3) << i << "] ";
		//printf("%p\n", commands_arg[i]);
		stream << (void*) commands_arg[i] << endl;
	}
}
	
void Linker::dump_commands_reg(ostream& stream) {
	stream << "#! dump of Linker.commands_reg\n";
	assert(stream == cout);
	for (int i = 0; i < CODE_SIZE; i++) {
		stream << "#! [" << setw(3) << i << "] ";
		//printf("%p\n", commands_reg[i]);
		stream << (void*) assembly_reg[i] << endl;
	}
}
	
void Linker::dump_assembly_arg(ostream& stream) {
	stream << "#! dump of Linker.assembly_arg\n";
	assert(stream == cout);
	for (int i = 0; i < CODE_SIZE; i++) {
		stream << "#! [" << setw(3) << i << "] ";
		//printf("%p\n", assembly_arg[i]);
		stream << (void*) assembly_arg[i] << endl;
	}
}
	
void Linker::dump_assembly_reg(ostream& stream) {
	stream << "#! dump of Linker.assembly_reg\n";
	assert(stream == cout);
	for (int i = 0; i < CODE_SIZE; i++) {
		stream << "#! [" << setw(3) << i << "] ";
		//printf("%p\n", assembly_reg[i]);
		stream << (void*) assembly_reg[i] << endl;
	}
}
	
	
	
}
////////////////////////////////////////////////////////////////////////
