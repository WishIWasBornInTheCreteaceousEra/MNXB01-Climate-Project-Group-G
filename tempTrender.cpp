//This is the implementation file
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <TF1.h> 
#include <TF2.h> 
#include <TH1.h> 
#include <TH2.h>
#include <TH3F.h>
#include <TRandom.h>
#include <TPolyLine3D.h>
#include <TMath.h>   
#include <TPaveStats.h>
#include <TCanvas.h> 
#include <TGraph.h> 
#include <TStyle.h>  
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
	//Creating Data Set that can be globally accessed.
	ifstream f(filePath.c_str());
	if (f.fail()){
		cerr<<"Could not open file.\n";
	}
	Reader(f, DYear, DMonth, DDay, DHour, DTemp);
	f.close();
}

//This function returns a histogram containing the temperature distribution of this Date throughout the years.
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
	
	//Show Statistics and Values of fit and data 
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);

	//Draw and save it
	hist->Draw();	
	string fileName=FileName;
	fileName.append("_TempOnDay.jpg");
	a1->SaveAs(fileName.c_str());	
}
//This Function returns a histogram of the temperature per day in a chosen year.
void tempTrender::tempPerDay(double Year, double Hour){
	TH1D* hist = new TH1D("Temperature Per Day","Temperature Throughout a Year; Day of the year; Temperature[#circC]", 357, 0, 356);	
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
//This function returns a histogram containing the dates which were the hottest and coldest days in a given Data Set in red and blue, respectively.
void tempTrender::hotCold(double Hour){
	//Plotting Histograms
	TCanvas* c1 = new TCanvas("c1", "Hottest and Coldest Days", 900, 600);
	TH1D* Hot = new TH1D("Hot","Hottest Date of a Year; Day of the year; Temperature[#circC]", 357, 0, 356);	
	TH1D* Cold = new TH1D("Cold","Coldest Date of a Year; Day of the year; Temperature[#circC]", 357, 0, 356);
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
	
	//TF1* func = new TF1("Gaussian", Gaussian, 1, 366, 3);
	//func->SetParameters(5, 200, 50); //Starting values for fitting
	
	Cold->SetFillColor(kBlue);
	Hot->SetFillColor(kRed);
	
	//Hot->Fit(func, "Q0R");
	//cout << "The mean is " << func->GetParameter(1) << endl;
	//cout << "Its uncertainty is " << func->GetParError(1) << endl;
	TLegend *leg = new TLegend(0.65, 0.75, 0.92, 0.92, "", "NDC");
	leg->SetFillStyle(0); //Hollow fill (transparent)
	leg->SetBorderSize(0); //Get rid of the border
	leg->AddEntry(Hot, "", "F"); //Use object title, draw fill
	leg->AddEntry(Cold, "Coldest Date of a Year", "F"); //Use custom title
	Hot->Draw();
	Cold->Draw("SAME"); //Draw on top of the existing plot
	leg->Draw(); //Legends are automatically drawn with "SAME"
	
	string fileName=FileName;
	fileName.append("_HottestandColdestDays.jpg");
	c1->SaveAs(fileName.c_str());
	
}
//This function returns the total temperature data for the data set along with a linear fit, in order to deduce whether or not the city is heating up over time.
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
	Graph->Fit("pol1", "Q");
	Graph->Draw();	
	TF1 *fit = Graph->GetFunction("pol1");
	cout<<"The slope of the Temperature over time is "<<fit->GetParameter(0)<<endl;
	string fileName=FileName;
	fileName.append("_Seasons.jpg");
	d1->SaveAs(fileName.c_str());
}
//Make a graph of the temperature distribution over months in a year
void tempTrender::tempDistYearGraph(double Year, double Hour){
	//Matrix Generation	
	vector< vector<double> > Data;
	for (double Month=1;  Month<=12 ; Month++){
		vector <double> Mnths;
		for (size_t k=0; k<DTemp.size(); k++){
			if (DYear.at(k) == Year && DMonth.at(k) == Month && DHour.at(k) == Hour){
			Mnths.push_back(DTemp.at(k));
			}
		}	
		Data.push_back(Mnths);
		}

   
   TCanvas *e1=new TCanvas("e1","Graph of Temperature Distribution of Months in a Given Year",800,600);
   gStyle->SetOptStat(0);
   TH3F* h3 = new TH3F("tido", "", 10, 1, 12, 10, 0, 31, 10, -10, 25);
   h3->GetXaxis()->SetTitle("Month");
   h3->GetXaxis()->SetTitleOffset(2.0); h3->GetXaxis()->CenterTitle(true);
   h3->GetYaxis()->SetTitle("Day");
   h3->GetYaxis()->SetTitleOffset(2.0); h3->GetYaxis()->CenterTitle(true);
   h3->GetZaxis()->SetTitle("Temperature");
   h3->GetZaxis()->SetTitleOffset(1.0); h3->GetZaxis()->CenterTitle(true);
   h3->Draw();    
   

   TPolyLine3D *l1 = new TPolyLine3D(1);    
   TPolyLine3D *l2 = new TPolyLine3D(2);
   TPolyLine3D *l3 = new TPolyLine3D(3);
   TPolyLine3D *l4 = new TPolyLine3D(4);
   TPolyLine3D *l5 = new TPolyLine3D(5);
   TPolyLine3D *l6 = new TPolyLine3D(6);
   TPolyLine3D *l7 = new TPolyLine3D(7);
   TPolyLine3D *l8 = new TPolyLine3D(8);
   TPolyLine3D *l9 = new TPolyLine3D(9);
   TPolyLine3D *l10 = new TPolyLine3D(10);
   TPolyLine3D *l11 = new TPolyLine3D(11);
   TPolyLine3D *l12 = new TPolyLine3D(12);
   
   for (int N=0; N< 28; N++)
	{	
		l1->SetPoint(N,1,N,(Data.at(0)).at(N));
		l2->SetPoint(N,2,N,(Data.at(1)).at(N));
		l3->SetPoint(N,3,N,(Data.at(2)).at(N));
		l4->SetPoint(N,4,N,(Data.at(3)).at(N));
		l5->SetPoint(N,5,N,(Data.at(4)).at(N));
		l6->SetPoint(N,6,N,(Data.at(5)).at(N));
		l7->SetPoint(N,7,N,(Data.at(6)).at(N));
		l8->SetPoint(N,8,N,(Data.at(7)).at(N));
		l9->SetPoint(N,9,N,(Data.at(8)).at(N));
		l10->SetPoint(N,10,N,(Data.at(9)).at(N));
		l11->SetPoint(N,11,N,(Data.at(10)).at(N));
		l12->SetPoint(N,12,N,(Data.at(11)).at(N));
	}
   
   
   l1->SetLineColorAlpha(kRed, 1.35); l1->SetLineWidth(3);
   l2->SetLineColor(kRed+1); l2->SetLineWidth(3);
   l3->SetLineColor(kBlue); l3->SetLineWidth(3);
   l4->SetLineColor(kBlue+2); l4->SetLineWidth(3);
   l5->SetLineColor(kOrange);l5->SetLineWidth(3);
   l6->SetLineColor(kOrange+1);l6->SetLineWidth(3);
   l7->SetLineColor(kPink);l7->SetLineWidth(3);
   l8->SetLineColor(kPink+1);l8->SetLineWidth(3);
   l9->SetLineColor(kGreen);l9->SetLineWidth(3);
   l10->SetLineColor(kGreen+1);l10->SetLineWidth(3);
   l11->SetLineColor(kYellow+1);l11->SetLineWidth(3);
   l12->SetLineColor(kYellow+3);l12->SetLineWidth(3);
   
   l1->Draw(); 
   l2->Draw();
   l3->Draw();
   l4->Draw(); 
   l5->Draw(); 
   l6->Draw();
   l7->Draw();
   l8->Draw();  
   l9->Draw(); 
   l10->Draw();
   l11->Draw();
   l12->Draw();
   
         

  
   e1->Update();


}
//Make a histogram of the temperature distribution over months in a year
void tempTrender::tempDistYearHist(double Year, double Hour){
	
	//Matrix Generation	
	vector< vector<double> > Data;
	for (double Month=1;  Month<=12 ; Month++){
		vector <double> Mnths;
		for (size_t k=0; k<DTemp.size(); k++){
			if (DYear.at(k) == Year && DMonth.at(k) == Month && DHour.at(k) == Hour){
			Mnths.push_back(DTemp.at(k));
			}
		}	
		Data.push_back(Mnths);
		}
   TCanvas *f1=new TCanvas("f1","Histogram of Temperature Distribution of Months in a Given Year",800,600);
   THStack *a = new THStack("a","");  
   TH2F *h2sta = new TH2F("h2sta","h2sta",24,1,13, 24,-11,20);
   h2sta->SetFillColor(38);
  
  
   int maxt = 30;
   
   TH2F *V1 = new TH2F("V1","V1",24,1,13, 24,-11,maxt);
   TH2F *V2 = new TH2F("V2","V2",24,1,13, 24,-11,maxt);
   TH2F *V3 = new TH2F("V3","V3",24,1,13, 24,-11,maxt);
   TH2F *V4 = new TH2F("V4","V4",24,1,13, 24,-11,maxt);
   TH2F *V5 = new TH2F("V5","V5",24,1,13, 24,-11,maxt);
   TH2F *V6 = new TH2F("V6","V6",24,1,13, 24,-11,maxt);
   TH2F *V7 = new TH2F("V7","V7",24,1,13, 24,-11,maxt);
   TH2F *V8 = new TH2F("V8","V8",24,1,13, 24,-11,maxt);
   TH2F *V9 = new TH2F("V9","V9",24,1,13, 24,-11,maxt);
   TH2F *V10 = new TH2F("V10","V10",24,1,13, 24,-11,maxt);
   TH2F *V11 = new TH2F("V11","V11",24,1,13, 24,-11,maxt);
   TH2F *V12 = new TH2F("V12","V12",24,1,13, 24,-11,maxt);
   
   
   V1->SetFillColor(kRed+2);
   V2->SetFillColor(kRed);
   V3->SetFillColor(kMagenta+2);
   V4->SetFillColor(kMagenta);
   V5->SetFillColor(kBlue+2);
   V6->SetFillColor(kBlue);
   V7->SetFillColor(kCyan+2);
   V8->SetFillColor(kCyan);
   V9->SetFillColor(kGreen+2);
   V10->SetFillColor(kGreen);
   V11->SetFillColor(kYellow+1);
   V12->SetFillColor(kYellow);
   
   for (int i=0; i< 28; i++)
   {
	   V1->Fill(1,(Data.at(0)).at(i));  
	   V2->Fill(2,(Data.at(1)).at(i));
	   V3->Fill(3,(Data.at(2)).at(i));
	   V4->Fill(4,(Data.at(3)).at(i));
	   V5->Fill(5,(Data.at(4)).at(i));
	   V6->Fill(6,(Data.at(5)).at(i));
	   V7->Fill(7,(Data.at(6)).at(i));
	   V8->Fill(8,(Data.at(7)).at(i));
	   V9->Fill(9,(Data.at(8)).at(i));
	   V10->Fill(10,(Data.at(9)).at(i));
	   V11->Fill(11,(Data.at(10)).at(i));
	   V12->Fill(12,(Data.at(11)).at(i));
   }
   
   a->Add(h2sta);
   a->Add(V1);
   a->Add(V2);
   a->Add(V3);
   a->Add(V4);
   a->Add(V5);
   a->Add(V6);
   a->Add(V7);
   a->Add(V8);
   a->Add(V9);
   a->Add(V10);
   a->Add(V11);
   a->Add(V12);
   a->Draw();
   a->GetXaxis()->SetTitle("Month");
   a->GetXaxis()->SetTitleOffset(2.0); a->GetXaxis()->CenterTitle(true);
   a->GetYaxis()->SetTitle("Temperature");
   a->GetYaxis()->SetTitleOffset(2.0); a->GetYaxis()->CenterTitle(true);
   
   f1->Update();
   
}

//Reads all the data in an smhi file.
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

//Splits the data into their relevant vectors.
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
//Obselete Function as cannot be passed in ROOT 5.
double tempTrender::Gaussian(double *x, double *par){
	return par[0]*exp(-0.5*(x[0]*x[0]-2*x[0]*par[1]+par[1]*par[1])/(par[2]*par[2]));
}
