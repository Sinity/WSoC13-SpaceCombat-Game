#ifndef ESTRING_H
#define ESTRING_H

#include <cstdlib>
#include "object.h"

namespace ezo{
/**
 * @brief zero-terminated string
 * @author Ezo
 * @date 03.08.2013
 * @version 1.0.1
 * 
 * Simple class with basic string funcionality.  
 * 
 * @todo overload += operator for integers, floats, const char*'s, string(this)
 * @todo add split(string sequencePoint). Should return array... but i must create it for join(string sequencePoint) func.
 *			Or should I use decorator pattern?
 */
class string : public Object
{
public:
	//c'tors and destructor
	string();
	string(const char* cstring);
	string(const string& estring);
    explicit string(unsigned int __length);
	~string();
	
	//assigns
	const string& operator=(const string& str);
	const string& operator=(const char* str);
	
	//get single char
	char& operator[](int pos) const;

	//multiple string("ala"*2 = "alaala")
	string operator*(unsigned int multipler);
	
	//concantate/append string
	string operator+(const string& str2);
	string operator+=(const string& str2);

	//get cstring
	operator const char*() const;
	operator char*();
	const char* c() const;
	
	//getters
    size_t length() const;
    size_t size() const;

	//format string like sprintf.
	static string format(const string& fmt, ...);

	//resize buffer with string. 
    bool resize(size_t __size);
    size_t getLength() const;
    void setLength(const size_t &value);

private:
    void allocate(size_t __size);
    void deallocate();

    char* str; /**< @brief Array of characters terminated by zero.*/
    size_t __length; /**< @brief Amount of characters in string*/
    size_t __size;   /**< @brief Amout of allocated memory in bytes*/
};
}
#endif // ESTRING_H
