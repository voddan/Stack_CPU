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
#include <vector>
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

template<class T> ostream& operator<< (ostream& stream, list<T*>& lst){
	stream << "list<" << typeid(T).name() << "*>[ ";
	for(typename list<T*>::const_iterator iter = lst.begin();
		iter != lst.end(); iter++){
		stream << (dynamic_cast<Printable*> (*iter))->to_string() << " ";
	}
	stream << "]\n";
	return stream;
}

template<typename T> 
list<T>& operator<<(
		list<T>& lst, 
		typename list<T>::value_type item) {
	lst.push_back(item);
	return lst;
}

// why is it a problem? vector::iterator is unknown (?!)
//template<typename T> void read(vector<T>::const_iterator iter, T* pointer, int num) {}

} // namespace utils

#endif // _UTILS_HPP_
