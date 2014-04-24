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
	 
	ifstream input("a.out");
	
	Stack_CPU cpu;
	
	cpu.load_instruct(input);
	cpu.dump_instruct(cout);
	
	
	return 0;
}
