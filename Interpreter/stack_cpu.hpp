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
#include <linker.hpp>

using namespace std;
using namespace command;
using namespace linker;

namespace stack_cpu {
	
struct Instruct {
	Instruct(bool has_arg, Code code, Reg r1, Reg r2, Reg r3)
		: _has_arg(has_arg), _code(code.val), _r1(r1.val), _r2(r2.val), _r3(r3.val) {}
	
	// why is it so?
	// explicit Instruct(wchar_t arr);
	
	bool has_arg() { return _has_arg; }
	Code    code() { return _code; }
	Reg       r1() { return _r1; }
	Reg       r2() { return _r2; }
	Reg       r3() { return _r3; }

	nondebug(private:)
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
			Linker::load_registers(regs);
		}
		
		void run_instructions();
		
	nondebug(private:)
		const stack<int> user_stack;
		const stack<int> prog_stack;
		
		unsigned ip_reg;
		unsigned ret_reg;
		
		int regs[REG_SIZE];
};

	
}
//////////////////////////////////////////////////////////////////////// 


#endif // _STACK_CPU_HPP_
