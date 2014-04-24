/* command_set.hpp
 * 
 * 
 * the set of commands
 * */
 
#ifndef _COMMAND_SET_HPP_
#define _COMMAND_SET_HPP_
 
#include <string>
#include <sstream>

#include <assert.h>

#include <utils.hpp>
#include <command.hpp>

using namespace std;
using namespace utils;
using namespace command;

namespace command_set { // Commands with NO arguments
	
class ADD : public Com_Non{
	public:
		ADD(Reg reg, Reg reg_1, Reg reg_2) : Com_Non("add", 1, reg, reg_1, reg_2) {}
		virtual ~ADD() {}
		
		//*
		static void execute(Reg reg, Reg reg_1, Reg reg_2) {
			*reg.reg() = *reg_1.reg() + *reg_2.reg();
			// *reg().reg() = *reg_1().reg() + *reg_2().reg();
			// *reg = *reg_1 + *reg_2;
		} // */
		
		/*
		static void execute(int* reg, int* reg_1, int* reg_2) {
			*reg = *reg_1 + *reg_2;
		} // */
		
		/*
		pair<Code, execute_func_t*> execute_indexed() {
			pair<Code, execute_func_t*> result(this->code(), &execute);
			//return pair(code());
			return result;
		} // */
};		

class MOV : public Com_Non{
	public:
		MOV(Reg reg, Reg reg_1) : Com_Non("mov", 2, reg, reg_1, Reg(0)) {}
		virtual ~MOV() {}
		
		//*
		static void execute(Reg reg, Reg reg_1, Reg reg_2) {
			*reg.reg() = *reg_1.reg();
			// *reg = *reg_1;
		} // */
		
		/*
		static void execute(int* reg, int* reg_1, int* reg_2) {
			*reg = *reg_1;
		}// */
};		

}
////////////////////////////////////////////////////////////////////////

namespace command_set { // Commands with ARGuments
	
class SET : public Com_Arg{
	public:
		SET(Reg reg, int arg) : Com_Arg("set", 3, reg, arg) {}
		virtual ~SET() {}
		
		//*
		static void execute(Reg reg, int arg) {
			*reg.reg() = arg;
			// *reg().reg() = arg();
		} // */
		
		/*
		static void execute(int* reg, int arg) {
			*reg = arg;
		}// */
};		

}
////////////////////////////////////////////////////////////////////////

#endif // _COMMAND_SET_HPP_
