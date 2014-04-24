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

#define bytes(xx, y) (( (xx) << (sizeof(xx) * 8 - (y)) ) >> (sizeof(xx) * 8 - (y)) )


#endif // _CONSTS_HPP_
