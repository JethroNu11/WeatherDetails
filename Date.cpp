#include "Date.h"

//	Default Constructor
Date::Date() : day(0), month(0), year(0) {

}

//	Setter for the Day variable.
bool Date::SetDay(unsigned dayInput) {
	bool isSet;

	if( ( dayInput < 1 ) || ( dayInput > 31 ) ) {
		day = 0;
		isSet = false;
	}else{
		day = dayInput;
		isSet = true;
	}

	return( isSet );
}

//	Setter for the Month variable.
bool Date::SetMonth(unsigned monthInput) {
	bool isSet;

	if( ( monthInput < 1 ) || ( monthInput > 12 ) ) {
		month = 0;
		isSet = false;
	}else{
		month = monthInput;
		isSet = true;
	}

	return( isSet );
}

//	Setter for the Year variable.
bool Date::SetYear(unsigned yearInput) {
	bool isSet;

	if( ( yearInput < 1900 ) || ( yearInput > 2025 ) ) {
		year = 0;
		isSet = false;
	}else{
		year = yearInput;
		isSet = true;
	}

	return( isSet );
}

//	Getter for the Day variable.
unsigned Date::GetDay() const {
	return( day );
}

//	Getter for the Month variable.
unsigned Date::GetMonthNumber() const {
	return( month );
}

//	Getter for the Month variable as it's corresponding month name.
const std::string Date::GetMonthName() const {
	std::string monthNames[ 12 ] = {
		"January", "February", "March", "April",
		"May", "June", "July", "August", "September",
		"October", "November", "December"
	};

	return( monthNames[ month-1 ] );
}

//	Getter for the Year variable.
unsigned Date::GetYear() const {
	return( year );
}

//	'Equals' operator (==) overload for comparing Date objects.
bool Date::operator ==( const Date & comparedDate ) const {
	return( ( this->GetDay() == comparedDate.GetDay() ) && ( this->GetMonthNumber() == comparedDate.GetMonthNumber() ) && ( this->GetYear() == comparedDate.GetYear() ) );
}

//	'Less Than' operator (<) overload for comparing Date objects.
bool Date::operator <( const Date & comparedDate ) const {
	bool isLower;

	if( this->GetYear() == comparedDate.GetYear() ) {
		if( this->GetMonthNumber() == comparedDate.GetMonthNumber() ) {
			isLower = this->GetDay() < comparedDate.GetDay();
		}else{
			isLower = this->GetMonthNumber() < comparedDate.GetMonthNumber();
		}
	}else{
		isLower = this->GetYear() < comparedDate.GetYear();
	}

	return( isLower );
}

//	'Greater Than' operator (>) overload for comparing Date objects.
bool Date::operator >( const Date & comparedDate ) const {
	bool isHigher;

	if( this->GetYear() == comparedDate.GetYear() ) {
		if( this->GetMonthNumber() == comparedDate.GetMonthNumber() ) {
			isHigher = this->GetDay() > comparedDate.GetDay();
		}else{
			isHigher = this->GetMonthNumber() > comparedDate.GetMonthNumber();
		}
	}else{
		isHigher = this->GetYear() > comparedDate.GetYear();
	}

	return( isHigher );
}
