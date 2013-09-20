#ifndef OBJECT_H
#define OBJECT_H

namespace ezo{
/**
 * @brief Base class						   
 *                                             
 * All classes will inherit from this class.   
 * 											   
 * @author Ezo								   
 * @date 22.05.2013                            
 * @version 1.0                                
 */
class Object
{
public:
	/**
	 * @brief Empty virtual destructor
	 * 
	 * Without this function polymorphism willn't work properly for all derived objects.
	 */
	virtual ~Object(){}
};
}
#endif
