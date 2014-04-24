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
	 
	Com_Arg com = SET(Reg(0), 239);
	
	cout << com.code().val << endl;
	
	cout << SET::execute_indexed().first.val << endl;
	cout << SET::execute_indexed().second << endl;
	
	
	return 0;
}
