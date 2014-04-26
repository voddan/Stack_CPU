/* consts.hpp
 * 
 * Constants for ather parts of porogram
 */

#ifndef _CONSTS_HPP_
#define _CONSTS_HPP_


namespace command {
// command code range
#define CODE_SIZE 64

// register name range
#define REG_SIZE 8
}
////////////////////////////////////////////////////////////////////////

//#define DEBUG
#ifdef DEBUG
	#define debug(obj) std::cout << obj << std::endl
#else
	#define debug(obj)
#endif

// inverted
#ifndef DEBUG
	#define nondebug(mod) mod
#else
	#define nondebug(mod)
#endif
////////////////////////////////////////////////////////////////////////

#endif // _CONSTS_HPP_
