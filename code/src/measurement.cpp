#include "../include/measurement.h"
#include <fstream>
#include <iostream>
#include <map>
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

std::vector<std::string> Measurement::parse_date() const {
  // why c++ wouln't have date parsing in the std is beyond be
  std::stringstream date(Measurement::date);
  std::string date_item;
  std::vector<std::string> parsed_date_items;
  while (date.good() && getline(date, date_item, '-')) {
    parsed_date_items.push_back(date_item);
  }

  return parsed_date_items;
}
Month Measurement::measurement_month() const {
  auto parsed_date_items = Measurement::parse_date();

  return (Month)std::stoi(parsed_date_items[1]);
}
int Measurement::measurement_year() const {
  auto parsed_date_items = Measurement::parse_date();

  return std::stoi(parsed_date_items[0]);
}

void run(int month_int) {
  Month month = (Month)month_int;
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
    Measurement measurement = measurementFromLine(line);
    if (measurement.measurement_month() == month) {
      measurements.push_back(measurementFromLine(line));
    }
  }

  // bucket measurements per year
  std::map<int, std::vector<Measurement>> measurements_per_year;
  for (Measurement m : measurements) {
      measurements_per_year[m.measurement_year()].push_back(m);
  }

  std::cout << measurements.size() << std::endl;
  std::cout << measurements[0].measurement_month() << std::endl;
  std::cout << measurements_per_year.size() << std::endl;
}
