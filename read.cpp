#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <stdlib.h>

using namespace std;

int main()
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


	for (int i=0; i < 0; i++)
	{
		cout << "year: " << year[i] << endl;
		cout << "month: " << month[i] << endl;
		cout << "day: " << day[i] << endl;
		cout << "time: " << time[i] << endl;
		cout << "temperature: " << temp[i] << endl;
		cout << "------------------" << endl;
	}
	
	
	
	int RR = 430000;
	int CC = 12;




	vector<vector<int> > matrix(RR);
	for ( int i = 0 ; i < RR ; i++ )
	{
		matrix[i].resize(CC);
	}	
	
	
	
	
	std::vector<int> intmonth;
	
	for (int i=0; i< month.size(); i++)
    {
     int num = atoi(month.at(i).c_str());
     intmonth.push_back(num);
	}
	
	
	std::vector<int> inttemp;
	
	for (int i=0; i< temp.size(); i++)
    {
     int num = atoi(temp.at(i).c_str());
     inttemp.push_back(num);
	}
	
	
	vector<string> midday;
	
	
	//~ for ( int i= 0; i< 5 ; i++)
	//~ {
		//~ cout<< inttemp.at(i) << endl;
	//~ }
	
	
	int var= 1;
	
	
		
	for (int i= 1;  i<13 ; i++)
	{
		
		for (int j = 0; j< 1465 ; j++)
		{
			if ( year[j] == "1951"){
				
			if ( intmonth[j] == i)
			{
				
				if ( time[j] == "12:00:00")
				{
					//cout << inttemp[i] << endl;
					matrix[j][i] = inttemp[j] ;
					
					cout << matrix[j][i] << " | ";
					//cout << inttemp[i] << endl;
			
				}
				
			}
			
			
			
}

}

cout << endl;
}

//~ for(int x=0;x<12;x++)  // loop 3 times for three lines
    //~ {
        //~ for(int y=0;y<7;y++)  // loop for the three elements on the line
        //~ {
            //~ cout<<matrix[x][y];  // display the current element out of the array
        //~ }
    //~ cout<<endl;  // when the inner loop is done, go to a new line
    //~ }
	
}
	
	
	
	
	//~ std::vector<int> intNumbers;
	
	//~ ofstream myfile;
	//~ myfile.open ("example.txt");
	
    //~ for (int i=0; i< midday.size(); i++)
    //~ {
     //~ int num = atoi(midday.at(i).c_str());
     //~ intNumbers.push_back(num);
     
	 //~ myfile << intNumbers[i] << endl;
	 
     //~ //cout << intNumbers[i] << endl;
    //~ }
	



