#include "tempTrender.h"
#include <string>

//This is the main file
void project() {
	string pathToFile = "/home/courseuser/Documents/MNXB01-project/MNXB01-Climate-Project-Group-G-Draft"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	
	t.tempOnDay(8, 23); //Call some functions that you've implemented
	t.tempOnDayAndre(8, 23);
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);
	
	//t.Seasons();
}
