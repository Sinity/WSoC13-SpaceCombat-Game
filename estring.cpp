#include "estring.h"

#include <cstring>
#include <cstdarg>
#include <cstdio>

namespace ezo{
/* *****************************************************************************
 * 						     CONSTRUCTORS AND DESTRUCTOR                       *
 * ****************************************************************************/ 

/**
 * @brief Creates empty string. 
 */
string::string()
{
	str = nullptr;
	allocate(0);
	__length = 0;
}

/**
 * @brief Create string and allocate space for amount of characters in param.
 * @param length amount of characters
 * @warning if allocate(malloc) fails, it will be ignored
 */
string::string(unsigned int _length)
{
	str = nullptr;
	allocate(_length);
    __length = _length;
}

/**
 * @brief Create string from other string.(copy constructor)
 * @param estring other string.
 */
string::string(const string& estring)
{
	str = nullptr;
	__length = estring.__length;
	allocate(__length);
	strcpy(str, estring.str);
}

/**
 * @brief Create string from c-style string.
 * @param cstring zero-termianted string
 */
string::string(const char* cstring)
{
	str = nullptr;
	allocate(strlen(cstring));
	__length = __size - 1;
	strcpy(str, cstring);
}

/**
 * @brief Deallocate string.
 */
string::~string()
{
	if(str != nullptr)
		free(str);
}

/* *****************************************************************************
 * 							    ALLOCATION STUFF                               *
 * ****************************************************************************/       

 /**
 * @brief Allocate memory for string. If string already exist, destroy it.
 * @param length amunt of letters of new string. 
 * @return void
 * @warning If malloc fails, program will crash(operation on nullptr).
 *  
 * Function will deallocate old string if it exist, allocate memory,
 *	 and set first char to zero(creates empty string).
 * If caller set size to zero, it will allocate space only for zero terminator.
 */
inline void string::allocate(size_t _length)
{
	if(str != nullptr)
		deallocate();
	__size = _length + 1;
	str = (char*)malloc(__size);
	str[0] = 0;
}

/**
 * @brief deallocate memory used for array with raw string(str member of this class).
 * @return void
 * 
 * Function is safe even if string doesn't exist.
 */
inline void string::deallocate()
{
	if(str != nullptr)
		free(str);
	__size = __length = 0;	
}

/**
 * @brief Resize string.
 * @param _length amount of letters that string must hold
 * @return True if success, false if _length if less than existing string.
 * @warning If realloc fails, caller won't be noticed about that, and in this
 * 			 case string will be wrong and program will crash if you use it.
 */
inline bool string::resize(size_t _length)
{
	++_length; //space for characters + null terminator
    if(_length < __length+1)
        return false;	//too small to hold existing string.
		
	str = (char*)realloc(str, _length);
	this->__size = _length;
	return true;
}


/* *****************************************************************************
 * 							 OPERATOR OVERLOADINGS!			                   *
 * ****************************************************************************/ 

/**
 * @brief Copy string from parameter to this object.
 * @param str string to copy
 * @return reference to this object
 */
const string& string::operator=(const string& str)
{
	if(str.__length > __length)
		resize(str.__length);
	__length = str.__length;
	strcpy(this->str, str.str);
	return *this;
}

	
/**
 * @brief Copy cstring from parameter to this object.
 * @param str c-style string to copy
 * @return reference to this object
 */	
const string& string::operator=(const char* str)
{
	size_t len = strlen(str);
	if(len > __size-1)
		resize(len);
	__length = len;
	strcpy(this->str, str);
	return *this;
}

/**
 * @brief return character on position from argument <b>pos</b>
 * @param pos position of character, from 0
 * @return character on position from argument <b>pos</b>
 * @warning there is no checking for range - 
 * 				if <b>pos</b> argument is out of range(0-size) it will 
 * 				produce wrong results and can crash application. 
 */
char& string::operator[](int pos) const
{
	return str[pos];
}

/**
 * @brief multiple strings by argument.
 * @param mult multipler
 * @return multiplied string. If mult = 0, returns empty string.
 */
string string::operator*(unsigned int mult)
{
	if(mult == 0)
		return string(mult);
		
	int resultLength = __length*mult;
	string result(resultLength);
	
	for(unsigned int i = 0; i < mult; i++)
	{
		strcpy(result.str + i*__length, str);
	}
	result.__length = resultLength;
	
	return result;
}

/**
 * @brief concancate this with param
 * @param str2 second product of concantenation
 * @return concantenated string
 * 
 * @warning if program can't get more memory, it will crash.
 */
string string::operator+(const string& str2)
{
	string result(__length+str2.__length);
	result.__length = __length+str2.__length;
	result.__size = __size + str2.__size;
	strcpy(result.str, str);
	strcpy(result.str+__length, str2.str);
	return result;
}

/**
 * @brief append str2 to this string.
 * @param str2 string that will be appended
 * @return this(result) string.
 * 
 * @warning if resize fails(out of memory), it willn't be noticed.
 */
string string::operator+=(const string& str2)
{
	this->resize(__length + str2.__length);
	strcpy(str+__length, str2.str);
	__length = __length + str2.__length;
	return *this;
}


/* *****************************************************************************
 * 	    					CONVERSION FUNCTIONS    		                   *
 * ****************************************************************************/ 
 
/**
 * @brief Convert string to read only c-style string (const char*)
 */
string::operator const char*() const
{
	return (const char*)str;
}

/**
 * @brief Convert string to c-style string(char*)
 */
string::operator char*()
{
	return str;
}

/**
 * @brief Convert string to c-style read only string (const char*)
 */
const char* string::c() const
{
	return (const char*)str;
}

/* *****************************************************************************
 * 							   		 GETTERS              		               *
 * ****************************************************************************/ 

/**
 * @return amount of characters in string
 */
size_t string::length() const
{
	return __length;
}

/**
 * @return allocated space for string in bytes
 */
size_t string::size() const
{
	return __size;
}

/* *****************************************************************************
 * 						   		STATIC FUNCTIONS       	  		               *
 * ****************************************************************************/ 

/**
 * @brief format string like sprintf function. 
 * @param fmt pattern with tags like %d, %f, %s, %c, %p etc.
 * @param ... variables matching to tags. 
 * @return formatted string.
 * @warning function don't checking for wrong usage like: variables from ... 
 * 				not matching to pattern, amount of variables is wrong etc.
 * 
 * I will replace it later, it's not mine(found on stackoverflow)
 */
string string::format(const string& fmt, ...) 
{
    int size = 1024;
    string str(size);
	
    va_list ap;
    while (1) 
	{
        va_start(ap, fmt);
        int n = vsnprintf((char*)str, size, fmt.c(), ap);
        va_end(ap);
        if (n > -1 && n < size) 
		{
            str.resize(n);
			str.__length = n;
            return str;
        }
        if (n > -1)
            size = n + 1; //check it. can be slow.
        else
            size *= 2;
		str.resize(size);
    }
    return str;
}
}
