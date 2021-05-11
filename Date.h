#if !defined(_DATE_H)
#define _DATE_H

//	Include 'string' to allow creation and manipulation of std::string Objects.
#include <string>

/**
 * 	@class		Date
 *
 * 	@brief		Definition of the Date Class.
 *
 * 	File Name: Date.h
 *
 *	@author 	Geoffrey Lawson (33176674)
 *
 *	@version 	0.2		11/5/2021		Added operator overloads for '==', '<' and '>'.
 *	@version 	0.1		16/4/2021		Initial creation of the Date class.
 *
 *	@date 		11/5/2021
 *
 */
class Date {
public:
	/**
	 * @brief	Default Constructor.
	 *			Initialises primitive variables to default value (0).
	 *
	 */
	Date();
	/**
	 * @brief	Setter for the day variable.
	 *			Validates that the input is an integer between 1 and 31.
	 *			Assigns the default value (0) if input is invalid.
	 *
	 * @param	dayInput	Unsigned value to be used to set the day variable.
	 *
	 * @return	True if the variable assignment is completed with no errors, false if an error occurs and the default value is assigned.
	 *
	 * @post	The day variable is overwritten with a valid unsigned.
	 */
	bool SetDay( unsigned dayInput );
	/**
	 * @brief	Setter for the month variable.
	 *			Validates that the input is an integer between 1 and 12.
	 *			Assigns the default value (0) if input is invalid.
	 *
	 * @param	monthInput	Unsigned value to be used to set the month variable.
	 *
	 * @return	True if the variable assignment is completed with no errors, false if an error occurs and the default value is assigned.
	 *
	 * @post	The month variable is overwritten with a valid unsigned.
	 */
	bool SetMonth( unsigned monthInput );
	/**
	 * @brief	Setter for the year variable.
	 *			Validates that the input is an integer between 1900 and 2021.
	 *			Assigns the default value (0) if input is invalid.
	 *
	 * @param	yearInput	Unsigned value to be used to set the year variable.
	 *
	 * @return	True if the variable assignment is completed with no errors, false if an error occurs and the default value is assigned.
	 *
	 * @post	The year variable is overwritten with a valid unsigned.
	 */
	bool SetYear( unsigned yearInput );
	/**
	 * @brief	Getter for the day variable.
	 *			Const method so that the unsigned value cannot be changed by the method calling it.
	 *
	 * @return	Const unsigned with the value of the day variable.
	 */
	unsigned GetDay() const;
	/**
	 * @brief	Getter for the month variable value.
	 *			Const method so that the unsigned value cannot be changed by the method calling it.
	 *
	 * @return	Const unsigned with the value of the month variable.
	 */
	unsigned GetMonthNumber() const;
	/**
	 * @brief	Getter for the month variable converted to the month's name.
	 *			Const method so that the string value cannot be changed by the method calling it.
	 *
	 * @return	Const string of the given month's name.
	 */
	const std::string GetMonthName() const;
	/**
	 * @brief	Getter for the year variable.
	 *			Const method so that the unsigned value cannot be changed by the method calling it.
	 *
	 * @return	Unsigned with the value of the year variable.
	 */
	unsigned GetYear() const;
	/**
	 *	@brief	Comparison operator overload (==) for the Date class. Compares the primitive values for two Date objects.
	 *
	 *	@param	comparedDate	Constant reference to the second Date object in the comparison.
	 *
	 *	@return	True if the current Date object references the same day, month and year as the parameter Date object, or False if not.
	 */
	bool operator ==( const Date & comparedDate ) const;
	/**
	 *	@brief	Less Than operator overload (<) for the Date class. Compares the primitive values for two Date objects.
	 *
	 *	@param	comparedDate	Constant reference to the second Date object in the comparison.
	 *
	 *	@return	True if the current Date object references a date earlier than the parameter Date object, or False if not.
	 */
	bool operator <( const Date & comparedDate ) const;
	/**
	 *	@brief	Greater Than operator overload (>) for the Date class. Compares the primitive values for two Date objects.
	 *
	 *	@param	comparedDate	Constant reference to the second Date object in the comparison.
	 *
	 *	@return	True if the current Date object references a date later than the parameter Date object, or False if not.
	 */
	bool operator >( const Date & comparedDate ) const;
private:
	///	Unsigned value that represents the day of the month
	unsigned day;
	///	Unsigned value that represents the month of the year
	unsigned month;
	///	Unsigned value that represents the year
	unsigned year;
};

#endif  //_DATE_H

