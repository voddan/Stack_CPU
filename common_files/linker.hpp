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
	
	static int get_reg(Reg reg);
	static int* set_reg(Reg reg);
	
	static void run_command_arg(Code code, Reg reg, int arg);
	static void run_command_reg(Code code, Reg reg, Reg reg_1, Reg reg_2);
	
	static void reset_ip_register();
	static bool has_instruction();
	
	static void set_ret_register(unsigned pos);
	
	static wchar_t read_head();
	static int read_arg();
	//---------------------------
	static void dump_registers(ostream& stream);
	static void dump_registers_val(ostream& stream);
	
	// TODO: dump stacks
	static void dump_commands_arg	(ostream& stream);
	static void dump_commands_reg	(ostream& stream);
	
	static void dump_instructions	(ostream& stream);
	
	//---------------------------
	//---------------------------
	
	static void load_ip_register(unsigned* reg);
	
	static void load_registers(int arr[REG_SIZE]);
	
	static void add_commands_arg(pair<Code, Com_Arg::execute_func_t>);
	static void add_commands_reg(pair<Code, Com_Non::execute_func_t>);
	
	static bool load_instructions(ifstream& stream);
	
	//---------------------------
	// TODO: operations with stacks
	// TODO: operations special registers
	nondebug(private:)
		static int* _registers[REG_SIZE];
		
		static Com_Arg::execute_func_t commands_arg[CODE_SIZE];
		static Com_Non::execute_func_t commands_reg[CODE_SIZE];
		
		static unsigned* ip_register;
		static unsigned* ret_register;
		
		static vector<char> instructions;
};


}
////////////////////////////////////////////////////////////////////////

#endif // _LINKER_HPP_

