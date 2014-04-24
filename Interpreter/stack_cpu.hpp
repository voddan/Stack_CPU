/* stack_cpu.hpp
 * 
 * Classes for imulating my stack_cpu
 * 
 */
 
#ifndef _STACK_CPU_HPP_
#define _STACK_CPU_HPP_

#include <stack>
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <istream>

#include <consts.hpp>
#include <command.hpp>

using namespace std;
using namespace command;

namespace stack_cpu {
	
struct Instruct {
	Instruct(bool has_arg, Code code, Reg r1, Reg r2, Reg r3)
		: _has_arg(has_arg), _code(code.val), _r1(r1.val), _r2(r2.val), _r3(r3.val) {}
	
	/*	
	Instruct(bool has_arg, Code code, Reg r1, Reg r2, Reg r3) { 
		_has_arg = has_arg;
		_code    = code.val;
		_r1      = r1.val;
		_r2      = r2.val;
		_r3      = r3.val;
	} // */
		
	//~ Instruct() : _has_arg(false), _code(0), _r1(0), _r2(0), _r3(0) {}
	//~ Instruct(const Instruct& instr) 
		//~ : _has_arg(instr._has_arg), _code(instr._code.val), 
		//~ _r1(instr._r1.val), _r2(instr._r2.val), _r3(instr._r3.val) {}
		
	// why is it so?
	// explicit Instruct(wchar_t arr);

	private:
		bool _has_arg;
		Code _code;
		Reg  _r1;
		Reg  _r2;
		Reg  _r3;
};
	
class Stack_CPU {
	public:
		Stack_CPU(): ip_reg(0), ret_reg(0) {
			memset(regs, 0, REG_SIZE*sizeof(int)); 
			instruct.reserve(100);
		}
		
		//------------------
		bool load_instruct(ifstream& stream);
		void run_instruct();
		
		void dump_instruct	(ostream& stream);
		void dump_regs		(ostream& stream);
		void dump_user_stack	(ostream& stream);
		void dump_prog_stack	(ostream& stream);
	private:
		const stack<int> user_stack;
		const stack<int> prog_stack;
		
		int ip_reg;
		int ret_reg;
		
		int regs[REG_SIZE];
		
		vector<char> instruct;
};

	
}
//////////////////////////////////////////////////////////////////////// 


#endif // _STACK_CPU_HPP_
