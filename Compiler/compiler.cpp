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
#include <typeinfo>

#include "../utils.hpp"
#include "command.hpp"

using namespace std;
using namespace utils;

using namespace command;
//----------------------------------------------------------------------

int main() {
	 
	Command_list list;
	list << new Command("move");
	 
	cout << list;
	
	return 0;
}
