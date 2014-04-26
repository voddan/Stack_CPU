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
	
struct ADD : public Com_Non{
	ADD(Reg reg, Reg reg_1, Reg reg_2) : Com_Non(reg, reg_1, reg_2) {}
	virtual ~ADD() {}
	
	
	///////////////////////
	//~ static void execute(Reg reg, Reg reg_1, Reg reg_2) {
		//~ *reg.reg() = *reg_1.reg() + *reg_2.reg();
	//~ }
	static void execute_s(Reg reg, Reg reg_1, Reg reg_2) {
		ADD obj(reg, reg_1, reg_2);
///		obj.execute(reg, reg_1, reg_2);
	}
	
	//~ void execute(Reg reg, Reg reg_1, Reg reg_2) {
		//~ *reg.reg() = *reg_1.reg() + *reg_2.reg();
	//~ }
	
	// how to inherit it?
	//~ static pair<Code, execute_func_t> execute_indexed() {
		//~ return pair<Code, execute_func_t> (Code(_code), ADD::execute);
	//~ }
	//~ static pair<Code, execute_func_t> execute_indexed() {
		//~ return pair<Code, execute_func_t> (Code(_code), ADD::execute_s);
	//~ }
	
	//------------------------------
	protected:
	struct Object : Com_Non::Object{
		Object() : Com_Non::Object("add", Code(1)) {}
		virtual void execute(Reg reg, Reg reg_1, Reg reg_2) {
			*reg.reg() = *reg_1.reg() + *reg_2.reg();
		};
	};
	private: virtual Command::Object object() const { return _object; }
	private: static const ADD::Object _object;
};		
const ADD::Object ADD::_object;

struct MOV : public Com_Non{
	MOV(Reg reg, Reg reg_1) : Com_Non(reg, reg_1, Reg(0)) {}
	virtual ~MOV() {}
	
	static void execute(Reg reg, Reg reg_1, Reg reg_2) {
		*reg.reg() = *reg_1.reg();
	}
	
	// how to inherit it?
	//~ static pair<Code, execute_func_t> execute_indexed() {
		//~ return pair<Code, execute_func_t> (Code(_code), MOV::execute);
	//~ }
	
	//------------------------------
	protected:
	struct Object : Com_Non::Object{
		Object() : Com_Non::Object("mov", Code(2)) {}
		virtual void execute(Reg reg, Reg reg_1, Reg reg_2) {
			*reg.reg() = *reg_1.reg();
		};
	};
	private: virtual Command::Object object() const { return _object; }
	private: static const MOV::Object _object;
};	
const MOV::Object MOV::_object;	

}
////////////////////////////////////////////////////////////////////////

namespace command_set { // Commands with ARGuments
	
struct SET : public Com_Arg{
	SET(Reg reg, int arg) : Com_Arg( reg, arg) {}
	virtual ~SET() {}
	
	static void execute(Reg reg, int arg) {
		debug( "#! SET::execute " );
		debug( "#!" << reg << " | " << reg.reg() );
		debug( "#!" << hex << arg );
		*reg.reg() = arg;
	}
	
	// how to inherit it?
	//~ static pair<Code, execute_func_t> execute_indexed() {
		//~ return pair<Code, execute_func_t> (Code(_code), SET::execute);
	//~ }
	
	//------------------------------
	protected:
	struct Object : Com_Arg::Object{
		Object() : Com_Arg::Object("set", Code(3)) {}
		virtual void execute(Reg reg, int arg) {
			*reg.reg() = arg;
		};
	};
	private: virtual Command::Object object() const { return _object; }
	private: static const SET::Object _object;
};	
const SET::Object SET::_object;			

}
////////////////////////////////////////////////////////////////////////

#endif // _COMMAND_SET_HPP_
