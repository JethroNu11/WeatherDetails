#include "WeatherDetails.h"

#include <iostream>

WeatherDetails::WeatherDetails() : A_T( nullptr ), S_R( nullptr ), W_S( nullptr ) {

}

bool WeatherDetails::SetAmbientTemp( float & ambientTempInput ) {
	bool isSet;

	//if( &ambientTempInput != NULL ) {
		//std::cout << "setting A_T to " << ambientTempInput << std::endl;
		if( ( ambientTempInput < -273 ) || ( ambientTempInput > 100 ) ) {
		//std::cout << "invalid A_T input." << std::endl;
			A_T = nullptr;
			isSet = false;
		}else{
		//std::cout << "valid A_T input." << std::endl;
			A_T = &ambientTempInput;
			isSet = true;
		}
	//}else{
		//std::cout << "A_T input was a null pointer." << std::endl;
		//A_T = nullptr;
		//isSet = false;
	//}

	return( isSet );
}

float * WeatherDetails::GetAmbientTemp() const {
	return( A_T );
}

bool WeatherDetails::SetSolarRadiation( unsigned & solarRadiationInput ) {
	bool isSet;

	//if( solarRadiationInput != nullptr ) {
		if( ( solarRadiationInput > 2000 ) ) {
			//std::cout << "solar rad setting invalid" << std::endl;
			S_R = nullptr;
			isSet = false;
		}else{
			//std::cout << "solar rad setting valid" << std::endl;
			S_R = & solarRadiationInput;
			isSet = true;
		}
	//}else{
		//S_R = nullptr;
		//isSet = false;
	//}

	return( isSet );
}

unsigned * WeatherDetails::GetSolarRadiation() const {
	return( S_R );
}

bool WeatherDetails::SetWindSpeed( unsigned & windSpeedInput ) {
	bool isSet;

	//if( windSpeedInput != nullptr ) {
	if( windSpeedInput > 150 ) {
		W_S = nullptr;
		isSet = false;
	}else{
		W_S = & windSpeedInput;
		isSet = true;
	}
	//}else{
		//W_S = nullptr;
		//isSet = false;
	//}

	return( isSet );
}

unsigned * WeatherDetails::GetWindSpeed() const {
	return( W_S );
}
