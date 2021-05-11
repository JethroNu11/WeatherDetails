#if !defined(_WEATHERDETAILS_H)
#define _WEATHERDETAILS_H

/**
 * 	@class		WeatherDetails
 *
 * 	@brief		Definition of the WeatherDetails Class.
 *
 * 	File Name: WeatherDetails.h
 *
 *	@author		Geoffrey Lawson (33176674)
 *
 *	@version	0.2		4/5/2021	Changed class to store pointers to data, not the actual data itself.
 *	@version	0.1		16/4/2021	Initial creation of the WeatherDetails class.
 *
 *	@date		4/5/2021
 *
 */
class WeatherDetails {
public:
	/**
	 * @brief	Default Constructor.
	 *			Initialises primitive variables to default values (nullptr).
	 *
	 */
	WeatherDetails();
	/**
	 * @brief	Setter for the A_T variable.
	 *			Validates that the input is a float between -273 and 100.
	 *			Assigns the default value (nullptr) if input is invalid.
	 *
	 * @param	ambientTempInput	Pointer to the float value to assign to the A_T variable.
	 *
	 * @return	True if the variable assignment is completed with no errors, false if an error occurs and the default value is assigned.
	 *
	 * @post	The A_T variable is overwritten with a valid float.
	 */
	bool SetAmbientTemp( float & ambientTempInput );
	/**
	 * @brief	Getter for the A_T variable value.
	 *			Const method so that the float value cannot be changed by the method calling it.
	 *
	 * @return	Const float with the value of the A_T variable.
	 */
	float * GetAmbientTemp() const;
	/**
	 * @brief	Setter for the S_R variable.
	 *			Validates that the input is an unsigned between 100 and 2000.
	 *			Assigns the default value (nullptr) if input is invalid.
	 *
	 * @param	solarRadiationInput	Pointer to the unsigned value to assign to the S_R variable.
	 *
	 * @return	True if the variable assignment is completed with no errors, false if an error occurs and the default value is assigned.
	 *
	 * @post	The S_R variable is overwritten with a valid unsigned.
	 */
	bool SetSolarRadiation( unsigned & solarRadiationInput );
	/**
	 * @brief	Getter for the S_R variable value.
	 *			Const method so that the unsigned value cannot be changed by the method calling it.
	 *
	 * @return	Const unsigned with the value of the S_R variable.
	 */
	unsigned * GetSolarRadiation() const;
	/**
	 * @brief	Setter for the W_S variable.
	 *			Validates that the input is an unsigned between 0 and 150.
	 *			Assigns the default value (nullptr) if input is invalid.
	 *
	 * @param	windSpeedInput	Pointer to the unsigned value to assign to the W_S variable.
	 *
	 * @return	True if the variable assignment is completed with no errors, false if an error occurs and the default value is assigned.
	 *
	 * @post	The W_S variable is overwritten with a valid unsigned.
	 */
	bool SetWindSpeed( unsigned & windSpeedInput );
	/**
	 * @brief	Getter for the W_S variable value.
	 *			Const method so that the unsigned value cannot be changed by the method calling it.
	 *
	 * @return	Const unsigned with the value of the W_S variable.
	 */
	unsigned * GetWindSpeed() const;
private:
	///	Float value that represents the Ambient Temperature
	float * A_T;
	///	Unsigned value that represents the Solar Radiation
	unsigned * S_R;
	/// Unsigned value that represents the Wind Speed
	unsigned * W_S;
};

#endif  //_WEATHERDETAILS_H



