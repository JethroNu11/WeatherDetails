//	Include 'iostream' (Input/Output Stream), to allow the use of 'cin', 'cout' and 'endl' methods.
#include <iostream>
//	Include 'iomanip' (Input/Output Manipulation), to allow the use of 'setw' to format the width of the month names.
#include <iomanip>
//	Include 'sstream' (String Stream), to allow for more efficient conversions between data types.
#include <sstream>
//	include 'fstream' (File Stream), to allow input to / output from files.
#include <fstream>
//	Include 'cmath', for the 'sqrt(float)' method when calculating standard deviation.
#include <cmath>
//	Include 'map', to allow direct association between two objects.
#include <map>

//	Include the Date class header file, to store dates from file input.
#include "../Classes/Date.cpp"
//	Include the MyTime class header file, to store time from file input.
#include "../Classes/MyTime.cpp"
//	Include the WeatherDetails class header file, to store temperature, sun and wind information from file input.
#include "../Classes/WeatherDetails.cpp"
//	Include the Binary Search Tree header file, to store data from the files in a tree structure.
#include "../Classes/Bst.h"
//	Include the USCollect template header file for extracting pointers to required data from Bst Nodes with unsigned values.
#include "../Classes/USCollect.cpp"
//	Include the FLCollect template header file for extracting pointers to required data from Bst Nodes with float values.
#include "../Classes/FLCollect.cpp"

using namespace std;
/*using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::setw;
using std::map;
using std::stringstream;
using std::istream;
using std::ifstream;
using std::ostream;*/

typedef map< Time, WeatherDetails > TD_Map;
typedef TD_Map::const_iterator cTD_Itr;
typedef map< Date, TD_Map > DTD_Map;
typedef DTD_Map::const_iterator cDTD_Itr;

void print( float & x );
void print( unsigned & x );
void setBounds( DTD_Map & dateTimeData, unsigned & lowestYear, unsigned & highestYear );
static void inputFile( istream & is, DTD_Map & dateTimeData, Bst< float > & AT_Tree, Bst< unsigned > & SR_Tree, Bst< unsigned > & WS_Tree );
void outputInfo( ostream & os, DTD_Map & dateTimeData, Bst< float > & AT_Tree, Bst< unsigned > & SR_Tree, Bst< unsigned > & WS_Tree );
void outputAvgWS( unsigned month, unsigned year, DTD_Map & dateTimeData );
void outputAvgAT( unsigned year, DTD_Map & dateTimeData );
void outputTotalSR( unsigned year, DTD_Map & dateTimeData );
void exportDetails( unsigned year, DTD_Map & dateTimeData );
unsigned getUnsigned( string name, unsigned lowerBound, unsigned upperBound );
string getMonthName( unsigned monthNum );
stringstream & operator >>( stringstream & is, Date & d );
stringstream & operator >>( stringstream & is, Time & t );
ostream & operator <<( ostream & os, const Date & d );
ostream & operator <<( ostream & os, const Time & t );

/**
 * @brief	Main part of the program. Handles file input and menu selection.
 *
 */
