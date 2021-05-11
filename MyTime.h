#if !defined(_MYTIME_H)
#define _MYTIME_H

/**
 * 	@class 		Time
 *
 * 	@brief 		Definition of the Time Class.
 *
 * 	File Name: MyTime.h
 *
 *	@author 	Geoffrey Lawson (33176674)
 *
 *	@version 	0.3		11/5/2021	Added operator overloads for '==', '<' and '>'.
 *	@version 	0.2		5/5/2021	Renaming file from 'Time.h' to 'MyTime.h' to avoid clash with <iomanip>
 *	@version 	0.1		16/4/2021	Initial creation of the Time class.
 *
 *	@date 		11/5/2021
 *
 */
class Time {
public:
	/**
	 * @brief	Default Constructor.
	 *			Initialises primitive variables to default value (99).
	 *
	 */
	Time();
	/**
	 * @brief	Setter for the hour variable.
	 *			Validates that the input is an integer between 0 and 23.
	 *			Assigns the default value (99) if input is invalid.
	 *
	 * @param	hourInput	Unsigned value to be used to set the hour variable.
	 *
	 * @return	True if the variable assignment is completed with no errors, false if an error occurs and the default value is assigned.
	 *
	 * @post	The hour variable is overwritten with a valid unsigned.
	 */
	bool SetHour( unsigned hourInput );
	/**
	 * @brief	Setter for the minute variable.
	 *			Validates that the input is an integer between 0 and 59.
	 *			Assigns the default value (99) if input is invalid.
	 *
	 * @param	minuteInput	Unsigned value to be used to set the minute variable.
	 *
	 * @return	True if the variable assignment is completed with no errors, false if an error occurs and the default value is assigned.
	 *
	 * @post	The minute variable is overwritten with a valid unsigned.
	 */
	bool SetMinute( unsigned minuteInput );
	/**
	 * @brief	Getter for the hour variable.
	 *			Const method so that the unsigned value cannot be changed by the method calling it.
	 *
	 * @return	Const unsigned with the value of the hour variable.
	 */
	unsigned GetHour() const ;
	/**
	 * @brief	Getter for the minute variable value.
	 *			Const method so that the unsigned value cannot be changed by the method calling it.
	 *
	 * @return	Const unsigned with the value of the minute variable.
	 */
	unsigned GetMinute() const ;
	/**
	 *	@brief	Comparison operator overload (==) for the Time class. Compares the primitive values for two Time objects.
	 *
	 *	@param	comparedTime	Constant reference to the second Time object in the comparison.
	 *
	 *	@return	True if the current Time object references a time equal to the parameter Time object, or False if not.
	 */
	bool operator ==( const Time & comparedTime ) const ;
	/**
	 *	@brief	Less Than operator overload (<) for the Time class. Compares the primitive values for two Time objects.
	 *
	 *	@param	comparedTime	Constant reference to the second Time object in the comparison.
	 *
	 *	@return	True if the current Time object references a time earlier than the parameter Time object, or False if not.
	 */
	bool operator <( const Time & comparedTime ) const ;
	/**
	 *	@brief	Greater Than operator overload (>) for the Time class. Compares the primitive values for two Time objects.
	 *
	 *	@param	comparedTime	Constant reference to the second Time object in the comparison.
	 *
	 *	@return	True if the current Time object references a time later than the parameter Time object, or False if not.
	 */
	bool operator >( const Time & comparedTime ) const ;
private:
	///	Unsigned value that represents the time hour
	unsigned hour;
	///	Unsigned value that represents the time minute
	unsigned minute;
};

#endif  //_MYTIME_H


