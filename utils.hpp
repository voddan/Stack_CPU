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

using namespace std;

//----------------------------------------------------------------------

namespace utils{ // namespace utils
	
class Printable {
	public: 
		virtual string to_string() const = 0;
};

ostream& operator<< (ostream& stream, const Printable& obj){
	stream << obj.to_string();
	return stream;
}

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


} // namespace utils

#endif // _UTILS_HPP_
