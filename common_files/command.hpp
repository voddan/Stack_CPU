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
	
struct Command : public Printable{
	virtual ~Command() {}
	
	const string 	name() const {return object().name;}
	const Code 	code() const {return object().code;}
	
	virtual string to_string() const {return "Command(" + name() + ")";}
	//----------------
	
	virtual void compile(ostream&) = 0;
	static wchar_t head_pack(bool has_arg, Code code, Reg r1, Reg r2, Reg r3); 
		
		
	//------------------------
	protected: struct Object {
		Object(): name("---"), code(Code(0)) {}
		Object(string _name, Code _code) :
			name(_name), code(_code) {}
			
		const string name;
		const Code code;
	};
	private: virtual Object object() const { return _object; }
	private: static const Object _object;
};
const Command::Object Command::_object;



class Command_list : public list <Command*>, public Printable {
	public:
		~Command_list();
		
		virtual string to_string() const;
		
		void compile(ostream& stream);
};

}
////////////////////////////////////////////////////////////////////////

namespace command { // Com_Arg; Com_Non
	
// TODO: add adress modification
struct Com_Arg : public Command{
	Com_Arg(Reg reg, int arg) :
		_reg(reg), _arg(arg) {}
	virtual ~Com_Arg() {}
	
	Reg 	reg() const {return _reg;}
	int 	arg() const {return _arg;}
	
	virtual string to_string() const;
	//----------------
	
	virtual void compile(ostream& stream);
	
	
	typedef void (*execute_func_t)(Reg, int);
	
	private:
		const Reg _reg;
		const int _arg;
		
	//////////////////////////////////
	protected:
	struct Object : Command::Object{
		Object(string name, Code code) : Command::Object(name, code) {}
		virtual void execute(Reg reg, int arg) {};
	};
	private: virtual Command::Object object() const { return _object; }
	private: static const Com_Arg::Object _object;
};

struct Com_Non : public Command{
	Com_Non(Reg reg, Reg reg_1, Reg reg_2) :
		_reg(reg), _reg_1(reg_1), _reg_2(reg_2)  {}
	virtual ~Com_Non() {}
	
	Reg reg  () const {return _reg;}
	Reg reg_1() const {return _reg_1;}
	Reg reg_2() const {return _reg_2;}
	
	virtual string to_string() const;
	//----------------
	
	typedef void (*execute_func_t)(Reg, Reg, Reg);
	
	//~ pair<Code, execute_func_t> execute_func_indexed() {
		//~ return pair<Code, execute_func_t> (code(), &execute);
	//~ }
	
	virtual void compile(ostream& stream);
	
	pair<Code, execute_func_t> execute_indexed() {
		//object_com_non().execute;
		//(execute_func_t)
		return pair<Code, execute_func_t> (code(),   (object_com_non().execute_func()));
		//return pair<Code, execute_func_t> (code(),  object_com_non().execute);
		//return pair<Code, execute_func_t> (code(), 0);
	}

	private:
		const Reg _reg;
		const Reg _reg_1;
		const Reg _reg_2;
		
	///////////////////////////////
	protected:
	struct Object : Command::Object{
		Object(string name, Code code) : Command::Object(name, code) {}
		virtual void execute(Reg reg, Reg reg_1, Reg reg_2) {};
		
		execute_func_t execute_func() {return reinterpret_cast<execute_func_t> (&execute);}
	};
	private: virtual Command::Object object() const { return object_com_non(); }
	private: virtual Com_Non::Object object_com_non() const { return _object; }
	private: static const Com_Non::Object _object;
};	

}
////////////////////////////////////////////////////////////////////////

#endif // _COMMAND_HPP_
