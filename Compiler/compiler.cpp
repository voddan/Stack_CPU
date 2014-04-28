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

#include <token.hpp>

using namespace std;
using namespace utils;

using namespace command;
using namespace command_set;

using namespace token;
//----------------------------------------------------------------------
/*
char* skip_spaces(char* buf) {
	while( ' ' == *buf || '\t' == *buf )
		buf += 1;
	return buf;
}

void parse_line(char* buf, Token_list& list) {
	buf = skip_spaces(buf);
	printf("'%s'\n", buf);
	* 
	// big swich here
	if( '\n' == *buf ) return;
}

int main() {
	ifstream input ("my_asm.in");
	
	Token_list tokens;
	
	#define BUF_LEN 100
	char buf[BUF_LEN] = {};
	while( input.getline(buf, BUF_LEN) ) {
		parse_line(buf, tokens);
	}
	
	cout << "=====================================" << endl;
	cout << tokens;

	//~ ofstream output("a.out");
	//~ list.to_bytecode(output);
	
	return 0;
}
*/
int main() {
	Command_list list;
	// 0
	list << new SET(Reg(0), 64);
	list << new SET(Reg(1), 128);
	list << new SET(Reg(2), 255);
	list << new SET(Reg(3), 512);
	list << new SET(Reg(4), 1024);
	// 30
	
	list << new JMP(46);
	// 36
	
	list << new ADD(Reg(6), Reg(0), Reg(6));
	list << new ADD(Reg(6), Reg(1), Reg(6));
	list << new ADD(Reg(6), Reg(2), Reg(6));
	list << new ADD(Reg(6), Reg(3), Reg(6));
	list << new ADD(Reg(6), Reg(4), Reg(6));
	// 46
	
	list << new MOV(Reg(7), Reg(6));
	// 48
	
	list << new RET();
	// 50
	/////////////
	cout << list;

	//ofstream output("test_compiler_to_bytecode.out");
	ofstream output("ded.out");
	list.to_bytecode(output);
	
}
