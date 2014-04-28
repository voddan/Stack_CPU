/* test.cpp
 * 
 * for testing compiler.cpp
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


//----------------------------------------------------------------------
void print_test_name(string name){
	cout << std::endl;
	cout << "#!---------------\n";
	cout << "#!--" << name << "--\n";
	cout << std::endl;
}

void test_Command();
void test_Command_compile();
void test_compiler_to_bytecode();

int main() {
	print_test_name("file test.cpp from Stack_CPU for testing");
	
	test_Command();
	
	test_Command_compile();
	
	test_compiler_to_bytecode();
	
	return 0;
}


void test_Command() {
	print_test_name("test_Command");
	using namespace command;
	using namespace command_set;
	
	cout << ADD(Reg(1), Reg(2), Reg(3)) << "\n";
	
	Command_list lst;
	lst << new MOV(Reg(2), Reg(3));
	cout <<  lst;
	
	list<Command*> L2;
	L2 << new SET(Reg(1), (255));
	
	cout << L2;
	delete (L2.front());
}

void test_Command_compile() {
	print_test_name("test_Command_compile: writing to test.out");
	using namespace command;
	using namespace command_set;
	
	Command_list list;
	list << new ADD(Reg(1), Reg(2), Reg(3));
	list << new MOV(Reg(2), Reg(3));
	list << new SET(Reg(1), (255));
	list << new MOV(Reg(3), Reg(1));
	cout << list;

	ofstream output("test_Command_compile.out");
	list.to_bytecode(output);
}

void test_command_Reg_registers() {
	print_test_name("test_command_Reg_registers");
	using namespace command;
	using namespace command_set;
	using namespace linker;

	int regs[8] = {};
	Linker::load_registers(regs);
	 
	*Linker::set_reg(Reg(0)) =  45;
	*Linker::set_reg(Reg(2)) =  3;
	*Linker::set_reg(Reg(1)) =  89;
	
	Linker::dump_registers_val(cout);
	Linker::dump_registers(cout);
	
	Com_Non::execute_func_t func1 = ADD::execute;
	func1(Reg(0), Reg(1), Reg(2));
	
	Linker::dump_registers_val(cout);
	
	Com_Arg::execute_func_t func2 = SET::execute;
	func2(Reg(0), 239);
	
	Linker::dump_registers_val(cout); 
}

void test_compiler_to_bytecode() {
	print_test_name("test_compiler_to_bytecode");
	
	using namespace std;
	using namespace utils;
	using namespace command;
	using namespace command_set;
	
	Command_list list;
	// 0
	list << new SET(Reg(0), 64);
	list << new SET(Reg(1), 128);
	list << new SET(Reg(2), 255);
	list << new SET(Reg(3), 512);
	list << new SET(Reg(4), 1024);
	// 30
	
	list << new JMP(46);
	// 36
	
	list << new ADD(Reg(6), Reg(0), Reg(6));
	list << new ADD(Reg(6), Reg(1), Reg(6));
	list << new ADD(Reg(6), Reg(2), Reg(6));
	list << new ADD(Reg(6), Reg(3), Reg(6));
	list << new ADD(Reg(6), Reg(4), Reg(6));
	// 46
	
	list << new MOV(Reg(7), Reg(6));
	// 48
	
	list << new RET();
	// 50
	/////////////
	cout << list;

	ofstream output("test_compiler_to_bytecode.out");
	list.to_bytecode(output);
}
