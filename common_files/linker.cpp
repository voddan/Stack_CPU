/* linker.cpp
 * 
 * Implementation for linker.hpp
 * */
 
#include <string>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <iomanip>

#include <assert.h>

#include <utils.hpp>
#include <consts.hpp>
#include <command.hpp>

#include <linker.hpp>

using namespace std;
using namespace utils;

namespace linker { // DATA

int* Linker::_registers[] = {};

Com_Arg::execute_func_t Linker::commands_arg[CODE_SIZE] = {};
Com_Non::execute_func_t Linker::commands_non[CODE_SIZE] = {};

}
////////////////////////////////////////////////////////////////////////

namespace linker { // Stack_CPU::
	
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

void Linker::add_commands_non(pair<Code, Com_Non::execute_func_t> p) {
	Linker::commands_non[p.first.val] = p.second;
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
}
	
void Linker::dump_commands_arg(ostream& stream) {
	stream << "#! dump of Linker.commands_arg\n";
	assert(stream == cout);
	for (int i = 0; i < CODE_SIZE; i++) {
		stream << "#! [" << setw(3) << i << "] ";
		printf("%p\n", commands_arg[i]);
	}
}
	
void Linker::dump_commands_non(ostream& stream) {
	stream << "#! dump of Linker.commands_non\n";
	assert(stream == cout);
	for (int i = 0; i < CODE_SIZE; i++) {
		stream << "#! [" << setw(3) << i << "] ";
		printf("%p\n", commands_non[i]);
	}
}
	
	
	
}
////////////////////////////////////////////////////////////////////////