int main() {
	DTD_Map dateTimeData;
	Bst< float > AT_Tree;

	Bst< unsigned > SR_Tree;
	Bst< unsigned > WS_Tree;

	unsigned month, year, lowestYear, highestYear;
	bool quitProgram;

	/// Open the index of all data files
	ifstream indexInputFile( "../Data/met_index.txt" );
	if( !indexInputFile ) return -1;

	string fileName, firstRow;

	cout << "Inputting data from files, please wait." << endl;

	/// Individually open, extract and close each of the given data files.
	while( indexInputFile.peek() != EOF ) {
		getline( indexInputFile, fileName );
		ifstream infile( "../Data/" + fileName );
		if( infile ) {
			cout << "Getting data from file: " << fileName << endl;
			infile >> firstRow;
			infile.ignore();

			// Input the data into the DateTimeDataMap Map
			inputFile( infile, dateTimeData, AT_Tree, SR_Tree, WS_Tree );
		}else{
			cout << "Error opening file: " << fileName << endl;
		}
		infile.close();
	}

	indexInputFile.close();

	//General information for debugging/reference purposes.
	cout << "Nodes in AT_Tree: " << AT_Tree.TreeNodeCount() << endl;
	cout << "Height of AT_Tree: " << AT_Tree.TreeHeight() << endl;
	cout << "Nodes in SR_Tree: " << SR_Tree.TreeNodeCount() << endl;
	cout << "Height of SR_Tree: " << SR_Tree.TreeHeight() << endl;
	cout << "Nodes in WS_Tree: " << WS_Tree.TreeNodeCount() << endl;
	cout << "Height of WS_Tree: " << WS_Tree.TreeHeight() << endl;

	setBounds( dateTimeData, lowestYear, highestYear );

	//	Display the main menu
	do{
		cout	<< "===================================================================================================" << endl
				<< "1: Print average wind speed (km/h) for a given month and year (with sample standard deviation)." << endl
				<< "2: Print average ambient air temperature (C) for each month of a given year (with sample standard deviation)." << endl
				<< "3: Print total solar radiation (kWh/m2) for each month of a given year (with sample standard deviation)." << endl
				<< "4: Export average wind speed (km/h), average ambient air temperature (C) and total solar radiation (kWh/m2) for each month of a given year to a .csv file (with sample standard deviations)." << endl
				<< "5: Quit the program." << endl
				<< "===================================================================================================" << endl;

		switch( getUnsigned( "Menu Choice", 1, 5 ) ){
			case 1:		//Print average wind speed (km/h) for a given month and year (with sample standard deviation)
				month = getUnsigned( "Month", 1, 12 );
				year = getUnsigned( "Year", lowestYear, highestYear );
				outputAvgWS( month, year, dateTimeData );
				break;
			case 2:		//Print average ambient air temperature (C) for each month of a given year (with sample standard deviation)
				year = getUnsigned( "Year", lowestYear, highestYear );
				outputAvgAT( year, dateTimeData );
				break;
			case 3:		//Print total solar radiation (kWh/m2) for each month of a given year (with sample standard deviation)
				year = getUnsigned( "Year", lowestYear, highestYear );
				outputTotalSR( year, dateTimeData );
				break;
			case 4:		//Export all weather details for each month of a given year to csv
				year = getUnsigned( "Year", lowestYear, highestYear );
				exportDetails( year, dateTimeData );
				break;
			case 5:		//Quit program
				cout << "Program closed." << endl;
				quitProgram = true;
				break;
			default:	//Default output, shouldn't be needed as the getUnsigned method already handles all the input validation.
				cout << "Error: Input is not valid. Please enter the number for an option from the menu." << endl;
				break;
		}
	}while( !quitProgram );

	return( 0 );
}

/**
 *	@brief	Outputs the given float value to the screen on its own line.
 *
 *	@param	x	Reference to a float variable to display on the screen.
 *
 *	@post	The given float value is printed to the screen, and the output stream is moved to a new line.
 */
void print( float & x ) {
	cout << x << endl;
}

/**
 *	@brief	Outputs the given unsigned value to the screen on its own line.
 *
 *	@param	x	Reference to an unsigned variable to display on the screen.
 *
 *	@post	The given unsigned value is printed to the screen, and the output stream is moved to a new line.
 */
void print( unsigned & x ) {
	cout << x << endl;
}




/**
 *	@brief
 *
 *	@param	dateTimeData	Reference to a DTD_Map object that has Date objects to be checked.
 *	@param	lowestYear		Reference to an unsigned value representing the lowest year in the DTD_Map's Date objects
 *	@param	highestYear		Reference to an unsigned value representing the highest year in the DTD_Map's Date objects
 *
 *	@post	The lowestYear and highestYear variables have been set to the relevant lowest and highest year values from the dateTimeData.
 */
void setBounds( DTD_Map & dateTimeData, unsigned & lowestYear, unsigned & highestYear ) {
	for( cDTD_Itr DTDItr = dateTimeData.begin(); DTDItr != dateTimeData.end(); DTDItr++ ) {
		if( DTDItr == dateTimeData.begin() ) {
			lowestYear = highestYear = DTDItr->first.GetYear();
		}else if( DTDItr->first.GetYear() < lowestYear) {
			lowestYear = DTDItr->first.GetYear();
		}else if( DTDItr->first.GetYear() > highestYear) {
			highestYear = DTDItr->first.GetYear();
		}
	}
}

