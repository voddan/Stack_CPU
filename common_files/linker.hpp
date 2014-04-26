/* linker.hpp
 * 
 * */
 
#ifndef _LINKER_HPP_
#define _LINKER_HPP_
 
#include <string>
#include <list>
#include <sstream>

#include <assert.h>

#include <utils.hpp>
#include <consts.hpp>

using namespace std;
using namespace utils;

namespace linker {

struct Linker{ // POD
	static void dump_registers(ostream& stream);
	static void dump_registers_val(ostream& stream);
	//---------------------------
	
	static void load_registers(int arr[REG_SIZE]);
	
	private:
		static int* _registers[REG_SIZE];
};

}
////////////////////////////////////////////////////////////////////////

#endif // _LINKER_HPP_

