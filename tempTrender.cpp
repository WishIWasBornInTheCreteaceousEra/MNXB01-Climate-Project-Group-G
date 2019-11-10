//This is the implementation file
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TGraph.h> //Graphing Classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <THStack.h>
#include <TLegend.h>
#include "tempTrender.h"

using namespace std;


tempTrender::tempTrender(string filePath){
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	
	//Creating File Name to use in saving of figures.
	int pos1 = filePath.find("/"); 
	string fileName = filePath.substr(pos1 + 1);
	int pos2 = fileName.find(".");
	fileName = fileName.substr(0,  pos2);
	FileName=fileName;
	//Creating Data Set.
	ifstream f(filePath.c_str());
	if (f.fail()){
		cerr<<"Could not open file.\n";
	}
	Reader(f, DYear, DMonth, DDay, DHour, DTemp);
	f.close();
}


void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate){
	//Histogram that will contain the data from the csv files.
	TH1D* hist = new TH1D("Histogram","Temperature On a Day Throughout the Years; Temperature[#circC]; Entries", 300, -20,40);
	
	//Pruning the Data
	for (size_t i= 0;  i<DMonth.size() ; i++){
		if (DMonth.at(i) == monthToCalculate && DDay.at(i) == dayToCalculate){
					hist->Fill(DTemp.at(i)); 
					i++;
			}
		}

	TCanvas* a1 = new TCanvas("a1", "Temperature on a Given Day Throughout the Years", 900, 600);
	//double mean = hist->GetMean();
	//double stdev = hist->GetRMS();
	
	//Set color and the minimum at 0
	hist->SetFillColor(kBlue);
	hist->SetMinimum(0);
	//Fit it with a Gaussian
	hist->Fit("gaus");
	
	//Show Mean of fot and data (and other stuff)
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);

	//Draw it and save it
	hist->Draw();	
	string fileName=FileName;
	fileName.append("_TempOnDay.jpg");
	a1->SaveAs(fileName.c_str());	
}

void tempTrender::tempPerDay(double Year, double Hour){
	TH1D* hist = new TH1D("Histogram","Temperature Throughout a Year; Day of the year; Temperature[#circC]", 357, 0, 356);	
	int bin=0;
	for (size_t i= 0;  i<DHour.size() ; i++){
		if ( DYear.at(i) == Year && DHour.at(i) == Hour){
			hist->SetBinContent(bin, DTemp.at(i));
			hist->SetBinError(bin, sqrt(abs(DTemp.at(i))));
			bin++;
		}
	}	
	TCanvas* b1 = new TCanvas("b1", "Temperature Throughout one year", 900, 600);
	//Set color
	hist->SetFillColor(kBlue);
	// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);
	//Draw it and save it
	hist->Draw();	
	string fileName=FileName;
	fileName.append("_TempPerDay.jpg");
	b1->SaveAs(fileName.c_str());
	
}

void tempTrender::hotCold(double Hour){
	//Plotting Histograms
	TCanvas* c1 = new TCanvas("c1", "Hottest and Coldest Days", 900, 600);
	TH1D* Hot = new TH1D("Hot","Hottest Temperature in a Year; Day of the year; Temperature[#circC]", 357, 0, 356);	
	TH1D* Cold = new TH1D("Cold","Coldest Temperature in a Year; Day of the year; Temperature[#circC]", 357, 0, 356);
	// Finding the Hottest and Coldest Days at a Given Hour
    size_t Year = DYear.at(0); //Year we start from
    size_t LastYear =DYear.at(DYear.size()-1);
    int Day=0;
	for (Year;  Year<=LastYear ; Year++){
		vector <double> Yrs;
		for (size_t k=0; k<DTemp.size(); k++){
			if (DYear.at(k) == Year && DHour.at(k) == Hour){
			Yrs.push_back(DTemp.at(k));
			Day++;
			}
		}
		Cold->Fill(min_element(Yrs.begin(), Yrs.end())- Yrs.begin());
		Hot->Fill(max_element(Yrs.begin(), Yrs.end())- Yrs.begin());
	}
	
	TF1* func = new TF1("Gaussian", Gaussian, 1, 366, 3);
	func->SetParameters(5, 200, 50); //Starting values for fitting
	
	Cold->SetFillColor(kBlue);
	Hot->SetFillColor(kRed);
	
	Hot->Fit(func, "Q0R");
	cout << "The mean is " << func->GetParameter(1) << endl;
	cout << "Its uncertainty is " << func->GetParError(1) << endl;
	TLegend *leg = new TLegend(0.65, 0.75, 0.92, 0.92, "", "NDC");
	leg->SetFillStyle(0); //Hollow fill (transparent)
	leg->SetBorderSize(0); //Get rid of the border
	leg->AddEntry(Hot, "", "F"); //Use object title, draw fill
	leg->AddEntry(Cold, "A title", "F"); //Use custom title
	Hot->Draw();
	Cold->Draw("SAME"); //Draw on top of the existing plot
	leg->Draw(); //Legends are automatically drawn with "SAME"
	
	string fileName=FileName;
	fileName.append("_HottestandColdestDays.jpg");
	c1->SaveAs(fileName.c_str());
	
}

void tempTrender::Seasons(double Hour){
	//Seasons
	TCanvas* d1 = new TCanvas("d1","Temperature fluctuations over time.");
	vector<double> t, TatHr;//time and Temp. at Hour
	double days;
	for (size_t i= 0;  i<DHour.size() ; i++){
		if ( DHour.at(i) == Hour){
			t.push_back(days);
			TatHr.push_back(DTemp.at(i));
			days++;	
		}
	}
 
	TGraph* Graph= new TGraph(days, &t[0], &TatHr[0]);
	Graph->SetTitle("Temperature over Time; Time (Days);Temperature[#circC]");
	Graph->Draw();	
	string fileName=FileName;
	fileName.append("_Seasons.jpg");
	d1->SaveAs(fileName.c_str());
}


void tempTrender::Reader(ifstream &file, vector<double> &v1, vector<double> &v2, vector<double> &v3, vector<double> &v4, vector<double> &v5){
	string s, date="-", semi=";";
	int start=0, i=0;

	while (getline(file, s, '\n')){
		if (start>0){
			split(v1, s, date);
			split(v2, s, date);
			split(v3, s, semi);
			split(v4, s, semi);
			split(v5, s, semi);
		}
		
		if (s.find("Datum") != string::npos){ //This statement can be used to find locations where the variable in the find() field, useful for time.
			start++;
		}
	}
}

			
void tempTrender::split(vector<double> &vect, string &s, string &delimiter){
		size_t start=0, end, dlen = delimiter.length();
		double var;
		string token;
		if ((end = s.find(delimiter, start )) != string::npos){
			token = s.substr(start, end - start);
			stringstream SD(token);
			SD>>var;
			start = end + dlen;
			vect.push_back(var);
			s = s.substr(start);
		}
}
double tempTrender::Gaussian(double *x, double *par){
	return par[0]*exp(-0.5*(x[0]*x[0]-2*x[0]*par[1]+par[1]*par[1])/(par[2]*par[2]));
}

