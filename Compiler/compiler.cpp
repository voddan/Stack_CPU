/*compiler.cpp
 * 
 * text 	->
 * tokens (text)->
 * comands (MAN)-> 
 * byte-code (machine)	!
 * 
 * */
 
#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <typeinfo>

#include "../utils.hpp"
#include "command.hpp"

using namespace std;
using namespace utils;

using namespace command;
//----------------------------------------------------------------------

int main() {
	 
	Command_list list;
	list << new ADD(Reg(1), Reg(2), Reg(3));
	list << new MOV(Reg(2), Reg(3));
	list << new SET(Reg(1), (255));
	list << new MOV(Reg(3), Reg(1));
	 
	cout << list;
	
	ofstream output("a.out");
	list.compile(output);
	
	return 0;
}
