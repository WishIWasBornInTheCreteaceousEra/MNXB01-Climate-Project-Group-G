#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <vector>
//This is the file that will contain the list of data and function members
class tempTrender {
	//Global Variables

	std::string FileName;
	
	std::vector<double> DYear;
	std::vector<double> DMonth;
	std::vector<double> DDay;
	std::vector<double> DHour;
	std::vector<double> DTemp;

	public:
	tempTrender(std::string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	
	//Main Functions
	void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	void Seasons(double Hour); //Make Graph of Temperature on a given hour every day.
	void tempPerDay(double Year, double Hour);
	void hotCold(double Hour); //Make a histogram of the hottest and coldest day of the year
	void tempDistYearHist(double Year, double Hour);//Make a histogram of the temperature distribution over months in a year
	void tempDistYearGraph(double Year, double Hour);//Make a graph of the temperature distribution over months in a year
	
	
	//Auxiliary Functions
	void Reader(ifstream &file, std::vector<double> &v1, std::vector<double> &v2, std::vector<double> &v3, std::vector<double> &v4, std::vector<double> &v5);
	void split(std::vector<double> &vect, std::string &s, std::string &delimiter);
	double Gaussian(double* x, double* par);
	
	private:
	//Private Variables

	int monthToCalculate;
	int dayToCalculate;
	double Hour;
	double Year;
	double OverWriteDouble;
	 
	
	std::vector<double> vect;
	
	std::string filePath;
	std::string s;
	std::string delimiter;

};

#endif
