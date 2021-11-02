#include "../include/measurement.h"
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

    while(ss.good() && std::getline(ss, cell, ';')){
        // Initialize and add <colname, int vector> pairs to result
        row.push_back(cell);
    }

    return Measurement(row[0], std::stod(row[2]));
}
