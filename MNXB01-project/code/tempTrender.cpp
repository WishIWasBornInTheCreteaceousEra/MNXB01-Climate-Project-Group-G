#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include "tempTrender.h"

using namespace std;

//This is the implementation file



tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
}

//What does this function do?
void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate){
	//Create Vectors to contain all data.
	vector<double> year, month, day, time, temp;
	//Indexing value for the constructed vectors.
	int i=0, junk=0;
	//Creating a value which will continually be overwritten by the string value
	double OverWriteDouble=0.0;
	ifstream f("datasets/smhi-openda_Karlstad.csv"); //opening the file for reading //change to filepath
	if (f.fail()){
		cerr<<"Could not open file.\n";
	}
	//Histogram
	TH1D* hist = new TH1D("Histogram","Temperature On a Day Throughout the Years; Temperature[#circC]; Entries", 300, -20,40);
	
	//Pruning Initial Entries.
	for (int j=0; j<10 ; j++){
		f.ignore(5000, '\n');
	}		

	while (getline(f, s, '\n')){
		if (junk == 0 ){
			StoI(junk, s);
			 }
		else{
			//Sorting the relevant data into vectors
			getline(f, s, '-');
				VectorConstructor(year, s);	
			getline(f, s, '-');
				VectorConstructor(month, s);	
			getline(f, s, ';');
				VectorConstructor(day, s);	
			getline(f, s, ';');
				VectorConstructor(time, s);
			getline(f, s, ';');
				VectorConstructor(temp, s);
			f.ignore(400, '\n');
			//If the data 
			if (month.at(i) == monthToCalculate && day.at(i) == dayToCalculate){
				hist->Fill(temp.at(i)); //Going to become redundant as we make a function to take a vector and fill a histogram.
		}
		i++;
		}
	}
	cout<<i<<endl;
	f.close();
	TCanvas* c1 = new TCanvas("c1", "Temperature on a Given Day Throughout the Years", 900, 600);
	//double mean = hist->GetMean();
	//double stdev = hist->GetRMS();
	
	//Set color and the minimum at 0
	hist->SetFillColor(kBlue);
	hist->SetMinimum(0);
	//Fit it with a Gaussian
	hist->Fit("gaus");

	//Draw it and save it
	hist->Draw();	
	c1->SaveAs("TempOnDay.jpg");	
}

vector<std::string> tempTrender::split(string s, string delimiter){
		size_t start=0, end, dlen = delimiter.length();
		string token;
		vector<string> res;
		while ((end = s.find(delimiter, start)) != string::npos){
			token = s.substr(start, end - start);
			start = end + dlen;
			res.push_back(token);
		}
		res.push_back(s.substr(start));
		return res;
}


void tempTrender::VectorConstructor(vector<double> &vect, string &s){
			double OverWriteDouble=0.0;
			stringstream VtoD(s);
			VtoD>>OverWriteDouble;
			vect.push_back(OverWriteDouble);
}

void tempTrender::StoI(int &var, string &s){
			stringstream SD(s);
			SD>>var;
}


