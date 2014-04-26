/* linker.hpp
 * 
 * Things, which are needed by Command to work,
 * but may changes because of Stack_CPU
 * */
 
#ifndef _LINKER_HPP_
#define _LINKER_HPP_
 
#include <string>
#include <list>
#include <sstream>

#include <assert.h>

#include <utils.hpp>
#include <consts.hpp>

#include <command.hpp>

using namespace std;
using namespace utils;
using namespace command;

namespace linker {

struct Linker{
	static void dump_registers(ostream& stream);
	static void dump_registers_val(ostream& stream);
	// dump stacks
	void dump_commands_arg	(ostream& stream);
	void dump_commands_non	(ostream& stream);
	
	void dump_instructions	(ostream& stream);
	
	//---------------------------
	
	static void load_registers(int arr[REG_SIZE]);
	
	static void add_commands_arg(pair<Code, Com_Arg::execute_func_t>);
	static void add_commands_non(pair<Code, Com_Non::execute_func_t>);
	
	bool load_instructions(ifstream& stream);
	
	//---------------------------
	// operations with stacks
	// operations special registers
	private:
		static int* _registers[REG_SIZE];
		
		static Com_Arg::execute_func_t commands_arg[CODE_SIZE];
		static Com_Non::execute_func_t commands_non[CODE_SIZE];
		
		static int* ip_register;
		static int* ret_register;
		
		static vector<char> instructions;
};


}
////////////////////////////////////////////////////////////////////////

#endif // _LINKER_HPP_

