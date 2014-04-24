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
#include <fstream>

#include <utils.hpp>
#include <command_set.hpp>
#include <command.hpp>

using namespace std;
using namespace utils;

using namespace command;
using namespace command_set;
//----------------------------------------------------------------------

int main() {
	 
	Command_list list;
	
	list << new SET(Reg(0), 64);
	list << new SET(Reg(1), 128);
	list << new SET(Reg(2), 255);
	list << new SET(Reg(3), 512);
	list << new SET(Reg(4), 1024);
	
	list << new ADD(Reg(6), Reg(0), Reg(6));
	list << new ADD(Reg(6), Reg(1), Reg(6));
	list << new ADD(Reg(6), Reg(2), Reg(6));
	list << new ADD(Reg(6), Reg(3), Reg(6));
	list << new ADD(Reg(6), Reg(4), Reg(6));
	
	list << new MOV(Reg(7), Reg(6));
	
	
	/////////////
	cout << list;

	ofstream output("../Interpreter/a.out");
	list.compile(output);
	
	return 0;
}
