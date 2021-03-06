/* command.cpp
 * 
 * Implementation for commamd.hpp
 * */
#include <BUILD.H>
 
#include <string>
#include <list>
#include <sstream>

#include <assert.h>

#include <utils.hpp>
#include <command.hpp>

using namespace std;
using namespace utils;

namespace command { // Code; Reg
	
string Code::to_string() const { 
	ostringstream str;
	str << std::hex << val;
	return str.str();
}

string Reg::to_string() const { 
	ostringstream str;
	str << "(" << _names[val] << ")";
	return str.str();
}
	

const string Reg::_names[] = {
	"aa", "bb", "cc", "dd", "ee", "xx", "yy", "zz"
};
}
////////////////////////////////////////////////////////////////////////

namespace command { // Command; Command_list
	
wchar_t Command::head_pack(bool has_arg, Code code, Reg r1, Reg r2, Reg r3) {
	wchar_t arr = 0;
	assert(CODE_SIZE == 64);
	assert(REG_SIZE == 8);
	
	if(has_arg) arr |= (1 << (7 + 8));
	
	assert(0 <= code.val && code.val < CODE_SIZE);
	arr |= (code.val << (1 + 8));
	
	assert(0 <= r1.val && r1.val < REG_SIZE); 
	arr |= (r1.val << (6));
	
	assert(0 <= r2.val && r2.val < REG_SIZE); 
	arr |= (r2.val << (3));
	
	assert(0 <= r3.val && r3.val < REG_SIZE); 
	arr |= (r3.val << (0));
	
	// swaps for big-small endian
	wchar_t result = ((arr << 8) & 0xff00) | ((arr >> 8) & 0x00ff);
	
	return result;
}
		

Command_list::~Command_list() {
	for(list<Command*>::iterator iter = begin();
		iter != end(); iter++) {
			delete *iter;
		}
}

string Command_list::to_string() const {
	ostringstream stream;
	stream << "Command_list[ \n";
	for(Command_list::const_iterator iter = begin();
		iter != end(); iter++){
		stream << "\t" << (**iter) << " \n";
	}
	stream << "]\n";
	return stream.str();
}

void Command_list::to_bytecode(ostream& stream) {
	for(Command_list::const_iterator iter = begin();
		iter != end(); iter++){
		(*iter)->to_bytecode(stream);
	}
}

}
////////////////////////////////////////////////////////////////////////

namespace command { // Com_Arg; Com_Non
	
string Com_Arg::to_string() const {
	ostringstream str;
	str << "Com_Arg(" << name() << ": "; 
	str << _reg << " ~ "; 
	str << _arg << ")";
	return str.str();
}

//----------------



void Com_Arg::to_bytecode(ostream& stream) {
	wchar_t head = head_pack(true, code(), reg(), Reg(0), Reg(0));
	stream.write((char*) &head, 2);
	
	stream.write((char*) &_arg, 4);
}

		
string Com_Non::to_string() const {
	ostringstream str;
	str << "Com_Non(" << name() << ": "; 
	str << _reg   << " ~ "; 
	str << _reg_1 << ", "; 
	str << _reg_2 << ")"; 
	return str.str();
}

//----------------

void Com_Non::to_bytecode(ostream& stream) {
	wchar_t head = head_pack(false, code(), reg(), reg_1(), reg_2());
	stream.write((char*) &head, 2);
}

}
////////////////////////////////////////////////////////////////////////