/**
 *	@brief	Inserts all the data from the given Input Stream as objects in the dateTimeData map.
 *
 *	@param	is				Reference to the Input Stream that will be used to get the data from the file.
 *	@param	dateTimeData	Reference to the DTD_Map object that will connect the Date, Time and WeatherDetails objects for a single record.
 *	@param	AT_Tree			Reference to the Binary Search Tree of floats to store the Ambient Temperature values.
 *	@param	SR_Tree			Reference to the Binary Search Tree of unsigned to store the Solar Radiation values.
 *	@param	WS_Tree			Reference to the Binary Search Tree of unsigned to store the Wind Speed values.
 *
 *	@pre	All three Bst objects have been initialised, and the Input Stream is a valid file to be input.
 *	@post	The data from the given Input Stream file has been loaded into three Trees, and the dateTimeData map connects a given datetime
 *			with it's values.
 */
static void inputFile( istream & is, DTD_Map & dateTimeData, Bst< float > & AT_Tree, Bst< unsigned > & SR_Tree, Bst< unsigned > & WS_Tree ) {
	string lineString, number;

	float AT_Input;
	unsigned SR_Input, WS_Input;

	///	Declare static FLCollect and USCollect for extracting tree node data.
	FLCollect C_AT;
	USCollect C_SR;
	USCollect C_WS;

	while( is.peek() != EOF ) {
		stringstream line, value;
		///	Declare temporary Date object.
		Date date;
		///	Declare temporary Time object.
		Time time;
		///	Declare temporary WeatherDetails object.
		WeatherDetails details;

		getline( is, lineString);
		line << lineString;
		line >> date;
		line >> time;

		for( unsigned i = 0; i < 9; i++ ) {
			line.ignore( 50, ',' );
		}

		getline( line, number, ',' );
		value << number;
		value >> WS_Input;
		value.clear();

		getline( line, number, ',' );
		value << number;
		value >> SR_Input;
		value.clear();

		for( unsigned i = 0; i < 5; i++ ) {
			line.ignore( 50, ',' );
		}

		getline( line, number, ' ' );
		value << number;
		value >> AT_Input;
		value.clear();

		///	Insert AT value into AT_Tree and details
		AT_Tree.Insert( AT_Input );
		C_AT.SetTarget( AT_Input );
		AT_Tree.InOrder( C_AT.ExtractTarget );
		if( !( details.SetAmbientTemp( C_AT.GetTargetPtr() ) ) ) {
			cout << "Error with Ambient Temperature input: " << AT_Input << endl;
		}

		///	Insert SR value into SR_Tree and details
		SR_Tree.Insert( SR_Input );
		C_SR.SetTarget( SR_Input );
		SR_Tree.InOrder( C_SR.ExtractTarget );
		if( !( details.SetSolarRadiation( C_SR.GetTargetPtr() ) ) ) {
			cout << "Error with Solar Radiation input: " << SR_Input << endl;
		}

		///	Insert WS value into WS_Tree and details
		WS_Tree.Insert( WS_Input );
		C_WS.SetTarget( WS_Input );
		WS_Tree.InOrder( C_WS.ExtractTarget );
		if( !( details.SetWindSpeed( C_WS.GetTargetPtr() ) ) ) {
			cout << "Error with Wind Speed input: " << WS_Input << endl;
		}

		dateTimeData[date][time] = details;

		line.clear();
	}
}

/**
 *	@brief	Outputs the average wind speed in kilometers per hour for the given month of the given year.
 *
 *	@param	month			unsigned value representing the month of the year
 *	@param	year			unsigned value representing the year
 *	@param	dateTimeData	DateTimeDate Map object with all the
 *
 *	@post	If the relevant data exists, the Wind Speed information (average km/h and standard deviation) for the given month of the given year
 *			is displayed on the screen, otherwise an appropriate error message is output.
 */
