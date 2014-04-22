/* test.cpp
 * 
 * for testing compiler.cpp
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


//----------------------------------------------------------------------

void test_Command();

int main() {
	 
	test_Command();
	
	return 0;
}

void test_Command() {
	using namespace command;
	
	cout << Command("mul") << "\n";
	
	Command_list lst;
	lst << new Command("move");
	cout <<  lst;
	
	list<Command*> L2;
	L2 << new Command("sub");
	cout << L2;
	delete (L2.front());
}
