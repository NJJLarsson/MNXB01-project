#include "tempTrender.h"
#include <string>

void project() {
	const std::string pathToFile = "/home/je2487la/FinalProject/MNXB01-project/datasets/smhi-opendata_1_52230_20210926_100815_Falsterbo.csvS"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	
	t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	t.tempPerDay();
	t.tempMeanYearly(1967, 2017);
	//t.hotCold();
	//t.tempPerYear(2050);
}