void outputAvgWS( unsigned month, unsigned year, DTD_Map & dateTimeData ) {
	float WS_Total, WS_Avg, WS_StdDev;
	unsigned WS_Count;
	bool sameMonth = true;

	WS_Total = WS_StdDev = WS_Count = 0;

	//maybe turn this into a function to get the first date that exists in the chosen month, in case it starts
	//at like 5 or something? Like 'Date start;' then 'getFirstDay(start, month, year);'
	Date start;
	start.SetDay(1);
	start.SetMonth(month);
	start.SetYear(year);

	//Phase 1: Calculate WS_Total and WS_Count
	for( cDTD_Itr DTDItr = dateTimeData.find(start); DTDItr != dateTimeData.end() && sameMonth; DTDItr++ ) { //Iterate through dateTimeData map
		if( ( DTDItr->first.GetMonthNumber() != month ) || ( DTDItr->first.GetYear() != year ) ) { //Check if the correct month is selected
			sameMonth = false;
		}else{
			for( cTD_Itr TDItr = DTDItr->second.begin(); TDItr != DTDItr->second.end(); TDItr++ ) {	//Iterate through timeData map
				if( TDItr->second.GetWindSpeed() != nullptr ) { //check if the value is a nullptr
					WS_Total += *TDItr->second.GetWindSpeed(); //add value to total
					WS_Count++; //Increment count
				}
			}
		}
	}

	//Phase 2: Depending on WS_Count, either calculate and output WS_Avg and WS_StdDev, or output 'No Data'.
	if( WS_Count > 0 ) {
		WS_Avg = ( WS_Total / WS_Count );
		sameMonth = true;
		for( cDTD_Itr DTDItr = dateTimeData.find(start); DTDItr != dateTimeData.end() && sameMonth; DTDItr++ ) {
			if( ( DTDItr->first.GetMonthNumber() != month ) || ( DTDItr->first.GetYear() != year ) ) {
				sameMonth = false;
			}else{
				for( cTD_Itr TDItr = DTDItr->second.begin(); TDItr != DTDItr->second.end(); TDItr++ ) {
					if( TDItr->second.GetWindSpeed() != nullptr ) {
						//WS_StdDev += ( ( WS_Tree.Get( *TDItr->second.GetWindSpeed() ) ) - WS_Avg ) * ( ( WS_Tree.Get( *TDItr->second.GetWindSpeed() ) ) - WS_Avg );
						WS_StdDev += ( *TDItr->second.GetWindSpeed() - WS_Avg ) * ( *TDItr->second.GetWindSpeed() - WS_Avg );
					}
				}
			}
		}
		WS_StdDev = sqrt( ( WS_StdDev /= ( WS_Count - 1 ) ) );

		cout 	<< getMonthName( month ) << ' ' << year << ":" << endl
				<< "Average speed: " << ( WS_Avg * 3.6 ) << "km/h." << endl
				<< "Sample Standard Deviation: " << ( WS_StdDev * 3.6 ) << "." << endl;
	}else{
		cout << getMonthName( month ) << ' ' << year << ": No Data" << endl;
	}

}

/**
 *	@brief	Outputs the average ambient temperature in degrees Celsius for each individual month in the given year.
 *
 *	@param	year			unsigned value representing the year.
 *	@param	dateTimeData	DateTimeDate Map object with all the records inside it.
 *
 *	@post	If the relevant data exists, the Ambient Temperature information (average degrees Celsius and standard deviation) for each
 *			month of the given year is displayed on the screen, otherwise an appropriate error message is output.
 */
