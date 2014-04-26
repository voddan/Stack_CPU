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

int main() {
	print_test_name("file test.cpp from Stack_CPU for testing");
	
	test_Command();
	
	test_Command_compile();
	
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

	ofstream output("test.out");
	list.compile(output);
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
