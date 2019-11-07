#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <vector>
//This is the file that will contain the list of data and function members
class tempTrender {
	public:
	tempTrender(string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	
	//Main Functions
	void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	
	
	
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	//void tempPerDay(); //Make a histogram of the average temperature of each day of the year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year
	
	
	//Auxiliary Functions
	void VectorConstructor(vector<double> &vect, string &s);
	void StoI(int &var, string &s);
	vector<string> split(string s, string delimiter);
	
	private:
	int monthToCalculate;
	int dayToCalculate;
	double OverWriteDouble;
	vector<double> vect;
	string s;//This needs to be more descriptive
	string delimiter;
};

#endif
