#include "../include/measurement.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Measurement::Measurement(std::string date, double measurement)
    : date(date), measurement(measurement) {}

Measurement measurementFromLine(std::string line) {
  std::stringstream ss(line);
  std::vector<std::string> row;
  std::string cell;

  while (ss.good() && std::getline(ss, cell, ';')) {
    // Initialize and add <colname, int vector> pairs to result
    row.push_back(cell);
  }

  return Measurement(row[0], std::stod(row[2]));
}

void run() {
  std::ifstream file(
      "/Users/enniomara/Downloads/MNXB01-project "
      "2/datasets/smhi-opendata_1_105370_20210926_100841_Falun.csv");

  std::string line;
  // Read until we encouter "Datum;", which means that the next lines will be
  // the actual data
  while (getline(file, line)) {
    if (line.rfind("Datum;", 0) == 0) {
      break;
    }
  }

  std::vector<Measurement> measurements;
  while (getline(file, line)) {
    measurements.push_back(measurementFromLine(line));
  }

  std::cout << measurements.size() << std::endl;
}
