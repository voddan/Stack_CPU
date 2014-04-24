/* command.hpp
 * 
 * */
 
#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_
 
#include <string>
#include <list>
#include <sstream>

#include <assert.h>

#include <utils.hpp>
#include <consts.hpp>

using namespace std;
using namespace utils;

namespace command { // Code; Reg
	
struct Code : Printable{
	explicit Code(int x) : val((assert(0 <= x && x < CODE_SIZE), x)) {}
	const int val;
	virtual string to_string() const;
};

struct Reg : Printable{ // POD
	explicit Reg(int x) : val((assert(0 <= x && x < REG_SIZE), x)) {}
	const int val;
	
	int* reg() {return _registers[val];}
	virtual string to_string() const;
	
	static void dump_registers(ostream& stream);
	static void dump_registers_val(ostream& stream);
	//---------------------------
	
	static void load_registers(int arr[REG_SIZE]);
	
	private:
		static const string _names[REG_SIZE];
		static int* _registers[REG_SIZE];
};

}
////////////////////////////////////////////////////////////////////////

namespace command { // Command; Command_list
	
class Command : public Printable{
	public:
		Command(string name, int code) 
			: _name(name), _code(Code(code)) {}
		virtual ~Command() {}
		
		string 	name() const {return _name;}
		Code 	code() const {return _code;}
		
		virtual string to_string() const {return "Command(" + _name + ")";}
		//----------------
		
		virtual void compile(ostream&) = 0;
		//TODO: use bytes()
		static wchar_t head_pack(bool has_arg, Code code, Reg r1, Reg r2, Reg r3); 
		
	private:
		const string _name;
		const Code _code;
};

class Command_list : public list <Command*>, public Printable {
	public:
		~Command_list();
		
		virtual string to_string() const;
	
		
		void compile(ostream& stream);
};

}
////////////////////////////////////////////////////////////////////////

namespace command { // Com_Arg; Com_Non
	
//typedef void (*Execute_func) ();
	
// TODO: add adress modification
class Com_Arg : public Command{
	public:
		Com_Arg(string name, int code, Reg reg, int arg)
			: Command(name, code), _reg(reg), _arg(arg) {}
		virtual ~Com_Arg() {}
		
		Reg 	reg() const {return _reg;}
		int 	arg() const {return _arg;}
		
		virtual string to_string() const;
		//----------------
		
		typedef void (*execute_func_t)(Reg, int);
		static void execute(Reg reg, int arg);
		
		virtual void compile(ostream& stream);

	private:
		const Reg _reg;
		const int _arg;
};

class Com_Non : public Command{
	public:
		Com_Non(string name, int code, Reg reg, Reg reg_1, Reg reg_2) : Command(name, code), 
			_reg(reg), _reg_1(reg_1), _reg_2(reg_2)  {}
		virtual ~Com_Non() {}
		
		Reg reg  () const {return _reg;}
		Reg reg_1() const {return _reg_1;}
		Reg reg_2() const {return _reg_2;}
		
		virtual string to_string() const;
		//----------------
		
		typedef void (*execute_func_t)(Reg, Reg, Reg);
		static void execute(Reg reg, Reg reg_1, Reg reg_2);
		
		virtual void compile(ostream& stream);

	private:
		const Reg _reg;
		const Reg _reg_1;
		const Reg _reg_2;
};	

}
////////////////////////////////////////////////////////////////////////

#endif // _COMMAND_HPP_
