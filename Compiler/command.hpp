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

#include "../utils.hpp"

using namespace std;
using namespace utils;

namespace command {
	
class Command : public Printable{
	public:
		Command(string name) : _name(name) {}
		virtual ~Command() {}
		//----------------
		string name() {return _name;}
		virtual string to_string() const {return "Command(" + _name + ")";}

	private:
		const string _name;
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
#endif // _COMMAND_HPP_
