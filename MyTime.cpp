#include "MyTime.h"

//	Default constructor.
Time::Time() : hour( 99 ), minute( 99 ) {

}

//	Setter for the Hour variable.
bool Time::SetHour( unsigned hourInput ) {
	bool isSet;

	if( hourInput > 24 ) {
		hour = 99;
		isSet = false;
	}else{
		hour = hourInput;
		isSet = true;
	}

	return( isSet );
}

//	Setter for the Minute variable.
bool Time::SetMinute( unsigned minuteInput ) {
	bool isSet;

	if( minuteInput > 59 ) {
		minute = 99;
		isSet = false;
	}else{
		minute = minuteInput;
		isSet = true;
	}

	return( isSet );
}

//	Getter for the Hour variable.
unsigned Time::GetHour() const {
	return( hour );
}

//	Getter for the Minute variable.
unsigned Time::GetMinute() const {
	return( minute );
}

//	'Equals' operator (==) overload for comparing Time objects.
bool Time::operator ==( const Time & comparedTime ) const {
	return( ( this->GetHour() == comparedTime.GetHour() ) && ( this->GetMinute() == comparedTime.GetMinute() ) );
}

//	'Less Than' operator (<) overload for comparing Time objects.
bool Time::operator <( const Time & comparedTime ) const {
	bool isLower;

	if( this->GetHour() == comparedTime.GetHour() ) {
		isLower = this->GetMinute() < comparedTime.GetMinute();
	}else{
		isLower = this->GetHour() < comparedTime.GetHour();
	}

	return( isLower );
}

//	'Greater Than' operator (>) overload for comparing Time objects.
bool Time::operator >( const Time & comparedTime ) const {
	bool isHigher;

	if( this->GetHour() == comparedTime.GetHour() ) {
		isHigher = this->GetMinute() > comparedTime.GetMinute();
	}else{
		isHigher = this->GetHour() > comparedTime.GetHour();
	}

	return( isHigher );
}
