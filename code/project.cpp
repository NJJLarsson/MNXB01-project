#include "tempTrender.h"
#include <string>
#include "measurement.h"

void project() {
	const std::string pathToFile = "/home/antton/MNXB01-project/datasets/smhi-opendata_1_52230_20210926_100815_Falsterbo.csv"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	
	t.tempOnDay(8, 23); //Call some functions that you've implemented
	t.tempOnDay(235);
	t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);
  t.tempMeanYearly(1967, 2017);
	run(pathToFile, 11); 	// Analyze each year on november
}
