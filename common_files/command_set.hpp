/* command_set.hpp
 * 
 * 
 * the set of commands
 * */
 
#ifndef _COMMAND_SET_HPP_
#define _COMMAND_SET_HPP_
 
#include <string>
#include <sstream>
#include <iostream>

#include <assert.h>

#include <utils.hpp>
#include <command.hpp>
#include <linker.hpp>

using namespace std;
using namespace utils;
using namespace command;
using namespace linker;

namespace command_set { // Commands for REGisters
	
struct ADD : public Com_Non{
	ADD(Reg reg, Reg reg_1, Reg reg_2) : Com_Non("add", _code, reg, reg_1, reg_2) {}
	
	static void execute(Reg reg, Reg reg_1, Reg reg_2) {
		debug("#! ADD::execute");
		*(Linker::set_reg(reg)) = Linker::get_reg(reg_1) + Linker::get_reg(reg_2);
	}
	
	static pair<Code, execute_func_t> execute_indexed() {
		return pair<Code, execute_func_t> (_code, ADD::execute);
	}
	private: static const Code _code;
};	
const Code ADD::_code(1);	

struct MOV : public Com_Non{
	MOV(Reg reg, Reg reg_1) : Com_Non("mov", _code, reg, reg_1, Reg(0)) {}
	
	static void execute(Reg reg, Reg reg_1, Reg reg_2) {
		debug("#! MOV::execute");
		*(Linker::set_reg(reg)) = Linker::get_reg(reg_1);
	}
	
	static pair<Code, execute_func_t> execute_indexed() {
		return pair<Code, execute_func_t> (_code, MOV::execute);
	}
	private: static const Code _code;
};
const Code MOV::_code(2);	
	
struct RET : public Com_Non{
	RET() : Com_Non("ret", _code, Reg(0), Reg(0), Reg(0)) {}
	
	static void execute(Reg reg, Reg reg_1, Reg reg_2) {
		debug("#! RET::execute");
		debug("return");
		Linker::set_ip_register( Linker::get_ret_register() );
		// should be unsaving of registers
	}
	
	static pair<Code, execute_func_t> execute_indexed() {
		return pair<Code, execute_func_t> (_code, RET::execute);
	}
	private: static const Code _code;
};
const Code RET::_code(63);		

}
////////////////////////////////////////////////////////////////////////

namespace command_set { // Commands with ARGuments
	
struct SET : public Com_Arg{
	SET(Reg reg, int arg) : Com_Arg("set", _code, reg, arg) {}
	
	static void execute(Reg reg, int arg) {
		debug( "#! SET::execute " );
		debug( "#!" << reg << " | " << Linker::get_reg(reg) << " | " << Linker::set_reg(reg) );
		debug( "#!" << hex << arg << dec);
		*(Linker::set_reg(reg)) = arg;
	}
	
	static pair<Code, execute_func_t> execute_indexed() {
		return pair<Code, execute_func_t> (_code, SET::execute);
	}
	private: static const Code _code;
};
const Code SET::_code(3);		

}
////////////////////////////////////////////////////////////////////////

#endif // _COMMAND_SET_HPP_
