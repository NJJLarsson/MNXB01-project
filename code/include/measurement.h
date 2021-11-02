#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>
class Measurement {
public:
  Measurement(std::string date, double measurement);

  const std::string date;
  const double measurement;
};

// takes a comma delimetered line from the dataset, and builds a measurement object
Measurement measurementFromLine(std::string line);

#endif
