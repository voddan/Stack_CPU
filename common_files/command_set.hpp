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

using namespace std;
using namespace utils;
using namespace command;

namespace command_set { // Commands with NO arguments
	
class ADD : public Com_Non{
	public:
		ADD(Reg reg, Reg reg_1, Reg reg_2) : Com_Non("add", _code, reg, reg_1, reg_2) {}
		virtual ~ADD() {}
		
		//~ static void execute(Reg reg, Reg reg_1, Reg reg_2) {
			//~ *reg.reg() = *reg_1.reg() + *reg_2.reg();
		//~ }
		static void execute_s(Reg reg, Reg reg_1, Reg reg_2) {
			ADD obj(reg, reg_1, reg_2);
			obj.execute(reg, reg_1, reg_2);
		}
		
		void execute(Reg reg, Reg reg_1, Reg reg_2) {
			*reg.reg() = *reg_1.reg() + *reg_2.reg();
		}
		
		// how to inherit it?
		//~ static pair<Code, execute_func_t> execute_indexed() {
			//~ return pair<Code, execute_func_t> (Code(_code), ADD::execute);
		//~ }
		static pair<Code, execute_func_t> execute_indexed() {
			return pair<Code, execute_func_t> (Code(_code), ADD::execute_s);
		}
		
	private:
		static const int _code = 1;
};		

class MOV : public Com_Non{
	public:
		MOV(Reg reg, Reg reg_1) : Com_Non("mov", _code, reg, reg_1, Reg(0)) {}
		virtual ~MOV() {}
		
		static void execute(Reg reg, Reg reg_1, Reg reg_2) {
			*reg.reg() = *reg_1.reg();
		}
		
		// how to inherit it?
		static pair<Code, execute_func_t> execute_indexed() {
			return pair<Code, execute_func_t> (Code(_code), MOV::execute);
		}
		
	private:
		static const int _code = 2;
};		

}
////////////////////////////////////////////////////////////////////////

namespace command_set { // Commands with ARGuments
	
class SET : public Com_Arg{
	public:
		SET(Reg reg, int arg) : Com_Arg("set", _code, reg, arg) {}
		virtual ~SET() {}
		
		static void execute(Reg reg, int arg) {
			debug( "#! SET::execute " );
			debug( "#!" << reg << " | " << reg.reg() );
			debug( "#!" << hex << arg );
			*reg.reg() = arg;
		}
		
		// how to inherit it?
		static pair<Code, execute_func_t> execute_indexed() {
			return pair<Code, execute_func_t> (Code(_code), SET::execute);
		}
		
	private:
		static const int _code = 3;
};		

}
////////////////////////////////////////////////////////////////////////

#endif // _COMMAND_SET_HPP_
