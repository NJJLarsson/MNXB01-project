#include <iostream>
#include <fstream>
#include <sstream>
#include <TGraph.h>
#include<TH1F.h>
#include<TProfile.h>
#include<TLegend.h>
#include <TCanvas.h> // canvas object
#include "tempTrender.h"

using namespace std;

//Utils
bool hasEnding (std::string const &fullString, std::string const &ending) {
  //compares two strings to check if the first string ends with the second string
  //e.g. hasEnding("binary", "nary") returns True
  //Function taken from https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
  //maybe should go in its own file and then get included here ?
	if (fullString.length() >= ending.length()) {
	    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
	} else {
	    return false;
	}
}

int date_to_number (int month, int day) {
  //takes month and date and returns the corresponding # out of 365 days in a year
  int month_sum = 0; //contribution of months to the day number
  int days_in_month [12] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
  for (int i=0; i<month; i++) {
    month_sum += days_in_month[i];
  }
  return month_sum+day;
}

double VecAvg(vector<double> v){ //Average of vector elements
  double sum = 0;
  int denom = v.size();
  for(int i=0; i < denom; i++){
    sum += v[i];
  }
  return sum/denom;
}

//Member Functions
// #0
tempTrender::tempTrender(const string& filePath) : _path{filePath}{ //filePath has now been stored in member variable _path
  cout << "The user supplied " << filePath <<" as the path to the data file.\n";
  //std::cout << "You should probably store this information in a member variable of the class! Good luck with the project! :)\n";

}
// #1
void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate) const { //Make a histogram of the temperature on this day

  //Incorrect input handling
  if (monthToCalculate>12 || dayToCalculate>31) {
    cout << "Invalid date requested. Please input a valid date with the format tempOnDay(Month, Day)" << endl;
    return;
  }

  //Convert inputed ints to strings, and combine them in "02-14" format
  string month_prefix = "";
  if (monthToCalculate < 10) { 
    month_prefix = "0";
  }
  string day_prefix = "";
  if (dayToCalculate < 10) {
    day_prefix = "0";
  }
  string dateToCalculate_string = month_prefix+to_string(monthToCalculate)+"-"+day_prefix+to_string(dayToCalculate);
  cout<<"The requested date was " << dateToCalculate_string << endl;

  //Code to open the csv files
  fstream fin; //File pointer
  fin.open(_path, ios::in); //Open file at '_path'
  if (fin.fail()) { //Check that file can be opened.
    cout << "File could not be opened. Please check that the provided path is correct." << endl;
	return;
  }

  // CREATE PROFILE HISTOGRAM that we will fill with data from specified date
	//(name, title;xlabel;ylabel, bins, xmin, xmax)
  TH1D* hDayTemp = new TH1D("one_day_tempt", "Temperature for date;Temperature [\xb0 C]; Entries", 100, -20, 40); 

  //Iterate through file, line by line, checking if the date matches with input
  vector<string> row;
  string line, cell, date_string;
  int temp;
  int i = 0;
  while (getline(fin, line)){ //read whole file, row by row, store line in variable 'line' each loop
    i++;
    row.clear();

    stringstream lineStream(line); //Slice line by ; and store each part in vector 'row'
	while (lineStream.good() && getline(lineStream, cell, ';')) {
        row.push_back(cell);
    }
	date_string = row[0]; //save the date of the line
    //If the date matches with requested date
    if (hasEnding(date_string, dateToCalculate_string)) {
      temp = stoi(row[2]);
      //cout << "line " << i << ", at date " << date_string << " the temperature was " << temp << endl;
      hDayTemp->Fill(temp);
    }

  }

  //Histogram drawing
  TCanvas* c1 = new TCanvas("c1", "1 - histogram canvas", 900, 600);
  hDayTemp->SetFillColorAlpha(kRed, 0.35);
  hDayTemp->Draw();

  //Legend
  //TODO: make legend nicer
  auto legend = new TLegend();
  legend->AddEntry(hDayTemp,("Temperature on "+dateToCalculate_string).c_str(),"f");
  legend->Draw();

  //Answering questions
  Double_t mean_val = hDayTemp->GetMean(1);
  Double_t stdev = hDayTemp->GetRMS(1);
  cout << "The mean value for date " << dateToCalculate_string << " is: " << mean_val << "C" << endl;
  cout << "The standard deviation is: " << stdev << endl;

  //TODO: Fit gaussian to histogram to calulcate probabilities?
}

