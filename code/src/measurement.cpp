#include "../include/measurement.h"
#include <iostream>
#include <string>

Measurement::Measurement(std::string date, double measurement)
    : date(date), measurement(measurement) {}
