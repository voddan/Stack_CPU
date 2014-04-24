/** utils.hpp
 * 
 * Util functions 
 * for i/o and dump
 * 
 * */ 

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>
#include <list>
#include <typeinfo>
#include <ostream>

using namespace std;

//----------------------------------------------------------------------

namespace utils{ // namespace utils
	
class Printable {
	public: 
		virtual string to_string() const = 0;
};

ostream& operator<< (ostream& stream, const Printable& obj);

template<class T> ostream& operator<< (ostream& stream, list<T*>& lst);

/*
template<typename T> 
list<T>& operator<<(
		list<T>& lst, 
		typename list<T>::value_type item);
// */
//*
// why it does not work?
template<typename T> 
list<T>& operator<<(
		list<T>& lst, 
		typename list<T>::value_type item) {
	lst.push_back(item);
	return lst;
} // */


} // namespace utils

#endif // _UTILS_HPP_
