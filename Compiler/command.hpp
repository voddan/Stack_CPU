/* command.hpp
 * 
 * */
 
#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_
 
#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <typeinfo>

#include <assert.h>

#include "../utils.hpp"

using namespace std;
using namespace utils;

namespace command { // Code; Reg
	
#define CODE_SIZE 64
struct Code : Printable{
	Code(int x) : val((assert(0 <= x && x < CODE_SIZE), x)) {}
	const int val;
	virtual string to_string() const { 
		ostringstream str;
		str << std::hex << val;
		return str.str();
	}
};

#define REG_SIZE 8
struct Reg : Printable{
	Reg(int x) : val((assert(0 <= x && x < REG_SIZE), x)) {}
	const int val;
	int* reg() {return 0;}
	virtual string to_string() const { 
		ostringstream str;
		str << std::hex << val;
		return str.str();
	}
};
	
}

namespace command { // Command; Command_list
	
class Command : public Printable{
	public:
		Command(string name, int code) 
			: _name(name), _code(Code(code)) {}
		virtual ~Command() {}
		
		string 	name() const {return _name;}
		int 	code() const {return _code.val;}
		
		virtual string to_string() const {return "Command(" + _name + ")";}
		//----------------

	private:
		const string _name;
		const Code _code;
};

class Command_list : public list <Command*>, public Printable {
	public:
		~Command_list() {
			for(list<Command*>::iterator iter = begin();
				iter != end(); iter++) {
					delete *iter;
				}
		}
		
		virtual string to_string() const {
			ostringstream stream;
			stream << "Command_list[ \n";
			for(Command_list::const_iterator iter = begin();
				iter != end(); iter++){
				stream << "\t" << (**iter) << " \n";
			}
			stream << "]\n";
			return stream.str();
		}
		
};

}

namespace command { // Com_Arg; Com_Non
	
// TODO: add adress modification
class Com_Arg : public Command{
	public:
		Com_Arg(string name, int code, Reg reg, int arg)
			: Command(name, code), _reg(reg), _arg(arg) {}
		virtual ~Com_Arg() {}
		
		Reg 	reg() const {return _reg;}
		int 	arg() const {return _arg;}
		
		virtual string to_string() const {
			ostringstream str;
			str << "Com_Arg(" << name() << ": "; 
			str << _reg.to_string() << ", "; 
			str << _arg		<< ")";
			return str.str();
		}
		
		//----------------

	private:
		const Reg _reg;
		const int _arg;
};

class Com_Non : public Command{
	public:
		Com_Non(string name, int code, Reg reg, Reg reg_1, Reg reg_2) : Command(name, code), 
			_reg(reg), _reg_1(reg_1), _reg_2(reg_2)  {}
		virtual ~Com_Non() {}
		
		Reg 	reg  () const {return _reg;}
		Reg 	reg_1() const {return _reg_1;}
		Reg 	reg_2() const {return _reg_2;}
		
		virtual string to_string() const {
			ostringstream str;
			str << "Com_Non(" << name() << ": "; 
			str << _reg.to_string() << " ~ "; 
			str << _reg_1.to_string() << ", "; 
			str << _reg_2.to_string() << ")"; 
			return str.str();
		}
		
		//----------------

	private:
		const Reg _reg;
		const Reg _reg_1;
		const Reg _reg_2;
};	

};

namespace command { // Commands with NO arguments
	
class ADD : public Com_Non{
	public:
		ADD(Reg reg, Reg reg_1, Reg reg_2) : Com_Non("add", 1, reg, reg_1, reg_2) {}
		virtual ~ADD() {}
		
		void execute() {
			*reg().reg() = *reg_1().reg() + *reg_2().reg();
		}
};		

class MOV : public Com_Non{
	public:
		MOV(Reg reg, Reg reg_1) : Com_Non("mov", 2, reg, reg_1, Reg(0)) {}
		virtual ~MOV() {}
		
		void execute() {
			*reg().reg() = *reg_1().reg();
		}
};		

};

namespace command { // Commands with ARGuments
	
class SET : public Com_Arg{
	public:
		SET(Reg reg, int arg) : Com_Arg("set", 1, reg, arg) {}
		virtual ~SET() {}
		
		void execute() {
			*reg().reg() = arg();
		}
};		

};

#endif // _COMMAND_HPP_
