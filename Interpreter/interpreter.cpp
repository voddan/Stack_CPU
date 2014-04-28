/* interpreter.cpp
 * 
 * The interpreter of byte-code from the compiler
 * 
 * */
 
#include <string>
#include <list>
#include <iostream>
#include <fstream>

#include <utils.hpp>
#include <command_set.hpp>
#include <command.hpp>

using namespace std;
using namespace utils;

using namespace command;
using namespace command_set;


//----------------------------------------------------------------------
#include <stack_cpu.hpp>

using namespace stack_cpu;

int main() {
	Stack_CPU cpu; 			// main subject of data
	//-------------------------
	Linker::load_ip_register (&(cpu.ip_reg ));
	Linker::load_ret_register(&(cpu.ret_reg));

	//----------
	Linker::add_commands_reg(ADD::execute_indexed());
	Linker::add_commands_reg(MOV::execute_indexed());
	Linker::add_commands_reg(RET::execute_indexed());
	
	Linker::add_commands_arg(SET::execute_indexed());
	Linker::add_commands_arg(JMP::execute_indexed());
	//----------
	
	Linker::load_registers(cpu.regs);
	 
	ifstream input("a.out");
	Linker::load_instructions(input);
	
	//-------------------------
	Linker::dump_instructions(cout);
	cout << endl;
	
	Linker::dump_registers_val(cout);
	cout << endl;
	//-------------------------
	//Linker::dump_commands_arg(cout);
	//Linker::dump_commands_reg(cout);
	//cout << endl;
	
	cpu.run_instructions();
	
	Linker::dump_registers_val(cout);
	cout << endl;
	
	return 0;
}