// #2
void tempTrender::tempOnDay(int dateToCalculate) const { //Make a histogram of the temperature on this date

  //Incorrect input handling
  if (dateToCalculate>365) {
    cout << "Invalid date requested. Please input a valid day number between 1 and 365." << endl;
    return;
  }
  cout<<"The requested day was day number " << dateToCalculate << endl;

  //Code to open the csv files
  fstream fin; //File pointer
  fin.open(_path, ios::in); //Open file at '_path'
  if (fin.fail()) { //Check that file can be opened.
    cout << "File could not be opened. Please check that the provided path is correct." << endl;
	return;
  }

  // CREATE PROFILE HISTOGRAM that we will fill with data from specified date
	//(name, title;xlabel;ylabel, bins, xmin, xmax)
  TH1D* hDayTemp2 = new TH1D("one_day_tempt_2", "Temperature for date;Temperature [\xb0 C]; Entries", 100, -20, 40);

  //Iterate through file, line by line, checking if the date matches with input
  vector<string> row, year_month_day;
  string line, cell, date_string, date_item;
  int month, day, temp;
  int i = 0;
  while (getline(fin, line)){ //read whole file, row by row, store line in variable 'line' each loop
    i++;
    if(i>13) { //Skip header lines of the csv file. Not the cleanest but will do for now.
	
      row.clear();
      year_month_day.clear();

      stringstream lineStream(line); //Slice line by ; and store each part in vector 'row'
	  while (lineStream.good() && getline(lineStream, cell, ';')) {
          row.push_back(cell);
      }
      temp = stoi(row[2]); //save the temperature in the lane
	  date_string = row[0]; //save the date of the line
      stringstream dateStream(date_string); //split 'date_string' into year, month, day using 'getline()', save results in 'year_mont_day' vector
      while (dateStream.good() && getline(dateStream, date_item, '-')) { 
        year_month_day.push_back(date_item);
      }
      month = stoi(year_month_day[1]);
      day = stoi(year_month_day[2]);
      if (month==2 && day==29) { //Deal with leap years by skipping 02/29
        continue;
      }
      //If the date matches with requested date
      if (date_to_number(month,day)==dateToCalculate) {
        temp = stoi(row[2]);
        //cout << "line " << i << ", at date " << date_string << " the temperature was " << temp << endl;
        hDayTemp2->Fill(temp);
      }
    }
  }

  //Histogram drawing
  TCanvas* c2 = new TCanvas("c2", "2 - histogram canvas", 900, 600);
  hDayTemp2->SetFillColorAlpha(kRed, 0.35);
  hDayTemp2->Draw();

  //Legend
  //TODO: make legend nicer
  auto legend2 = new TLegend();
  legend2->AddEntry(hDayTemp2,("Temperature on day "+to_string(dateToCalculate)).c_str(), "f");
  legend2->Draw();

}

// #3
void tempTrender::tempPerDay() const { //Make a histogram of the average temperature of each day of the year

  //Code to open the csv files
  fstream fin; //File pointer
  fin.open(_path, ios::in); //Open file at '_path'
  if (fin.fail()) { //Check that file can be opened.
    cout << "File could not be opened. Please check that the provided path is correct." << endl;
	return;
  }

  // CREATE TProfile HISTOGRAM, specifying option "s" to draw standard deviation
	//(name, title;xlabel;ylabel, bins, xmin, xmax, option)
  auto* hTempPerDay = new TProfile("temp_per_day", "Temperature per day;Day of year;Temperature [\xb0 C]", 365, 1, 365, "s"); 

  //Iterate through file, line by line, checking if the date matches with input
  vector<string> row, year_month_day;
  string line, cell, date_string, date_item;
  int month, day, temp;
  while (getline(fin, line)){ //read whole file, row by row, store line in variable 'line' each loop
    row.clear();
    year_month_day.clear();
    stringstream lineStream(line); //Slice line by ; and store each part in vector 'row'
	while (lineStream.good() && getline(lineStream, cell, ';')) {
        row.push_back(cell);
    }
	date_string = row[0]; //save the date of the line
    if (any_of(date_string.begin(), date_string.end(), ::isdigit)) { //crude check to see if 'date_string' is indeed a date
      temp = stoi(row[2]);

      stringstream dateStream(date_string); //split 'date_string' into year, month, day using 'getline()', save results in 'year_mont_day' vector
      while (dateStream.good() && getline(dateStream, date_item, '-')) { 
        year_month_day.push_back(date_item);
      }
      month = stoi(year_month_day[1]);
      day = stoi(year_month_day[2]);
      if (month==2 && day==29) { //Deal with leap years by skipping 02/29
        continue;
      }
      hTempPerDay->Fill(date_to_number(month,day), temp); //Fill temp value in corresponding bin
    } 
  }
  TCanvas* c3 = new TCanvas("c3", "3 - TProfile histogram canvas", 900, 600);
  hTempPerDay->Draw();
}
// void tempTrender::hotCold() const {} //Make a histogram of the hottest and coldest day of the year
// void tempTrender::tempPerYear(int yearToExtrapolate) const {} //Make a histogram of average temperature per year, then fit and extrapolate to the given year

