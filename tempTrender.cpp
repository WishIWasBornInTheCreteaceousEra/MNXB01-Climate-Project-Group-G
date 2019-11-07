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

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate){
vector<string> test(10);
vector<int> x(10);
int m=0;
for (int j=0; j<10 ; j++)
		{
			myFile.ignore(5000, '\n');
			
		}		
		
		do
		{	
			getline(myFile, test[m], '\n');
			stringstream geek(test[m]);
			geek >> x[m];
			//cout << x[m] << endl;
			m++;
				
		}
		while( x.at(m) != 0 );	

ifstream f("smhi-openda_Karlstad_1.csv"); //opening the file for reading
if (f.fail()){
	cout<<"Could not open file.\n";
//	return(1);
}
f.ignore(256, '\n');
char fline[256];
char delim = '\n';
char ddel = '-';
double temp;
vector<double> temps;
int entries=0;
while (f.getline(fline, 256, delim)) 
{
vector<string> v = split(fline, ";");
for (unsigned int i = 0; i < v.size(); i++){
//cout << v[i] << " " << endl;
}
temp = atof(v[2].c_str()); //turns string into double
//cout << temp << endl;
vector<string> date = split(v[0], "-");
//cout << date[0] << " , " << date[1] << " , " << date[2] << endl;
int year;
int month;
int day;
istringstream(date[0]) >> year;
istringstream(date[1]) >> month;
istringstream(date[2]) >> day;
if (month == monthToCalculate && day == dayToCalculate){
	cout << " The temperature on " <<month<<"/"<<day << " was " << v[2] << " degrees" << endl; 
	temps.push_back(temp);
	entries++;
//	cout << temps[0] << endl;
	}
}
TH1I* hist = new TH1I("temperature", "Temperature;Temperature[#circC];Entries", 300, -20,40);
hist->SetFillColor(kRed +1 );

//cout << entries << endl;
for (unsigned int n = 0; n<temps.size(); n++){
	cout << temps[n] << endl;
	hist->Fill(temps[n]);
	}
	
double mean = hist->GetMean();
double stdev = hist->GetRMS();
TCanvas* can = new TCanvas();
hist->Draw();		
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

void tempTrender::delete_lines(const char *file_name, int n){
	
	ifstream is(file_name);
	ofstream ofs;
	ofs.open("temp.csv", ofstream::out);
	char c;
	int line_no=1;
	while (is.get(c)){
		if(c == '\n'){
		line_no++;}
		if (line_no > n){
		ofs << c;}
		}
//		cout << line_no << endl;
		ofs.close();
		is.close();
		remove(file_name);
		rename("temp.csv", file_name);
}

void tempTrender::tempOnDayAndre(int monthToCalculate, int dayToCalculate){
	
	ifstream file("smhi-openda_Karlstad_1.csv"); //opening the file for reading

	cout << "Hello!" <<endl; //This is just to test
	
	string helpstring; // help variable for "-" and ";" and the like
	string Temperature;
	string year;
	string hour;
	string minute;
	string second;

	while(file >> year >> helpstring >> monthToCalculate >> helpstring >> dayToCalculate >> helpstring >> hour >> helpstring >> minute >> helpstring >> second >> helpstring >> Temperature >> helpstring >> helpstring) {
		cout << "The temperature on that day in the year " << year << " at the time " << hour << " is " << Temperature;
	}

}



void main()
{
	
	int integer;
	
	ifstream myFile("smhi-openda_Karlstad.csv");

	if (!myFile.is_open())
	{
		cout << "File is open" << endl;
	}

	vector<string> year(430000);
	vector<string> month(430000);
	vector<string> day(430000);
	vector<string> time(430000);
	vector<string> temp(430000);
	vector<string> test(10);
	vector<int> x(10);
	int vectorSize= 430000;
	int counter = 0;
	int m=0;
	


	while (myFile.good())
	{

		for (int j=0; j<10 ; j++)
		{
			myFile.ignore(5000, '\n');
			
		}		
		
		do
		{	
			getline(myFile, test[m], '\n');
			stringstream geek(test[m]);
			geek >> x[m];
			//cout << x[m] << endl;
			m++;
				
		}
		while( x.at(m) != 0 );
		
		
		
		
		 	
	
		for (int i=0; i < vectorSize ; i++)
		{
	 

			getline(myFile, year[i], '-');
			getline(myFile, month[i], '-');
			getline(myFile, day[i], ';');
			getline(myFile, time[i], ';');
			getline(myFile, temp[i], ';');
			myFile.ignore(400, '\n');
		
		}
	
		
	}


	for (int i=0; i < 1; i++)
	{
		cout << "year: " << year[i] << endl;
		cout << "month: " << month[i] << endl;
		cout << "day: " << day[i] << endl;
		cout << "time: " << time[i] << endl;
		cout << "temperature: " << temp[i] << endl;
		cout << "------------------" << endl;
	}
}	
void tempTrender::Seasons(){	
	vector<string> midday;
	
	for (int i= 0;  i<430000 ; i++)
	{
		if ( time[i] == "12:00:00")
		{
			
			midday.push_back(temp[i]);
			
		}
	}
	
	std::vector<int> intNumbers;
	
	ofstream myfile;
	myfile.open ("example.txt");
	
    for (int i=0; i< midday.size(); i++)
    {
     int num = atoi(midday.at(i).c_str());
     intNumbers.push_back(num);
     
	 myfile << intNumbers[i] << endl;
	 
     //cout << intNumbers[i] << endl;
    }

int k=4000;
double x[k], y[k];
double j=0, s=0;

for (int i=0.; i<k; i++){
	x[i]=j;
	myfile>>s;
	y[i]=s;
	j++;
	}
TGraph* hist= new TGraph(k, x, y);
hist->Draw();
}

}


