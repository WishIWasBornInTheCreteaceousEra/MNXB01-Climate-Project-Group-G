#include "tempTrender.h"
#include <string>

//This is the main file
void project() {
	string pathToFile = "/home/courseuser/HOME/FINAL_PROJECT/Git_Repo/MNXB01-Climate-Project-Group-G-/smhi-openda_Karlstad_1.csv"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	
	t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);
}