// #4
void tempTrender::tempMeanYearly(int yearStart, int yearEnd) const { 
  //create a line-graph showin mean-yearly temperature over time.
  
  cout<<"The requested time period was " << yearStart << "-" << yearEnd << endl;

  //Create graph to store/display our data
  auto graph1 = new TGraph();
  //Code to open the csv files
  fstream fin; //File pointer
  fin.open(_path, ios::in); //Open file at '_path'
  if (fin.fail()) { //Check that file can be opened.
    cout << "File could not be opened. Please check that the provided path is correct." << endl;
	  return;
  };
  //Iterate through file, line by line, checking if the date matches with input
  vector<string> row, rowdate;
  
  string line, cell, date_string, YearString, Last_Date;
  double tempentry; 
  double tempdailysum = 0; 
  double tempyearlysum = 0;
  int sumentries = 0;
  vector<double> tempdailyaverage, YearlyAverage;
  double  tempyearlyaverage;
  int i = 0 ;
  int k= 0;
  int Year_Last = 0;
  int Year_Count = 0;
  int YearCurrent = 0;
  bool RepeatedDate = false;

  while (getline(fin, line)){ //read whole file, row by row, store line in variable 'line' each loop
    i++;
    row.clear();

    stringstream lineStream(line); //Slice line by ; and store each part in vector 'row'
	while (lineStream.good() && getline(lineStream, cell, ';')) {
      row.push_back(cell);
    }
	if(i >= 20){ //Does this mean that the user can't select the first year of a dataset?
              // Yes. Too bad!
      date_string = row[0]; //save the date of the line
      if (Last_Date==date_string) {
        RepeatedDate = true;
      } else {
        RepeatedDate = false;
      }
      YearString = date_string.substr(0, 4);
      YearCurrent = stoi(YearString);// Save year to integer
    } else {
      continue;
    }

  
  //If the year is within the specified range
    if (YearCurrent>=yearStart && YearCurrent<= yearEnd) {
      tempentry = stoi(row[2]); //Save temp as int

      //Check wheter current date matches last
      if (RepeatedDate){ //If yes: add temp entry to the sum of the days entries, increase sum of the entries by one
        tempdailysum += tempentry ;
        sumentries++ ;
      } else { //New day we haven't seen before
        if (Last_Date.empty()) { //first loop
          tempdailysum += tempentry ;
          sumentries++ ;
        } else { //all other loops beyond the first
          tempdailyaverage.push_back((tempdailysum / sumentries)); //if not: add sum to vector containing all daily averages 
          tempdailysum = 0; //Reset tempdailysum & sumentries
          sumentries = 0;

          //Start calculation for new date
          tempdailysum += tempentry;
          sumentries++;

          if(Year_Last == 0 || Year_Last!=YearCurrent){ //If year has changed, sum up all daily entries and average them out.
            Year_Count++; //keep count of years we've seen
            //cout << Year_Last << YearCurrent << "Happy New Year" << endl;
            tempyearlyaverage = VecAvg(tempdailyaverage);
            tempdailyaverage.clear();
            YearlyAverage.push_back(tempyearlyaverage);
            graph1->SetPoint(k,YearCurrent, tempyearlyaverage);
            k++ ;
          }
        }
      }
    
    } else { //if year not in the desired range
      continue;
    }
    //update a copy of the date to check against in the next iteration
    Last_Date = date_string;
    Year_Last = YearCurrent;

  }

  cout << "The average temperatures of " << YearlyAverage.size() << " years were calculated" << endl;
  TCanvas* c5 = new TCanvas("c5", "5- Yearly average temperature", 900, 600);
	c5->DrawFrame(yearStart-2,5,yearEnd+2,11.5);
	gPad->SetGrid(1, 1);
  graph1->Draw();
}
