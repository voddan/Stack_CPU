#include <BUILD.H>

#include <cstdio>
#include <iostream>

#include <stack_cpu.hpp>
#include <command_set.hpp>
#include <linker.hpp>

using namespace std;

using namespace stack_cpu;
using namespace command_set;
using namespace linker;
//-----------------------------------------------------

Stack_CPU cpu;

//-----------------------------------------------------
extern "C"
void init() {
	printf("init.. \n");
	//~ Linker::load_ip_register (&(cpu.ip_reg ));
	//~ Linker::load_ret_register(&(cpu.ret_reg));

	Linker::load_registers(cpu.regs);
	
	Linker::add_commands_arg(SET::execute_indexed());
	Linker::add_commands_arg(JMP::execute_indexed());
	
	Linker::add_commands_reg(ADD::execute_indexed());
	Linker::add_commands_reg(MOV::execute_indexed());
	Linker::add_commands_reg(RET::execute_indexed());
	
	//~ Linker::set_ip_register(0);
	//~ Linker::set_ret_register(Linker::end_instruction());
}

extern "C"
void run_command_arg(int code, int reg, int arg) {
	debug("run_command_arg " << code << " " << reg << " " << arg);
	assert(0 <= code && code < CODE_SIZE);
	assert(0 <= reg && reg < REG_SIZE);
	Linker::run_command_arg(Code(code), Reg(reg), arg);
}

extern "C"
void run_command_reg(int code, int reg, int reg_1, int reg_2) {
	debug("run_command_arg " << code << " " << reg << " " << reg_1 << " " << reg_2);
	assert(0 <= code && code < CODE_SIZE);
	assert(0 <= reg && reg < REG_SIZE);
	assert(0 <= reg_1 && reg_1 < REG_SIZE);
	assert(0 <= reg_2 && reg_2 < REG_SIZE);
	Linker::run_command_reg(Code(code), Reg(reg), Reg(reg_1), Reg(reg_2));
}

extern "C"
void dump_registers_val() {
	Linker::dump_registers_val(cout);
}


