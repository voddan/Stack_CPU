/* command.hpp
 * 
 * */
 
#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include <BUILD.H>
 
#include <string>
#include <list>
#include <sstream>

#include <assert.h>

#include <utils.hpp>


using namespace std;
using namespace utils;

namespace command { // Code; Reg
	
struct Code : Printable{
	explicit Code(int x) : val((assert(0 <= x && x < CODE_SIZE), x)) {}
	//Code(const Code& code) : val(code.val) {}
	const int val;
	//int val;
	
	virtual string to_string() const;
};

struct Reg : Printable{ // POD
	explicit Reg(int x) : val((assert(0 <= x && x < REG_SIZE), x)) {}
	const int val;
	//int val;
	
	virtual string to_string() const;
	
	private:
		static const string _names[REG_SIZE];
};

}
////////////////////////////////////////////////////////////////////////

namespace command { // Command; Command_list
	
struct Command : public Printable{
	Command(string name, Code code) 
		: _name(name), _code(code) {}
	virtual ~Command() {}
	
	string 	name() const {return _name;}
	Code 	code() const {return _code;}
	
	virtual string to_string() const {return "Command(" + _name + ")";}
	//----------------
	
	virtual void to_bytecode(ostream&) = 0;
	static wchar_t head_pack(bool has_arg, Code code, Reg r1, Reg r2, Reg r3); 
		
	private:
		const string _name;
		const Code _code;
};

struct Command_list : public list <Command*>, public Printable {
	~Command_list();
	
	virtual string to_string() const;
	
	void to_bytecode(ostream& stream);
};

}
////////////////////////////////////////////////////////////////////////

namespace command { // Com_Arg; Com_Non
	
struct Com_Arg : public Command{
	Com_Arg(string name, Code code, Reg reg, int arg)
		: Command(name, code), _reg(reg), _arg(arg) {}
	virtual ~Com_Arg() {}
	
	Reg 	reg() const {return _reg;}
	int 	arg() const {return _arg;}
	
	virtual string to_string() const;
	//----------------
	
	typedef void (*execute_func_t)(Reg, int);
	typedef void (*assembly_func_t)(ostream&, Reg, int);
	
	virtual void to_bytecode(ostream& stream);

	private:
		const Reg _reg;
		const int _arg;
};

struct Com_Non : public Command{
	Com_Non(string name, Code code, Reg reg, Reg reg_1, Reg reg_2) : Command(name, code), 
		_reg(reg), _reg_1(reg_1), _reg_2(reg_2)  {}
	virtual ~Com_Non() {}
	
	Reg reg  () const {return _reg;}
	Reg reg_1() const {return _reg_1;}
	Reg reg_2() const {return _reg_2;}
	
	virtual string to_string() const;
	//----------------
	
	typedef void (*execute_func_t)(Reg, Reg, Reg);
	typedef void (*assembly_func_t)(ostream&, Reg, Reg, Reg);
	
	virtual void to_bytecode(ostream& stream);

	private:
		const Reg _reg;
		const Reg _reg_1;
		const Reg _reg_2;
};	

}
////////////////////////////////////////////////////////////////////////

#endif // _COMMAND_HPP_
