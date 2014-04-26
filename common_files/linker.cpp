/* linker.cpp
 * 
 * Implementation for linker.hpp
 * */
 
#include <string>
#include <list>
#include <sstream>

#include <assert.h>

#include <utils.hpp>
#include <consts.hpp>
#include <command.hpp>

#include <linker.hpp>

using namespace std;
using namespace utils;

namespace linker {

int* Linker::_registers[] = {};

void Linker::dump_registers_val(ostream& stream) {
	stream << "#! dump of Linker::registers (values)" << endl;
	for(int i = 0; i < REG_SIZE; i++) {
		stream << "#! " << *(_registers[i]) << endl;
	}
}

void Linker::dump_registers(ostream& stream) {
	stream << "#! dump of Linker::registers (pointers)" << endl;
	for(int i = 0; i < REG_SIZE; i++) {
		stream << "#! " << _registers[i] << endl;
	}
}


void Linker::load_registers(int arr[REG_SIZE]) {
	for(int i = 0; i < REG_SIZE; i++) {
		  _registers[i] = (arr + i);
		*(_registers[i]) = 0;
	}
}


}
////////////////////////////////////////////////////////////////////////