void outputAvgAT( unsigned year, DTD_Map & dateTimeData ) {
	unsigned i;
	float AT_Avg, AT_StdDev;
	float AT_Total[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	unsigned AT_Count[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//Phase 1: Calculate the AT_Total and AT_Count values for each month
	for( cDTD_Itr DTDItr = dateTimeData.begin(); DTDItr != dateTimeData.end(); DTDItr++ ) { //Iterate through dateTimeData map
		if( DTDItr->first.GetYear() == year ) { //Check if the correct year is selected
			for( cTD_Itr TDItr = DTDItr->second.begin(); TDItr != DTDItr->second.end(); TDItr++ ) {	//Iterate through timeData map
				if( TDItr->second.GetAmbientTemp() != nullptr ) { //check if the value is a nullptr
					AT_Total[ ( DTDItr->first.GetMonthNumber() - 1 ) ] += *TDItr->second.GetAmbientTemp(); //add value to total for that month
					AT_Count[ ( DTDItr->first.GetMonthNumber() - 1 ) ]++; //Increment count for that month
				}
			}
		}
	}

	cout << "Ambient Temperature data for each month of the year " << year << ":" << endl;

	//Phase 2: Depending on AT_Count for each month, either calculate and output AT_Avg and AT_StdDev, or output 'No Data'.
	for( i = 0; i < 12; i++ ) { //loop through each month's number
		if( AT_Count[ i ] != 0 ) {
			AT_Avg = AT_Total[ i ] / AT_Count[ i ];
			AT_StdDev = 0;
			for( cDTD_Itr DTDItr = dateTimeData.begin(); DTDItr != dateTimeData.end(); DTDItr++ ) { //Iterate through dateTimeData map
				if( ( DTDItr->first.GetMonthNumber() == ( i+1) ) && ( DTDItr->first.GetYear() == year ) ) { //Check if the correct year is selected
					for( cTD_Itr TDItr = DTDItr->second.begin(); TDItr != DTDItr->second.end(); TDItr++ ) {	//Iterate through timeData map
						if( TDItr->second.GetAmbientTemp() != nullptr ) { //check if the value is a nullptr
							AT_StdDev += ( *TDItr->second.GetAmbientTemp() - AT_Avg ) * ( *TDItr->second.GetAmbientTemp() - AT_Avg );
						}
					}
				}
			}
			AT_StdDev = sqrt( ( AT_StdDev /= ( AT_Count[ i ] - 1 ) ) );
			cout << setw( 10 ) << getMonthName( ( i+1 ) ) << ": Average: " << AT_Avg << " degrees C, Standard Deviation: " << AT_StdDev << "." << endl;
		}else{
			cout << setw( 10 ) << getMonthName( ( i+1 ) ) << ": No Data." << endl;
		}
	}


}

/**
 *	@brief	Outputs the total solar radiation in kilowatts per square meter for each individual month in the given year.
 *
 *	@param	year			unsigned value representing the year
 *	@param	dateTimeData	DateTimeDate Map object with all the records inside it.
 *
 *	@post	If the relevant data exists, the Solar Radiation information (total kWh/m2) for each month of the given year is
 *			displayed on the screen, otherwise an appropriate error message is output.
 */
void outputTotalSR( unsigned year, DTD_Map & dateTimeData ) {
	unsigned i;
	float SR_Total[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for( cDTD_Itr DTDItr = dateTimeData.begin(); DTDItr != dateTimeData.end(); DTDItr++ ) { //Iterate through dateTimeData map
		if( DTDItr->first.GetYear() == year ) { //Check if the correct year is selected
			for( cTD_Itr TDItr = DTDItr->second.begin(); TDItr != DTDItr->second.end(); TDItr++ ) {	//Iterate through timeData map
				if( TDItr->second.GetSolarRadiation() != nullptr ) { //check if the value is a nullptr
					SR_Total[ ( DTDItr->first.GetMonthNumber() - 1 ) ] += *TDItr->second.GetSolarRadiation(); //add value to total for that month
				}
			}
		}
	}

	cout << "Solar Radiation data for each month of the year " << year << ":" << endl;

	for( i = 0; i < 12; i++ ) {
		if( SR_Total[ i ] != 0 ) {
			cout << setw( 10 ) << getMonthName( ( i+1 ) ) << ": " << ( SR_Total[ i ] / 6000 ) << " kWh/m2." << endl;
		}else{
			cout << setw( 10 ) << getMonthName( ( i+1 ) ) << ": No Data." << endl;
		}
	}
}

/**
 *	@brief	Exports the average wind speed (with standard deviation), average temperature (with standard deviation), and total solar radiation for each month in the given year to a .csv file.
 *
 *	@param	year	unsigned value representing the year
 *	@param	dateTimeData	Reference to the DTD_Map object that has all the Date, Time and WeatherDetails information.

 *	@post	The information from the given year is exported into a CSV file at the hardcoded directory.
 */
void exportDetails( unsigned year, DTD_Map & dateTimeData ) {
	unsigned i, totalCount = 0;
	float AT_Avg, AT_StdDev, WS_Avg, WS_StdDev;

	unsigned AT_Count[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned WS_Count[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	float AT_Total[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float SR_Total[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float WS_Total[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//Phase 1: Calculate the AT_Total and AT_Count values for each month
	for( cDTD_Itr DTDItr = dateTimeData.begin(); DTDItr != dateTimeData.end(); DTDItr++ ) { //Iterate through dateTimeData map
		if( DTDItr->first.GetYear() == year ) { //Check if the correct year is selected
			for( cTD_Itr TDItr = DTDItr->second.begin(); TDItr != DTDItr->second.end(); TDItr++ ) {	//Iterate through timeData map
				//Get Ambient Temp info
				if( TDItr->second.GetAmbientTemp() != nullptr ) { //check if the value is a nullptr
					AT_Total[ ( DTDItr->first.GetMonthNumber() - 1 ) ] += *TDItr->second.GetAmbientTemp(); //add value to total for that month
					AT_Count[ ( DTDItr->first.GetMonthNumber() - 1 ) ]++; //Increment count for that month
				}
				//Get Wind Speed info
				if( TDItr->second.GetWindSpeed() != nullptr ) { //check if the value is a nullptr
					WS_Total[ ( DTDItr->first.GetMonthNumber() - 1 ) ] += *TDItr->second.GetWindSpeed(); //add value to total
					WS_Count[ ( DTDItr->first.GetMonthNumber() - 1 ) ]++; //Increment count
				}
				//Get Solar Radiation info
				if( TDItr->second.GetSolarRadiation() != nullptr ) { //check if the value is a nullptr
					SR_Total[ ( DTDItr->first.GetMonthNumber() - 1 ) ] += *TDItr->second.GetSolarRadiation(); //add value to total for that month
				}
			}
		}
	}

	for( i = 0; i < 12; i++ ) {
		totalCount += ( AT_Count[ i ] + SR_Total[ i ] + WS_Count[ i ] );
	}

	ofstream ofile( "../Data/Exports/WindTempSolar.csv" );

	ofile << year << '\n';

	if( totalCount == 0 ) {
		ofile << "No Data" << '\n';
	}else{
		//Phase 2: Depending on the count for each month, calculate average and standard deviation
		for( i = 0; i < 12; i++ ) { //loop through each month's number
			if( ( AT_Count[ i ] + SR_Total[ i ] + WS_Count[ i ] ) > 0 ) {
				ofile << getMonthName( ( i+1 ) ) << ',';
				AT_StdDev = WS_StdDev = 0;
				AT_Avg = AT_Total[ i ] / AT_Count[ i ];
				WS_Avg = WS_Total[ i ] / WS_Count[ i ];
				//Get standard deviations
				for( cDTD_Itr DTDItr = dateTimeData.begin(); DTDItr != dateTimeData.end(); DTDItr++ ) { //Iterate through dateTimeData map
					if( ( DTDItr->first.GetMonthNumber() == ( i+1) ) && ( DTDItr->first.GetYear() == year ) ) { //Check if the correct year is selected
						for( cTD_Itr TDItr = DTDItr->second.begin(); TDItr != DTDItr->second.end(); TDItr++ ) {	//Iterate through timeData map
							//Get Ambient Temperature Standard Deviation for the current month.
							if( ( TDItr->second.GetAmbientTemp() != nullptr ) && ( AT_Count[ i ] != 0 ) ) {
								AT_StdDev += ( *TDItr->second.GetAmbientTemp() - AT_Avg ) * ( *TDItr->second.GetAmbientTemp() - AT_Avg );
							}
							//Get Wind Speed Standard Deviation for the current month.
							if( ( TDItr->second.GetWindSpeed() != nullptr ) && ( WS_Count[ i ] != 0 ) ) {
								WS_StdDev += ( *TDItr->second.GetWindSpeed() - WS_Avg ) * ( *TDItr->second.GetWindSpeed() - WS_Avg );
							}
						}
					}
				}

				if( WS_Count[ i ] > 0 ) {
					WS_StdDev = sqrt( ( WS_StdDev /= ( WS_Count[ i ] - 1 ) ) );
					ofile << ( WS_Avg * 3.6 ) << '(' << ( WS_StdDev * 3.6 ) << ')';
				}
				ofile << ',';

				if( AT_Count[ i ] != 0 ) {
					AT_StdDev = sqrt( ( AT_StdDev /= ( AT_Count[ i ] - 1 ) ) );
					ofile << AT_Avg << '(' << AT_StdDev << ')';
				}
				ofile << ',';

				if( SR_Total[ i ] != 0 ) {
					ofile << ( SR_Total[ i ] / 6000 );
				}
				ofile << '\n';
			}
		}
	}

	ofile.close();

	cout << "Export successful." << endl;
}

/**
 *	@brief	Validates user input to ensure only a valid unsigned value is entered into the program.
 *
 *	@param	name	string to identify the purpose of the unsigned value to the user
 *	@param	lowerBound	Unsigned value representing the lowest accepted value from the user's input.
 *	@param	upperBound	Unsigned value representing the highest accepted value from the user's input.
 *
 *	@return	A valid unsigned integer within the given bounds.
 */
unsigned getUnsigned( string name, unsigned lowerBound, unsigned upperBound ) {
	string input;
	unsigned number;
	bool isValid = false;

	while( !isValid ) {
		cout << "Enter " << name << " (between " << lowerBound << " and " << upperBound << "): " << endl;

		cin >> input;
		stringstream ss( input );
		if( ss >> number ) {
			if( ( number < lowerBound ) || ( number > upperBound ) ) {
				cout << "Error: Input is out of range. Please try again." << endl;
			}else{
				isValid = true;
			}
		}else{
			cout << "Error: Input is invalid. Please try again." << endl;
		}
		ss.clear();
	}

	return( number );
}

/**
 *	@brief	Returns the actual month name for a given unsigned value.
 *
 *	@param	monthNum	Unsigned value representing the number of the month name to extract.
 *
 *	@return	A string representing the month name for the given value.
 */
string getMonthName( unsigned monthNum ) {
	string monthNames[ 12 ] = {
		"January", 		"February",	"March", 	"April",
		"May", 			"June", 	"July", 	"August",
		"September",	"October", 	"November",	"December"
	};

	return( monthNames[ monthNum-1 ] );
}

/**
 *	@brief	Input operator overload for inputting data into a Date object.
 *
 *	@param	is	Input stream (stringstream) to collect the data from.
 *	@param	d	Date object to input the data into.
 *
 *	@return	The input stream after the Date object is finished receiving data.
 */
stringstream & operator >>( stringstream & is, Date & d ) {
	string number;
	stringstream value;
	unsigned day, month, year;

	getline( is, number, '/' );
	value << number;
	value >> day;
	value.clear();

	getline( is, number, '/' );
	value << number;
	value >> month;
	value.clear();

	getline( is, number, ' ' );
	value << number;
	value >> year;
	value.clear();

	if( !( d.SetDay( day ) ) ) {
		cout << "Error with Date input: Day: " << day << endl;
	}
	if( !( d.SetMonth( month ) ) ) {
		cout << "Error with Date input: Month: " << month << endl;
	}
	if( !( d.SetYear( year ) ) ) {
		cout << "Error with Date input: Year: " << year << endl;
	}

	return( is );
}

/**
 *	@brief	Input operator overload for inputting data into a Time object.
 *
 *	@param	is	Input stream (stringstream) to collect the data from.
 *	@param	t	Time object to input the data into.
 *
 *	@return	The input stream after the Time object is finished receiving data.
 */
stringstream & operator >>( stringstream & is, Time & t ) {
	string number;
	stringstream value;
	unsigned hour, minute;

	getline( is, number, ':' );
	value << number;
	value >> hour;
	value.clear();

	getline( is, number, ',' );
	value << number;
	value >> minute;
	value.clear();

	if( !( t.SetHour( hour ) ) ) {
		cout << "Error with Time input: Hour: " << hour << endl;
	}
	if( !( t.SetMinute( minute ) ) ) {
		cout << "Error with Time input: Minute: " << minute << endl;
	}

	return( is );
}

//	Output operator (<<) overload for a Date object.
ostream & operator <<( ostream & os, const Date & d ) {

	os	<< "Date:    "
		<< d.GetDay() << ' '
		<< d.GetMonthName() << ' '
		<< d.GetYear();

	return( os );
}

//	Output operator (<<) overload for a Time object.
ostream & operator <<( ostream & os, const Time & t ) {

	os	<< "Time:    "
		<< t.GetHour() << ':'
		<< t.GetMinute();

	return( os );
}
