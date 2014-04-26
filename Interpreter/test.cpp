/* test.cpp
 * 
 * Tests for interpreter.cpp
 * 
 * */
 
#include <string>
#include <list>
#include <iostream>
#include <fstream>

#include <utils.hpp>
#include <command_set.hpp>
#include <command.hpp>

#include <stack_cpu.hpp>
#include <linker.hpp>

using namespace std;
using namespace utils;

using namespace command;
using namespace command_set;

using namespace stack_cpu;
//----------------------------------------------------------------------
void print_test_name(string name){
	cout << std::endl;
	cout << "#!---------------\n";
	cout << "#!--" << name << "--\n";
	cout << std::endl;
}

void test_load_instruct();

int main() {
	
	test_load_instruct();
	
	return 0;
}

void test_load_instruct() {
	print_test_name("test_load_instruct");
	using namespace linker;
	
	ifstream input("a.out");
	
	Linker::load_instructions(input);
	Linker::dump_instructions(cout);
}



