#include <iostream>
#include<fstream>
#include <sstream>
#include<TH1F.h> 
#include "tempTrender.h"

using namespace std;

tempTrender::tempTrender(const string& filePath) : _path{filePath}{ //filePath has now been stored in member variable _path
  cout << "The user supplied " << filePath <<" as the path to the data file.\n";
  //std::cout << "You should probably store this information in a member variable of the class! Good luck with the project! :)\n";

}

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const { //Make a histogram of the temperature on this day

  cout<<"I am stil working!" << endl;
  //Code to open the csv files
  fstream fin; //File pointer
  fin.open(_path, ios::in); //Open file at '_path'
  if (fin.fail()) { //Check that file can be opened.
    cout << "File could not be opened. Please check that the provided path is correct." << endl;
	return;
  }

  vector<string> row;
  string line, cell;
  string delimiter=";";
  
  int i = 0;
  int j = 0;
  while (getline(fin, line)){ //read whole file, row by row, store line in variable 'line' each loop
    i++;
    row.clear();

    stringstream lineStream(line);
	while (lineStream.good() && getline(lineStream, cell, ';')) {
		j++;
        row.push_back(cell);
    }

	if(i%10000==0){
	  cout << "line " << i << ", at date " << row[0] << " the temperature was " << row[2] << endl;
    }
    j=0;
  }


  // CREATE HISTOGRAM that we will fill with data from specified date
	//(name, title;xlabel;ylabel, bins, xmin, xmax)
  //TH1D* hDayTemp = new TH1D("one_day_tempt", ";Temperature [C]; Entries", 100, -20, 40); 

  //hDayTemp->Draw();
}
// void tempTrender::tempOnDay(int dateToCalculate) const {} //Make a histogram of the temperature on this date
// void tempTrender::tempPerDay() const {} //Make a histogram of the average temperature of each day of the year
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year
