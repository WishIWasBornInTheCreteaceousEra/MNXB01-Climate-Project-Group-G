#include "tempTrender.h"
#include <string>

//This is the main file
void project() {
	string pathToFile = "datasets/smhi-openda_Karlstad.csv"; //This Class can read any smhi file provided in the datasets.
	tempTrender t(pathToFile);
	
	
	t.Seasons(12.);//This function returns the total temperature data for the data set along with a linear fit, in order to deduce whether or not the city is heating up over time.
	t.hotCold(12.);//This function returns a histogram containing the dates which were the hottest and coldest days in a given Data Set in red and blue, respectively.
	t.tempOnDay(8, 23); //This function returns a histogram containing the temperature distribution of this Date throughout the years.
	t.tempPerDay(2004., 12.);//This Function returns a histogram of the temperature per day in a chosen year.
	t.tempDistYearHist(2004., 12.);//Make a Histogram of the temperature distribution over months in a year
	t.tempDistYearGraph(2004, 12.);//Make a graph of the temperature distribution over months in a year
	

}
